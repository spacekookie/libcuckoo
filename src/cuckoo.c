/*
 * This file is part of libcuckoo
 * It is free software under the LGPL 3.0
 *
 * @author Katharina "spacekookie" Sabel
 */

/* Public API header */
#include <cuckoo.h>

/* Stdlib requirements */
#include <memory.h>
#include <malloc.h>

/* Internal hashing submodule */
#include "hashing.h"


typedef struct cc_map_item {
    const char      *key;           // Index key
    void            *value;         // User data
    unsigned short  table;          // Table location
    unsigned short  prev;           // Previous table location
    unsigned int    qu_idx;         // Insert queue location
} cc_map_item;


typedef struct cuckoo_map {
    size_t          size;           // Table max size (upper bound)
    size_t          *used;          // Occupancy of each table
    unsigned short  num_tables;     // Number of tables
    cc_map_item ***tables;          // Actual data storage
} cuckoo_map;


/** Utility funtion - move to utils.h ? */
unsigned int check_flagmask(int32_t flags, int32_t mask);


int cuckoo_init(cuckoo_map **map, size_t init_size, uint32_t flags)
{
    struct cuckoo_map *m;
    int ret = CUCKOO_SUCCESS;
    int i;

    /* Refuse to alloc invalid table start size */
    if(init_size <= 0) {
        fprintf(stderr, "Invalid initial size!\n");
        return CUCKOO_ERROR;
    }

    /** Malloc some space for our table */
    m = malloc(sizeof(cuckoo_map) * 1);
    if(m == NULL) {
        ret = CUCKOO_MALLOC_FAIL;
        goto cleanup;
    }
    memset(m, 0, sizeof(cuckoo_map));

    /* Set initial table size */
    m->size = init_size;

    /* Handle runtime flags */
    if(check_flagmask(flags, CUCKOO_TABLES_THREE) == 0) {
        m->num_tables = 3;
    } else if(check_flagmask(flags, CUCKOO_TABLES_FOUR) == 0) {
        m->num_tables = 4;
    }  else {
        m->num_tables = 2;
    }

    /** Check other runtime flags */
    // FIXME: This behaviour should be supported!
    if(check_flagmask(flags, CUCKOO_ASYNC | CUCKOO_QUEUED) == 0) {
        fprintf(stderr, "Runtime modes besides 'default' not supported!\n");
        ret = CUCKOO_INVALID_OPTIONS;
        goto cleanup;
    }


    /** Prepare occupancy stat list  */
    m->used = malloc(sizeof(size_t) * m->num_tables);
    if(m->used == NULL) {
        ret = CUCKOO_MALLOC_FAIL;
        goto cleanup;
    }

    /** Create the right number of tables */
    size_t tables = sizeof(cc_map_item**) * m->num_tables;
    m->tables = malloc(tables);
    if(m->tables == NULL) {
        ret = CUCKOO_MALLOC_FAIL;
        goto cleanup;
    }
    memset(m->tables, 0, tables);

    /** Open up the tables by the desired amount */

    size_t init = sizeof(cc_map_item) * init_size;
    for(i = 0; i < m->num_tables; i++) {
        m->tables[i] = malloc(init);
        if(m->tables[i] == NULL) {
            ret = CUCKOO_MALLOC_FAIL;
            goto cleanup;
        }
        memset(m->tables[i], 0, init);
    }

    /** Assign the pointer and return */
    (*map) = m;
    return ret;

    /** Free memory according to how far the allocation step got **/
    cleanup:
    if(m->used != NULL) free(m->used);
    for(i = 0; i < m->num_tables; i++) if(m->tables[i] != NULL) free(m->tables[i]);
    if(m->tables != NULL) free(m->tables);
    if(m != NULL) free(m);

    return ret;
}


int cuckoo_free(struct cuckoo_map *map, void (*free_cb)(void*))
{
    int i, j;

    if(map == NULL) return CUCKOO_INVALID_OPTIONS;

    /* Iterate over all tables */
    for(i = 0; i < map->num_tables; i++) {

        /* Run "free cb for all children - if it exists */
        if(free_cb != NULL) {
            for(j = 0; j < map->used[i]; j++) {
                free_cb(map->tables[i][j]);
            }
        }

        if(map->tables[i] != NULL) free(map->tables[i]);
    }

    if(map->used != NULL) free(map->used);
    if(map->tables != NULL) free(map->tables);
    free(map);

    return CUCKOO_SUCCESS;
}


/************************************************************/

unsigned int check_flagmask(int32_t flags, int32_t mask)
{
    int32_t x = flags & mask;
    if(x == 0) return 1;

    if(x != 1) {
        while(((x % 2) == 0) && x > 1) x /= 2;
        if(x != 1) return 1;
    }

    return 0;
}
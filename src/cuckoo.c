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
    char            *key;
    void            *value;

    /* An element knows what table it's in */
    unsigned short  table;

    /* An element also knows it's previous table */
    unsigned short  prev;

    /* Only used for queue inserts */
    unsigned int    qu_idx;
} cc_map_item;

typedef struct cuckoo_map {
    size_t          size;
    unsigned short  num_tables;

    /** A list of "cc_map_item" tables */
    cc_map_item ***tables;

} cuckoo_map;

unsigned int check_flagmask(int32_t flags, int32_t mask);


int cuckoo_init(cuckoo_map **map, size_t init_size, uint32_t flags)
{
    struct cuckoo_map *m;
    int ret = CUCKOO_SUCCESS;
    int i;

    if(init_size <= 0) {
        fprintf(stderr, "Invalid initial size!\n");
        return CUCKOO_ERROR;
    }

    /** Malloc some space for our table */
    m = malloc(sizeof(cuckoo_map) * 1);
    if(m == NULL) {
        ret = CUCKOO_MALLOC_FAIL;
        goto container;
    }
    memset(m, 0, sizeof(cuckoo_map));

    /* Set initial table size */
    m->size = init_size;

    /* Handle runtime flags */
    if(check_flagmask(flags, CC_FLAGS_TABLES_THREE) == 0) {
        m->num_tables = 3;
    } else if(check_flagmask(flags, CC_FLAGS_TABLES_FOUR) == 0) {
        m->num_tables = 4;
    }  else {
        m->num_tables = 2;
    }

    /** Check other runtime flags */
    // FIXME: This behaviour should be supported!
    if(check_flagmask(flags, CC_FLAGS_ASYNC | CC_FLAGS_QUEUED)) {
        fprintf(stderr, "Runtime modes besides 'default' not supported!\n");
        ret = CUCKOO_INVALID_OPTIONS;
        goto container;
    }

    /** Create the right number of tables */
    size_t tables = sizeof(cc_map_item**) * m->num_tables;
    m->tables = malloc(tables);
    if(m->tables == NULL) {
        ret = CUCKOO_MALLOC_FAIL;
        goto meta;
    }
    memset(m->tables, 0, tables);

    /** Open up the tables by the desired amount */

    size_t init = sizeof(cc_map_item) * init_size;
    for(i = 0; i < m->num_tables; i++) {
        m->tables[i] = malloc(init);
        if(m->tables[i] == NULL) {
            ret = CUCKOO_MALLOC_FAIL;
            goto tables;
        }
        memset(m->tables[i], 0, init);
    }

    /** Assign the pointer and return */
    (*map) = m;
    return ret;

    /** Free memory according to how far the allocation step got **/

    tables:
    for(i = 0; i < m->num_tables; i++) {
        if(m->tables[i] == NULL) free(m->tables[i]);
    }

    meta:
    if(m->tables != NULL) free(m->tables);

    container:
    if(m != NULL) free(m);

    return ret;
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
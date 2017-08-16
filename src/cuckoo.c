/*
 * This file is part of libcuckoo
 * It is free software under the LGPL 3.0
 *
 * @author Katharina "spacekookie" Sabel
 */

// Include our internal headers
#include <cuckoo.h>
#include <memory.h>
#include <malloc.h>


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

uint32_t cuckoo_init(cuckoo_map **map, size_t init_size, uint32_t flags)
{
    struct cuckoo_map *m;
    int i;

    if(init_size <= 0) {
        printf("Invalid initial size!\n");
        return 1;
    }

    /** Malloc some space for our table */
    m = malloc(sizeof(cuckoo_map) * 1);
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

    /** Create the right number of tables */
    size_t tables = sizeof(cc_map_item**) * m->num_tables;
    m->tables = malloc(tables);
    memset(m->tables, 0, tables);

    /** Open up the tables by the desired amount */

    size_t init = sizeof(cc_map_item) * init_size;
    for(i = 0; i < m->num_tables; i++) {
        m->tables[i] = malloc(init);
        memset(m->tables[i], 0, init);
    }

    /** Assign the pointer and return */
    (*map) = m;
    return 0;
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
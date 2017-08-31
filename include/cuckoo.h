/*
 * This file is part of libcuckoo
 * It is free software under the LGPL 3.0
 *
 * @author Katharina "spacekookie" Fey
 */

#ifndef __LIBCUCKOO_H_
#define __LIBCUCKOO_H_

#include <stdint.h>
#include <stddef.h>


typedef struct cc_map_item {
    char            *key;           // Index key
    void            *value;         // User data
    uint8_t         table;          // Table location
    uint8_t         prev;           // Previous table location
    uint32_t        qu_idx;         // Insert queue location
} cc_map_item;


typedef struct cuckoo_map {
    size_t          size;           // Table max size (upper bound)
    size_t          *used;          // Occupancy of each table
    uint8_t         num_tables;     // Number of tables
    uint32_t        rec_lim;        // Upper limit for recursive inserts
    cc_map_item     ***tables;      // Actual data storage
} cuckoo_map;


/** Runtime flags given to initialiser **/
#define CUCKOO_DEFAULT              (1 << 1)
#define CUCKOO_REC_UNLIMITED        (1 << 2)
#define CUCKOO_REC_LIMITED          (1 << 3)
#define CUCKOO_QUEUED               (1 << 4)
#define CUCKOO_ASYNC                (1 << 5)
#define CUCKOO_TABLES_TWO           (1 << 6)
#define CUCKOO_TABLES_THREE         (1 << 7)
#define CUCKOO_TABLES_FOUR          (1 << 8)

/** Don't provide a callback function */
#define CUCKOO_NO_CB                NULL

#define CUCKOO_SUCCESS              0
#define CUCKOO_ERROR                1

/* Runtime issues */
#define CUCKOO_MALLOC_FAIL          10
#define CUCKOO_FAILED_INSERT        11
#define CUCKOO_HASHING_FAILED       12

/* User created issues */
#define CUCKOO_INVALID_OPTIONS      20
#define CUCKOO_NOT_IMPLEMENTED      21


/**
 * Creates a new cuckoo map with an initial size and a few runtime
 * flags that can be combined to achieve different behaviours. This
 * includes the queueing style, number of tables and hash functions.
 *
 * By default it will create two tables and use simple queuing for
 * inserting new items.
 *
 * @param map           A reference pointer to a map to be created
 * @param init_size     The initial size of the map tables
 * @param rt_flgs       Runtime flags provided via OR operator (|)
 * @return
 */
int cuckoo_init(struct cuckoo_map **map, size_t init_size, uint32_t flags);


/**
 *
 * @param map
 * @param key
 * @param data
 * @return
 */
int cuckoo_insert(struct cuckoo_map *map, const char *key, void *data);


/**
 *
 * @param map
 * @param key
 * @return
 */
int cuckoo_contains(struct cuckoo_map *map, const char *key);


/**
 * Count all elements in all tables and returns a
 *
 * @param map
 * @return
 */
size_t cuckoo_size(struct cuckoo_map *map);


/**
 *
 * @param map
 * @param key
 * @param data
 * @return
 */
int cuckoo_retrieve(struct cuckoo_map *map, const char *key, void **data);


/**
 *
 * @param map
 * @param key
 * @return
 */
int cuckoo_remove(struct cuckoo_map *map, const char *key, void (*free_cb)(void*));


/**
 *
 * @param map
 * @return
 */
int cuckoo_clear(struct cuckoo_map *map, void (*free_cb)(void*));


/**
 *
 * @param map
 * @return
 */
int cuckoo_free(struct cuckoo_map *map, void (*free_cb)(void*));

#endif // __LIBCUCKOO_H_
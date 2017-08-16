/*
 * This file is part of libcuckoo
 * It is free software under the LGPL 3.0
 *
 * @author Katharina "spacekookie" Fey
 */

#include <unitypes.h>

/** Forward declare our map so users can import them */
typedef struct cuckoo_map cuckoo_map;

/** Runtime flags given to initialiser **/
#define CC_FLAGS_DEFAULT        (1 << 1)
#define CC_FLAGS_QUEUED         (1 << 2)
#define CC_FLAGS_ASYNC          (1 << 3)
#define CC_FLAGS_TABLES_TWO     (1 << 4)
#define CC_FLAGS_TABLES_THREE   (1 << 5)
#define CC_FLAGS_TABLES_FOUR    (1 << 6)


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
uint32_t cuckoo_init(struct cuckoo_map **map, size_t init_size, uint32_t flags);

/**
 * Starts walking through the queue to syndicate tables with queue 
 * entries to allow for quick lookup times. 
 */
//int32_t cuckoo_async(cuckoo_map *map);
//
//int32_t cuckoo_insert(cuckoo_map *map, const char *key, void *val);
//
//int32_t cuckoo_remove(cuckoo_map *map, const char *key);
//
//int32_t cuckoo_get(cuckoo_map *map, void *(*item), const char *key);
//
//int32_t cuckoo_get_any(cuckoo_map *map, void *(*item));

/**
 * Blocking call that will sync the slow insert queue with the fast
 * bucket map to optimise lookup times. This function will block until
 * no more items can be synced.
 *
 * Returns
 *      == 0 if all items were synced
 *      >= 1 indicating the amount of items still in the queue
 *      <= 1 error codes that need lookup from <cuckoo/errors.h>
 */
int32_t cuckoo_sync(cuckoo_map *map);

int32_t cuckoo_clear(cuckoo_map *map);

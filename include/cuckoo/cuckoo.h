/*
 * This file is part of libcuckoo
 * It is free software under the LGPL 3.0
 *
 * @author Katharina "spacekookie" Sabel
 */

/** Forward declare our map so users can import them */
struct cuckoo_map;
typedef struct cuckoo_map cuckoo_map;

/** Runtime flags given to initialiser **/
#define CUCKOO_RT_DEFAULT   (1 << 1)
#define CUCKOO_RT_QUEUED    (1 << 2)
#define CUCKOO_RT_ASYNC     (1 << 3)

 /**
  * Creates a new cuckoo map with an initial size and a few
  * runtime parameter flags that can be combined to create different
  * behaviours. Note that DEFAULT can not be combined with any other 
  * type. 
  * Errors will be returned if runtime flag combinations are invalid.
  *     (see cuckoo/errors.h for details)
  *
  * Map pointer is required to access elements at a later date.
  *
  */
int32_t cuckoo_init(cuckoo_map *map, int32_t init_size, int32_t rt_flgs);

/**
 * Starts walking through the queue to syndicate tables with queue 
 * entries to allow for quick lookup times. 
 */
int32_t cuckoo_async(cuckoo_map *map);

int32_t cuckoo_insert(cuckoo_map *map, const char *key, void *val);

int32_t cuckoo_remove(cuckoo_map *map, const char *key);

int32_t cuckoo_get(cuckoo_map *map, void *(*item), const char *key);

int32_t cuckoo_get_any(cuckoo_map *map, void *(*item));

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

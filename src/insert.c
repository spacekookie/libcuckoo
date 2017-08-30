/**
 * Moving insert algorithm into it's own file because it's complicated :)
 */


#include <cuckoo.h>
#include <malloc.h>
#include <memory.h>

#include "hashing.h"

#define IGNORE -255

#define TABLE_INIT  -1
#define TABLE_ONE   0
#define TABLE_TWO   1
#define TABLE_THREE 2
#define TABLE_FOUR  3


int insert_to_next(struct cuckoo_map *map, cc_map_item *item, cc_map_item **overflow);


int cuckoo_insert(struct cuckoo_map *map, const char *key, void *data)
{
    int ret;
    cc_map_item *collision = NULL;
    cc_map_item *item;

    /* Check for present arguments */
    if(map == NULL)     return CUCKOO_INVALID_OPTIONS;
    if(key == NULL)     return CUCKOO_INVALID_OPTIONS;
    if(data == NULL)    return CUCKOO_INVALID_OPTIONS;

    /* Allocate space for a new map_item */
    item = (cc_map_item*) malloc(sizeof(cc_map_item));
    if(item == NULL) {
        ret = CUCKOO_MALLOC_FAIL;
        return ret;
    }
    memset(item, 0, sizeof(cc_map_item));

    /** Create a new cc_map_item with all fields set */
    item->prev = (short) TABLE_INIT;
    item->table = TABLE_INIT;
    item->qu_idx = IGNORE;
    item->key = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(item->key, key);
    item->value = data;

    /* Insert "recursively" everything is settled */
    ret = CUCKOO_SUCCESS;
    int rec_ctr = 0;
    do {
        if(collision != NULL) item = collision;

        ret = insert_to_next(map, item, &collision);
        if(ret != 0) return ret;

        rec_ctr++;
        if(rec_ctr >= map->rec_lim) {
            ret = CUCKOO_FAILED_INSERT;
            break;
        }

    } while(collision != NULL);

//    printf("STOP\n\n");
    return ret;
}


int insert_to_next(struct cuckoo_map *map, cc_map_item *item, cc_map_item **overflow)
{
    short curr = item->table;
    unsigned long hash;
    cc_map_item *coll;
    int ret;

    /* Make sure overflow is NULL */
    *overflow = NULL;
    char *key = item->key;

    /* Initial is TABLE_INIT + 1 = 0 */
    short next = curr + (short) 1;
    if(next >= map->num_tables) next = 0;

    item->table = next;
    item->prev = curr;

    switch(next) {
        case TABLE_ONE:
            ret = cc_hashing_murmur(&hash, item->key, map->size);
            break;

        case TABLE_TWO:
            ret = cc_hashing_numeric(&hash, item->key, map->size);
            break;

        case TABLE_THREE:
            ret = cc_hashing_jenkins(&hash, item->key, map->size);
            break;

        case TABLE_FOUR:
            ret = cc_hashing_bernstein(&hash, item->key, map->size);
            break;

        default:
            return CUCKOO_FAILED_INSERT;
    }

    /* Make sure hashing was successful */
    if(ret != 0) return ret;

    /* Signal potential collisions */
    coll = map->tables[next][hash];
    // printf("Inserting %s into %i:%i\n", item->key, next, hash);

    if(coll != NULL) {
        *overflow = coll;
        // printf(" ==> Displacing %s\n", coll->key);
    }


    /* Then write new element to table */
    map->tables[next][hash] = item;
    return CUCKOO_SUCCESS;
}

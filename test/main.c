#include <cuckoo.h>
#include <stdio.h>

int main(void)
{
    int ret;
    cuckoo_map *map;
    ret = cuckoo_init(&map, 10, CC_FLAGS_TABLES_FOUR | CC_FLAGS_DEFAULT);
    if(ret != 0) {
        printf("An error occured while initialising a map!\n");
        return ret;
    }

    return 0;
}
#include <cuckoo.h>
#include <stdio.h>

int main(void)
{
    int ret;
    cuckoo_map *map;
    ret = cuckoo_init(&map, 10, CUCKOO_TABLES_THREE | CUCKOO_DEFAULT);
    if(ret != 0) {
        printf("An error occured while initialising a map!\n");
        return ret;
    }

    ret = cuckoo_free(map, CUCKOO_NO_CB);

    return 0;
}
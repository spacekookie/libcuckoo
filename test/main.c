#include <cuckoo.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

int main(void)
{
    int ret;
    cuckoo_map *map;
    ret = cuckoo_init(&map, 11, CUCKOO_TABLES_TWO | CUCKOO_DEFAULT);
    if(ret != 0) {
        printf("An error occured while initialising a map!\n");
        return ret;
    }

    char *string = malloc(sizeof(char) * strlen("Something"));
    strcpy(string, "Something");

    cuckoo_insert(map, "One", string);
    cuckoo_insert(map, "Two", string);
    cuckoo_insert(map, "Three", string);
    cuckoo_insert(map, "Four", string);
    cuckoo_insert(map, "Five", string);
    cuckoo_insert(map, "a", string);
    cuckoo_insert(map, "b", string);
    cuckoo_insert(map, "c", string);
    cuckoo_insert(map, "d", string);
    cuckoo_insert(map, "e", string);
    cuckoo_insert(map, "f", string);


    ret = cuckoo_free(map, CUCKOO_NO_CB);
    free(string);

    return 0;
}

//    const char words[][6] = {"argon", "emina", "fogey", "balch", "molto", "china", "pross", "bream", "laban", "baker",
//                             "fifty", "hakea", "gawra", "doria", "bloke", "lenes", "buret", "luffa", "kirov", "liker",
//                             "nikos", "hazen", "mammy", "mures", "saxon", "zayin", "janie", "favor", "cotte", "cacao",
//                             "knish", "ammon", "hemin", "kadai", "kondo", "brent", "brogh", "podgy", "cream", "meryl",
//                             "lipid", "adela", "dylan", "marys", "pokie", "hooey", "brute", "angie", "linda", "femur",
//                             "alvis", "vomit", "power", "mulla", "havel", "flory", "byrne", "snuck", "wavey", "burke",
//                             "poloi", "elath", "eanes", "testy", "fecit", "hiker", "pasay", "purin", "sidon", "latex",
//                             "ghazi", "swish", "arvol", "tripe", "stalk", "torii", "whose", "spade", "atila", "titan",
//                             "ginzo", "jolty", "alamo", "dried", "rover", "foram", "loewe", "crest", "tanis", "unsad",
//                             "riser", "starr", "ccuta", "percy", "flake", "balas", "putto", "slide", "fayme", "bejel",
//                             "boffo", "chook", "nikon", "spiel", "aviso", "parsi", "apsis", "enfin", "lucca", "infix",
//                             "marin", "posen", "vitus", "jorum", "nanny", "rowte", "ceiba", "glary", "siple", "abbai",
//                             "lucan", "akita", "tuart", "nonet", "might", "amuse", "mushy", "pskov", "tonic", "sunay",
//                             "aimak", "acton", "doorn", "hodur", "laker", "varna", "thant", "vapid", "kirby", "jedda",
//                             "hiker", "legit", "dozen", "holst", "lowse", "tonus", "vinie", "obuda", "never", "fenny",
//                             "ahwaz", "claim", "storm", "abeam", "ellin", "since", "creed", "quant", "beria", "rowel",
//                             "kinau", "irish", "yakut", "presa", "fulah", "piura", "ampyx", "korma", "alary", "pluto",
//                             "canal", "erose", "pesky", "maker", "ascus", "tobol", "heald", "punka", "nanna", "nikos",
//                             "colum", "trews", "going", "fusee", "visor", "haulm", "peter", "hoots", "jesus", "ruler",
//                             "twite", "admin", "fluid", "agura", "skete", "speel", "basin", "thokk", "footy", "unfar"};
//
//
//    unsigned long hash;
//    int list[101];
//    memset(list, 0, sizeof(int) * 101);
//
//    for(int i = 0; i < 100; i++) {
//        cc_hashing_jenkins(&hash, words[i], 100);
//        printf("Hash val for: %s: %ld\n", words[i], hash);
//        list[hash] += 1;
//    }
//
//    printf("\n\n ======================== \n\n");
//
//    for(int i = 0; i < 100; i++) {
//        printf("%d\n", list[i]);
//    }
//
//
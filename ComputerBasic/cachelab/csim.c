#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringIsEqual(char *a, char *b) {
    return strcmp(a, b) == 0;
}

struct cacheLine {
    int valid;
    long long tag;
    long long lastUsed;
};

struct cacheLine **cacheSet;
int setBits = 0, lineBits = 0, blockBits = 0, detailValue = 0;
int hitBits = 0, missBits = 0, evictionBits = 0;
int hitValue = 0, missValue = 0, evictionValue = 0;

void handleLRU(int type, long long lastUsedNumber) {
    if(type == 0) {
        for(int i = 0; i < (1 << setBits); ++i) {
            for(int j = 0; j < lineBits; ++j) {
                if(cacheSet[i][j].valid == 1) {
                    cacheSet[i][j].lastUsed++;
                }
            }
        }
    }
    else {
        for(int i = 0; i < (1 << setBits); ++i) {
            for(int j = 0; j < lineBits; ++j) {
                if(cacheSet[i][j].valid == 1 && cacheSet[i][j].lastUsed < lastUsedNumber) {
                    cacheSet[i][j].lastUsed++;
                }
            }
        }
    }
}

void findCache(int setNumber, long long tag) {
    // printf("\n%d %lld\n", setNumber, tag);
    struct cacheLine *nullCache = NULL;
    hitValue = 0, missValue = 0, evictionValue = 0;
    for(int j = 0; j < lineBits; ++j) {
        // printCacheLine(cacheSet[setNumber][j]);
        if(cacheSet[setNumber][j].tag == tag && cacheSet[setNumber][j].valid == 1) {
            hitValue = 1;
            hitBits++;
            handleLRU(1, cacheSet[setNumber][j].lastUsed);
            cacheSet[setNumber][j].lastUsed = 0;
            return;
        }
        if(cacheSet[setNumber][j].valid == 0 && nullCache == NULL) {
            nullCache = &cacheSet[setNumber][j];
        }
    }
    missBits++;
    missValue = 1;
    if(nullCache != NULL) {
        handleLRU(0, 0);
        nullCache->valid = 1, nullCache->tag = tag;
        nullCache->lastUsed = 0;
        return;
    }

    struct cacheLine *maxCache = &cacheSet[setNumber][0];
    for(int j = 0; j < lineBits; ++j) {
        if(cacheSet[setNumber][j].lastUsed > maxCache->lastUsed) {
            maxCache = &cacheSet[setNumber][j];
        }
    }

    handleLRU(0, 0);
    evictionValue = 1;
    evictionBits++;
    maxCache->tag = tag, maxCache->valid = 1, maxCache->lastUsed = 0;
    return;
}

void judgePrint() {
    if(detailValue == 1) {
        if(hitValue == 1) {
            printf(" hit");
        }
        else if(missValue == 1) {
            printf(" miss");
        }
        if(evictionValue == 1) {
            printf(" eviction");
        }
    }
}

int main(int argc, char **args)
{
    char *fileLoad = (char *)malloc(sizeof(char) * 100);
    for(int i = 0; i < argc; ++i) {
        if(stringIsEqual(args[i], "-v")) {
            detailValue = 1;
        }

        if(stringIsEqual(args[i], "-s")) {
            setBits = atoi(args[i + 1]);
        }

        if(stringIsEqual(args[i], "-E")) {
            lineBits = atoi(args[i + 1]);
        }

        if(stringIsEqual(args[i], "-b")) {
            blockBits = atoi(args[i + 1]);
        }

        if(stringIsEqual(args[i], "-t")) {
            fileLoad = args[i + 1];
        }
    }

    cacheSet = (struct cacheLine **)malloc(sizeof(struct cacheLine *) * (1 << setBits));
    for(int i = 0; i < (1 << setBits); ++i)
        *(cacheSet + i) = (struct cacheLine *)malloc(sizeof(struct cacheLine) * (lineBits));

    for(int i = 0; i < (1 << setBits); ++i)
        for(int j = 0; j < lineBits; ++j)
            cacheSet[i][j].valid = cacheSet[i][j].tag = cacheSet[i][j].lastUsed = 0;

    FILE *in = fopen(fileLoad, "r");

    while(fgets(fileLoad, 101, in) != NULL) {
        char option;
        long long address;
        int size;
        sscanf(fileLoad, " %c %llx,%d", &option, &address, &size);
        if(detailValue == 1)
            printf("%c %llx,%d", option, address, size);
        address >>= blockBits;
        long long fx = (1 << setBits);
        switch(option) {
            case 'L':
                findCache(address % fx, address);
                judgePrint();
                break;
            case 'S':
                findCache(address % fx, address);
                judgePrint();
                break;
            case 'M':
                findCache(address % fx, address);
                judgePrint();
                findCache(address % fx, address);
                judgePrint();
                break;
            default:
                break;
        }
        if(detailValue == 1)
            puts("");
    }
    printSummary(hitBits, missBits, evictionBits);
    return 0;
}

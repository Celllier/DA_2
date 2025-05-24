#include "Utils.h"

int Utils::amountOfItems(const bool usedItems[], int size) {
    int ret=0;
    for (int i = 0; i < size; i++) {
        if (usedItems[i]) ret++;
    }
    return ret;
}

void Utils::copyFromTo(const bool from[], bool to[], int size) {
    for (int i = 0; i < size; i++) {
        to[i] = from[i];
    }
}

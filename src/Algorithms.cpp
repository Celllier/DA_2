

#include "RequestProcessor.h"
#include "Algorithms.h"
#include <algorithm>
#include <iostream>

#include "Utils.h"

int Algorithms::BF(const Request& request, int curCapacity, bool usedItems[], bool temp[], int& max, int idx, int sum) {
    if (idx >= request.size) {
        if (sum > max ||
            sum == max && Utils::amountOfItems(temp, request.size) < Utils::amountOfItems(usedItems, request.size)) {
            Utils::copyFromTo(temp, usedItems, request.size);
            max = sum;
        }
        return sum;
    }

    int in = 0, out = 0;
    Item curItem = request.items[idx];
    if (curItem.weight <= curCapacity) {
        temp[idx] = true;
        in = BF(request, curCapacity - curItem.weight, usedItems, temp, max, idx + 1, sum + curItem.value);
    }
    temp[idx] = false;
    out = BF(request, curCapacity, usedItems, temp, max, idx + 1, sum);
    return std::max(in, out);
}






void Algorithms::Greedy(const Request &request, bool usedItems[]) {
    std::vector<Item> items;
    for (int i = 0; i < request.size; i++) {
        items.push_back(request.items[i]);
        usedItems[i] = false;
    }

    std::sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return (float)(a.value / a.weight) > (float)(b.value / b.weight);
    });

    int curCapacity = request.capacity;
    for (auto item : items) {
        if (item.weight <= curCapacity) {
            usedItems[item.index - 1] = true;
            curCapacity -= item.weight;
        }
    }
}


void Algorithms::DP(const Request &request, bool usedItems[]) {
    int size = request.size;
    int capacity = request.capacity;

    // Allocate dynamic 2D array
    int** max_value_dp_table = new int*[size+1];
    for (int i = 0; i <= size; i++) {
        max_value_dp_table[i] = new int[capacity+1];
        for (int w = 0; w <= capacity; w++) {
            max_value_dp_table[i][w] = 0;
        }
    }
    // int max_value_dp_table[size][capacity+1];

     for (int i = 0; i <= capacity; i++) {
        if ( i >= request.items[0].weight ) {
            max_value_dp_table[0][i] = request.items[0].value;
        }
        else {
            max_value_dp_table[0][i] = 0;
        }
    }

    for (int i = 1; i <= size; i++) {
        max_value_dp_table[i][0] = 0;

    }

    for (int i = 1; i <= size; i++) {
        int weight = request.items[i-1].weight;
        int value = request.items[i-1].value;
        for (int w = 1; w <= capacity; w++) {
            if (w < weight) {
                max_value_dp_table[i][w] = max_value_dp_table[i - 1][w];
            } else {
                max_value_dp_table[i][w] = std::max(
                    max_value_dp_table[i - 1][w],
                    value + max_value_dp_table[i - 1][w - weight]);
            }
        }
    }


    // reconstrução da solução

    for (int i = 0; i < size; i++) {
        usedItems[i] = false;
    }

    // capacidade disponivel
    int remaining = capacity;
    int idx = 0;
    if ((size + capacity) % 2 != 0) {
        idx = -1;
    }

    for (int i = size-1; i > 0; --i) {
        if (i == 0) {
            if (max_value_dp_table[i][remaining] > 0) {
                usedItems[i] = true;
            }
        } else if (max_value_dp_table[i][remaining] != max_value_dp_table[i - 1][remaining]) {

            usedItems[i+idx] = true;
            remaining -= request.items[i].weight;
        }
    }



    // significa que ainda sobra capacidade então usou-se o item 0
    if (remaining > 0 &&  request.items[0].weight  <= remaining) {
        usedItems[0] = true;
    }



    for (int i = 0; i <= size; ++i) {
        delete[] max_value_dp_table[i];
    }
    delete[] max_value_dp_table;



}


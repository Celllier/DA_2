

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
    std::pair<int, int>** max_value_dp_table = new std::pair<int, int>*[size];
    for (int i = 0; i < size; i++) {
        max_value_dp_table[i] = new std::pair<int, int>[capacity + 1];
        for (int j = 0; j <= capacity; ++j) {
            max_value_dp_table[i][j] = std::make_pair(0, 0);
        }
    }


     for (int i = 0; i <= capacity; i++) {
        if ( i >= request.items[0].weight ) {
            max_value_dp_table[0][i] = std::make_pair(request.items[0].value, 1);
        }
        else {
            max_value_dp_table[0][i] = std::make_pair(0, 0);
        }
    }



    for (int i = 1; i < size; i++) {
        max_value_dp_table[i][0] = std::make_pair(0,0);

    }


    for (int i = 1; i < size; i++) {
        int weight = request.items[i].weight;
        int value = request.items[i].value;
        //std::cout << "ITEM WEIGHT: " << weight << "ITEM VALUE" << value << std::endl;
        for (int w = 1; w <= capacity; w++) {
            std::pair<int, int> without_item = max_value_dp_table[i - 1][w];
            std::pair<int, int> with_item = std::make_pair(0, 0);
            if (w >= weight) {
                with_item = max_value_dp_table[i - 1][w - weight];
                with_item.first += value;
                with_item.second += 1;
            }

            if (with_item.first > without_item.first) {
                max_value_dp_table[i][w] = with_item;
            } else if (with_item.first < without_item.first) {
                max_value_dp_table[i][w] = without_item;
            } else { // Values are equal, choose the one with fewer pallets
                if (with_item.second < without_item.second) {
                    max_value_dp_table[i][w] = with_item;
                } else {
                    max_value_dp_table[i][w] = without_item;
                }
            }
            //std::cout << "WEIGHT " << w  << " Current value " <<  max_value_dp_table[i][w].first << "previous value" <<  max_value_dp_table[i-1][w].first << std::endl;
        }
    }

    // reconstrução da solução

    for (int i = 0; i < size; i++) {
        usedItems[i] = false;
    }

    // capacidade disponivel
    int remaining = capacity;



    for (int i = size - 1; i >= 1; --i) {
        if (remaining == 0) {
            break;
        }
        if (max_value_dp_table[i][remaining] != max_value_dp_table[i - 1][remaining]) {
            usedItems[i] = true;
            remaining-= request.items[i].weight;
        }
    }

    // Check if the first item was used
    if (remaining >= request.items[0].weight && max_value_dp_table[0][remaining].first > 0) {
        usedItems[0] = true;
    }





    for (int i = 0; i < size; i++) {
        //std::cout << "MADE IT TO "  << i << std::endl;
        delete[] max_value_dp_table[i];
    }


    delete[] max_value_dp_table;



}


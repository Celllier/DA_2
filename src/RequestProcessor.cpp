//
// Created by micael on 02-05-2025.
//

#include "RequestProcessor.h"
#include "Algorithms.h"
#include <iostream>

void RequestProcessor::processRequest(Request &request) {
    switch (request.type) {
        case BruteForce: {
            processBF(request);
            break;
        }
        case DynamicProgramming: {
            processDP(request);
            break;
        }
        case Greedy: {
            processGreedy(request);
            break;
        }
        case ILP: {
            processILP(request);
            break;
        }
    }
}


void RequestProcessor::processBF(Request &request) {
    std::cout << "Processing BF..." << std::endl;
    bool temp[request.size];
    bool usedItems[request.size];
    int max = 0;
    Algorithms::BF(request, request.capacity, usedItems, temp, max);

    std::vector<Item> items;
    for (int i = 0; i < request.size; i++) {
        if (usedItems[i]) items.push_back(request.items[i]);
    }

    for (auto item : items) {
        std::cout << item.index << " " << item.weight << " " << item.value << std::endl;
    }
}

void RequestProcessor::processDP(Request &request) {
    std::cout << "Processing DP..." << std::endl;

}

void RequestProcessor::processGreedy(Request &request) {
    std::cout << "Processing Greedy..." << std::endl;
    bool usedItems[request.size];
    Algorithms::Greedy(request, usedItems);

    std::vector<Item> items;
    for (int i = 0; i < request.size; i++) {
        if (usedItems[i]) items.push_back(request.items[i]);
    }

    for (auto item : items) {
        std::cout << item.index << " " << item.weight << " " << item.value << std::endl;
    }
}

void RequestProcessor::processILP(Request &request) {
    std::cout << "Processing ILP..." << std::endl;

}
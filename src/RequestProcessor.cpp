#include "RequestProcessor.h"

#include <chrono>

#include "Algorithms.h"
#include <iostream>

#include "InputHandler.h"

void RequestProcessor::processRequest(Request &request) {

    std::string request_name [] = {
        "Brute Force",
        "Dynamic Programming",
        "Greedy",
        "ILP"   };

    auto start = std::chrono::high_resolution_clock::now();

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
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken for request of type " << request_name[request.type] << ": "
              << duration.count() << " seconds" << std::endl;
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

    int totalProfit = 0;
    int totalWeight = 0;

    for (auto item : items) {
        std::cout << item.index << " " << item.weight << " " << item.value << std::endl;
        totalProfit += item.value;
        totalWeight += item.weight;
    }

    std::cout << "Max Profit: " << totalProfit << std::endl;
    std::cout  << "Max Weight: " << totalWeight << std::endl;

}

void RequestProcessor::processDP(Request &request) {
    std::cout << "Processing DP..." << std::endl;

    bool usedItems[request.size] = {false};
    Algorithms::DP(request, usedItems);

    std::vector<Item> items;
    for (int i = 0; i < request.size; i++) {
        if (usedItems[i]) items.push_back(request.items[i]);
    }

    int totalProfit = 0;
    int totalWeight = 0;

    for (auto item : items) {
        std::cout << item.index << " " << item.weight << " " << item.value << std::endl;
        totalProfit += item.value;
        totalWeight += item.weight;
    }

    std::cout << "Max Profit: " << totalProfit << std::endl;
    std::cout  << "Max Weight: " << totalWeight << std::endl;

}

void RequestProcessor::processGreedy(Request &request) {
    std::cout << "Processing Greedy..." << std::endl;
    bool usedItems[request.size];
    Algorithms::Greedy(request, usedItems);

    std::vector<Item> items;
    for (int i = 0; i < request.size; i++) {
        if (usedItems[i]) items.push_back(request.items[i]);
    }

    int totalProfit = 0;
    int totalWeight = 0;

    for (auto item : items) {
        std::cout << item.index << " " << item.weight << " " << item.value << std::endl;
        totalProfit += item.value;
        totalWeight += item.weight;
    }

    std::cout << "Max Profit: " << totalProfit << std::endl;
    std::cout  << "Max Weight: " << totalWeight << std::endl;
}

void RequestProcessor::processILP(Request &request) {
    std::cout << "Processing ILP..." << std::endl;
    int res = Algorithms::ILP(request);

    if(!res) {
        InputHandler::parseILPResults(request);
    }

}
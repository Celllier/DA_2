//
// Created by micael on 02-05-2025.
//

#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H
#include <vector>

enum RequestType {
    BruteForce,
    DynamicProgramming,
    Greedy,
    ILP
};

typedef struct {
    int index;
    int value;
    int weight;
} Item;


typedef struct {
    int capacity = 0;
    int size = 0;
    std::vector<Item> items;
    RequestType type = BruteForce;
} Request;


class RequestProcessor {
public:
    static void processRequest(Request &request);

    static void processBF(Request &request);

    static void processDP(Request &request);

    static void processGreedy(Request &request);

    static void processILP(Request &request);
};

#endif //REQUESTPROCESSOR_H

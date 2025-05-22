#ifndef ALGORITHMS_H
#define ALGORITHMS_H

class Algorithms {
public:
 static int BF(const Request& request, int curCapacity, bool usedItems[], bool temp[], int& max, int idx = 0, int sum = 0);

 static void Greedy(const Request& request, bool usedItems[]);

 static void DP(const Request &request, bool usedItems[]);

 static int ILP(const Request &request);

};

#endif // ALGORITHMS_H

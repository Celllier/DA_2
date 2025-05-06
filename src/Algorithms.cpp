

#include "RequestProcessor.h"
#include "Algorithms.h"

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

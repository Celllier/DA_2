#ifndef ALGORITHMS_H
#define ALGORITHMS_H
/**
 * @brief Contains various algorithm implementations for solving the generic 0/1 Knapsack problem.
 *
 * Includes brute-force, greedy, dynamic programming, and ILP approaches.
 */
class Algorithms {
public:
    /**
    * @brief Brute-force recursive solution to the 0/1 knapsack problem.
    *
    * Explores all combinations of items recursively to find the optimal set.
    *
    * @param request The input request containing items and capacity.
    * @param curCapacity Remaining truck capacity.
    * @param usedItems Output array marking selected items.
    * @param temp Temporary array used during recursion.
    * @param max Reference to current best value found.
    * @param idx Current item index.
    * @param sum Current sum of values in this path.
    * @return Maximum value found.
    *
    * Complexity Time: O(2^n), Space: O(n)
    */
    static int BF(const Request& request, int curCapacity, bool usedItems[], bool temp[], int& max, int idx = 0, int sum = 0);

    /**
    * @brief Greedy approximation of the knapsack solution.
    *
    * Uses value-to-weight ratio to pick items until capacity is exhausted.
    *
    * @param request The input request containing items and capacity.
    * @param usedItems Output array marking selected items.
    *
    * Complexity Time: O(n log n), Space: O(n)
    */
    static void Greedy(const Request& request, bool usedItems[]);

    /**
    * @brief Dynamic programming solution to the generic knapsack problem.
    *
    * Builds a DP table of optimal substructure solutions.
    *
    * @param request The input request containing items and capacity.
    * @param usedItems Output array marking selected items.
    *
    * Complexity Time: O(n * W), Space: O(n * W), where W is the capacity
    */
    static void DP(const Request &request, bool usedItems[]);

    /**
    * @brief Solves the knapsack problem using an external ILP solver (Python).
    *
    * Calls a Python script that generates and solves the integer linear program.
    *
    * @param request The input request with file paths to truck and pallet data.
    * @return Exit code of the Python script (0 if success).
    *
    * Complexity Time
    * - Time: O(2^n) in the worst case (due to the NP-hard nature of the problem and ILP), but the default solver used
    *         CBC is highly optimized and performs well on small to moderately sized instances.
    * - Space: O(n), where n is the number of items (variables), due to the need to store decision variables,
    *          constraints, and intermediate solver state.
    */
    static int ILP(const Request &request);


};


#endif // ALGORITHMS_H

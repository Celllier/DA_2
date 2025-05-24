#ifndef REQUESTPROCESSOR_H
#define REQUESTPROCESSOR_H
#include <vector>
#include <string>

/**
 * @enum RequestType
 * @brief Enumerates the types of algorithms that can be used to process a request.
 */
enum RequestType {
    BruteForce, ///< Brute-force approach
    DynamicProgramming,  ///< Dynamic programming approach
    Greedy,  ///< Greedy algorithm approach
    ILP  ///< Integer Linear Programming approach
};

/**
* @struct Item
* @brief Represents a single item with index, value, and weight.
*/
typedef struct {
    int index;  ///< Index of the item
    int value;  ///< Value of the item
    int weight; ///< Weight of the item
} Item;

/**
 * @struct Request
 * @brief Represents a processing request, including the item list, algorithm type, and input paths.
 */
typedef struct {
    int capacity = 0; ///< Maximum truck capacity
    int size = 0;   ///< Number of items in the request
    std::vector<Item> items; ///< List of items to consider
    RequestType type = BruteForce; ///< Default selected algorithm type for processing
    std::string pallets_path;  ///< File path to the pallets input
    std::string truck_path;  ///< File path to the truck input
} Request;

/**
 * @class RequestProcessor
 * @brief Provides static methods to process different types of requests based on algorithm type.
 */
class RequestProcessor {
public:
    /**
    * @brief Dispatches the request to the appropriate algorithm based on the request type.
    *
    * @param request The request to be processed.
    */
    static void processRequest(Request &request);

    /**
    * @brief Processes the request using the Brute Force algorithm.
    *
    * @param request The request to be processed.
    */
    static void processBF(Request &request);

    /**
    * @brief Processes the request using the Dynamic Programming algorithm.
    *
    * @param request The request to be processed.
    */
    static void processDP(Request &request);

    /**
    * @brief Processes the request using the Greedy algorithm.
    *
    * @param request The request to be processed.
    */
    static void processGreedy(Request &request);

    /**
    * @brief Processes the request using Integer Linear Programming.
    *
    * @param request The request to be processed.
    */
    static void processILP(Request &request);
};

#endif //REQUESTPROCESSOR_H

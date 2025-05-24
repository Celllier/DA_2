#ifndef UTILS_H
#define UTILS_H

/**
 * @class Utils
 * @brief A utility class providing helper functions for array operations.
 */
class Utils {
public:

     /**
     * @brief Counts the number of items marked as used in a boolean array.
     *
     * @param usedItems An array of booleans where `true` represents a used item.
     * @param size The number of elements in the array.
     * @return The number of `true` values in the array.
     */
     static int amountOfItems(const bool usedItems[], int size);

     /**
     * @brief Copies boolean values from one array to another.
     *
     * @param from The source array to copy from.
     * @param to The destination array to copy to.
     * @param size The number of elements to copy.
     */
     static void copyFromTo(const bool from[], bool to[], int size);
};

#endif //UTILS_H

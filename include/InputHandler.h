//
// Created by micael on 02-05-2025.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <sstream>

#include "RequestProcessor.h"


class InputHandler {
public:

    /**
     *@brief Ignores an input after pressing the key enter
     */
    static void waitForInput();

    /**
     *@brief Waits for an user input.
     * @return Returns the user input.
     */
    static std::string getInput();

    /**
     * @brief Waits for an user input string.
     * @return the user input.
     */
    static std::string getInputLine();

    /**
     * @brief Converts an user input string to a variable T.
     * @tparam T Type of the expected conversion defined by the input string.
     * @param str String read in the input.
     * @param var
     * @return  true if conversion is successful.
     */
    template <typename T>
    static bool convertStrToVar(const std::string &str, T &var){
        std::istringstream ss{str};
        ss >> var;
        if(ss.fail() || !ss.eof()){
            return false;
        }
        return true;
    }

    /**
     * @brief Expects a variable of type T from input cin.
     * @tparam T Type of the expected variable.
     * @param var Variable used to extract the expected type.
     * @return true if it gets the expected variable.
     */
    template<typename T>
    static bool get(T &var) {
        std::string str = getInput();
        if (str.empty()) {
            return false;
        }
        return convertStrToVar(str, var);
    }

    /**
    * @brief Converts a string to lowercase.
    * @param input The input string.
    * @return A new string with all characters converted to lowercase.
    */
    static std::string toLowerString(const std::string& input);


    /**
    * @brief Converts a string to uppercase.
    * @param input The input string.
    * @return A new string with all characters converted to uppercase.
    */
    static std::string toUpperString(const std::string& input);

    /**
    * @brief Strips whitespaces, tab and new line chars.
    * @param input The input string.
    * @return A new trimmed string.
    */
    static void trimString(std::string &str);

    static Request parseTruckAndPallets(const std::string& filepath, bool &correct);

    static void parsePallets(const std::string& filepath, Request &request, bool &correct);




};
#endif //INPUTHANDLER_H



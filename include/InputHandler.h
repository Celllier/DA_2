#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <sstream>
#include <algorithm>
#include <iostream>
#include "RequestProcessor.h"
/**
* @brief Utility class for handling user input and parsing input files.
*
* This class provides helper functions to read and validate user input,
* convert strings, trim unnecessary characters, and parse data files
* required by the application.
*/
class InputHandler {
public:

    /**
    * @brief Pauses execution until the user presses enter.
    *
    * Typically used to allow the user to read console output before continuing.
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

    /**
    * @brief Parses truck capacity and size from a file.
    *
    * @param filepath Path to the input file.
    * @param correct Set to false if file couldn't be opened.
    * @return A Request object containing truck information.
    */
    static Request parseTruckAndPallets(const std::string& filepath, bool &correct);

    /**
    * @brief Parses pallet data from a file and populates a request object.
    *
    * @param filepath Path to the pallets file.
    * @param request Reference to the Request object to populate.
    * @param correct Set to false if file couldn't be opened.
    */
    static void parsePallets(const std::string& filepath, Request &request, bool &correct);

    /**
    * @brief Parses results from an ILP output file and prints them.
    *
    * @param request Request context (unused but available for extended functionality).
    */
    static void parseILPResults(Request &request);




};

#endif //INPUTHANDLER_H



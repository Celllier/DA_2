//
// Created by micael on 02-05-2025.
//

#include "InputHandler.h"

#include <fstream>
#include <iostream>
#include <limits>

void InputHandler::waitForInput() {
    std::cout << std::endl << "Press enter to continue ..." << std::endl;
    std::string tempString;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin,tempString);
}

std::string InputHandler::getInput() {
    std::string input;
    std::cout << ">> ";
    std::cin >> input;
    std::cout << std::endl;
    return input;
}

std::string InputHandler::getInputLine() {
    std::string input;
    std::cout << ">> ";
    getline(std::cin, input);
    std::cout << std::endl;
    return input;
}

// change this
void InputHandler::trimString(std::string &str) {
    while (!str.empty() && (str.back() == '\r' || str.back() == ','))
        str.pop_back();
}


std::string InputHandler::toLowerString(const std::string& input) {
    std::string lowerStr = input;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

std::string InputHandler::toUpperString(const std::string& input) {
    std::string lowerStr = input;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return lowerStr;
}


Request InputHandler::parseTruckAndPallets(const std::string& filepath, bool &correct) {
    Request request;
    std::ifstream file(filepath);
    std::string line;

    if (!file) {
        std::cerr << "Error: Could not open file " << filepath << "\n";
        correct = false;
        return request;
    }

    getline(file, line);  //remove header

    getline(file, line);
    std::istringstream ss(line);
    char token;
    int capacity, size;
    ss >> capacity >> token >> size;

    request.capacity = capacity;
    request.size = size;
    request.truck_path = filepath;

    return request;
}


void InputHandler::parsePallets(const std::string& filepath, Request &request, bool &correct) {
    std::ifstream file(filepath);
    std::string line;

    if (!file) {
        std::cerr << "Error: Could not open file " << filepath << "\n";
        correct = false;
        return;
    }

    getline(file, line);  //remove header

    while(getline(file, line)) {
        std::istringstream ss(line);
        char token;
        int index, weight, value;
        ss >> index >> token >> weight >> token >> value;
        Item item = {index, value, weight};
        request.items.push_back(item);
    }

    request.pallets_path = filepath;



}

void InputHandler::parseILPResults(Request &request) {
    std::string filepath = "../results/output.txt";
    std::ifstream file(filepath);
    std::string line;

    if (!file) {
        std::cerr << "Error: Could not open file " << filepath << "\n";
        return;
    }

    getline(file, line);  //remove header



    while(getline(file, line)) {
        std::istringstream ss(line);
        char token;
        int index, weight, value;
        ss >> index >> weight  >> value;

        std::cout << index << " " <<  weight << " " << value << std::endl;

    }
}
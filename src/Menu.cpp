//
// Created by micael on 02-05-2025.
//


#include "Menu.h"
#include <filesystem>
#include <vector>


Menu *Menu::invalidInput() {
    std::cout << "Invalid input. Please try again." << std::endl;
    InputHandler::waitForInput();
    return this;
}


void MainMenu::show() {
    std::cout << CLEAR;
    int options = 0;
    std::cout << R"(
     //////////////////////////////////////////////////////////////
     //  _____ _   _  ____    _      __  __    _    ____  ____   //
     // |_   _| | | |/ ___|  / \    |  \/  |  / \  |  _ \/ ___|  //
     //   | | | | | | |  _  / _ \   | |\/| | / _ \ | |_) \___ \  //
     //   | | | |_| | |_| |/ ___ \  | |  | |/ ___ \|  __/ ___) | //
     //   |_|  \___/ \____/_/   \_\ |_|  |_/_/   \_\_|   |____/  //
     //////////////////////////////////////////////////////////////
    )" <<  "\n\n";


    std::cout << "MAIN MENU: \n\n";

    std::cout << "(" << ++options << ") >> " << "Process Input" << std::endl;
    std::cout << "(0) >> Go back "  << "Exit" << std::endl;
}

Menu *MainMenu::getNextMenu() {
    int option;
    if(!InputHandler::get(option)) {
        return invalidInput();
    }
    switch (option) {
        case 0: {
            return nullptr;
        }
        case 1: {
            return new InputMenu();
        }
    }
    InputHandler::waitForInput();

    return this;
}





void InputMenu::show() {
    std::cout << CLEAR;
    int options = 0;

    std::cout << "CHOSE THE INPUT FILE: \n\n";
    std::string directoryPallets = "../dataset/pallets/";
    std::string directoryTruckPallets = "../dataset/truckAndPallets/";
    std::vector<std::filesystem::path> filesPallets;
    std::vector<std::filesystem::path> filesTruck;

    try {
        for (const auto &entry : std::filesystem::directory_iterator(directoryPallets)) {
            if (entry.is_regular_file()) {
                filesPallets.push_back(entry.path().filename());
            }
        }

        for (const auto &entry : std::filesystem::directory_iterator(directoryTruckPallets)) {
            if (entry.is_regular_file()) {
                filesTruck.push_back(entry.path().filename());
            }
        }

        if (filesPallets.empty() || filesTruck.empty()) {
            std::cout << "No files found in dataset directory\n"
            << "Insert input files in the dataset folder\n";
            return;
        }

        std::sort(filesPallets.begin(), filesPallets.end());
        std::sort(filesTruck.begin(), filesTruck.end());

        if (filesPallets.size() != filesTruck.size()) {
            std::cout << "Files not equal number of files\n";
            return;
        }


        for (int i = 0; i < filesPallets.size(); ++i) {
            std::cout << "(" << ++options << ") >> " << filesPallets[i].string() << " and " << filesTruck[i].string() << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cout << e.code() << " " << e.what() << std::endl;
    }


    std::cout << "(0) >> Go back "<< std::endl;
}




Menu *InputMenu::getNextMenu() {
    int option;
    if(!InputHandler::get(option)) {
        return invalidInput();
    }
    if (option == 0) return nullptr;


    std::string directoryPallets = "../dataset/pallets/";
    std::string directoryTruckPallets = "../dataset/truckAndPallets/";
    std::vector<std::filesystem::path> filesPallets;
    std::vector<std::filesystem::path> filesTruck;

    for (const auto &entry : std::filesystem::directory_iterator(directoryPallets)) {
        if (entry.is_regular_file()) {
            filesPallets.push_back(entry.path().filename());
        }
    }

    for (const auto &entry : std::filesystem::directory_iterator(directoryTruckPallets)) {
        if (entry.is_regular_file()) {
            filesTruck.push_back(entry.path().filename());
        }
    }

    std::sort(filesPallets.begin(), filesPallets.end());
    std::sort(filesTruck.begin(), filesTruck.end());

    std::string filepathPallets = directoryPallets + filesPallets[option - 1].string();
    std::string filepathTruck = directoryTruckPallets + filesTruck[option - 1].string();

    bool correctFile = true;
    Request r = InputHandler::parseTruckAndPallets(filepathTruck, correctFile);
    InputHandler::parsePallets(filepathPallets, r, correctFile);

    return new DecisionMenu(r);

    //InputHandler::waitForInput();

    //return this;
}



void DecisionMenu::show() {
    std::cout << CLEAR;
    int options = 0;

    std::cout << "DECIDE YOUR APPROACH: \n\n";

    std::cout << "(" << ++options << ") >> " << "Brute Force" << std::endl;
    std::cout << "(" << ++options << ") >> " << "Dynamic Programming" << std::endl;
    std::cout << "(" << ++options << ") >> " << "Greedy" << std::endl;
    std::cout << "(" << ++options << ") >> " << "Integer Linear Programming" << std::endl;
    std::cout << "(0) >> Go back "  << "Exit" << std::endl;
}

Menu *DecisionMenu::getNextMenu() {
    int option;
    if(!InputHandler::get(option)) {
        return invalidInput();
    }

    switch (option) {
        case 0: {
            return nullptr;
        }
        case 1: {
            this->request.type = BruteForce;
            break;
        }
        case 2: {
            this->request.type = DynamicProgramming;
            break;
        }
        case 3: {
            this->request.type = Greedy;
            break;
        }
        case 4: {
            this->request.type = ILP;
            break;
        }
    }

    RequestProcessor::processRequest(this->request);

    InputHandler::waitForInput();

    return this;
}
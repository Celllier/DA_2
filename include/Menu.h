#ifndef MENU_H
#define MENU_H

#define CLEAR "\033[2J\033[1;1H"
#include <algorithm>
#include "InputHandler.h"


/**
* @brief Base class for all menu screens in the application.
*/
class Menu {
protected:

    /**
    * @brief Displays an error message for invalid input and returns the current menu.
    * @return A pointer to the current menu.
    */
    Menu * invalidInput();

public:

    /**
    * @brief Virtual destructor for proper polymorphic behavior.
    */
    virtual ~Menu() = default;

    /**
    * @brief Displays the menu interface.
    */
    virtual void show() = 0;

    /**
    * @brief Determines the next menu or action based on user input.
    * @return A pointer to the next menu.
    */
    virtual Menu *getNextMenu() = 0;
};


/**
* @brief Main menu of the application.
* Allows the user to initiate input processing or exit the application.
*/
class MainMenu : public Menu {
public:

    /**
    * @brief Displays the main menu interface.
    */
    void show() override;

    /**
    * @brief Determines the next menu based on user input.
    * @return A pointer to the next menu.
    */
    Menu *getNextMenu() override;
};


/**
* @brief Menu for selecting input files for processing.
*
* Lists available datasets and passes selected files to the application.
*/
class InputMenu : public Menu {
public:

    /**
    * @brief Displays available input datasets for selection.
    */
    void show() override;

    /**
    * @brief Handles user input and determines the next menu.
    *
    * @return A pointer to the DecisionMenu or nullptr to go back.
    */
    Menu *getNextMenu() override;
};

/**
* @brief Menu for selecting the algorithm to use for a given request.
*
* Displays options for algorithm types and processes the selected request.
*/
class DecisionMenu : public Menu {
public:
    Request request; ///< The request containing data and algorithm selection

    /**
    * @brief Constructs a DecisionMenu using a given request.
    *
    * @param request The request object to be processed.
    */
    explicit DecisionMenu(const Request& request) : request(request) {
        this->request = request;
    }

    /**
    * @brief Displays the algorithm selection menu.
    */
    void show() override;

    /**
    * @brief Handles user input and processes the request using the selected algorithm.
    *
    * @return A pointer to the current menu or nullptr to go back.
    */
    Menu *getNextMenu() override;
};



#endif //MENU_H


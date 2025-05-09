//
// Created by micael on 02-05-2025.
//

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
    // RouteNetwork& route_network_; ///< Reference to the route network being managed.

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



class InputMenu : public Menu {
public:

    /**
    * @brief Displays the input menu interface.
    */
    void show() override;

    /**
    * @brief Determines the next menu or action based on user input.
    * @return A pointer to the next menu.
    */
    Menu *getNextMenu() override;
};

class DecisionMenu : public Menu {
public:
    Request request;

    explicit DecisionMenu(const Request& request) : request(request) {
        this->request = request;
    }

    /**
    * @brief Displays the input menu interface.
    */
    void show() override;

    /**
    * @brief Determines the next menu or action based on user input.
    * @return A pointer to the next menu.
    */
    Menu *getNextMenu() override;
};



#endif //MENU_H


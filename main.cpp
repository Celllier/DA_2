#include <iostream>
#include <stack>

#include "Menu.h"


int main() {
    std::stack<Menu*> menu;

    menu.push(new MainMenu());

    while(!menu.empty()) {
        menu.top()->show();
        Menu * menuPtr = menu.top()->getNextMenu();

        if(menuPtr) {
            if(menuPtr != menu.top()) {
                menu.push(menuPtr);
            }
        }
        else {
            delete menu.top();
            menu.pop();
            //if (menu.size()==1) break;
        }
    }

    std::cout << "BYE! See you next time." << std::endl;

}

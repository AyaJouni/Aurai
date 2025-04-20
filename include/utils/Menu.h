// Menu.h
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <iomanip>
#include "Exception.h"

class MenuItem
{
private:
    std::string label;
    std::function<void()> action;

public:
    MenuItem(const std::string &label, std::function<void()> action)
        : label(label), action(action) {}

    const std::string &getLabel() const
    {
        return label;
    }

    void execute() const
    {
        action();
    }
};

class Menu
{
private:
    std::string title;
    std::vector<MenuItem> items;
    bool exitOnSelection;

public:
    Menu(const std::string &title, bool exitOnSelection = false)
        : title(title), exitOnSelection(exitOnSelection)
    {
        if (!exitOnSelection)
        {
            // Add a standard "Return to previous menu" option
            addItem("Return to previous menu", []() {});
        }
    }

    void addItem(const std::string &label, std::function<void()> action)
    {
        items.push_back(MenuItem(label, action));
    }

    void display() const
    {
        std::cout << "\n"
                  << std::string(50, '=') << "\n";
        std::cout << std::setw(25) << " " << title << "\n";
        std::cout << std::string(50, '=') << "\n";

        for (size_t i = 0; i < items.size(); i++)
        {
            std::cout << i + 1 << ". " << items[i].getLabel() << "\n";
        }

        std::cout << std::string(50, '-') << "\n";
    }

    int getUserChoice() const
    {
        int choice;
        std::string input;

        while (true)
        {
            std::cout << "Enter your choice (1-" << items.size() << "): ";
            std::getline(std::cin, input);

            try
            {
                if (!input.empty())
                {
                    choice = std::stoi(input);

                    if (choice >= 1 && choice <= static_cast<int>(items.size()))
                    {
                        return choice;
                    }
                }

                std::cout << "Invalid choice. Please try again.\n";
            }
            catch (const std::exception &)
            {
                std::cout << "Invalid input. Please enter a number.\n";
            }
        }
    }

    void run()
    {
        while (true)
        {
            display();
            int choice = getUserChoice();

            // Execute the selected action
            if (choice == static_cast<int>(items.size()) && !exitOnSelection)
            {
                // This is the "Return to previous menu" option
                break;
            }

            try
            {
                items[choice - 1].execute();

                if (exitOnSelection)
                {
                    break;
                }

                // Pause after action execution
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
            }
            catch (const CRMException &e)
            {
                std::cout << "\nError: " << e.what() << "\n";
                std::cout << "Press Enter to continue...";
                std::cin.get();
            }
            catch (const std::exception &e)
            {
                std::cout << "\nUnexpected error: " << e.what() << "\n";
                std::cout << "Press Enter to continue...";
                std::cin.get();
            }
        }
    }
};

// Helper class for creating nested menus
class MenuManager
{
private:
    std::vector<Menu> menus;

public:
    // Add a new menu and return its index
    int addMenu(const std::string &title, bool exitOnSelection = false)
    {
        menus.emplace_back(title, exitOnSelection);
        return menus.size() - 1;
    }

    // Get a reference to a menu by index
    Menu &getMenu(int index)
    {
        if (index < 0 || index >= static_cast<int>(menus.size()))
        {
            throw std::out_of_range("Invalid menu index");
        }
        return menus[index];
    }

    // Add an item to a menu that will open another menu
    void addSubmenuItem(int parentIndex, const std::string &label, int childIndex)
    {
        Menu &parentMenu = getMenu(parentIndex);

        parentMenu.addItem(label, [this, childIndex]()
                           { this->getMenu(childIndex).run(); });
    }
};

#endif // MENU_H
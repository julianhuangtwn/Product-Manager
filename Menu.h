
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds
{
    class Menu
    {
        char* m_text;
        int m_numOfOptions;

        //Sets to empty state
        void setEmpty(void);

    public:
        //Constructor setting options for the menu
        Menu(const char* options = nullptr);

        //Deleting dynamic memory
        ~Menu();

        //Displays the end of menu choices, and return user choice
        unsigned int run(void) const;

        //Display the actual dynamic options
        void displayOption(const unsigned int choice) const;
    };
}

#endif
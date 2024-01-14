
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    //Constructor setting options for the menu
    Menu::Menu(const char* options)
    {
        int character;

        setEmpty();

        if (options != nullptr && options[0] != '\0')
        {
            for (character = 0; options[character] != '\0'; character++)
            {
                if (options[character] == '\t')
                {
                    m_numOfOptions++;
                } 
            }
            m_numOfOptions++;
            if (m_numOfOptions <= 15)
            {
                m_text = new char[strlen(options) + 1];
                strcpy(m_text, options);
            }
        }
    }

    //Sets to empty state
    void Menu::setEmpty()
    {
        m_text = nullptr;
        m_numOfOptions = 0;
    }

    //Deleting dynamic memory
    Menu::~Menu()
    {
        delete[] m_text;
    }

    //Displays the end of menu choices, and return user choice
    unsigned int Menu::run(void) const
    {
        int character, listNum = 1, menuChoice;
        
        if (m_text == nullptr || m_text[0] == '\0')
        {
            cout << "Invalid Menu!" << endl;
            menuChoice = 0;
        }
        else
        {
            cout << endl << listNum++ << "- ";
            for (character = 0; m_text[character] != '\0'; character++)
            {
                if (m_text[character] == '\t')
                {
                    cout << endl << listNum << "- ";
                    listNum++;
                }
                else
                {
                    cout << m_text[character];
                }
            }

            cout << endl << "---------------------------------" << endl;
            cout << "0- Exit" << endl;
            cout << "> ";

            menuChoice = ut.getint(0, m_numOfOptions);
            cin.ignore(1000, '\n');
        }

        return menuChoice;
    }

    //Display the actual dynamic options
    void Menu::displayOption(const unsigned int choice) const
    {
        unsigned int choicePosition = 1, characterMatched;

        for (characterMatched = 0; choicePosition != choice; characterMatched++)
        {
            if (m_text[characterMatched] == '\t')
            {
                choicePosition++;
            }
        }

        cout << endl << "****";

        for (; m_text[characterMatched] != '\t' && m_text[characterMatched] != '\0'; characterMatched++)
        {
            cout << m_text[characterMatched];
        }

        cout << "****" << endl;
    }
}
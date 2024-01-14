
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Perishable.h"
#include "Item.h"
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    //Prints the menu header
    unsigned int AidMan::menu()
    {
        Date systemDate;
        cout << "Aid Management System" << endl;
        cout << "Date: ";
        systemDate.formatted(true);
        systemDate.write(cout) << endl;
        cout << "Data file: ";
        if (m_fileName == nullptr)
        {
            cout << "No file" << endl;
        }
        else
        {
            cout << m_fileName << endl;
        }
        cout << "---------------------------------";
        return(m_menu.run());
    }

    //Constructor that also sets the menu options
    AidMan::AidMan(const char* fileName) : m_menu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database")
    {
        int item;

        m_fileName = nullptr;
        for (item = 0; item < sdds_max_num_items; item++)
        {
            m_items[item] = nullptr;
        }
        if (fileName != nullptr && fileName[0] != '\0')
        {
            ut.alocpy(m_fileName, fileName);
        }
        m_numItems = 0;
    }

    //Destructor deleting all dynamic memories including the pointer array
    AidMan::~AidMan()
    {
        delete[] m_fileName;
        for (int item = 0; item < m_numItems; item++)
        {
            delete m_items[item];            
        }
    }

    //The menu choice switch cases calling specific functions
    void AidMan::run()
    {
        unsigned int choice = -1;

        while (choice != 0)
        {
            choice = menu();
            if (choice != 0 && m_fileName == nullptr && choice != 7)
            {
                choice = 7;
            }
            if (choice != 0)
            {
                m_menu.displayOption(choice);
                switch (choice)
                {
                case 1:
                    list();
                    break;

                case 2:
                    addItem();
                    break;

                case 3:
                    removeItem();
                    break;

                case 4:
                    updateQty();
                    break;

                case 5:
                    sort();
                    break;

                case 6:
                    shipItem();
                    break;

                case 7:
                    load();
                    break;
                }
            }
        }

        save();
        cout << "Exiting Program!" << endl;
    }

    //Save info to m_fileName
    void AidMan::save()
    {
        int item;

        if (m_fileName != nullptr)
        {
            ofstream fileOut(m_fileName);
            for (item = 0; item < m_numItems; item++)
            {
                m_items[item]->save(fileOut);
                fileOut << '\n';
            }
        }
    }

    //A manual deallocate function that deallocates everything, and setting numItems to 0
    void AidMan::deallocate()
    {
        int item;

        for (item = 0; item < m_numItems; item++)
        {
            if (m_items[item] != nullptr)
            {
                delete m_items[item];
                m_items[item] = nullptr;
            }
        }
        if (m_fileName != nullptr)
        {
            delete[] m_fileName;
            m_fileName = nullptr;
        }
        m_numItems = 0;
    }

    //Loads the file and store information to the array of pointers
    void AidMan::load(void)
    {
        int item, choice;
        char fileName[FILE_NAME_LEN], firstDigit;

        save();
        deallocate();
        cout << "Enter file name (default data.dat): ";
        cin.getline(fileName, FILE_NAME_LEN, '\n');
        ut.alocpy(m_fileName, fileName);
        ifstream fileRead(m_fileName);
        if (!fileRead)
        {
            cout << "Failed to open " << m_fileName << " for reading!" << endl;
            cout << "Would you like to create a new data file?" << endl;
            cout << "1- Yes!" << endl;
            cout << "0- Exit" << endl;
            cout << "> ";
            choice = ut.getint();
            if (choice == 1)
            {
                ofstream newFile(m_fileName);
            }
        }
        else
        {
            for (item = 0; fileRead; item++)
            {   
                firstDigit = fileRead.peek();
                if (firstDigit >= '1' && firstDigit <= '3') //As peek peeks char, we need to compare the char value, not int, even though sku is int
                {
                    m_items[item] = new Perishable(); //Setting pointer as a dynamic object
                }
                else if (firstDigit >= '4' && firstDigit <= '9')
                {
                    m_items[item] = new Item();
                }
                else
                {
                    fileRead.setstate(ios::badbit);
                }

                if (fileRead)
                {
                    m_items[item]->load(fileRead);
                    if (fileRead)
                    {
                        m_numItems++;
                    }
                    else
                    {
                        delete m_items[item];
                    }
                }
            }

            cout << m_numItems << " records loaded!" << endl << endl;;
        }
    }

    //Prints all items stored
    int AidMan::list(const char* sub_desc) const
    {
        int item, matched = 0, zeroAscii = 48;
        char choice = 0, skip = 0;

        if (m_numItems != 0)
        {
            cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            if (sub_desc == nullptr)
            {
                for (item = 0; item < m_numItems; item++)
                {
                    cout.fill(' ');
                    cout.width(4);
                    cout << item + 1 << " | ";
                    m_items[item]->linear(true);
                    m_items[item]->display(cout) << endl;
                    m_items[item]->linear(false);
                }
                matched = m_numItems;

                cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
                cout << "Enter row number to display details or <ENTER> to continue:" << endl;
                cout << "> ";
                while ((choice < '1' || choice > char(m_numItems + zeroAscii)) && !skip)
                    //zeroAscii is the numeric ascii value for 0, where if you add it to an int, you get the ascii value of the character number you need
                {
                    if (cin.peek() != '\n')
                    {
                        choice = cin.peek();
                        if (choice < '1' || choice >  char(m_numItems + zeroAscii))
                        {
                            cout << "Invalid choice: ";
                            cin.ignore(1000, '\n');
                            choice = 0;
                        }
                    }
                    else
                    {
                        cout << endl;
                        skip = 1;
                    }
                }
                cin.ignore(1000, '\n');

                if (skip != 1)
                {
                    m_items[choice - zeroAscii - 1]->display(cout) << endl;
                }
            }
            else
            {
                for (item = 0; item < m_numItems; item++)
                {
                    if (strstr(m_items[item]->desc(), sub_desc) != nullptr)
                    {
                        cout.fill(' ');
                        cout.width(4);
                        cout << item + 1 << " | ";
                        m_items[item]->linear(true);
                        m_items[item]->display(cout) << endl;
                        m_items[item]->linear(false);
                        matched++;
                    }
                }
                cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            }
        }
        else
        {
            cout << "The list is emtpy!\n" << endl;
        }

        return matched;
    }

    //Search the index that matches the sku
    int AidMan::search(const int sku) const
    {
        int matchedIndex = -1;

        for (int item = 0; item < m_numItems && matchedIndex == -1; item++)
        {
            if (*m_items[item] == sku)
            {
                matchedIndex = item;
            }
        }

        return matchedIndex;
    }

    //Add an item to the list
    void AidMan::addItem()
    {
        int choice, sku;

        if (m_numItems >= sdds_max_num_items)
        {
            cout << "Database full!" << endl;
        }
        else
        {
            cout << "1- Perishable" << endl;
            cout << "2- Non-Perishable" << endl;
            cout << "-----------------" << endl;
            cout << "0- Exit" << endl;
            cout << "> ";
            choice = ut.getint(0, 2);
            if (choice != 0)
            {
                switch (choice)
                {
                case 1:
                    m_items[m_numItems] = new Perishable();
                    break;

                case 2:
                    m_items[m_numItems] = new Item();
                    break;

                case 0:
                    break;
                }
                sku = m_items[m_numItems]->readSku(cin);
                    
                if (search(sku) == -1)
                {
                    m_items[m_numItems]->read(cin);
                    if (!cin)
                    {
                        delete m_items[m_numItems];
                    }
                    else
                    {
                        m_numItems++;
                    }
                }
                else
                {
                    cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl << endl;
                    delete m_items[m_numItems];
                }
            }
        }
    }

    //Remove a pointer from the list
    void AidMan::remove(int index)
    {
        iProduct* temp = nullptr;


        delete m_items[index];
        m_items[index] = nullptr;

        for (int item = index; item < m_numItems; item++)
        {
            if ((item + 1) < m_numItems)
            {
                temp = m_items[item + 1]; //Make current pointer point to the next
                m_items[item] = temp;
            }
        }
        m_numItems--;
    }

    //Prompting which item to remove
    void AidMan::removeItem()
    {
        int matched = 0, sku, matchedIndex, choice = -1;
        char description[MAX_DESC_LEN];

        cout << "Item description: ";
        cin.getline(description, MAX_DESC_LEN, '\n');
        matched = list(description);
        if (matched > 0)
        {
            sku = ut.getint("Enter SKU: ");
            matchedIndex = search(sku);
            if (matchedIndex != -1)
            {
                cout << "Following item will be removed: " << endl;
                m_items[matchedIndex]->display(cout);
                cout << "Are you sure?" << endl;
                cout << "1- Yes!" << endl;
                cout << "0- Exit" << endl;
                cout << "> ";
                choice = ut.getint(0, 1);
                if (choice == 1)
                {
                    remove(matchedIndex);
                    cout << "Item removed!" << endl << endl;;
                }
            }
            else
            {
                cout << "SKU not found!" << endl;
            }
        }
    }

    //Update the quantity currently on hand
    void AidMan::updateQty()
    {
        int matches, sku, matchedIndex, choice, quantity, originalQty;
        char description[MAX_DESC_LEN];

        cout << "Item description: ";
        cin.getline(description, MAX_DESC_LEN, '\n');
        matches = list(description);
        if (matches == 0)
        {
            cout << "No matches found!" << endl;
        }
        else
        {
            sku = ut.getint("Enter SKU: ");
            matchedIndex = search(sku);
            if (matchedIndex != -1)
            {
                cout << "1- Add" << endl;
                cout << "2- Reduce" << endl;
                cout << "0- Exit" << endl;
                cout << "> ";
                choice = ut.getint(0, 2);
                switch (choice)
                {
                case 0:
                    cout << "Aborted!" << endl << endl;
                    break;
                case 1:
                    if (m_items[matchedIndex]->qtyNeeded() == m_items[matchedIndex]->qty())
                    {
                        cout << "Quantity Needed already fulfilled!" << endl << endl;
                    }
                    else
                    {
                        originalQty = m_items[matchedIndex]->qty();
                        cout << "Quantity to add: ";
                        quantity = ut.getint(1, m_items[matchedIndex]->qtyNeeded());
                        *m_items[matchedIndex] += quantity;
                        cout << m_items[matchedIndex]->qty() - originalQty << " items added!" << endl << endl;
                    }
                    break;
                case 2:
                    if (m_items[matchedIndex]->qty() == 0)
                    {
                        cout << "Quaintity on hand is zero!" << endl;
                    }
                    else
                    {
                        originalQty = m_items[matchedIndex]->qty();
                        cout << "Quantity to reduce: ";
                        quantity = ut.getint(1, m_items[matchedIndex]->qty());
                        *m_items[matchedIndex] -= quantity;
                        cout << originalQty - m_items[matchedIndex]->qty() << " items removed!" << endl << endl;
                    }
                    break;
                }
            }
            else
            {
                cout << "SKU not found!" << endl;
            }
        }
    }

    //Sorts the list based on qty and qtyNeeded in descending order
    void AidMan::sort()
    {
        iProduct* temp;
        int diffnext, diff;

        for (int i = m_numItems - 1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                diffnext = (m_items[j + 1]->qtyNeeded() - m_items[j + 1]->qty());
                diff = (m_items[j]->qtyNeeded() - m_items[j]->qty());
                if (diffnext > diff)
                {
                    temp = m_items[j];
                    m_items[j] = m_items[j + 1];
                    m_items[j + 1] = temp;
                }
            }
        }
        cout << "Sort completed!" << endl << endl;
    }

    //Deletes/ships items that quantity on hand have reached quantity needed, and storing info to a file
    void AidMan::shipItem()
    {
        int shipped = 0;
        Date currDate;
        currDate.formatted(true);
        ofstream order("shippingOrder.txt");
        order << "Shipping Order, Date: ";
        currDate.write(order) << endl;

        order << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
        order << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

        for (int item = 0; item < m_numItems; item++)
        {
            if (m_items[item]->qty() == m_items[item]->qtyNeeded())
            {
                m_items[item]->linear(true);
                order.width(4);
                order.fill(' ');
                order << shipped + 1 << " | ";
                m_items[item]->display(order) << endl;
                m_items[item]->linear(false);
                remove(item);
                shipped++;
            }
        }
        order << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        
        cout << "Shipping Order for " << shipped << " times saved!" << endl << endl;
    }

}
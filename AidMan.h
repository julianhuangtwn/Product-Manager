
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

#define FILE_NAME_LEN 50

namespace sdds
{
    // Maximum number of items
    const int sdds_max_num_items = 100;

    class AidMan
    {
        char* m_fileName;
        Menu m_menu;
        iProduct* m_items[sdds_max_num_items];
        int m_numItems;

        //Prints the menu header
        unsigned int menu(void);

    public:
        //Constructor that also sets the menu options
        AidMan(const char* options = nullptr);

        //Destructor deleting all dynamic memories including the pointer array
        ~AidMan();

        //The menu choice switch cases calling specific functions
        void run(void);

        //Save info to m_fileName
        void save(void);

        //A manual deallocate function that deallocates everything, and setting numItems to 0
        void deallocate(void);

        //Loads the file and store information to the array of pointers
        void load(void);

        //Prints all items stored
        int list(const char* sub_desc = nullptr) const;

        //Search the index that matches the sku
        int search(const int sku) const;

        //Add an item to the list
        void addItem();

        //Remove a pointer from the list
        void remove(int index);

        //Prompting which item to remove
        void removeItem();

        //Update the quantity currently on hand
        void updateQty();

        //Sorts the list based on qty and qtyNeeded in descending order
        void sort();

        //Deletes/ships items that quantity on hand have reached quantity needed, and storing info to a file
        void shipItem();
    };
}

#endif
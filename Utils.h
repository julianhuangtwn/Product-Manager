
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include <fstream>

using namespace std;

namespace sdds {

    class Utils {

    public:
        // Acquires system date
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);

        // Return the number of days in a month based on the year
        // year: four digit number (example: 2023)
        int daysOfMon(int mon, int year)const;

        //Deletes dynamic memory allocated in destination, then copies strong from source to destination
        void alocpy(char*& destination, const char* source);
        
        //User input an int and returns the int. If int wasn't entered error msg will be prompted and retry input
        //Prompt is displayed when it is not null
        int getint(const char* prompt = nullptr);

        //User input an int and returns the int. If int wasn't entered error msg will be prompted and retry input
        //Also checks that int is within range. If not, based on errMes different msg will be displayed
        //Prompt is displayed when it is not null
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);

        //Extracts a character from file input buffer
        void extractCharFile(ifstream& ifstr, char character);

    };
    extern Utils ut;  // Provides global access to the ut instance 
}


#endif // !SDDS_UTILS_H

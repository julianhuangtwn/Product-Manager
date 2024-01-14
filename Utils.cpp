
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include "Utils.h"

using namespace std;

namespace sdds {
    // Utils object that will be accessible accross all files
    Utils ut;


    // Acquires system date
    void Utils::getSystemDate(int* year, int* mon, int* day) {
        //Source: cplusplus.com. (n.d.). time_t.
        //time_t is a datatype that stores seconds since epoch Jan 1, 1970 till current system time
        //time(NULL) returns the current system time in seconds since epoch, 0 or NULL means no specific time is required just the current time
        //const time_t currSecondsEpoch = time(nullptr);
        time_t epochSeconds = time(NULL);

        //Source: cplusplus.com. (n.d.). struct tm.
        //tm is a structure that has various broken down time member variables, such as int tm_year, tm_mon, tm_hour...
        //Source: cplusplus.com. (n.d.). localtime
        //localtime is a standalone function in ctime where it converts/stores time_t type variable into tm, and it returns a pointer to tm structure
        //const tm* currTimeTM = localtime(&currSecondsEpoch);
        tm localTime = *localtime(&epochSeconds);
        if (day != nullptr)
        {
            *day = localTime.tm_mday;
        }
        if (mon != nullptr)
        {
            *mon = localTime.tm_mon + 1;
        }
        //Source: cplusplus.com. (n.d.). struct tm.
        //tm_year is designed to start from 1900 instead of epoch time, hence to get current time need to add 1900
        if (year != nullptr)
        {
            *year = localTime.tm_year + 1900;
        }
        
    }

    // Return the number of days in a month based on the year
    // Returns -1 if month is not valid
    // year: four digit number (example: 2023)
    int Utils::daysOfMon(int month, int year)const {
        int days = -1;
        int monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        if (month >= 1 && month <= 12)
        {
            days = monthDays[month - 1];

            if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2)
            {
                days++;
            }
        }

        return days;
    }

    //Deletes dynamic memory allocated in destination, then copies strong from source to destination
    void Utils::alocpy(char*& destination, const char* source)
    {
        if (destination != nullptr)
        {
            delete[] destination;
            destination = nullptr;
        }
        if (source != nullptr && source[0] != '\0')
        {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }

    //User input an int and returns the int. If int wasn't entered error msg will be prompted and retry input
    //Prompt is displayed when it is not null
    int Utils::getint(const char* prompt)
    {
        int value;
        bool valid = false;

        if (prompt != nullptr)
        {
            cout << prompt;
        }

        do
        {
            cin >> value;
            if (!cin)
            {
                cout << "Invalid Integer, retry: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
            {
                valid = true;
            }
        } while (!valid);

        return value;
    }

    //User input an int and returns the int. If int wasn't entered error msg will be prompted and retry input
    //Also checks that int is within range. If not, based on errMes different msg will be displayed
    //Prompt is displayed when it is not null
    int Utils::getint(int min, int max, const char* prompt, const char* errMes)
    {
        int value;

        if (prompt != nullptr)
        {
            cout << prompt;
        }

        do
        {
            value = getint(nullptr);
            if (value < min || value > max)
            {
                if (errMes != nullptr)
                {
                    cout << errMes << ", retry: ";
                }
                else
                {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                }
            }
        } while (value < min || value > max);

        return value;
    }

    //Extracts a character from file input buffer
    void Utils::extractCharFile(ifstream& ifstr, char character)
    {
        if (ifstr.peek() == character) //istr.peek() looks at next char waiting in buffer without extracting
        {
            ifstr.ignore(); //ignores one char in the buffer
        }
        else
        {
            ifstr.ignore(1000, character); //Ignores 1000 characters or up until ch and extract it
            ifstr.setstate(ios::failbit); //Sets cin to a bad state, allowing if (istr)
        }
    }
}
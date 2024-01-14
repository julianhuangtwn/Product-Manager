
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <ctime>
#include "Date.h" 
#include "Utils.h"

using namespace std;

namespace sdds
{
    //Validates the current members are in a valid state
    bool Date::validate(void)
    {
        bool valid = true;
        int daysInMonth;
        int currentYear;

        //Calls utils object to get system date
        ut.getSystemDate(&currentYear);

        //Calls utils object to get days of a month and year
        daysInMonth = ut.daysOfMon(m_month, m_year);

        if ((m_year < currentYear) || m_year > MAX_YEAR)
        {
            m_state = "Invalid year in date";
            m_state = 1;
            valid = false;
        }

        if (valid && (m_month < 1 || m_month > 12))
        {
            m_state = "Invalid month in date";
            m_state = 2;
            valid = false;
        }

        if (valid && (m_day < 1 || m_day > daysInMonth))
        {
            m_state = "Invalid day in date";
            m_state = 3;
            valid = false;
        }

        if (valid)
        {
            m_state.clear();
        }
        else
        {
            cout << m_state << endl;
        }

        return valid;
    }

    //Converts m_year, m_month, m_day members into an int, for comparison purposes
    int Date::calculateUniqDate() const
    {
        return (m_year * 372 + m_month * 31 + m_day);
    }

    //Constructor that sets members to current system date as default if no arguments are passed
    //Or sets members to the arguments
    Date::Date(int year, int month, int day)
    {
        if (year == 0 && month == 0 && day == 0)
        {
            ut.getSystemDate(&m_year, &m_month, &m_day);
        }
        else
        {
            m_year = year;
            m_month = month;
            m_day = day;
        }
        m_formatted = false;
        m_state.setEmpty();

        validate();
    }

    //Destructor that calls clear() from Status
    Date::~Date()
    {
       if ((const char*)m_state != nullptr)
       {
           m_state.clear();
       }
    }

    //Overloaded == returns true if both Date objects equal based on the int returned from calculateUniqDate()
    bool Date::operator ==(const Date& comparison) const
    {
        return (calculateUniqDate() == comparison.calculateUniqDate());
    }

    //Overloaded != returns true if both Date objects don't equal based on the int returned from callculateUniqDate()
    bool Date::operator !=(const Date& comparison) const
    {
        return (calculateUniqDate() != comparison.calculateUniqDate());
    }

    //Overloaded < returns true if current Date is less than the other Date object based on the int returned from callculateUniqDate()
    bool Date::operator <(const Date& comparison) const
    {
        return (calculateUniqDate() < comparison.calculateUniqDate());
    }

    //Overloaded > returns true if current Dates greater than the other Date object based on the int returned from callculateUniqDate()
    bool Date::operator >(const Date& comparison) const
    {
        return (calculateUniqDate() > comparison.calculateUniqDate());
    }

    //Overloaded <= returns true if current Date is less than or equal to the other Date object based on the int returned from callculateUniqDate()
    bool Date::operator <=(const Date& comparison) const
    {
        return (calculateUniqDate() <= comparison.calculateUniqDate());
    }

    //Overloaded >= returns true if current Dates greater than or equal to the other Date object based on the int returned from callculateUniqDate()
    bool Date::operator >=(const Date& comparison) const
    {
        return (calculateUniqDate() >= comparison.calculateUniqDate());
    }

    //Returns m_state
    const Status& Date::state() const
    {
        return m_state;
    }

    //Sets m_formatted based on passed in format
    Date& Date::formatted(bool format)
    {
        m_formatted = format;

        return *this;
    }

    //Overloaded bool cast returns true if m_state is valid
    Date::operator bool() const
    {
        return bool(m_state);
    }

    //Displays Date in specific format based on m_formatted
    ostream& Date::write(ostream& cout) const
    {
        if (m_formatted)
        {
            cout << m_year << "/";
            cout.width(2);
            cout.fill('0');
            cout << m_month << "/";
            cout.width(2);
            cout.fill('0');
            cout << m_day;
        }
        else
        {
            cout << m_year % 100;
            cout.width(2);
            cout.fill('0');
            cout << m_month;
            cout.width(2);
            cout.fill('0');
            cout << m_day;
        }

        return cout;
    }

    //Reads input and sets Date
    //If input format is wrong, cin will be set to a bad state
    istream& Date::read(istream& cin)
    {
        int date;

        cin >> date;
        if (cin)
        {
            //Only 4 or 6 digits are valid and are stored in Date
            //Otherwise, the corresponding position will be set to -1
            if (date >= 100000)
            {
                m_year = date / 10000 + 2000;
                m_month = (date - (m_year % 100 * 10000)) / 100;
                m_day = (date - (m_year % 100 * 10000)) % 100;
            }

            //5 digit input means year is wrong
            else if (date >= 10000 && date <= 99999)
            {
                m_year = -1;
                cin.setstate(ios::badbit);
            }

            //4 digit input will set to the month and day
            else if (date >= 1000 && date <= 9999)
            {
                m_month = date / 100;
                m_day = date % 100;
            }

            //3 digit input means month is wrong no matter what
            else if (date >= 100 && date <= 999)
            {
                m_month = -1;
                cin.setstate(ios::badbit);
            }

            //Since this is 2 digit input:
            //This if else determines if it is the day that is invalid or the month is missing
            else if (date >= 10 && date <= 99)
            {
                if (date >= 1 && date <= 31)
                {
                    m_month = -1;
                    m_day = date;
                }
                else
                {
                    m_day = -1;
                }
                cin.setstate(ios::badbit);
            }

            //1 digit input means day is wrong
            else if (date <= 9)
            {
                m_day = -1;
                cin.setstate(ios::badbit);
            }

            //Validates the input
            if (!validate())
            {
                cin.setstate(ios::badbit);
            }
        }
        else
        {
            m_state = "Invalid date value";
            cin.setstate(ios::badbit);
        }

        return cin;
    }

    //Overloaded << calls and returns write()
    ostream& operator <<(ostream& cout, const Date& source)
    {
        return (source.write(cout));
    }

    //Overloaded >> calls and returns read()
    istream& operator >>(istream& cin, Date& destination)
    {
        return (destination.read(cin));
    }
}
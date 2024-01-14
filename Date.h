
#ifndef SDDS_DATE_H
#define SDDS_DATE_H 

#include <iostream>
#include "Status.h"
#define MAX_YEAR 2030

namespace sdds
{
    class Date
    {
        int m_year;
        int m_month;
        int m_day;
        Status m_state;
        bool m_formatted;

        //Validates the current members are in a valid state
        bool validate(void);

        //Converts m_year, m_month, m_day members into an int, for comparison purposes
        int calculateUniqDate(void) const;

    public:
        //Constructor that sets members to current system date as default if no arguments are passed
        //Or sets members to the arguments
        Date(int year = 0, int month = 0, int day = 0);

        //Destructor that calls clear() from Status
        ~Date();

        //Overloaded == returns true if both Date objects equal based on the int returned from calculateUniqDate()
        bool operator ==(const Date& comparison) const;

        //Overloaded != returns true if both Date objects don't equal based on the int returned from callculateUniqDate()
        bool operator !=(const Date& comparison) const;

        //Overloaded < returns true if current Date is less than the other Date object based on the int returned from callculateUniqDate()
        bool operator <(const Date& comparison) const;

        //Overloaded > returns true if current Dates greater than the other Date object based on the int returned from callculateUniqDate()
        bool operator >(const Date& comparison) const;

        //Overloaded <= returns true if current Date is less than or equal to the other Date object based on the int returned from callculateUniqDate()
        bool operator <=(const Date& comparison) const;

        //Overloaded >= returns true if current Dates greater than or equal to the other Date object based on the int returned from callculateUniqDate()
        bool operator >=(const Date& comparison) const;

        //Returns m_state
        const Status& state(void) const;

        //Sets m_formatted based on passed in format
        Date& formatted(bool format);

        //Overloaded bool cast returns true if m_state is valid
        operator bool(void) const;

        //Displays Date in specific format based on m_formatted
        std::ostream& write(std::ostream& cout) const;

        //Reads input and sets Date
        //If input format is wrong, cin will be set to a bad state
        std::istream& read(std::istream& cin);
    }; 

    //Overloaded << calls and returns write()
    std::ostream& operator <<(std::ostream& cout, const Date& source);

    //Overloaded >> calls and returns read()
    std::istream& operator >>(std::istream& cin, Date& destination);
}

#endif
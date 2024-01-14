
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H 

#include <iostream>

namespace sdds
{
    class Status
    {
        char* m_status; //Stores a dynamic string/message for the status
        int m_statusCode; //Stores an error code

    public:
        //Constructor calling setEmpty 
        Status(void);
        
        //Constructor checking if a description is passed in, then assigns description to m_status
        Status(const char* description);

        //Sets members to empty state
        void setEmpty(void);

        //Copy constructor calling overloaded copy assignment operator to manage class with resource
        Status(const Status& source);

        //Overloaded copy assignment operator that deep copies m_status and shallow copy m_statusCode
        Status& operator =(const Status& source);

        //Destructor deallocating dynamic memory
        ~Status();

        //Assignment operator assigning code to m_statusCode
        Status& operator =(const int code);

        //Assignment operator assigning description to m_status if it's not empty or null
        Status& operator =(const char* description);

        //Overloaded int cast operator to return m_statusCode
        operator int(void) const;

        //Overloaded const char* cast operator to return m_status
        operator const char*(void) const;

        //Overloaded bool cast operator to return true if m_status is null
        operator bool(void) const;

        //Function that sets all members to empty state
        Status& clear(void);
    };

    //Overloaded << operator to print out members of source
    std::ostream& operator <<(std::ostream& cout, const Status& source);
}

#endif
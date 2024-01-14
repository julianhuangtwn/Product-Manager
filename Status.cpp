
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>
#include "Status.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    //Constructor calling setEmpty 
    Status::Status()
    {
        setEmpty();
    }

    //Constructor checking if a description is passed in, then assigns description to m_status
    Status::Status(const char* description)
    {
        if (description != nullptr && description[0] != '\0')
        {
            m_status = nullptr;
            ut.alocpy(m_status, description);
            m_statusCode = 0;
        }
        else
        {
            setEmpty();
        }
    }

    //Sets members to empty state
    void Status::setEmpty()
    {
        m_status = nullptr;
        m_statusCode = 0;
    }

    //Copy constructor calling overloaded copy assignment operator to manage class with resource
    Status::Status(const Status& source)
    {
        m_status = nullptr;
        *this = source;
    }

    //Overloaded copy assignment operator that deep copies m_status and shallow copy m_statusCode
    Status& Status::operator =(const Status& source)
    {
        //Checks if the current object address is the same as source address, and that source m_status isn't empty
        if (this != &source && !source)
        {
            m_status = nullptr;
            ut.alocpy(m_status, source.m_status);
            m_statusCode = source.m_statusCode;
        }

        return *this;
    }

    //Destructor deallocating dynamic memory
    Status::~Status()
    {
        clear();
    }

    //Assignment operator assigning code to m_statusCode
    Status& Status::operator =(const int code)
    {
        m_statusCode = code;

        return *this;
    }

    //Assignment operator assigning description to m_status if it's not empty or null
    Status& Status::operator =(const char* description)
    {
        if (!*this)
        {
            delete[] m_status;
            m_status = nullptr;
        }

        if (description != nullptr && description[0] != '\0')
        {
            ut.alocpy(m_status, description);
        }

        return *this;
    }

    //Overloaded int cast operator to return m_statusCode
    Status::operator int() const
    {
        return m_statusCode;
    }

    //Overloaded const char* cast operator to return m_status
    Status::operator const char*() const
    {
        return m_status;
    }

    //Overloaded bool cast operator to return true if m_status is null
    Status::operator bool() const
    {
        return (m_status == nullptr);
    }

    //Function that sets all members to empty state
    Status& Status::clear()
    {
        if (m_status != nullptr)
        {
            delete[] m_status;
            m_status = nullptr;
        }
        m_statusCode = 0;

        return *this;
    }

    //Overloaded << operator to print out members of source
    ostream& operator <<(std::ostream& cout, const Status& source)
    {
        if (!source)
        {
            if (int(source) != 0)
            {
                cout << "ERR#" << int(source) << ": ";
            }
            cout << (const char*)(source);
        }

        return cout;
    }
}
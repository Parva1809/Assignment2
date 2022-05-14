
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <ctype.h>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
    bool debug = false; // made global in utils.h
    int getTime()
    {
        int mins = -1;
        if (debug)
        {
            Time t(0);
            cout << "Enter current time: ";
            do
            {
                cin.clear();
                cin >> t; // needs extraction operator overloaded for Time
                if (!cin)
                {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else
                {
                    mins = int(t);
                }
                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else
        {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }

    int getInt(const char* prompt)
    {
        char value[30] = { '\0' };
        int val;

        bool flag = true;
        bool is_digit = true;

        if (prompt)
        {
            cout << prompt;
        }

        while (flag)
        {
            cin.clear();
            value[0] = '\0';
            is_digit = true;

            cin.getline(value, 100);

            if (isalpha(value[0]))
            {
                cout << "Bad integer value, try again: ";
                is_digit = false;
            }
            else
            {
                for (int i = 1; value[i] != '\0'; i++)
                {
                    if (!isdigit(value[i]))
                    {
                        cout << "Enter only an integer, try again: ";
                        is_digit = false;
                        break;
                    }
                }
            }
            if (is_digit)
            {
                val = atoi(value);
                flag = false;
            }
        }
        return val;
    }
    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
    {
        bool flag = true;
        int val;
        while (flag)
        {
            val = getInt(prompt);

            while (val < min || val > max)
            {
                if (errorMessage)
                {
                    cout << errorMessage;
                    if (showRangeAtError)
                    {
                        cout << "[" << min << " <= value <= " << max << "]: ";
                    }
                }
                val = getInt();
            }
            flag = false;
        }
        return val;
    }

    char* getcstr(const char* prompt, std::istream& istr, char delimiter)
    {
        string input;
        if (prompt)
        {
            cout << prompt;
        }
        getline(istr, input, delimiter);

        char* c = strcpy(new char[input.length() + 1], input.c_str());
        return c;
    }

    bool isDigit(char* str)
    {
        int i = 0;
        bool ret_val = true;
        while (str[i] != '\0')
        {
            if (!isdigit(str[i++]))
            {
                ret_val = false;
                break;
            }
        }
        return ret_val;
    }

}
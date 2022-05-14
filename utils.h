
#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_
#include <iostream>
namespace sdds
{
    template <typename type>
    void removeDynamicElement(type* array[], int index, int& size) {
        delete array[index];
        for (int j = index; j < size; j++) {
            array[j] = array[j + 1];
        }
        size--;
    }

    extern bool debug; // making sdds::debug variable global to all the files
                       // which include: "utils.h"

    int getTime(); // returns the time of day in minutes

    int getInt(const char* prompt = nullptr);
    int getInt(int min, int max, const char* prompt = nullptr, const char* errorMessage = nullptr, bool showRangeAtError = true);

    char* getcstr(
        const char* prompt = nullptr,  // User entry prompt
        std::istream& istr = std::cin, // the Stream to read from
        char delimiter = '\n'          // Delimiter to mark the end of data
    );

    bool isDigit(char* str);

}
#endif // !SDDS_UTILS_H_


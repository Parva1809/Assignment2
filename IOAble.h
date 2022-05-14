
#ifndef _SDDS_IOABLE_H_
#define _SDDS_IOABLE_H_

#include <iostream>
using namespace std;
namespace sdds
{
    class IOAble
    {
    public:
        virtual ostream& csvWrite(ostream& ostr) const = 0;
        virtual istream& csvRead(istream& istr) = 0;
        virtual ostream& write(ostream& ostr) const = 0;
        virtual istream& read(istream& istr) = 0;
        virtual ~IOAble() = default;
    };
    ostream& operator<<(ostream& ostr, const IOAble& io);
    istream& operator>>(istream& istr, IOAble& io);
}

#endif // _SDDS_IOABLE_H_#pragma once


#include <iostream>
#include "IOAble.h"

using namespace std;
namespace sdds
{

    ostream& operator<<(ostream& ostr, const IOAble& io)
    {
        io.write(ostr);
        return ostr;
    }
    istream& operator>>(istream& istr, IOAble& io)
    {
        io.read(istr);
        return istr;
    }

}
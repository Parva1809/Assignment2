
#include <iostream>
#include "utils.h"
#include "Patient.h"
#include "Ticket.h"

using namespace std;

namespace sdds
{
    Patient::Patient(int t, bool io)
    {
        name = nullptr;
        ticket = Ticket(t);
        io_flag = io;
    }
    Patient::~Patient()
    {
        delete[] name;
    }
    bool Patient::fileIO() const
    {
        return io_flag;
    }
    void Patient::fileIO(bool flag)
    {
        io_flag = flag;
    }
    bool Patient::operator==(const char p_type) const
    {
        return this->type() == p_type;
    }
    bool Patient::operator==(const Patient& p) const
    {
        return this->type() == p.type();
    }
    void Patient::setArrivalTime()
    {
        ticket.resetTime();
    }
    Patient::operator Time() const
    {
        return Time(ticket);
    }
    int Patient::number() const
    {
        return ticket.number();
    }
    ostream& Patient::csvWrite(ostream& ostr) const
    {
        ostr << type() << "," << name << "," << OHIP << ",";
        ticket.csvWrite(ostr);
        return ostr;
    }
    istream& Patient::csvRead(istream& istr)
    {
        delete[] name;
        name = getcstr(nullptr, istr, ',');
        istr >> OHIP;
        istr.ignore();
        ticket.csvRead(istr);
        return istr;
    }
    ostream& Patient::write(ostream& ostr) const
    {
        if (io_flag)
        {
            csvWrite(ostr);
        }
        else
        {
            ticket.write(ostr);
            ostr << endl;
            ostr << string(name).substr(0, 25);
            ostr << ", OHIP: " << OHIP;
        }
        return ostr;
    }
    istream& Patient::read(istream& istr)
    {
        if (io_flag)
        {
            csvRead(istr);
        }
        else
        {
            delete[] name;
            name = getcstr("Name: ", istr, '\n');
            OHIP = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ", true);
        }
        return istr;
    }

}

#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_

#include "IOAble.h"
#include "Ticket.h"

namespace sdds
{
    class Patient : public IOAble
    {
        char* name;
        int OHIP;
        Ticket ticket = Ticket(0);
        bool io_flag = false;

    public:
        Patient(int t = 0, bool io = false);
        ~Patient();
        virtual char type() const = 0;
        bool fileIO() const;
        void fileIO(bool flag);
        bool operator==(const char p_type) const;
        bool operator==(const Patient& p) const;
        void setArrivalTime();
        operator Time() const;
        int number() const;
        std::ostream& csvWrite(std::ostream& ostr) const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
    };
}

#endif // SDDS_PATIENT_H_#pragma once

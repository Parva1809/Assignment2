
#ifndef _SDDS_PRETRIAGE_H_
#define _SDDS_PRETRIAGE_H_

#include "Time.h"
#include "Patient.h"
#include "Menu.h"

namespace sdds
{
    const int maxNoOfPatients = 100;
    class PreTriage
    {
        Time
            M_averageCovidWait,
            M_averageTriageWait;
        Patient* m_lineup[maxNoOfPatients]{};
        char* M_DataFilename = nullptr;
        int M_LineupSize = 0;
        Menu
            M_appliMenu,
            M_PMenu;
        void reg();
        void admit();
        const Time getWaitTime(const Patient& p) const;
        void setAverageWaitTime(const Patient& p);
        void removePatientFromLineup(int index);
        int indexOfFirstInLine(char type) const;
        void load();

    public:
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run(void);
    };
}

#endif // _SDDS_PRETRIAGE_H_
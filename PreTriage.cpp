
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>

#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "utils.h"

using namespace std;
namespace sdds
{

	PreTriage::PreTriage(const char* dataFilename) : M_averageCovidWait(15), M_averageTriageWait(5),
		M_appliMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		M_PMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{

		M_DataFilename = new char[strlen(dataFilename) + 1];
		strcpy(M_DataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage()
	{
		ofstream file(M_DataFilename);

		file << M_averageCovidWait << "," << M_averageTriageWait << endl;
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << M_averageCovidWait << endl;
		cout << "   Triage: " << M_averageTriageWait << endl;
		cout << "Saving m_lineup..." << endl;

		for (int i = 0; i < M_LineupSize; i++)
		{
			m_lineup[i]->fileIO(true);
			file << *m_lineup[i] << endl;
			cout << (i + 1) << "- " << *m_lineup[i] << endl;
		}

		for (int i = 0; i < M_LineupSize; i++)
		{

			delete m_lineup[i];
			m_lineup[i] = nullptr;
		}

		delete[] M_DataFilename;
		M_DataFilename = nullptr;

		cout << "done!" << endl;
	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{
		int no_of_patient = 0;
		for (int i = 0; i < M_LineupSize; i++)
		{
			if (m_lineup[i]->type() == p.type())
			{
				no_of_patient++;
			}
		}
		return (Time(p) *= no_of_patient);
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		Time CT;
		CT.setToNow();

		if (p.type() == 'T')
		{
			M_averageTriageWait = ((int)(CT - Time(p)) + ((int)M_averageTriageWait * (p.number() - 1))) / p.number();
		}
		else if (p.type() == 'C')
		{
			M_averageCovidWait = ((int)(CT - Time(p)) + ((int)M_averageCovidWait * (p.number() - 1))) / p.number();
		}
	}

	void PreTriage::removePatientFromLineup(int index)
	{

		removeDynamicElement(m_lineup, index, M_LineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const
	{

		int index = -1;
		for (int i = 0; i < M_LineupSize; i++)
		{
			if (m_lineup[i]->type() == type)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	void PreTriage::load()
	{
		ifstream read(M_DataFilename);
		cout << "Loading data..." << endl;

		read >> M_averageCovidWait;
		read.ignore(1500, ',');
		read >> M_averageTriageWait;
		read.ignore(1500, '\n');

		Patient* patient = nullptr;
		for (int i = 0; i < maxNoOfPatients && read; i++)
		{

			char type = '\0';

			read >> type;
			read.ignore(1500, ',');

			if (type == 'C')
			{
				patient = new CovidPatient();
			}
			else if (type == 'T')
			{
				patient = new TriagePatient();
			}

			if (patient != nullptr)
			{

				patient->fileIO(true);
				patient->csvRead(read);
				patient->fileIO(false);
				m_lineup[i] = patient;
				patient = nullptr;
				M_LineupSize++;
			}
		}

		if (read)
		{
			cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
		}
		if (M_LineupSize == 0)
		{
			cout << "No data or bad data file!" << endl
				<< endl;
		}
		else
		{
			cout << M_LineupSize << " Records imported..." << endl
				<< endl;
		}
	}

	void PreTriage::reg()
	{

		int m_select;

		if (M_LineupSize >= maxNoOfPatients)
		{
			cout << "Line up full!" << endl;
		}
		else
		{
			M_PMenu >> m_select;
			switch (m_select)
			{
			case 1:
				m_lineup[M_LineupSize] = new CovidPatient();
				break;

			case 2:
				m_lineup[M_LineupSize] = new TriagePatient();
				break;

			case 0:
				break;

			default:
				break;
			}

			m_lineup[M_LineupSize]->setArrivalTime();
			cout << "Please enter patient information: " << endl;

			m_lineup[M_LineupSize]->fileIO(false);

			m_lineup[M_LineupSize]->read(cin);
			cout << endl;

			cout << "******************************************" << endl;
			m_lineup[M_LineupSize]->write(cout);

			cout << "Estimated Wait Time: ";
			cout << getWaitTime(*m_lineup[M_LineupSize]) << endl;
			cout << "******************************************" << endl
				<< endl;
			M_LineupSize++;
		}
	}

	void PreTriage::admit()
	{
		int choice;
		int ind_patient;
		char type = '\0';

		M_PMenu >> choice;
		while (choice)
		{
			if (choice == 1)
			{
				type = 'C';
				break;
			}
			else if (choice == 2)
			{
				type = 'T';
				break;
			}
			else if (choice == 0)
			{
				break;
			}
		}

		ind_patient = indexOfFirstInLine(type);
		if (ind_patient != -1)
		{
			cout << endl;
			cout << "******************************************" << endl;
			m_lineup[ind_patient]->fileIO(false);

			cout << "Calling for ";
			m_lineup[ind_patient]->write(cout);

			cout << "******************************************" << endl
				<< endl;

			setAverageWaitTime(*m_lineup[ind_patient]);
			removePatientFromLineup(ind_patient);
		}
	}

	void PreTriage::run(void)
	{

		int choice;
		do
		{
			M_appliMenu >> choice;

			while (choice)
			{
				if (choice == 1)
				{
					reg();
					break;
				}
				else if (choice == 2)
				{
					admit();
					break;
				}
				else if (choice == 0)
				{
					break;
				}
				else
				{
					cout << "Wrong option. Try again.";
					break;
				}
			}
		} while (choice != 0);
	}
}


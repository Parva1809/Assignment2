//Name    : Patel Jill Dineshbhai
//Email   : jdpatel44@myseneca.ca
//ID      : 158421198
//Subject : BTP200NAA
//Date    : 2 August 2021
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include <iostream>
#include "Patient.h"

namespace sdds
{
	class TriagePatient : public Patient
	{
		char* m_symptoms = nullptr;
	public:
		char type()const;
		TriagePatient();
		~TriagePatient();
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}
#endif 



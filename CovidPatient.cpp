//Name    : Patel Jill Dineshbhai
//Email   : jdpatel44@myseneca.ca
//ID      : 158421198
//Subject : BTP200NAA
//Date    : 2 August 2021
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#include <iostream>
#include "CovidPatient.h"

using namespace std;
namespace sdds
{
	int nextCovidTicket = 1;

	CovidPatient::CovidPatient() : Patient(nextCovidTicket)
	{
		nextCovidTicket++;
	}

	char CovidPatient::type() const
	{
		return 'C';
	}

	std::istream& CovidPatient::csvRead(std::istream& istr)
	{
		Patient::csvRead(istr);
		nextCovidTicket = Patient::number() + 1;
		istr.ignore(1000, '\n');
		return istr;
	}

	std::ostream& CovidPatient::write(std::ostream& ostr) const
	{
		if (fileIO())
		{
			Patient::csvWrite(ostr);
		}
		else
		{
			ostr << "COVID TEST" << endl;
			Patient::write(ostr) << endl;
		}
		return ostr;
	}

	std::istream& CovidPatient::read(std::istream& istr)
	{
		return fileIO() ? csvRead(istr) : Patient::read(istr);
	}
} // namespace sdds
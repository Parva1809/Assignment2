//Name    : Patel Jill Dineshbhai
//Email   : jdpatel44@myseneca.ca
//ID      : 158421198
//Subject : BTP200NAA
//Date    : 2 August 2021
//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include "Patient.h"
namespace sdds
{
	class CovidPatient : public Patient
	{
	public:
		CovidPatient();
		char type()const;
		std::istream& csvRead(std::istream& istr);
		virtual std::ostream& write(std::ostream& ostr)const;
		virtual std::istream& read(std::istream& istr);
	};
}
#endif
#pragma once

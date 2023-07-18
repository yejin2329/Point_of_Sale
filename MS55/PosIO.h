/* Citation and Sources...
Final Project Milestone 5
Module: PosIO
Filename: PosIO.H
Version 1.0
Author	Jenny Kim
Student ID: 139787220
Email: ykim314@myseneca.ca
Revision History
-----------------------------------------------------------
Date      2023/04/19
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
----------------------------------------------------------- */

#pragma once
#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H
#include <iostream>
#include <fstream>

namespace sdds {
	class PosIO {
	public:
		virtual std::ostream& write(std::ostream& os) const = 0;
		virtual std::istream& read(std::istream& is) = 0;
		virtual std::ofstream& save(std::ofstream& ofs) const = 0;
		virtual std::ifstream& load(std::ifstream& ifs) = 0;
		virtual ~PosIO() {};
		virtual char getType() const = 0;

	};

	std::ostream& operator<<(std::ostream& os, const PosIO& posIO);
	std::ofstream& operator<<(std::ofstream& ofs, const PosIO& posIO);
	std::istream& operator>>(std::istream& is, PosIO& posIO);
	std::ifstream& operator>>(std::ifstream& ifs, PosIO& posIO);
}

#endif
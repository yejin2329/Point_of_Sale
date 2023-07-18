/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: Perishable.h
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

#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H
#include <iostream>
#include <iomanip>
#include"POS.h"
#include "PosIO.h"
#include "Date.h"
#include "Item.h"

namespace sdds {
	class Perishable : public Item {
	private:
		Date m_expirydate;
	public:
		char getType() const;


		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& is);
		std::ofstream& save(std::ofstream& ofs) const;
		std::ifstream& load(std::ifstream& ifs);

		void setEmpty();
		~Perishable();

	};

	std::ostream& operator<<(std::ostream& os, const Perishable& peri);
	std::ofstream& operator<<(std::ofstream& ofs, const Perishable& peri);
	std::istream& operator>>(std::istream& is, Perishable& peri);
	std::ifstream& operator>>(std::ifstream& ifs, Perishable& peri);

}

#endif
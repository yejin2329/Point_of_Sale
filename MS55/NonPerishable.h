/* Citation and Sources...
Final Project Milestone 5
Module: NonPerishable
Filename: NonPerishable.h
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
#include "POS.h"
#include "PosIO.h"
#include "Item.h"
namespace sdds {
	class NonPerishable : public Item {

	public:
		char getType() const;
		~NonPerishable();


		std::ostream& write(std::ostream& os) const;
		std::ofstream& save(std::ofstream& ofs) const;
	};



}





#endif
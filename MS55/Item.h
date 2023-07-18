/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.h
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

#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include "POS.h"
#include "Error.h"

namespace sdds {
	class Item {
		char m_sku[MAX_SKU_LEN + 1] = { '\0' };
		char* m_name = nullptr;
		double m_price = 0.0;
		bool m_taxed = false;
		int m_quantity = 0;


	protected:
		int m_displayType = POS_LIST;


	public:
		Error m_error;
		Item();
		Item(const Item& other);
		Item& operator=(const Item& other);
		bool operator==(const char sku[MAX_SKU_LEN]) const;
		bool operator>(const Item&) const;
		int operator+= (int quantity);
		int operator-=(int quantity);
		operator bool() const;

		virtual char getType() const;
		Item& displayType(int pos);
		double cost() const;
		int quantity() const;
		Item& clear();
		virtual ~Item();
		void setEmpty();



		virtual std::ostream& write(std::ostream& os) const;
		virtual std::istream& read(std::istream& is);
		virtual std::ofstream& save(std::ofstream& ofs) const;
		virtual std::ifstream& load(std::ifstream& ifs);

		std::ostream& bprint(std::ostream& os) const;


		char* getName();

		Item& addquantity(int numAdd);
		Item& deductquantity(int num);

		char* getsku();


	};

	double operator+=(double& left, const Item& right);
	std::ostream& operator<<(std::ostream& os, const Item& item);
	std::ofstream& operator<<(std::ofstream& ofs, const Item& item);
	std::istream& operator>>(std::istream& is, Item& item);
	std::ifstream& operator>>(std::ifstream& ifs, Item& item);
}

#endif
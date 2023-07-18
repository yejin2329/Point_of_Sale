/* Citation and Sources...
Final Project Milestone 5
Module: Item
Filename: Item.cpp
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Item.h"
#include "Error.h"

using namespace std;
namespace sdds {

	Item::Item() {

		m_name = nullptr;
		m_price = 0.0;
		m_taxed = false;
		m_quantity = 0;
		m_displayType = POS_LIST;
	}

	Item::Item(const Item& other) {

		if (other.m_name != nullptr) {
			*this = other;
		}
		else {
			m_name = nullptr;
		}
	}
	Item& Item::operator=(const Item& other) {

		if (this != &other) {
			delete[] m_name;
			m_name = nullptr;

			if (other.m_name != nullptr) {

				std::strcpy(m_sku, other.m_sku);

				m_name = new char[std::strlen(other.m_name) + 1];
				std::strcpy(m_name, other.m_name);
				m_price = other.m_price;
				m_taxed = other.m_taxed;
				m_quantity = other.m_quantity;
			}
		}
		return *this;
	}

	Item::~Item() {

		delete[] m_name;
		m_name = nullptr;
	}


	bool Item::operator==(const char sku[MAX_SKU_LEN]) const {

		return (std::strcmp(m_sku, sku) == 0);
	}

	bool Item::operator>(const Item& other) const {

		return (std::strcmp(m_name, other.m_name) > 0);
	}

	int Item::operator+= (int quantity) {

		m_quantity += quantity;
		if (m_quantity > MAX_STOCK_NUMBER) {
			m_quantity = MAX_STOCK_NUMBER;
			m_error.set(ERROR_POS_QTY);
		}

		return m_quantity;
	}



	double operator+=(double& left, const Item& right) {

		left += right.cost() * right.quantity();
		return left;
	}

	int Item::operator-=(int quantity) {

		m_quantity -= quantity;
		if (m_quantity < 0) {
			m_quantity = 0;
		}
		return m_quantity;
	}
	Item::operator bool() const {

		return !(m_error);
	}

	Item& Item::displayType(int pos) {

		m_displayType = pos;
		return *this;
	}

	double Item::cost() const {

		double cost;
		if (m_taxed) {
			cost = m_price * (1 + TAX);
		}

		else {
			cost = m_price;
		}
		return cost;
	}

	int Item::quantity() const {

		return m_quantity;
	}

	Item& Item::clear() {

		m_error.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& os) const {

		std::string name_str(m_name);
		std::string truncated_name = name_str.substr(0, 20);


		if (*this) {

			if (m_displayType == POS_LIST) {

				os << std::setw(MAX_SKU_LEN) << std::left << m_sku << "|"
					<< std::setw(20) << std::left << truncated_name << "|"
					<< std::setw(7) << std::fixed << std::setprecision(2) << std::right << m_price << "|"
					<< " " << (m_taxed ? 'X' : ' ') << " |"
					<< std::setw(4) << std::right << m_quantity << "|"
					<< std::setw(9) << std::fixed << std::setprecision(2) << std::right << cost() * m_quantity << "|";
				os.unsetf(ios::right);

			}
			else if (m_displayType == POS_FORM) {

				os << "=============v" << endl
					<< std::setw(13) << std::left << "Name: " << truncated_name << std::endl
					<< std::setw(13) << std::left << "Sku: " << m_sku << std::endl
					<< std::setw(13) << std::left << "Price: " << std::fixed << std::setprecision(2) << m_price << std::endl
					<< std::setw(13) << std::left << "Price + tax: ";

				if (m_taxed) {
					os << cost();
				}
				else {
					os << "N/A";
				}

				os << std::endl
					<< std::setw(13) << std::left << "Stock Qty: " << m_quantity << std::endl;

			}
		}


		else {
			os << m_error;
		}


		return os;
	}

	std::istream& Item::read(std::istream& is) {
		char sku[10];
		char taxed;
		char name[101];
		std::string line;

		double price;
		int quantity;
		bool check = false;

		//Read Sku
		std::cout << "Sku" << std::endl;

		do {
			m_error.clear();
			std::cout << "> ";
			is >> sku;

			if (is.fail()) {
				m_error.set("Invalid Sku");
			}
			else {
				if (strlen(sku) > MAX_SKU_LEN) {
					m_error.set(ERROR_POS_SKU);
					std::cout << m_error << std::endl;
				}
				else {
					strncpy(m_sku, sku, MAX_SKU_LEN);
					check = true;
				}
			}
		} while (check == false);

		//Read Name
		check = false;
		std::cout << "Name" << std::endl;

		do {

			m_error.clear();
			is.clear();
			std::cout << "> ";

			is.ignore(1000, '\n');
			getline(is, line, '\n');
			is.putback('\n');
			stringstream ss(line);
			strcpy(name, line.c_str());

			if (is.fail()) {
				m_error.set("Invalid Name");
			}
			else {
				if (strlen(name) > MAX_NAME_LEN) {
					m_error.set(ERROR_POS_NAME);
					std::cout << m_error << std::endl;
				}
				else {
					m_name = new char[strlen(name) + 1];
					strcpy(m_name, name);
					check = true;
				}
			}
		} while (check == false);

		//Read Price
		check = false;
		std::cout << "Price" << std::endl;

		do {
			m_error.clear();
			is.clear();
			is.ignore(1000, '\n');
			std::cout << "> ";
			is >> price;
			if (is.fail() || price < 0) {
				m_error.set(ERROR_POS_PRICE);
				std::cout << m_error << std::endl;
			}
			else {
				m_price = price;
				check = true;
			}

		} while (check == false);

		// Read Taxed
		check = false;
		std::cout << "Taxed?" << std::endl;
		std::cout << "(Y)es/(N)o: ";
		do {
			m_error.clear();
			is.clear();
			is.ignore(1000, '\n');


			is >> taxed;
			if (is.fail() || (taxed != 'y' && taxed != 'n')) {
				std::cout << "Only 'y' and 'n' are acceptable: ";

			}
			else {
				if (taxed == 'y') {
					m_taxed = true;
				}

				else {
					m_taxed = false;
				}

				check = true;
			}

		} while (check == false);

		//Read Quantity

		check = false;
		std::cout << "Quantity" << std::endl;

		do {
			m_error.clear();
			is.clear();
			is.ignore(1000, '\n');
			std::cout << "> ";
			is >> quantity;
			if (is.fail() || quantity <= 0 || quantity >= 100) {
				m_error.set(ERROR_POS_QTY);
				std::cout << m_error << std::endl;
			}
			else {
				m_quantity = quantity;
				check = true;
			}

		} while (check == false);

		return is;
	}
	std::ofstream& Item::save(std::ofstream& ofs) const {
		if (ofs.is_open()) {
			if (!m_error) {
				ofs << getType() << "," << m_sku << "," << m_name << "," << std::fixed << std::setprecision(2) << m_price << "," << m_taxed << "," << m_quantity;
			}

			else {
				std::cerr << m_error << std::endl;
			}

		}
		else {
			std::cerr << "Error: the file is not open." << std::endl;
		}

		return ofs;
	}
	std::ifstream& Item::load(std::ifstream& ifs) {
		m_error.clear();

		char sku[11];
		char name[101];
		double price = 0.0;
		int quantity = 0;
		char comma = '\0';
		int tax = 0;


		if (ifs.peek() == ',') {
			ifs.get();

		}
		ifs.getline(sku, 10, ',');
		ifs.getline(name, 100, ',');
		ifs >> price >> comma >> tax >> comma >> quantity;

		if (ifs.fail()) {

			return ifs;
		}

		if (strlen(sku) > MAX_SKU_LEN) {
			m_error.set(ERROR_POS_SKU);
			return ifs;
		}

		else {
			strncpy(m_sku, sku, MAX_SKU_LEN);
		}

		//Validate name

		if (strlen(name) > MAX_NAME_LEN) {
			m_error.set(ERROR_POS_NAME);
			return ifs;
		}
		else {
			delete[] m_name;
			m_name = nullptr;
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
		}

		//validate price

		if (price <= 0.00) {
			m_error.set(ERROR_POS_PRICE);
			return ifs;
		}
		else {
			m_price = price;
		}

		//validate quntity
		if (quantity <= 0 || quantity > MAX_STOCK_NUMBER) {
			m_error.set(ERROR_POS_QTY);
			return ifs;
		}

		else {
			m_quantity = quantity;
		}

		// validate and set the taxed status
		if (tax == true) {
			m_taxed = true;
		}
		else if (tax == false) {
			m_taxed = false;
		}
		else {
			m_error.set(ERROR_POS_TAX);
			return ifs;
		}


		return ifs;


	}

	char Item::getType() const {
		return 'T';
	}


	std::ostream& Item::bprint(std::ostream& os) const {

		std::string name_str(m_name);
		std::string truncated_name = name_str.substr(0, 20);

		os << "| " << std::setw(20) << std::setfill(' ') << std::left << truncated_name;
		os << "| ";
		os << std::setw(9) << std::fixed << std::setprecision(2) << std::right << cost();
		os << " | ";
		os << (m_taxed ? " T  " : "    ") << "|";
		os << std::endl;
		return os;
	}

	char* Item::getName() {

		return m_name;
	}

	void Item::setEmpty() {

		delete[] m_name;
		m_name = nullptr;
		m_error.clear();

	}

	Item& Item::addquantity(int numAdd) {

		m_quantity += numAdd;
		return *this;
	}

	Item& Item::deductquantity(int num) {

		m_quantity -= num;
		return *this;
	}

	char* Item::getsku() {
		return m_sku;
	}

	//Helper Function

	std::ostream& operator<<(std::ostream& os, const Item& item) {
		return item.write(os);
	}
	std::ofstream& operator<<(std::ofstream& ofs, const Item& item) {
		return item.save(ofs);
	}
	std::istream& operator>>(std::istream& is, Item& item) {
		return item.read(is);
	}
	std::ifstream& operator>>(std::ifstream& ifs, Item& item) {
		return item.load(ifs);
	}


}


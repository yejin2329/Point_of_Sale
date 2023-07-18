/* Citation and Sources...
Final Project Milestone 5
Module: Perishable
Filename: .cpp
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

#include "Perishable.h"
#include "Error.h"
#include "Date.h"

namespace sdds {

	char Perishable::getType() const {
		return 'P';
	}

	std::ostream& Perishable::write(std::ostream& os) const {
		Item::write(os);
		if (*this) {
			if (m_displayType == POS_LIST) {
				os << "  ";
				os << m_expirydate.getyear();
				if (m_expirydate.getmon() > 9) {
					os << '/' << m_expirydate.getmon();
				}
				else {
					os << '/' << '0' << m_expirydate.getmon();
				}

				if (m_expirydate.getday() > 9) {
					os << '/' << m_expirydate.getday();
				}
				else {
					os << '/' << '0' << m_expirydate.getday();
				}
				os << " " << "|";
			}
			else if (m_displayType == POS_FORM) {
				os << "Expiry date: ";

				os << m_expirydate.getyear();
				if (m_expirydate.getmon() > 9) {
					os << '/' << m_expirydate.getmon();
				}
				else {
					os << '/' << '0' << m_expirydate.getmon();
				}

				if (m_expirydate.getday() > 9) {
					os << '/' << m_expirydate.getday();
				}
				else {
					os << '/' << '0' << m_expirydate.getday();
				}



				os << std::endl
					<< "=============^" << std::endl;
			}
		}

		return os;

	}


	std::istream& Perishable::read(std::istream& is) {
		Item::read(is);

		if (!this->m_error && !is.fail()) {
			Date expiry;
			expiry.dateOnly(true);
			std::cout << "Expiry date (YYYY/MM/DD)" << std::endl;
			std::cout << "> ";
			expiry.read(is);

			if (expiry) {
				m_expirydate = expiry;
			}
			else {

				Error received(expiry.error());
				m_error = received;
				received.clear();
			}
		}
		return is;
	}

	std::ofstream& Perishable::save(std::ofstream& ofs) const {
		Item::save(ofs);

		ofs << "," << m_expirydate.getyear();

		if (m_expirydate.getmon() > 9) {
			ofs << '/' << m_expirydate.getmon();
		}
		else {
			ofs << '/' << '0' << m_expirydate.getmon();
		}

		if (m_expirydate.getday() > 9) {
			ofs << '/' << m_expirydate.getday();
		}
		else {
			ofs << '/' << '0' << m_expirydate.getday();
		}
		ofs << std::endl;
		return ofs;
	}

	std::ifstream& Perishable::load(std::ifstream& ifs) {
		setEmpty();
		Item::load(ifs);
		if (!this->m_error && !ifs.fail()) {
			Date expiry;
			ifs.get();
			expiry.read(ifs);

			if (expiry) {
				m_expirydate = expiry;
			}
			else {
				Error received(expiry.error());
				m_error = received;
				received.clear();
			}

		}


		return ifs;
	}

	std::ostream& operator<<(std::ostream& os, const Perishable& peri) {
		return peri.write(os);
	}

	std::ofstream& operator<<(std::ofstream& ofs, const Perishable& peri) {
		return peri.save(ofs);
	}


	std::istream& operator>>(std::istream& is, Perishable& peri) {
		return peri.read(is);
	}

	std::ifstream& operator>>(std::ifstream& ifs, Perishable& peri) {
		return peri.load(ifs);
	}

	void Perishable::setEmpty() {
		Item::setEmpty();
		m_expirydate.setEmpty();
	}

	Perishable::~Perishable() {
		Perishable::setEmpty();
	}
}
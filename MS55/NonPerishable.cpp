/* Citation and Sources...
Final Project Milestone 5
Module: NonPerishable
Filename: NonPerishable.cpp
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

#include <iostream>
#include <iomanip>
#include"POS.h"
#include "PosIO.h"
#include "NonPerishable.h"
#include "Error.h"

namespace sdds {

    char NonPerishable::getType() const {
        return 'N';
    }

    NonPerishable::~NonPerishable() {
        Item::setEmpty();
    }

    std::ostream& NonPerishable::write(std::ostream& os) const {
        Item::write(os);

        if (!this->m_error) {
            if (m_displayType == POS_LIST) {
                os << "     N / A   |";
            }
            else if (m_displayType == POS_FORM) {
                os << "=============^" << std::endl;
            }
        }

        return os;
    }


    std::ofstream& NonPerishable::save(std::ofstream& ofs) const {
        Item::save(ofs);
        ofs << std::endl;
        return ofs;
    }
}





// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iomanip>
#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string &str) {
    m_id = ++id_generator;
    Utilities utilities;
    size_t nextPos = 0;
    std::string buffer{};
    bool more = true;
    try {
        m_name = utilities.extractToken(str, nextPos, more);
        buffer = utilities.extractToken(str, nextPos, more);
        m_serialNum = stoul(buffer);
        buffer = utilities.extractToken(str, nextPos, more);
        m_numStock = stoul(buffer);
        if(m_widthField < utilities.getFieldWidth()){m_widthField = utilities.getFieldWidth();}
        m_description = utilities.extractToken(str, nextPos, more);
    }
    catch(const char*) {
        cerr << "operation failed";
    }
}

const std::string& Station::getItemName() const {
    return m_name;
}

size_t Station::getNextSerialNumber() {
    return m_serialNum++;
}

size_t Station::getQuantity() const {
    return m_numStock;
}

void Station::updateQuantity() {
    if(m_numStock > 0) {m_numStock--;}
}

void Station::display(std::ostream &os, bool full) const {
    os << setw(3) << setfill('0') << m_id << setfill(' ') << " | " << setw(int(m_widthField)) << left << m_name << " | " << setw(6) << setfill('0') << right << m_serialNum << setfill(' ') << " | ";
    if(full) {
        os << setw(4) << m_numStock << " | " << m_description;
    }
    os << endl;
}
}



#include "Utilities.h"
#include "Station.h"
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	Station::Station(const std::string& str) {
		Utilities util;
		size_t next_pos = 0;
		bool more = true;
		m_id = ++id_generator;
		try {
			m_name = util.extractToken(str, next_pos, more);
			m_serialNumber = stoi(util.extractToken(str, next_pos, more));
			m_stock = stoi(util.extractToken(str, next_pos, more));
			if (util.getFieldWidth() > m_widthField) {
				m_widthField = util.getFieldWidth();
			}
			m_desc = util.extractToken(str, next_pos, more);
		}
		catch (const char*) {
			cerr << "ERROR";
		}
	}

	void Station::updateQuantity() {
		if (m_stock > 0) {
			m_stock--;
		}
	}

	const std::string& Station::getItemName() const {
		return m_name;
	}

	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		return m_stock;
	}

	void Station::display(std::ostream& os, bool full) const {
		os << right << setw(3) << setfill('0') << m_id << " | "
			<< left << setw(m_widthField) << setfill(' ') << m_name
			<< " | " << right << setw(6) << setfill('0') << m_serialNumber << " | ";

		if (full) {
			os << right << setw(4) << setfill(' ') << m_stock << " | " << left << m_desc;
		}

		os << endl;
	}
}
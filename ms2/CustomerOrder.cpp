#include <string>
#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(){
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}
	CustomerOrder::CustomerOrder(const std::string& str) : CustomerOrder() {
		Utilities util;
		size_t next_pos = 0;
		bool more = true;
		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);
		while(more){
			Item** tempItem = new Item*[m_cntItem + 1];
			for (size_t i = 0; i < m_cntItem; ++i) {
				tempItem[i] = new Item(*m_lstItem[i]);
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			tempItem[m_cntItem++] = new Item(util.extractToken(str, next_pos, more));
			m_lstItem = tempItem;
		}
		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept{
		if (this != &other) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_cntItem = other.m_cntItem;
			m_name = other.m_name;
			m_product = other.m_product;

			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& other){
		throw "Copy Constructor is not allowed";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept : CustomerOrder(){
		*this = move(other);
	}

	CustomerOrder::~CustomerOrder(){
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const{
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				result = false;
			}
		}
		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const{
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					result = false;
				}
				else {
					result = true;
				}
			}
		}
		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os){
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0) {
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					station.updateQuantity();

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				i = m_cntItem;
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << setw(6) << setfill('0') << left << m_lstItem[i]->m_serialNumber << "]" << setfill(' ')
				<< " " << setw(int(m_widthField)) << m_lstItem[i]->m_itemName << " - ";
			if (isItemFilled(m_lstItem[i]->m_itemName)) {
				os << "FILLED";
			}
			else {
				os << "TO BE FILLED";
			}
			os << endl;
		}
	}

}
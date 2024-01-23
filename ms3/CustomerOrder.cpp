// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "CustomerOrder.h"
using namespace std;
namespace sdds {

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {
    m_name = "";
    m_product = "";
    m_cntItem = 0;
    m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(const std::string& str) : CustomerOrder() {
    Utilities utilities;
    size_t nextPos = 0;
    string buffer{};
    bool more = false;
   
    try{
        m_name = utilities.extractToken(str, nextPos, more);
        m_product = utilities.extractToken(str, nextPos, more);
        while (more){
            buffer = utilities.extractToken(str, nextPos, more);
            Item** tempItem = new Item*[m_cntItem + 1];
            for(size_t i = 0; i < m_cntItem; i++) {
                tempItem[i] = new Item(*m_lstItem[i]);
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
            tempItem[m_cntItem++] = new Item(buffer);
            m_lstItem = tempItem;
        }
        if (utilities.getFieldWidth() > m_widthField){m_widthField = utilities.getFieldWidth();
        }
    }catch(const char*){
        cerr << "failed the extraction of a token";
    }
    
}

CustomerOrder::CustomerOrder(const CustomerOrder&) {
    throw "Copy construction is not allowed";
}

CustomerOrder::CustomerOrder(CustomerOrder&& source) noexcept : CustomerOrder() {
    *this = std::move(source);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& source) noexcept{
    if(this != &source){
        for (size_t i = 0; i < m_cntItem; i++){
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_cntItem = source.m_cntItem;
        m_name = source.m_name;
        m_product = source.m_product;
        m_lstItem = source.m_lstItem;
         
        source.m_cntItem = 0;
        source.m_lstItem = nullptr;
    }
    return *this;
}

CustomerOrder::~CustomerOrder() {
    for (size_t i = 0; i < m_cntItem; i++){
        delete m_lstItem[i];
    }
    delete[] m_lstItem;
}


bool CustomerOrder::isOrderFilled() const {
    bool result = true;
    for(size_t i = 0; i < m_cntItem; i++) {
        if(!m_lstItem[i]->m_isFilled) {
            result = false;
            i = m_cntItem;
        }
    }
    return result;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    bool result = true;
    for(size_t i = 0; i < m_cntItem; i++) {
        if(m_lstItem[i]->m_itemName == itemName) {
            if(!m_lstItem[i]->m_isFilled) {
                result = false;
                i = m_cntItem;
            }
            else {
                result = true;
            }
        }
    }
    return result;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    for(size_t i = 0; i < m_cntItem; i++) {
        if(m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
            if(station.getQuantity() > 0) {
                station.updateQuantity();
                m_lstItem[i]->m_isFilled = true;
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
                i = m_cntItem;
            }
            else {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
            }
            
        }
    }
}

void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << endl;
    for(size_t i = 0; i < m_cntItem; i++){
        os << "[" << setw(6) << setfill('0') << right << m_lstItem[i]->m_serialNumber << left << "]" << setfill(' ')
        << " " << setw(int(m_widthField)) << m_lstItem[i]->m_itemName << " - ";
        if(isItemFilled(m_lstItem[i]->m_itemName)){
            os << "FILLED";
        }else{
            os << "TO BE FILLED";
        }
        os << right << endl;
    }
   
}

}

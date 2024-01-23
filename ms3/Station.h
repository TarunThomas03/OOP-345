// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
namespace sdds {
class Station {
    size_t m_id;
    std::string m_name;
    std::string m_description;
    size_t m_serialNum;
    size_t m_numStock;
    static size_t m_widthField;
    static size_t id_generator;
public:
    Station(const std::string&);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
};
}

#endif /* Station_h */

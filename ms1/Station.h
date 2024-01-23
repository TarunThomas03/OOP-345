#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

namespace sdds
{
  class Station
  {
    int m_id            { 0 }; 
    std::string m_name  { "" }; 
    std::string m_desc  { "" }; 
    size_t m_serial_num { 0u }; 
    size_t m_curr_items { 0u }; 

    // Class Variables
    static size_t m_widthField;
    static size_t id_generator;

  public:
    Station(const std::string& src);
    const std::string &getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream &os, bool full) const;
  };
}
#endif // !SDDS_STATION_H
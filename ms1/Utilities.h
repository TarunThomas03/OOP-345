
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>

namespace sdds
{
  class Utilities
  {
    size_t m_widthField { 1u }; 
    // Class Variables
    static char m_delimiter;  
  public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

    // Class Functions
       static void setDelimiter(char newDelimiter);

       static char getDelimiter();
  };
}
#endif // !SDDS_UTILITIES_H
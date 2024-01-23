// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include "Utilities.h"
namespace sdds {
char Utilities::m_delimiter = 0;

void Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
    return m_widthField;
}

std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more) {
    std::string newStr{};
    if(str.find(m_delimiter, next_pos) !=  std::string::npos) {
        if(str.find(m_delimiter,next_pos) == next_pos) {
            more = false;
            throw "aboba";
        }
        newStr = str.substr(next_pos, str.substr(next_pos).find_first_of(m_delimiter));
        newStr = newStr.substr(newStr.find_first_not_of(" "), newStr.find_last_not_of(" ") - newStr.find_first_not_of(" ") + 1);
        next_pos = str.find(m_delimiter, next_pos) + 1;
        more = true;
        if(m_widthField < newStr.length()) {
            m_widthField = newStr.length();
        }
    }
    else {
        newStr = str.substr(next_pos, str.substr(next_pos).find_first_of(m_delimiter));
        newStr = newStr.substr(newStr.find_first_not_of(" "), newStr.find_last_not_of(" ") + 1);
        next_pos = str.find(m_delimiter, next_pos) + 1;
        more = false;
        if(m_widthField < newStr.length()) {
            m_widthField = newStr.length();
        }
    }
    return newStr;
}

void Utilities::setDelimiter(char newDelimiter) {
    m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() {
    return m_delimiter;
}
}




#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds {
    char Utilities::m_delimiter = 0;

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string newStr{};
        if (str.find(m_delimiter, next_pos) != std::string::npos) {
            if (str.find(m_delimiter, next_pos) == next_pos) {
                more = false;
                throw "Error";
            }
            newStr = str.substr(next_pos, str.substr(next_pos).find_first_of(m_delimiter));
            size_t start = newStr.find_first_not_of(" ");
            size_t end = newStr.find_last_not_of(" ");
            newStr = newStr.substr(start, end - start + 1);
            next_pos = str.find(m_delimiter, next_pos) + 1;
            more = true;
            if (m_widthField < newStr.length()) {
                m_widthField = newStr.length();
            }
        }
        else {
            newStr = str.substr(next_pos, str.substr(next_pos).find_first_of(m_delimiter));
            size_t start = newStr.find_first_not_of(" ");
            size_t end = newStr.find_last_not_of(" ");
            newStr = newStr.substr(start, end - start + 1);
            next_pos = str.find(m_delimiter, next_pos) + 1;
            more = false;
            if (m_widthField < newStr.length()) {
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
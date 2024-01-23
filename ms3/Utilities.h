// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
namespace sdds {
class Utilities {
    size_t m_widthField = 1;
    static char m_delimiter;
public:
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    static void setDelimiter(char newDelimiter);
    static char getDelimiter();
};
}

#endif /* Utilities_h */

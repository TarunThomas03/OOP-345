#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <vector>
namespace sdds{

struct Covid{
    std::string m_country;
    std::string m_city;
    std::string m_variant;
    std::string m_status = "General";
    int m_year;
    unsigned m_numOfCases;
    unsigned m_numOfDeaths;
};

class CovidCollection {
    std::vector<Covid> m_collection;
public:
    CovidCollection(const std::string filename);
    void display(std::ostream& out, const std::string& country = "ALL") const;
    
    //part 2
    void sort(const std::string& field = "country");
    bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
    std::list<Covid> getListForDeaths(unsigned int deaths) const;
    void updateStatus();
    
};

std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

}

#endif /* CovidCollection_hpp */
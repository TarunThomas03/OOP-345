#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <list>
#include "CovidCollection.h"

using namespace std;

namespace sdds{

CovidCollection::CovidCollection(const std::string filename) {
    fstream file(filename);
    if(file.is_open()){
        Covid covid;
        string buffer;
        while (std::getline(file, buffer)){
                       
            covid.m_country = buffer.substr(0, 25);
            covid.m_city =  buffer.substr(25, 25);
            covid.m_variant = buffer.substr(50, 25);;
            covid.m_year = stod(buffer.substr(75, 5));
            covid.m_numOfCases = stoi(buffer.substr(80, 5));
            covid.m_numOfDeaths = stoi(buffer.substr(85, 5));
            
            covid.m_country = covid.m_country.erase(covid.m_country.find_last_not_of(' ') + 1);
            covid.m_city = covid.m_city.erase(covid.m_city.find_last_not_of(' ') + 1);
            covid.m_variant = covid.m_variant.erase(covid.m_variant.find_last_not_of(' ') + 1);
            
            if (covid.m_year < 2000 || covid.m_year > 2100) {covid.m_year = -1;}
            
            m_collection.push_back(covid);
            
        }
        
        
       
    }else{
        throw "bad file name";
    }
    
    file.close();
}

void CovidCollection::display(std::ostream &out, const std::string& country) const {
    size_t totalCases = 0, totalDeaths = 0, worldDeaths = 0, worldCases = 0;
    if (country == "ALL"){
        for_each(m_collection.begin(), m_collection.end(), [&](Covid item){out << item << endl; totalCases += item.m_numOfCases; totalDeaths += item.m_numOfDeaths;
        });
        
        out << "| " << setw(79) << right << "Total cases around the world: " << left << totalCases << " |" << endl;
        out << "| " << setw(79) << right << "Total deaths around the world: " << left << totalDeaths << " |" << endl;
        out << right;
    }else{
        
        out << "Displaying information of country = " << country << endl;
        for_each(m_collection.begin(), m_collection.end(), [&](Covid item){if(item.m_country == country){ out << item << endl; totalCases += item.m_numOfCases; totalDeaths += item.m_numOfDeaths;} worldDeaths += item.m_numOfDeaths; worldCases += item.m_numOfCases;});
        out << "----------------------------------------------------------------------------------------" << endl;
        out << "| " << setw(80) << right << "Total cases in " + country + ": " << totalCases << " |" << endl;
        out << "| " << setw(80) << right << "Total deaths in " + country + ": " << totalDeaths << " |" << endl;
       
        string buffer =  country + " has ";
        buffer += to_string(((double(totalCases) / double(worldCases)) * 100));
        buffer += "% of global cases and ";
        buffer += to_string((double(totalDeaths) / double(worldDeaths) * 100));
        buffer += "% of global deaths";
        out << "| " << setw(84) << right << buffer;
        out << " |" << endl;
        
    }
    
}


void CovidCollection::sort(const std::string &field) { 
    std::sort(m_collection.begin(), m_collection.end(), [&](const Covid& a, const Covid& b){
        if (field == "country") {
            if (a.m_country != b.m_country) {
                return a.m_country < b.m_country;
            }
        } else if (field == "city") {
            if (a.m_city != b.m_city) {
                return a.m_city < b.m_city;
            }
        } else if (field == "variant") {
            if (a.m_variant != b.m_variant) {
                return a.m_variant < b.m_variant;
            }
        } else if (field == "year") {
            if (a.m_year != b.m_year) {
                return a.m_year < b.m_year;
            }
        } else if (field == "cases") {
            if (a.m_numOfCases != b.m_numOfCases) {
                return a.m_numOfCases < b.m_numOfCases;
            }
        }
        return a.m_numOfDeaths < b.m_numOfDeaths;
    });
}

bool CovidCollection::inCollection(const std::string &variant, const std::string &country, unsigned int deaths) const { 
        
    auto it = std::find_if(m_collection.begin(), m_collection.end(), [&](const Covid& item){
        return item.m_country == country && item.m_variant == variant && item.m_numOfDeaths > deaths;
    });
    
    return it != m_collection.end();
    
}

std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
    std::list<Covid> result;
    
    std::copy_if(m_collection.begin(), m_collection.end(), back_inserter(result), [&](const Covid& item){
        return item.m_numOfDeaths >= deaths; });
    
    return result;
}

void CovidCollection::updateStatus() { 
    std::for_each(m_collection.begin(), m_collection.end(), [](Covid& item){
        if(item.m_numOfDeaths > 300){
            item.m_status = "EPIDEMIC";
        }else if (item.m_numOfDeaths < 50){
            item.m_status = "EARLY";
        }else {
            item.m_status = "MILD";
        }
    });
}


std::ostream& operator<<(std::ostream& out, const Covid& theCovid){
    
    out << left << "| " << setw(21) << theCovid.m_country << " | " << setw(15) << theCovid.m_city << " | " << setw(20) << theCovid.m_variant << right << " | ";
    if (theCovid.m_year == -1) {out << "      ";} else {out << setw(6) << theCovid.m_year;}
    out << " | " << setw(4) << theCovid.m_numOfCases << " | " << setw(3) << theCovid.m_numOfDeaths << " | | " << setw(8) << right << theCovid.m_status << " |";
    return out;
}

}
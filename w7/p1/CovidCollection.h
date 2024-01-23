#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <vector>

namespace sdds
{
	struct Covid {
		std::string m_country;	
		std::string m_city;		
		std::string m_variant;	
		int m_year;				
		size_t m_numCase;		
		size_t m_numDeath;		
	};

	class CovidCollection {
		std::vector<Covid> m_collection{};	
	public:
		CovidCollection(const char* fileName);

		void display(std::ostream& out) const;
	};

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif 
// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include "Workstation.h"
namespace sdds {
class LineManager {
    std::vector<Workstation*> m_activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
public:
    LineManager(const std::string& file, const std::vector<Workstation*>& stations);
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};

}

#endif /* LineManager_h */

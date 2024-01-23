// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds {
class Workstation : public Station {
    std::deque<CustomerOrder> m_orders;
    Workstation* m_pNextStation = nullptr;
public:
    Workstation(const std::string&);
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* station = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    Workstation& operator+=(CustomerOrder&& newOrder);
    Workstation(const Workstation& source) = delete;
    Workstation& operator=(const Workstation& source) = delete;
    Workstation(Workstation&& source) = delete;
    Workstation& operator=(Workstation&& source) = delete;
};

extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

}

#endif /* Workstation_h */

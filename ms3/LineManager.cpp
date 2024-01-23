// Name: Tarun Thomas
// Seneca Student ID: 113605224
// Seneca email: tthomas60@myseneca.ca
// Date of completion: 1/12/2023
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "LineManager.h"
using namespace std;
namespace sdds {
LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
    std::fstream f;
    f.open(file);
    if(f) {
        std::string buffer{};
        while(getline(f, buffer)) {
            if (buffer.find('|') != std::string::npos) {
                std::string station, next;
                station = buffer.substr(0, buffer.find('|'));
                next = buffer.substr(buffer.find('|') + 1);
                
                auto it = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                    return ws->getItemName() == station;
                });
                if (it != stations.end()) {
                    m_activeLine.push_back(*it);
                }
                
                auto nextIt = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                    return ws->getItemName() == next;
                });
                if (nextIt != stations.end()) {
                    m_activeLine.back()->setNextStation(*nextIt);
                }
            }
            else {
                auto it = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                    return ws->getItemName() == buffer;
                });
                if (it != stations.end()) {
                    m_activeLine.push_back(*it);
                }
            }
            
            auto firstIt = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                return std::none_of(stations.begin(), stations.end(), [&](Workstation* otherWs) {
                    return otherWs != ws && otherWs->getNextStation() == ws;
                });
            });

            if (firstIt != stations.end()) {
                m_firstStation = *firstIt;
            }
            
            m_cntCustomerOrder = g_pending.size();
        }
    }
    else {
        std::cerr << "Cannot open file";
    }
}

void LineManager::reorderStations() {
    std::sort(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1, Workstation* ws2) {
            int d1 = 0, d2 = 0;
            Workstation* currentStation = m_firstStation;
            while(currentStation != ws1) {
                currentStation = currentStation->getNextStation();
                ++d1;
            }
            currentStation = m_firstStation;
            while(currentStation != ws2) {
                currentStation = currentStation->getNextStation();
                ++d2;
            }
            return d1 < d2;
        });
}

bool LineManager::run(std::ostream &os) {
    static size_t cnt = 0;
    ++cnt;
    bool result = false, buffer = false;
    os << "Line Manager Iteration: " << cnt << endl;
    if(!g_pending.empty()) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
        if(station) {
            station->fill(os);
        }
    });
    for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) {
        if(station) {
            buffer = station->attemptToMoveOrder();
            if(!buffer) {
                result = false;
            }
        }
    });
    if(g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
        result = true;
    }
    return result;
}

void LineManager::display(std::ostream &os) const {
    for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station){
        station->display(os);
    });
}
}

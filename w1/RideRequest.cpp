#include <cstring>
#include <iostream>
#include <iomanip>
#include "RideRequest.h"

using namespace std;

namespace sdds 
{
    float g_taxrate = 0;
    float g_discount = 0;

    //Default Constructor: 
    RideRequest::RideRequest()
    {
        m_name[0] = '\0';
        m_rideInfo = nullptr;
        m_priceRide = 0.0;
        m_discount = false;
        
    }

    //Rule of three:
    RideRequest::~RideRequest()
    {
        delete[] m_rideInfo;
    }

    RideRequest::RideRequest(const RideRequest& request)
    {
        m_rideInfo = nullptr;
        if(this != &request)
        {
            m_rideInfo = new char [strlen(request.m_rideInfo)+1];
            strcpy(m_rideInfo,request.m_rideInfo);
            strcpy(m_name,request.m_name);
            m_priceRide = request.m_priceRide;
            m_discount = request.m_discount;
        }
    }

   RideRequest& RideRequest::operator=(const RideRequest& request)
   {
        if(this != &request)
        {
            delete[] m_rideInfo;
            m_rideInfo = nullptr;
            strcpy(m_name, request.m_name);

            if(request.m_rideInfo)
            {
                m_rideInfo = new char[strlen(request.m_rideInfo) + 1];
                strcpy(m_rideInfo, request.m_rideInfo);
            }

            m_priceRide = request.m_priceRide;
            m_discount = request.m_discount;

        }
        return *this;
   }

    //This function will attempt to read from the istream and store the information read into the current object.
    void RideRequest::read(std::istream& is)
    {
        char discountStatus = '\0';

        //temp varibles:
        char t_rideInfo[1000];

        if(m_rideInfo)
        {
            delete[] m_rideInfo;
            m_rideInfo = nullptr;
        }

        if (is)
        {
            is.getline(m_name, 11, ',');

            //Reading the input for the rideInfo
            is.getline(t_rideInfo, 1000, ',');
            m_rideInfo = new char [strlen(t_rideInfo)+1];
            strcpy(m_rideInfo,t_rideInfo);

            is >> m_priceRide;
            is.ignore();
            is.get(discountStatus);

            if (discountStatus == 'Y')
            {
                m_discount = true;
            }      
            else
            {
                m_discount = false;
            }
            is.ignore();    
        }
    }

    //A query that displays to the screen the content of an Ride Request instance:
    void  RideRequest::display() const
    {
        static int counter = 1;

        //Calculating the price with tax:
        float priceWTax = m_priceRide * (1 + g_taxrate);
        float priceWDiscount = priceWTax - g_discount;

        if (m_name[0] != '\0') 
        {
            cout << setw(2) << left << counter++ << ". "
                << setw(10) << left << m_name << "|"
                << setw(25) << left << m_rideInfo << "|"
                << setw(12) << fixed << setprecision(2) << priceWTax << "|";

            if(m_discount)
            {
                
                cout << setw(13) << right << priceWDiscount;   
            }
        }
        else
        {
            cout << setw(2) << left << counter++ << ". No Ride Request";
        }
	cout << endl;
    }
}
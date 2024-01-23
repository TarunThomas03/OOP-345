#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>
#include <cstring>

namespace sdds
{
    //Global variables :
    extern float g_taxrate;
    extern float g_discount;

    class RideRequest
    {
        //Store info variables:
        char m_name[11];
        char* m_rideInfo;
        float m_priceRide;
        bool m_discount;

    public:

        //Default Constructor: 
        RideRequest();

        //Rule of three:
        ~RideRequest();
        RideRequest(const RideRequest& request);
        RideRequest& operator=(const RideRequest& request);

        //This function will attempt to read from the istream and store the information read into the current object.
        void read(std::istream& is);

        //A query that displays to the screen the content of an Ride Request instance:
        void display() const;

    };
    
}   

#endif
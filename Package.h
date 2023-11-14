class Package {
private:
    FlightTicket *singleFlightTicket;
    vector<FlightTicket> flightTickets;
    HotelVoucher *singleHotelVoucher;
    vector<HotelVoucher> hotelVouchers;
    EventTicket *singleEventTicket;
    vector<EventTicket> eventTickets;
    double packageCost = 0.0;
    double ticketComissions = 0.0;
    bool calculated = false;
    bool events[NUMBEROFEVENTS];

public:
    Package() {
        for (int i = 0; i < NUMBEROFEVENTS; i++)
            events[i] = false;
    }

    double getpackageCost() {
        return packageCost;
    }

    double getTicketComissions() {
        return ticketComissions;
    }

    void addFlightTicket(int ft, int d) {
        singleFlightTicket = new FlightTicket(ft, d);
        flightTickets.push_back(*singleFlightTicket);
    }

    void addHotelVoucher(int ht, int d) {
        singleHotelVoucher = new HotelVoucher(ht, d);
        hotelVouchers.push_back(*singleHotelVoucher);
    }

    void addEventTicket(int e) { 
        singleEventTicket = new EventTicket(e);
        eventTickets.push_back(*singleEventTicket);
        events[e] = true;
    }
    void printPackage() {
        for (int i = 0; i < 2; i++)
		    flightTickets[i].printTicket();
        for (int i = 0; i < hotelVouchers.size(); i++)
		    hotelVouchers[i].printTicket();
        for (int i = 0; i < eventTickets.size(); i++)
		    eventTickets[i].printTicket();

        if (validatePackage() == true)
        {
            if (calculated == false)
            {
                calculatePackageCost();
                cout << "Total cost of the package is $" << packageCost << endl;
            }
            else
            {
                cout << "Total cost of the package is $" << packageCost << endl;
                calculated = true;
            }
            cout << "The package is valid." << endl;
        }
        else
        {
            if (calculated == false)
            {
                calculatePackageCost();
                cout << "Total cost of the package is $" << packageCost << endl;
            }
            else
            {
                cout << "Total cost of the package is $" << packageCost << endl;
                calculated = true;
            }
            cout << "The package is invalid." << endl;

        }
    }

    // Validation of package
    bool validatePackage() {
        if (flightTickets[0].getDay() > flightTickets[1].getDay())
            return false;
        
        if (hotelVouchers.size() != (flightTickets[1].getDay() - flightTickets[0].getDay()))
            return false;

        for (int i = 0; i < eventTickets.size(); i++)
            if (eventTickets[i].getDay() < flightTickets[0].getDay() || eventTickets[i].getDay() > flightTickets[1].getDay())
                return false;
        

        return true;
    }

    // Other functionalites
    void calculatePackageCost() {
        calculated = true;
        for (int i = 0; i < 2; i++)
        {
            packageCost += flightTickets[i].getTicketPrice();
            ticketComissions += (flightTickets[i].getTicketPrice() * 0.05); // get 5% profit from air tickets
        }

        for (int i = 0; i < hotelVouchers.size(); i++)
        {
            if (hotelVouchers[i].gethotelType() == 3)
		        packageCost += hotelPriceMap[0];
            if (hotelVouchers[i].gethotelType() == 4)
                packageCost += hotelPriceMap[1];
            if (hotelVouchers[i].gethotelType() == 5)
                packageCost += hotelPriceMap[2];
        }

        for (int i = 0; i < NUMBEROFEVENTS; i++)
        {
            if (events[i] == true)
		    packageCost += eventPriceMap[i];    
        }
    }

};
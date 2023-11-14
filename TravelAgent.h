class TravelAgent {
private:
    ClientRequest singleClientRequest;
    vector<ClientRequest> clientRequests;
    Package package[MAXREQUESTS];

    int hotelQuotas[9][3];
    int eventQuotas[15];

    int totalPackages = 0;
    int totalProfit = 0;
    int totalFlyOut[10];
    int totalFlyIn[10];
    int total3Star[9];
    int total4Star[9];
    int total5Star[9];
    int totalEvents[15];

    int clientNo = 0;
    int eventNo;
    string line;
    double travelAgentCommission[MAXREQUESTS];
    vector<double> profits;
    double profit;

public:
    TravelAgent() {
        for (int i = 0; i < MAXREQUESTS; i++)
            travelAgentCommission[i] = 0;
            
        for (int i = 0; i < 3; i++)
        {
            for ( int j = 0; j < 9; j++)
             hotelQuotas[j][i] = 0;
        }

        for (int i = 0; i < 15; i++)
        {
            totalEvents[i] = 0;
            eventQuotas[i] = 0;
        }   

        for (int i = 0; i < 10; i++)
        {
            totalFlyOut[i] = 0;
            totalFlyIn[i] = 0;
        }

        for (int i= 0; i < 9; i++)
        {
            total3Star[i] = 0;
            total4Star[i] = 0;
            total5Star[i] = 0;
        }
    }

    // Read client requests and save them into an array or vector of ClientRequest(in objects or pointers)
    void readClientRequests() {
        ifstream readFile;

        // Exception for failing to read file
        if (readFile.fail())
        {
            cout << "File opening failed.\n";
            exit(1);
        }

        readFile.open("requestlist.txt");

         while (!readFile.eof())
        {
            singleClientRequest.cId = clientNo;
            readFile >> singleClientRequest.budget;
            readFile.ignore();
            readFile >> singleClientRequest.hotelType;
            readFile.ignore();

            getline(readFile, line, ']');
            istringstream iss(line);
            for (int i = 0; i <= line.length(); i++)
            {
                iss >> eventNo;
                iss.ignore();
                singleClientRequest.events[eventNo] = true;
            }
            
            clientRequests.push_back(singleClientRequest);
            clientNo++;

            for (int i = 0; i < NUMBEROFEVENTS; i++)
                singleClientRequest.events[i] = false;
        }
        clientRequests.pop_back();
        clientNo--;
        readFile.close();

        cout << setw(8) << "Client No" << setw(8) << "budget" << setw(8) << "hotel"
			<< setw(8) << "events" << endl;
            
        for (int i = 0; i < clientRequests.size(); i++)
        {
            clientRequests[i].print();
        }

        cout << "Total client requests: " << clientNo << endl;
        cout << endl;
    }

    // Generate packages from request
    void generatePackages() {
        cout << "Generating packages... " << endl;

        for (int i = 0; i < clientRequests.size(); i++)
        {
            package[i].addFlightTicket(0, clientRequests[i].earliestEventDay());
            package[i].addFlightTicket(1, clientRequests[i].latestEventDay());

            for (int j = clientRequests[i].earliestEventDay(); j < clientRequests[i].latestEventDay(); j++)
            {
                package[i].addHotelVoucher(clientRequests[i].hotelType, j);
                if (clientRequests[i].hotelType == 3)       // add hotelQuotas before validation
                    hotelQuotas[j][0] += 1;
                else if (clientRequests[i].hotelType == 4)
                    hotelQuotas[j][1] += 1;
                else if (clientRequests[i].hotelType == 5)
                    hotelQuotas[j][2] += 1;
            }

            for (int j = 0; j < NUMBEROFEVENTS; j++)
            {
                if (clientRequests[i].events[j] == true)
                {
                    package[i].addEventTicket(j);
                    eventQuotas[j] += 1;                  // add eventQuotas before validation
                    travelAgentCommission[i] += (eventPriceMap[j] * 0.1);
                }   
            }

            package[i].calculatePackageCost();
            travelAgentCommission[i] += (package[i].getTicketComissions()); // get air ticket profit from package class
            // Check hotel quotas for discounts and add commission based on discounts or normal price
            for (int j = clientRequests[i].earliestEventDay(); j < clientRequests[i].latestEventDay(); j++)
            {
                if (clientRequests[i].hotelType == 4)
                {   
                    if (hotelQuotas[j][1] > (hotelQuota[1] * 0.5) )
                        travelAgentCommission[i] += ((210 - (210 * 0.2)) * 0.05);
                    else
                        travelAgentCommission[i] += (210 * 0.05);

                }
                else if (clientRequests[i].hotelType == 5)
                {   
                    if (hotelQuotas[j][2] > (hotelQuota[2] * 0.2) && hotelQuotas[j][2] <= (hotelQuota[2] * 0.5))
                        travelAgentCommission[i] += ((320 - (320 * 0.2)) * 0.05);
                    else if (hotelQuotas[j][2] > (hotelQuota[2] * 0.5))
                        travelAgentCommission[i] += ((320 - (320 * 0.4)) * 0.05);
                    else
                        travelAgentCommission[i] += (320 * 0.05);
                }
            }
            
            // properly validate package that includes budget and quotas validation
            if (package[i].validatePackage() == true && (clientRequests[i].budget > package[i].getpackageCost()) && validateQuotas() == true)
            {
                cout << "Client " << clientRequests[i].cId << ": Package generated successfully - Budget = $" << clientRequests[i].budget << ", PackageCost = $ " << package[i].getpackageCost() << endl; 
                totalPackages += 1;
                totalFlyOut[clientRequests[i].earliestEventDay()] += 1;
                totalFlyIn[clientRequests[i].latestEventDay()] += 1;

                for (int j = clientRequests[i].earliestEventDay(); j < clientRequests[i].latestEventDay(); j++)
                {
                    if (clientRequests[i].hotelType == 3)       // add total for summary
                        total3Star[j] += 1;
                    else if (clientRequests[i].hotelType == 4)
                        total4Star[j] += 1;
                    else if (clientRequests[i].hotelType == 5)
                        total5Star[j] += 1;
                }

                for (int j = 0; j < NUMBEROFEVENTS; j++)
                    if (clientRequests[i].events[j] == true)
                        totalEvents[j] += 1;
            }
            else
            {
                cout << "Client " << clientRequests[i].cId << ": Not a sufficient budget or resources for this request." << endl;
                clientRequests[i].cId = -1;
                for (int j = clientRequests[i].earliestEventDay(); j < clientRequests[i].latestEventDay(); j++)
                {
                    if (clientRequests[i].hotelType == 3)           // decrement hotel and event quotas if not valid
                        hotelQuotas[j][0] -= 1;
                    else if (clientRequests[i].hotelType == 4)
                        hotelQuotas[j][1] -= 1;
                    else if (clientRequests[i].hotelType == 5)
                        hotelQuotas[j][2] -= 1;
                }
                
                for (int j = 0; j < NUMBEROFEVENTS; j++)
                    if (clientRequests[i].events[j] == true)
                        eventQuotas[j] -= 1; 

            }

        }
    }

    // Output to files, feasible packages and rejected requests
    void outputFiles() {
        ofstream outputFileRejected("rejectedrequests.txt");
        ofstream outputFileFeasible("feasiblerequests.txt");
        for (int i = 0; i < clientNo; i++)
        {
            if (clientRequests[i].cId == -1)
            {
                outputFileRejected << clientRequests[i].budget << "," << clientRequests[i].hotelType << "[";

                for (int j = 0; j < NUMBEROFEVENTS; j++)
                {
                    if (clientRequests[i].events[j] == true)
                    {
                        eventNo = j;
                        outputFileRejected << eventNo;
                        outputFileRejected << ",";
                    }
                }
                outputFileRejected << "]" << endl;
            }   
            else
            {
                outputFileFeasible << clientRequests[i].budget << "," << clientRequests[i].hotelType << "[";

                for (int j = 0; j < NUMBEROFEVENTS; j++)
                {
                    if (clientRequests[i].events[j] == true)
                    {
                        eventNo = j;
                        outputFileFeasible << eventNo;
                        outputFileFeasible <<",";
                    }
                }
                outputFileFeasible << "]" << endl;
            }
        }
        outputFileRejected.close();
        outputFileFeasible.close();
    }

    // validate quotas
    bool validateQuotas() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 9; j++)
                if (hotelQuotas[j][i] == hotelQuota[i])
                    return false;
        

        for (int i = 0; i < NUMBEROFEVENTS; i++)
            if (eventQuotas[i] == eventQuota[i])
                return false;

        return true;
    }

    // Print succesful packages and summary
    void printSuccessfulPackages() {
        outputFiles();
        for (int i = 0; i < clientNo; i++)
        {
            if (clientRequests[i].cId != -1)
            {
                cout << "Client " << i << ": " << "The package contains: " << endl;
                package[i].printPackage();

                // calculate profit
                profit += travelAgentCommission[i];
                profits.push_back(profit);

                cout << "Total profit of the package is $" << profits.back() << endl;
                totalProfit += profits.back();
                profit = 0;
                cout << endl;
            }
        }
        cout << endl;

        cout << "Summary of packages:" << endl
             << "Total packages generated: " << totalPackages << endl << endl;

        cout << "Total fly-out tickets (to Paris) for each day booked: " << endl;
        for (int i = 0; i < 10; i++)
            cout << totalFlyOut[i] << "  ";
        cout << endl
             << "Total fly-in tickets (to Sydney) for each day booked:" << endl;
        for (int i = 0; i < 10; i++)
            cout << totalFlyIn[i] << "  ";
        cout << endl << endl;

        cout << "Total hotel vouchers for each day sold: " << endl
             << "3 star hotel rooms" << endl;
        for (int i = 0; i < 9; i++)
            cout << total3Star[i] << "  ";
        cout << endl;
        cout << "4 star hotel rooms" << endl;
        for (int i = 0; i < 9; i++)
            cout << total4Star[i] << "  ";
        cout << endl;
        cout << "5 star hotel rooms" << endl;
        for (int i = 0; i < 9; i++)
            cout << total5Star[i] << "  ";
        cout << endl << endl;

        cout << "Total event tickets for each event sold: " << endl;
        for (int i = 0; i < 15; i++)
            cout << totalEvents[i] << "  ";
        cout << endl << endl;

        cout << "Total profit: $" << totalProfit << endl;
    }

};
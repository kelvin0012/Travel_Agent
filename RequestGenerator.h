class RequestGenerator {
private:
    int noOfClientRequests;
    int hotelType;
    vector<int> hotelTypes;
    int noOfEvents;
    int event;
    vector<int> events;
    int budget;
public:
    void generateClientRequests() {
        srand(time(NULL));
        noOfClientRequests = rand() % 50 + 100;
        ofstream outputFile("clientrequestslist.txt");
        
        for (int i = 0; i < noOfClientRequests; i++)
        {
            hotelType = rand() % 3 + 3;
            noOfEvents = rand() % 10 + 1;
            for (int j = 0; j < noOfEvents; j++)
            {
                event = rand() % 15;
                for (int k = 0; k < events.size(); k++)
                {
                    while (event == events[k])
                    {
                        event = rand() % 15;
                    }
                }
                events.push_back(event);
            }

            for (int j = 0; j < events.size(); j++)
            {
                if (events[j] == 0)
                {
                    budget = rand() % ((7500+(150*noOfEvents)) - (4500+(150*noOfEvents))) + (4500+(150*noOfEvents));
                    break;
                }
                else if (events[j] == 9)
                {
                    budget = rand() % ((6800+(150*noOfEvents)) - (3800+(150*noOfEvents))) + (3800+(150*noOfEvents));
                    break;
                }
                else 
                    budget = rand() % ((5250+(150*noOfEvents)) - (3250+(150*noOfEvents))) + (3250+(150*noOfEvents));
            }
            outputFile << budget << "," << hotelType << "," << "[";

            for (int j = 0; j < events.size(); j++)
            {
                outputFile << events[j];
                if (j == events.size()-1)
                    outputFile << "]" << endl;
                else
                    outputFile << ",";
            }
            events.clear();
        }
        outputFile.close();

    }
};
class EventTicket : public Ticket {// an object of this class represents a single event ticket
private:
	int eventid;

public:
	EventTicket(int e) : Ticket(eventDayMap[e], 2000){
		eventid = e;
	}

	string getEventName() {
		return nameMap[eventid];
	}

	void printTicket() {
		cout << "Event ticket for " << getEventName() << " on day " << eventDayMap[eventid] << " at price $" << eventPriceMap[eventid] << endl;
	}

};

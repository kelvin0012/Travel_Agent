
#ifndef CLIENTREQUEST_H_
#define CLIENTREQUEST_H_

class ClientRequest {
public:
	int cId;
	int hotelType;
	bool events[NUMBEROFEVENTS];
	int budget;
	ClientRequest() {
		cId = -1;
		hotelType = -1;
		budget = -1;
		for (int i = 0; i < NUMBEROFEVENTS; i++)
			events[i] = false;
	}

	int earliestEventDay() {
		int flyin = 9;
		for (int i = 0; i < NUMBEROFEVENTS; i++) {
			if (events[i] && eventDayMap[i] < flyin)
				flyin = eventDayMap[i];
		}
		return flyin;
	}

	int latestEventDay() {
		int flyout = 0;
		for (int i = 0; i < NUMBEROFEVENTS; i++)
		{
			if (events[i] && eventDayMap[i] > flyout)
				flyout = eventDayMap[i];
		}
		return flyout;
	}

	void print() {
		cout << setw(8) << cId << ":" << setw(8) << budget << setw(8)
				<< hotelType << setw(8);

		for (int i = 0; i < NUMBEROFEVENTS; i++) {
			if (events[i]) {
				cout << i;
				if (i < NUMBEROFEVENTS - 1)
					cout << ",";
			}
		}

		cout << endl;
	}
};

#endif /* CLIENTREQUEST_H_ */

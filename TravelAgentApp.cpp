
#ifndef TRAVELAGENT_CPP_
#define TRAVELAGENT_CPP_

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>

using namespace std;

#include "Constants.h"
#include "ClientRequest.h"
#include "Ticket.h"
#include "FlightTicket.h"
#include "HotelVoucher.h"
#include "EventTicket.h"
#include "Package.h"
#include "TravelAgent.h"
#include "RequestGenerator.h"

void clientRequestTest() {
	cout << "Test ClientRequest class ... " << endl;

	ClientRequest requestList[2];
	requestList[0].cId = 0;
	requestList[0].budget = 9020;
	requestList[0].hotelType = 5;
	requestList[0].events[14] = true;
	requestList[0].events[2] = true;
	requestList[0].events[7] = true;

	requestList[1].cId = 1;
	requestList[1].budget = 7805;
	requestList[1].hotelType = 3;
	requestList[1].events[0] = true;
	requestList[1].events[4] = true;
	requestList[1].events[10] = true;
	requestList[1].events[9] = true;
	requestList[1].events[3] = true;

	cout << "* Test data ..." << endl;
	cout << setw(8) << "Client No" << setw(8) << "budget" << setw(8) << "hotel"
			<< setw(8) << "events" << endl;

	for (int i = 0; i < 2; i++)
		requestList[i].print();

	cout << "\n* Test functions (an example)..." << endl;
	cout << "  - Earliest event day: " << requestList[0].earliestEventDay()
			<< endl;
	cout << "  - Latest event day: " << requestList[0].latestEventDay() << endl;
}

void flightTicketTest() {
	cout << "Test FlightTicket class ... " << endl;

	FlightTicket *tickets[2];
	tickets[0] = new FlightTicket(0, 1);
	tickets[1] = new FlightTicket(1, 7);

	for (int i = 0; i < 2; i++)
		tickets[i]->printTicket();

}

void hotelVoucherTest() {
	cout << "Test HotelVoucher class ... " << endl;
	
	HotelVoucher *tickets[3];
	tickets[0] = new HotelVoucher(3,1);
	tickets[1] = new HotelVoucher(4,5);
	tickets[2] = new HotelVoucher(5,7);

	for (int i = 0; i < 3; i++)
		tickets[i]->printTicket();

}

void eventTicketTest() {
	cout << "Test EventTicket class ... " << endl;

	EventTicket *tickets[3];
	tickets[0] = new EventTicket(2);
	tickets[1] = new EventTicket(5);
	tickets[2] = new EventTicket(14);


	for (int i = 0; i < 3; i++)
		tickets[i]->printTicket();

}

void requestGeneratorTest() {
	RequestGenerator rg;
	rg.generateClientRequests();
}


void packageTest() {
	cout << "Test Package class ... " << endl;
	cout << "Example Package 1..." << endl;
	cout << "The package contains : " << endl;
	Package p;
	p.addFlightTicket(0,3);
	p.addFlightTicket(1,8);

	p.addHotelVoucher(3,4);
	p.addHotelVoucher(4,8);
	p.addHotelVoucher(5,0);

	p.addEventTicket(2);
	p.addEventTicket(5);
	p.addEventTicket(14);

	p.printPackage();

	cout << "\nExample Package 2..." << endl;
	cout << "The package contains : " << endl;
	Package p2;
	p2.addFlightTicket(0,3);
	p2.addFlightTicket(1,6);

	p2.addHotelVoucher(5,3);
	p2.addHotelVoucher(3,4);
	p2.addHotelVoucher(5,5);

	p2.addEventTicket(1);
	p2.addEventTicket(7);
	p2.addEventTicket(8);

	p2.printPackage();
}

void travelAgentTest() {
	TravelAgent *agent;
	agent = new TravelAgent;
	agent->readClientRequests();
	agent->generatePackages();
	agent->printSuccessfulPackages();
}

int main() {
	srand(time(0)); // seed random number generator

	cout << "Choose a class to test: " << endl;
	cout << "1. Test ClientRequest class" << endl;
	cout << "2. Test FlightTicket class" << endl;
	cout << "3. Test HotelVoucher class" << endl;
	cout << "4. Test EventTicket class" << endl;
	cout << "5. Test RequestGenerator class" << endl;
	cout << "6. Test Package class" << endl;
	cout << "7. Test TravelAgent class" << endl;
	cout << "8. Quit" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		clientRequestTest();
		break;
	case 2:
		flightTicketTest();
		break;
	case 3:
		hotelVoucherTest();
		break;
	case 4:
		eventTicketTest();
		break;
	case 5:
		requestGeneratorTest();
		break;
	case 6:
		packageTest();
		break;
	case 7:
		travelAgentTest();
		break;
	case 8:
		cout << "Bye!" << endl;
		break;
	default:
		cout << "Invalid input!" << endl;
	}

	return 0;

}

#endif /* TRAVELAGENT_CPP */

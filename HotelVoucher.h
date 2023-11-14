class HotelVoucher : public Ticket {// an object of this class represents a hotel voucher for a single day
private:
	int hotelType;

public:
	HotelVoucher(int ht, int d) : Ticket(d, 2000){
		hotelType = ht;

	}

	int gethotelType() {
		return hotelType;
	}
	
	void printTicket() {
		switch (hotelType) {
			case 3:
				cout << "Hotel voucher for a 3 star room on day " << day << " at price $" << hotelPriceMap[0] << endl;
				break;
			case 4:
				cout << "Hotel voucher for a 4 star room on day " << day << " at price $" << hotelPriceMap[1] << endl;
				break;
			case 5:
				cout << "Hotel voucher for a 5 star room on day " << day << " at price $" << hotelPriceMap[2] << endl;
				break;
		};
	}
	
};

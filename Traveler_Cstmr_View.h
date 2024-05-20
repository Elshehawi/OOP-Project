//
// Created by Omar Elshehawi on 5/10/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_CSTMR_VIEW_H_
#define PROJECT_TRAVELER_TRAVELER_CSTMR_VIEW_H_
using namespace std;
#include "Traveler_Cstmr_mgr.h"

class CustomerView {
private:
    CustomerManager &customerManager;
    const Customer& customer;
    ItineraryReservation currentItinerary;

    void ReadFlightRequest(FlightRequset &request) const{
        string str;
        int val;

        cout << "Enter From: ";
        cin >> str;
        request.SetFrom(str);

        cout << "Enter From Date (dd-mm-yy): ";
        cin >> str;
        request.SetDatetimeFrom(str);

        cout << "Enter To: ";
        cin >> str;
        request.SetTo(str);

        cout << "Enter To Date (dd-mm-yy): ";
        cin >> str;
        request.SetDatetimeTo(str);

        cout << "Enter Number of adults children (5-16) and infants: ";
        cin >> val;
        request.SetAdults(val);
        cin >> val;
        request.SetChildren(val);
        cin >> val;
        request.SetInfants(val);
    }

    void ReadHotelRequest(HotelRequset &request) const{
        string str;
        int val;

        cout << "Enter From Date (dd-mm-yy): ";
        cin >> str;
        request.SetFromDate(str);

        cout << "Enter To Date (dd-mm-yy): ";
        cin >> str;
        request.SetToDate(str);

        cout << "Enter Country: ";
        cin >> str;
        request.SetCountry(str);

        cout << "Enter City: ";
        cin >> str;
        request.SetCity(str);

        cout << "Enter Number of adults and children: ";
        cin >> val;
        request.SetAdults(val);
        cin >> val;
        request.SetChildren(val);
    }

    int ChooseFlight(const vector<Flight> &flights) const {
        if (flights.size() == 0) {
            cout << "No trips for this request info\n";
            return -1;
        }

        for (const Flight& flight : flights) {
            cout << flight.ToString() << "\n";
        }

        return ReadInt(1, flights.size(), true);
    }

    int ChooseRoom(const vector<HotelRoom> &rooms) const{
        if (rooms.size() == 0) {
            cout << "No trips for this request info\n";
            return -1;
        }

        for (const HotelRoom& room : rooms) {
            cout << room.ToString() << "\n";
        }

        return ReadInt(1, rooms.size(), true);
    }

    void AddFlight() {
        FlightRequset request;
        ReadFlightRequest(request);

        vector<Flight> flights = customerManager.FindFlights(request);
        int flight_choice = ChooseFlight(flights);

        if (flight_choice == -1)
            return;

        Flight &flight = flights[flight_choice - 1];

        FlightReservation reservation(request, flight);
        currentItinerary.AddReservation(reservation);
    }

    void AddHotel() {
        HotelRequset request;
        ReadHotelRequest(request);

        vector<HotelRoom> rooms = customerManager.FindHotels(request);
        int hotel_choice = ChooseRoom(rooms);

        if (hotel_choice == -1)
            return;

        HotelRoom &room = rooms[hotel_choice - 1];

        HotelReservation reservation(request, room);
        currentItinerary.AddReservation(reservation);
    }

    void PayItinerary() {
        // We can mark it const, but wrong, don't
        vector<string> payment_choices = customerManager.GetPaymentChoices();
        int payment_chocie = ShowReadMenu(payment_choices, "Select a payment choice");
        PaymentCard* payment_card = customer.GetCards()[payment_chocie - 1];

        bool status = customerManager.MakeReservation(currentItinerary, *payment_card);

        if (status) {
            cout << "Itinerary reserved\n";
        } else
            cout << "Failed to reserve the Itinerary\n";
    }

public:
    CustomerView(CustomerManager &customerManager) :
            customerManager(customerManager), customer(*customerManager.GetCustomer()) {
    }

    void Display() {
        cout << "\n\nHello " << customer.GetName() << " | User View\n";

        vector<string> menu;
        menu.push_back("View Profile");
        menu.push_back("Make Itinerary");
        menu.push_back("List my itineraries");
        menu.push_back("Logout");

        while (true) {
            int choice = ShowReadMenu(menu);
            if (choice == 1)
                ViewProfile();
            else if (choice == 2)
                MakeItinerary();
            else if (choice == 3)
                ListItineraries();
            else
                break;
        }
    }

    void ViewProfile() const {
        cout << "\n" << customer.toString() << "\n";
    }

    void MakeItinerary() {
        vector<string> menu;
        menu.push_back("Add Flight");
        menu.push_back("Add Hotel");
        menu.push_back("Done");
        menu.push_back("Cancel");

        while (true) {
            int choice = ShowReadMenu(menu);
            if (choice == 1)
                AddFlight();
            else if (choice == 2)
                AddHotel();
            else if (choice == 3) {
                PayItinerary();
                currentItinerary.Clear();
                break;
            }
            else {
                currentItinerary.Clear();
                break;
            }
        }
    }
    void ListItineraries() const {
        vector<string> itineraries = customerManager.GetItineraries();

        if (itineraries.size() == 0) {
            cout << "No itineraries so far!\n";
        }

        for (string& str : itineraries)
            cout << str << "\n";
    }
};

#endif // PROJECT_TRAVELER_TRAVELER_CSTMR_VIEW_H_
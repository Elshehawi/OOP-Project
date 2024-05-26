//
// Created by Omar Elshehawi on 5/10/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_CSTMR_MGR_H
#define PROJECT_TRAVELER_TRAVELER_CSTMR_MGR_H

#include "Traveler_Cstmr.h"
#include "Traveler_Payment_Card.h"
#include "Traveler_Common_Resrvation.h"
#include "Traveler_Backend.h"

class CustomerManager {
private:
    Customer *customer;
    TravelerBackend &TravelerManager;

public:
    CustomerManager(User *user, TravelerBackend &TravelerManager) :
            customer(dynamic_cast<Customer*>(user)), TravelerManager(TravelerManager) {

        if (customer == nullptr) {
            cout << "Error: User is null pointer as input\n";
            assert(customer != nullptr);
        }

    }

    vector<Flight> FindFlights(const FlightRequset &request) const {
        return TravelerManager.FindFlights(request);
    }

    vector<HotelRoom> FindHotels(const HotelRequset &request) const {
        return TravelerManager.FindHotels(request);
    }

    vector<string> GetPaymentChoices() const {
        vector<string> cards_info;

        for (PaymentCard* card : customer->GetCards())
            cards_info.push_back(card->ToString());
        return cards_info;
    }

    bool MakeReservation(Reservation& reservation, PaymentCard &paymentCard) {

             // Should this function be const? No. Logic of MakeReservation expects adding reservation to internals
             //      Ok, so if we put const, a compile error is generated? Yes customer is not pointer
             //          But const won't prevent calling internal method for a pointer


        bool is_paid = TravelerManager.ChargeCost(reservation.TotalCost(), paymentCard);

        if (is_paid) {
            cout << "Money withdraw successfully :) \n";

            bool is_confirmed = TravelerManager.ConfirmReservation(reservation);

            if (is_confirmed) {
                customer->AddReservation(reservation);
                cout << "Reservation confirmed\n";
                cout << "Thanks For Dealing With Us :)\n";
                return true;
            } else {
                cout << "Failed to confirm some of your reservation items :(\n";
                cout << "Canceling payment and whatever reserved\n";
                bool is_uncharged = TravelerManager.UnchargeCost(reservation.TotalCost(), paymentCard);

                if (!is_uncharged)
                    cout << "Problems in returning back your money. :o\n Call us on +020 101 095 2971\n";
            }
        } else
            cout << "Failed to withdtaw Money for the reservation -_-\n";

        return false;
    }

    vector<string> GetItineraries() const {
        const ReservationsSet& set = customer->GetReservations();
        vector<string> itineraries;

        for (const Reservation* reservation : set.GetReservations())
            itineraries.push_back(reservation->ToString());

        return itineraries;
    }

    const Customer* GetCustomer() const {
        return customer;
    }
};



#endif //PROJECT_TRAVELER_TRAVELER_CSTMR_MGR_H

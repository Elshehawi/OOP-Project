//
// Created by Omar Elshehawi on 5/8/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_CSTMR_H
#define PROJECT_TRAVELER_TRAVELER_CSTMR_H
using namespace std;

#include "Traveler_User.h"
#include "Traveler_Payment_Card.h"
#include "Traveler_Common_Resrvation.h"
#include <sstream>

class Customer: public User {
protected:
    vector<PaymentCard*> cards; // polymophism
    ReservationsSet reservations;

public:
    Customer(const Customer&) = delete;
    void operator =(const Customer&) = delete;

    Customer() {
        SetType(UserType::CusomterUser);
    }

    ~Customer() {
        for (PaymentCard* card : cards)
            delete card;
        cards.clear();
    }

    void AddPaymentCard(const PaymentCard& card) {
        cards.push_back(card.Clone());
    }

    void AddReservation(const Reservation& reservation) {
        reservations.AddReservation(*reservation.Clone());
    }

    const vector<PaymentCard*>& GetCards() const {
        return cards;
    }

    const ReservationsSet& GetReservations() const {
        return reservations;
    }
};



#endif //PROJECT_TRAVELER_TRAVELER_CSTMR_H
//
// Created by Omar Elshehawi on 5/8/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_COMMON_RESRVATION_H
#define PROJECT_TRAVELER_TRAVELER_COMMON_RESRVATION_H
#include <iostream>
using namespace std;

class Reservation {
public:
    virtual Reservation* Clone() const = 0;

    virtual double TotalCost() const = 0;

    virtual string ToString() const = 0;

    virtual ~Reservation() {
    }
};

// i did not make hotelflight class for better code handling and
// if i want to add for example car reservation so,
// i will make a ItineraryReservation for adding any reservation to a vector
// so i can do what ever i want with then anytime

class ItineraryReservation: public Reservation {
protected:
    vector<Reservation*> reservations;	// As has pointers, we need copy constructor, Because the default copy constructor creates
                                        // a copy of that object only: it copies any pointers that class contains instead of
                                        // creating new memory and copying the content of teh pointer into that
public:
    ItineraryReservation() {
    }

    ItineraryReservation(const ItineraryReservation& anotherReservation) {	// copy constructor
        for (const Reservation* reservation : anotherReservation.GetReservations())
            AddReservation(*reservation);
    }

    void AddReservation(const Reservation& reservation) {
        reservations.push_back(reservation.Clone());
    }

    virtual double TotalCost() const {
        double cost = 0;

        for (const Reservation* reservation : reservations)
            cost += reservation->TotalCost();

        return cost;
    }

    ~ItineraryReservation() {
        Clear();
    }

    const vector<Reservation*>& GetReservations() const {
        return reservations;
    }

    void Clear() {
        for (const Reservation* reservation : reservations)
            delete reservation;
        reservations.clear();
    }

    virtual string ToString() const override {
        ostringstream oss;

        oss <<"-------------------------------------------------\n";
        oss << "Itinerary of " << reservations.size() << " sub-reservations\n";

        for (const Reservation* reservation : reservations)
            oss << reservation->ToString() << "\n";

        oss << "Total Itinerary cost: " << TotalCost() << "\n";
        oss <<"-------------------------------------------------\n";
        return oss.str();
    }

    virtual Reservation* Clone() const override {
        return new ItineraryReservation(*this);
    }
};

class ReservationsSet: public ItineraryReservation {
public:
    // We need another class that act like set of different reservations (not Itinerary)
    // This has same functionalities as ItineraryReservation
    // It is much better to have its own class, even empty class
    // Then code is more mentanable + we can do future changes easily

    using ItineraryReservation::ItineraryReservation;	// use its copy constructor

    virtual Reservation* Clone() const {
        return new ReservationsSet(*this);
    }
};
#endif //PROJECT_TRAVELER_TRAVELER_COMMON_RESRVATION_H
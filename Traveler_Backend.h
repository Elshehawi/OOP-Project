//
// Created by Omar Elshehawi on 5/10/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_BACKEND_H
#define PROJECT_TRAVELER_TRAVELER_BACKEND_H
using namespace std;

#include "Traveler_Payment_Card.h"
#include "Traveler_Utils.h"
#include "Traveler_User.h"
#include "Traveler_Payments_API.h"
#include "Traveler_Hotels_API.h"
#include "Traveler_Flights_API.h"


class TravelerBackend {
private:
    vector<IFlighsManager*> flightsManagers;
    IPayment* paymentHelper;

    vector<IHotelsManager*> hotelsManagers;

public:
    TravelerBackend(const TravelerBackend&) = delete;
    void operator=(const TravelerBackend&) = delete;

    TravelerBackend() {
        flightsManagers = FlightsFactory::GetManagers();
        paymentHelper = PaymentFactory::GetPaymentHelper();
        hotelsManagers = HotelsFactory::GetManagers();
    }
    vector<Flight> FindFlights(const FlightRequset &request) const {
        vector<Flight> flights;

        for (IFlighsManager* manager : flightsManagers) {
            manager->SetFlightRequset(request);
            vector<Flight> more_flights = manager->SearchFlights();

            flights.insert(flights.end(), more_flights.begin(), more_flights.end());
        }
        return flights;
    }

    vector<HotelRoom> FindHotels(const HotelRequset &request) const {
        vector<HotelRoom> rooms;

        for (IHotelsManager* manager : hotelsManagers) {
            manager->SetHotelRequest(request);
            vector<HotelRoom> more_rooms = manager->SearchHotelRooms();

            rooms.insert(rooms.end(), more_rooms.begin(), more_rooms.end());
        }
        return rooms;
    }

    bool ChargeCost(double cost, PaymentCard &payment_card) const {             //dynamic

        CreditCard* creditCard = nullptr;
        DebitCard* debitCard = nullptr;

        if ((creditCard = dynamic_cast<CreditCard*>(&payment_card)))
            paymentHelper->SetUserInfo(payment_card.GetOwnerName(), "");
        else if ((debitCard = dynamic_cast<DebitCard*>(&payment_card))) {
            paymentHelper->SetUserInfo(payment_card.GetOwnerName(), debitCard->GetBillingAddress());
        }
        paymentHelper->SetCardInfo(payment_card.GetCardNumber(), payment_card.GetExpiryDate(), payment_card.GetSecurityCode());

        bool payment_status = paymentHelper->MakePayment(cost);

        if (!payment_status)
            return false;	            // Don't reserve this flight

        return true;
    }

    bool UnchargeCost(double cost, PaymentCard &payment_card) const {
        return true;
    }

    bool CancelReservation(const Reservation& reservation) {
        return true;
    }

    bool ConfirmReservation(const Reservation& reservation) {
        // We can think of factory of factories to maybe be able to make this generic
        // But lets make your life easier at this stage

        FlightReservation* flight = nullptr;
        Reservation* reservationCpy = reservation.Clone();

        if ((flight = dynamic_cast<FlightReservation*>(reservationCpy))) {
            string name = flight->GetFlight().GetAirlineName();
            IFlighsManager* mgr = FlightsFactory::GetManager(name);

            if (mgr != nullptr && mgr->ReserveFlight(*flight))
                return true;

            return false;	// we shouldn't delete mgr pointer. In future, the factory should do so
        }

        HotelReservation* hotel = nullptr;
        if ((hotel = dynamic_cast<HotelReservation*>(reservationCpy))) {
            string name = hotel->GetRoom().GetHotelName();
            IHotelsManager* mgr = HotelsFactory::GetManager(name);

            if (mgr != nullptr && mgr->ReserveRoom(*hotel))
                return true;

            return false;	// we shouldn't delete mgr pointer. In future, the factory should do so
        }

        ItineraryReservation* itiniary = nullptr;
        if ((itiniary = dynamic_cast<ItineraryReservation*>(reservationCpy))) {
            vector<Reservation*> confirmed_reservations;

            for (Reservation* sub_reservation : itiniary->GetReservations()) {
                bool is_confirmed = ConfirmReservation(*sub_reservation);

                if (is_confirmed)
                    confirmed_reservations.push_back(sub_reservation);
                else {
                    // If failed to reserve, cancel all what is confirmed so far!
                    for (Reservation* conf_reservation : confirmed_reservations)
                        CancelReservation(*conf_reservation);
                    return false;
                }
            }
        } else
            assert(false);

        delete reservationCpy;       // Avoiding memory leak
        reservationCpy = nullptr;
        return true;
    }
};

#endif //PROJECT_TRAVELER_TRAVELER_BACKEND_H

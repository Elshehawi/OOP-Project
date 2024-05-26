//
// Created by Omar Elshehawi on 5/10/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_FLIGHTS_API_H
#define PROJECT_TRAVELER_TRAVELER_FLIGHTS_API_H
using namespace std;
#include <iostream>
#include "Traveler_Common_Resrvation.h"


class AirEnglandCustomerInfo {

};

class AirEnglandFlight {
public:
    string dateTimeForm;
    string dateTimeTo;
    double price;
};

class AirEnglandFlightAPI {
public:
    static vector<AirEnglandFlight> GetFlights(string from, string fromDate, string to, string toDate, int adults, int children) {
        vector<AirEnglandFlight> flights;

        flights.push_back( { "25-01-2024", "10-02-2024",2000 });
        flights.push_back( { "29-01-2024", "10-02-2024",3500 });
        return flights;
    }
    static bool ReserveFlight(const AirEnglandFlight& flights, const AirEnglandCustomerInfo &info) {
        return true;
    }
};

class TurkishFlight {
public:
    double price;                   // cost ??
    string datetime_from;
    string datetime_to;
};

class TurkishCustomerInfo {

};

class TurkishAirlinesOnlineAPI {
public:
    void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) {
    }
    void SetPassengersInfo(int infants, int childern, int adults) {
    }
    vector<TurkishFlight> GetAvailableFlights() const {
        vector<TurkishFlight> flights;

        flights.push_back( { 3000, "10-01-2024", "10-02-2024" });
        flights.push_back( { 4500, "12-01-2024", "10-02-2024" });
        return flights;
    }

    static bool ReserveFlight(const TurkishCustomerInfo &info, const TurkishFlight& flight) {
        return false;
    }
};


// as for reservation

class Flight {
private:
    string airlineName;
    double totalCost = 0;
    string dateTimeFrom;
    string dateTimeTo;

public:
    string ToString() const {
        ostringstream oss;
        oss << "Airline: " << airlineName << " Cost: " << totalCost << " Departure Date " << dateTimeFrom << " Arrival date " << dateTimeTo;
            return oss.str();
        }

        void SetAirlineName(const string& airlineName1) {
            airlineName = airlineName1;
        }

        void SetTotalCost(double totalCost1) {
            totalCost = totalCost1;
        }

        void SetDateTimeFrom(const string& dateTimeFrom1) {
            dateTimeFrom = dateTimeFrom1;
        }

        void SetDateTimeTo(const string& dateTimeTo1) {
            dateTimeTo = dateTimeTo1;
        }

        const string& GetDateTimeTo() const {
            return dateTimeTo;
        }

        double GetTotalCost() const {
            return totalCost;
        }

        const string& GetDateTimeFrom() const {
            return dateTimeFrom;
        }
        const string& GetAirlineName() const {
            return airlineName;
        }

};

class FlightRequset {
private:
    string DateTimeFrom;
    string from;
    string DateTimeTo;
    string to;
    int infants;
    int children;
    int adults;

public:
    void SetAdults(int adults) {
        this->adults = adults;
    }
    void SetChildren(int childern) {
        this->children = childern;
    }
    void SetDatetimeFrom(const string& datetimeFrom) {
        DateTimeFrom = datetimeFrom;
    }
    void SetDatetimeTo(const string& datetimeTo) {
        DateTimeTo = datetimeTo;
    }
    void SetFrom(const string& from) {
        this->from = from;
    }
    void SetInfants(int infants) {
        this->infants = infants;
    }
    void SetTo(const string& to) {
        this->to = to;
    }

    string GetDatePartFrom() const {
        return DateTimeFrom;	// extract date only
    }

    string GetDatePartTo() const {
        return DateTimeTo;	// extract date only
    }

    int GetAdults() const {
        return adults;
    }

    int GetChildren() const {
        return children;
    }

    const string& GetDatetimeFrom() const {
        return DateTimeFrom;
    }

    const string& GetDatetimeTo() const {
        return DateTimeTo;
    }

    const string& GetFrom() const {
        return from;
    }

    int GetInfants() const {
        return infants;
    }

    const string& GetTo() const {
        return to;
    }

};
class FlightReservation: public Reservation {
private:
    FlightRequset request;
    Flight flight;

public:
    FlightReservation(const FlightRequset &request, const Flight &flight) :
        request(request), flight(flight) {
}

    virtual FlightReservation* Clone() const override {
        return new FlightReservation(*this);
    }

    virtual double TotalCost() const override {
        return flight.GetTotalCost();
    }

    virtual string ToString() const override {
        ostringstream oss;
        oss << "Airline reservation with reservation: " << flight.GetAirlineName() << ": From " << request.GetFrom() << " on " << request.GetDatetimeFrom() << "\n";
        oss << "\tTo " << request.GetTo() << " on " << request.GetDatetimeTo() << "\n";
        oss << "\t" << "Adults: " << request.GetAdults() << " children: " << request.GetChildren() << " infants: " << request.GetInfants() << "\n";
        oss << "\tTotal Cost:" << TotalCost() << "\n";

        return oss.str();
    }

    const Flight& GetFlight() const {
        return flight;
    }

    const FlightRequset& GetRequest() const {
        return request;
    }
};

class IFlighsManager {
protected:
    FlightRequset request;
public:
    virtual void SetFlightRequset(const FlightRequset &request_) {
        request = request_;
    }
    virtual vector<Flight> SearchFlights() const = 0;

    virtual bool ReserveFlight(const FlightReservation &reservation) const = 0;

    virtual string GetName() const = 0;

    virtual ~IFlighsManager() {
    }
};

class AirEnglandFlighsManager: public IFlighsManager {
public:
    virtual string GetName() const override {
        return "AirEngland Airlines";
    }

    virtual vector<Flight> SearchFlights() const override {
        vector<AirEnglandFlight> flights_airEngland = AirEnglandFlightAPI::GetFlights(request.GetFrom(), request.GetDatePartFrom(), request.GetTo(), request.GetDatePartTo(), request.GetAdults(), request.GetChildren());
        vector<Flight> flights;

        // convert
        for (auto & flight_airEngland : flights_airEngland) {
            Flight flight;
            flight.SetAirlineName(GetName());
            flight.SetDateTimeFrom(flight_airEngland.dateTimeForm);
            flight.SetDateTimeTo(flight_airEngland.dateTimeTo);
            flight.SetTotalCost(flight_airEngland.price);

            flights.push_back(flight);
        }
        return flights;
    }

    virtual bool ReserveFlight(const FlightReservation &reservation) const {
        // Just dummy. We should map from reservation to the agency api
        return AirEnglandFlightAPI::ReserveFlight(AirEnglandFlight(), AirEnglandCustomerInfo());
    }
};

class TurkishFlighsManager: public IFlighsManager {
private:
public:
    virtual string GetName() const override {
        return "Turksih Airlines";
    }

    virtual vector<Flight> SearchFlights() const override {
        TurkishAirlinesOnlineAPI api;

        api.SetFromToInfo(request.GetDatetimeFrom(), request.GetFrom(), request.GetDatetimeTo(), request.GetTo());
        api.SetPassengersInfo(request.GetInfants(), request.GetChildren(), request.GetAdults());

        vector<TurkishFlight> flights_turkey = api.GetAvailableFlights();
        vector<Flight> flights;

        // convert
        for (auto & flight_turkey : flights_turkey) {
            Flight flight;
            flight.SetAirlineName("Turksih Airlines");
            flight.SetDateTimeFrom(flight_turkey.datetime_from);
            flight.SetDateTimeTo(flight_turkey.datetime_to);
            flight.SetTotalCost(flight_turkey.price);

            flights.push_back(flight);
        }
        return flights;
    }
    virtual bool ReserveFlight(const FlightReservation &reservation) const {
        // Just dummy. We should map from reservation to the agency api
        return TurkishAirlinesOnlineAPI::ReserveFlight(TurkishCustomerInfo(), TurkishFlight());
    }
};


// This class reduce the dependency of clients on specific managers.
// This is the only place that is coupled with the different types

class FlightsFactory {
    // We can design this factory in more efficient way: e.g. using map + singleton
public:
    static vector<IFlighsManager*> GetManagers() {
        vector<IFlighsManager*> flights_managers;

        flights_managers.push_back(new TurkishFlighsManager());
        flights_managers.push_back(new AirEnglandFlighsManager());

        return flights_managers;
    }

    static IFlighsManager* GetManager(string name) {
        for (IFlighsManager* mgr : FlightsFactory::GetManagers()) {
            if (mgr->GetName() == name)
                return mgr;
        }
        return nullptr;
    }
};



#endif //PROJECT_TRAVELER_TRAVELER_FLIGHTS_API_H

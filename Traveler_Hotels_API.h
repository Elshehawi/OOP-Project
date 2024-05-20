//
// Created by Omar Elshehawi on 5/10/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_HOTELS_API_H
#define PROJECT_TRAVELER_TRAVELER_HOTELS_API_H
#include "Traveler_Common_Resrvation.h"
using namespace std;


class HiltonRoom {
public:
    int available;
    double pricePerNight;
    string roomType;
    string dateFrom;
    string dateTo;
};

class HiltonHotelAPI {
public:
    static vector<HiltonRoom> SearchRooms(string country, string city, string from_date, string to_date, int adults, int children, int needed_rooms) {
        vector<HiltonRoom> rooms;

        rooms.push_back( { 10, 250.0, "Interior View", "29-01-2024", "10-02-2024" });
        rooms.push_back( { 8, 899.9, "City View", "29-01-2024", "10-02-2024" });
        rooms.push_back( { 4, 13000.0, "Deluxe View", "29-01-2024", "10-02-2024" });

        return rooms;
    }
};

class MarriottFoundRoom {
public:
    string roomType;
    int available;
    double pricePerNight;
    string dateFrom;
    string dateTo;
};

class MarriottHotelAPI {
public:
    static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children) {
        vector<MarriottFoundRoom> rooms;

        rooms.push_back( { "City View", 12, 1300.0, "29-01-2024", "10-02-2024" });
        rooms.push_back( { "Interior View", 6, 600.0, "29-01-2024", "10-02-2024" });
        rooms.push_back( { "Private View", 3, 15000.0, "29-01-2024", "10-02-2024" });

        return rooms;
    }
};

class HotelRoom {
private:
    string hotelName;
    string roomType;
    int available_rooms{0};
    double pricePerNight {0};
    string dateFrom;
    string dateTo;

public:
    string ToString() const {
        ostringstream oss;
        oss << "Hotel: " << hotelName << " Room Type: " << roomType << "(" << available_rooms << ") Price per night: " << pricePerNight << " From Date " << dateFrom << " to " << dateTo << "";
        return oss.str();
    }

    const string& GetDateFrom() const {
        return dateFrom;
    }

    void SetDateFrom(const string& dateFrom1) {
        dateFrom = dateFrom1;
    }

    const string& GetDateTo() const {
        return dateTo;
    }

    void SetDateTo(const string& dateTo1) {
        dateTo = dateTo1;
    }

    double GetPricePerNight() const {
        return pricePerNight;
    }

    void SetPricePerNight(double pricePerNight1) {
        pricePerNight = pricePerNight1;
    }

    const string& GetRoomType() const {
        return roomType;
    }

    void SetRoomType(const string& roomType1) {
        roomType = roomType1;
    }

    int GetAvailableRooms() const {
        return available_rooms;
    }

    void SetAvailableRooms(int availableRooms = 0) {
        available_rooms = availableRooms;
    }

    const string& GetHotelName() const {
        return hotelName;
    }

    void SetHotelName(const string& hotelName1) {
        hotelName = hotelName1;
    }
};

class HotelRequset {
private:
    string fromDate;
    string toDate;
    string country;
    string city;
    int rooms;
    int adults;
    int children;

public:
    int GetTotalNights() const {
        // Some date computations
        return 3;
    }
    int GetAdults() const {
        return adults;
    }

    void SetAdults(int adults) {
        this->adults = adults;
    }

    int GetChildren() const {
        return children;
    }

    void SetChildren(int children) {
        this->children = children;
    }

    const string& GetCity() const {
        return city;
    }

    void SetCity(const string& city) {
        this->city = city;
    }

    const string& GetCountry() const {
        return country;
    }

    void SetCountry(const string& country) {
        this->country = country;
    }

    const string& GetFromDate() const {
        return fromDate;
    }

    void SetFromDate(const string& fromDate1) {
        fromDate = fromDate1;
    }

    int GetRooms() const {
        return rooms;
    }

    void SetRooms(int rooms) {
        this->rooms = rooms;
    }

    const string& GetToDate() const {
        return toDate;
    }

    void SetToDate(const string& toDate1) {
        toDate = toDate1 ;
    }
};

class HotelReservation: public Reservation {
private:
    HotelRequset request;
    HotelRoom room;

public:
    HotelReservation(const HotelRequset &request, const HotelRoom &room) :
            request(request), room(room) {
    }

    virtual HotelReservation* Clone() const override {
        return new HotelReservation(*this);
    }

    virtual double TotalCost() const override {
        return room.GetPricePerNight() * request.GetTotalNights();
    }

    virtual string ToString() const override {
        ostringstream oss;
        oss << "Hotel reservation: " << room.GetHotelName() << ": " << request.GetCity() << " @ " << request.GetCountry() << "\n";
        oss << "\t" << request.GetFromDate() << " to " << request.GetToDate() << " : " << request.GetTotalNights() << "\n";
        oss << "\t" << "Adults: " << request.GetAdults() << " children " << request.GetChildren() << "\n";
        oss << "\tTotal Cost:" << TotalCost() << "\n";

        return oss.str();
    }

    const HotelRequset& GetRequest() const {
        return request;
    }

    const HotelRoom& GetRoom() const {
        return room;
    }
};

class IHotelsManager {
protected:
    HotelRequset request;
public:
    virtual string GetName() const = 0;

    virtual void SetHotelRequest(const HotelRequset &request_) {
        request = request_;
    }
    virtual vector<HotelRoom> SearchHotelRooms() = 0;

    virtual bool ReserveRoom(const HotelReservation &reservation) const = 0;

    virtual ~IHotelsManager() {
    }
};

class HiltonHotelsManager: public IHotelsManager {
private:

public:
    virtual string GetName() const override {
        return "Hilton Hotel";
    }

    virtual vector<HotelRoom> SearchHotelRooms() {
        vector<HiltonRoom> api_rooms = HiltonHotelAPI::SearchRooms(request.GetCountry(), request.GetCity(), request.GetFromDate(), request.GetToDate(), request.GetAdults(), request.GetChildren(), request.GetRooms());
        vector<HotelRoom> rooms;

        for (auto & api_room : api_rooms) {
            HotelRoom room;
            room.SetHotelName("Hilton Hotel");
            room.SetDateFrom(api_room.dateFrom);
            room.SetDateTo(api_room.dateTo);
            room.SetPricePerNight(api_room.pricePerNight);
            room.SetAvailableRooms(api_room.available);
            room.SetRoomType(api_room.roomType);

            rooms.push_back(room);
        }
        return rooms;
    }

    virtual bool ReserveRoom(const HotelReservation &reservation) const override{
        return true;
    }
};

class MarriottHotelsManager: public IHotelsManager {
private:

public:
    virtual string GetName() const override {
        return "Marriott Hotel";
    }

    virtual vector<HotelRoom> SearchHotelRooms() {

        vector<MarriottFoundRoom> api_rooms = MarriottHotelAPI::FindRooms(request.GetFromDate(), request.GetToDate(), request.GetCountry(), request.GetCity(), request.GetRooms(), request.GetAdults(), request.GetChildren());
        vector<HotelRoom> rooms;

        for (auto & api_room : api_rooms) {
            HotelRoom room;
            room.SetHotelName("Marriott Hotel");
            room.SetDateFrom(api_room.dateFrom);
            room.SetDateTo(api_room.dateTo);
            room.SetPricePerNight(api_room.pricePerNight);
            room.SetAvailableRooms(api_room.available);
            room.SetRoomType(api_room.roomType);

            rooms.push_back(room);
        }
        return rooms;
    }
    virtual bool ReserveRoom(const HotelReservation &reservation) const override{
        return true;
    }
};

class HotelsFactory {
public:
    static vector<IHotelsManager*> GetManagers() {
        vector<IHotelsManager*> managers;

        managers.push_back(new HiltonHotelsManager());
        managers.push_back(new MarriottHotelsManager());

        return managers;
    }

    static IHotelsManager* GetManager(string name) {
        for (IHotelsManager* mgr : HotelsFactory::GetManagers()) {
            if (mgr->GetName() == name)
                return mgr;
        }
        return nullptr;
    }
};
#endif //PROJECT_TRAVELER_TRAVELER_HOTELS_API_H

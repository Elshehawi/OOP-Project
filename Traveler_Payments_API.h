//
// Created by Omar Elshehawi on 5/10/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_PAYMENTS_API_H
#define PROJECT_TRAVELER_TRAVELER_PAYMENTS_API_H

using namespace std;

#include "json.hpp"
using namespace json;

class PayPalCreditCard {
        public:
        string name;
        string address;
        string id;
        string expiryDate;
        int ccv{};
};

class PayPalOnlinePaymentAPI {
public:
    void SetCardInfo(const PayPalCreditCard* const card) {
    }
    bool MakePayment(double money) {
        return true;
    }
};

class StripeUserInfo {
public:
    string name;
    string address;
};

class StripeCardInfo {
public:
    string id;
    string expiryDate;
};

class StripePaymentAPI {
public:
    bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money) {
        return true;
    }
};

class SquarePaymentAPI {
public:
    bool static WithDrawMoney(string JsonQuery) {
        json::JSON obj = JSON::Load(JsonQuery);
        return true;
    }
};




class IPayment {
public:
    virtual void SetUserInfo(string name, string address) = 0;
    virtual void SetCardInfo(string id, string expiryDate, int ccv) = 0;
    virtual bool MakePayment(double money) = 0;
    virtual ~IPayment() {
    }
};

class PayPalPayment: public IPayment {
private:
    PayPalOnlinePaymentAPI paypal;
    PayPalCreditCard card;
public:
    virtual void SetUserInfo(string name, string address) {
        card.name = name;
        card.address = address;
    }
    virtual void SetCardInfo(string id, string expiry_date, int ccv) {
        card.id = id;
        card.expiryDate = expiry_date;
        card.ccv = ccv;
    }
    virtual bool MakePayment(double money) {
        paypal.SetCardInfo(&card);
        return paypal.MakePayment(money);
    }
};

class StripePayment: public IPayment {
private:
    StripeCardInfo card;
    StripeUserInfo user;
public:
    virtual void SetUserInfo(string name, string address) {
        user.name = name;
        user.address = address;
    }
    virtual void SetCardInfo(string id, string expiry_date, int ccv) {
        card.id = id;
        card.expiryDate = expiry_date;
    }
    virtual bool MakePayment(double money) {
        return StripePaymentAPI::WithDrawMoney(user, card, money);
    }
};

class SquarePayment: public IPayment {
private:
    string name;
    string address;
    string id;
    string expiryDate;
    int ccv;

public:
    virtual void SetUserInfo(string name_, string address_) {
        name = name_;
        address = address_;
    }
    virtual void SetCardInfo(string id_, string expiry_date_, int ccv_) {
        id = id_;
        expiryDate = expiry_date_;
        ccv = ccv_;
    }
    virtual bool MakePayment(double money) {

        // This now similar to Adapter pattern. We change format of interface to match another interface
        // Adapter is a Structural Design Pattern that allows incompatible interfaces between
        // classes to work together without modifying their source code.
        // It acts as a bridge between two interfaces,
        // making them compatible so that they can collaborate and interact seamlessly.
        json::JSON obj;
        obj["user_info"] = json::Array(name, address);
        obj["card_info"]["ID"] = id;
        obj["card_info"]["DATE"] = expiryDate;
        obj["card_info"]["CCV"] = ccv;
        obj["money"] = money;

        ostringstream oss;
        oss << obj;
        string json_query = oss.str();

        return SquarePaymentAPI::WithDrawMoney(json_query);
    }
};

class PaymentFactory {
public:
    static IPayment* GetPaymentHelper() {
        if (true)
            return new SquarePayment();
        else if (true)
            return new PayPalPayment();
        else
            return new StripePayment();
    }
};
#endif //PROJECT_TRAVELER_TRAVELER_PAYMENTS_API_H

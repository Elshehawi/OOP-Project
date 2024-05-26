//
// Created by Omar Elshehawi on 5/6/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_PAYMENT_CARD_H
#define PROJECT_TRAVELER_TRAVELER_PAYMENT_CARD_H
using namespace std;


class PaymentCard {
protected:
    string owner_name;
    string card_number;
    string expiry_date;
    string type;            // master card or visa for e.g.
    int security_code;      // CVV
public:


    void SetCardNumber(const string& cardNumber) {
        card_number = cardNumber;
    }

    void SetExpiryDate(const string& expiryDate) {
        expiry_date = expiryDate;
    }

    void SetOwnerName(const string& ownerName) {
        owner_name = ownerName;
    }

    void SetSecurityCode(int securityCode) {
        security_code = securityCode;
    }

    const string& GetCardNumber() const {
        return card_number;
    }

    const string& GetExpiryDate() const {
        return expiry_date;
    }

    const string& GetOwnerName() const {
        return owner_name;
    }

    int GetSecurityCode() const {
        return security_code;
    }

    virtual string ToString() const {               //virtual func. is a member func. declared in base class to tell the compiler
                                                    // preform a dynamic linkage when u redine in a derived class
        ostringstream oss;
        oss << "Owner: " << owner_name << " Card number: " << card_number << " Expiry date: " << expiry_date; // secure(CVV)
        return oss.str();
    }

    virtual PaymentCard* Clone() const = 0;

    virtual ~PaymentCard() {
    }
};


class DebitCard: public PaymentCard {
protected:
    string billing_address;

public:
    void SetBillingAddress(const string& billingAddress) {
        billing_address = billingAddress;
    }

    const string& GetBillingAddress() const {
        return billing_address;
    }

    virtual PaymentCard* Clone() const override {
        return new DebitCard(*this);
    }

    virtual string ToString() const {
        ostringstream oss;
        oss << "[Debit Card]: " << PaymentCard::ToString() << " Billing Address: " << billing_address;
        return oss.str();
    }
};


class CreditCard: public PaymentCard {
public:                                                         // Ask about the best prac.
    virtual string ToString() const override {
        ostringstream oss;
        oss << "[Credit Card]: " << PaymentCard::ToString();
        return oss.str();
    }
    virtual PaymentCard* Clone() const override {
        return new CreditCard(*this);
    }
};


#endif //PROJECT_TRAVELER_TRAVELER_PAYMENT_CARD_H

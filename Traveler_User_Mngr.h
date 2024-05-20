//
// Created by Omar Elshehawi on 5/5/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_USER_MNGR_H
#define PROJECT_TRAVELER_TRAVELER_USER_MNGR_H

#include <map>
#include "Traveler_Utils.h"
#include "Traveler_User.h"
#include "Traveler_Payment_Card.h"
#include "Traveler_Cstmr.h"


class UsersManager {
protected:
    User* currentUser {nullptr};
    map<string, User*> usernameUserboject_map;

    // the following func. wipes users data when called (free space or just clear them.....)
    void DataWipe () {
        for(auto pair: usernameUserboject_map) {
            delete pair.second;
        }
        usernameUserboject_map.clear();
        currentUser = nullptr;
    }
public:
    UsersManager() {}

    ~UsersManager() {
        cout << "Destructor: UsersManager\n";
        DataWipe();
    }

    UsersManager(const UsersManager&) = delete;
    void operator = (const UsersManager&) = delete;

    void LoadDatabase() {
        // small database for simplicity
        cout << "UsersManager: LoadDatabase\n";

        DataWipe();

        auto* admin_user = new Admin();
        admin_user->SetUserName("omar");
        admin_user->SetPassword("1010");
        admin_user->SetEmail("omar@gmail.com");
        admin_user->SetName("Omar Mohamed Elshehawi");
        usernameUserboject_map[admin_user->GetUserName()] = admin_user;

        auto* customrUser = new Customer();
        customrUser->SetUserName("handosa");
        customrUser->SetPassword("4545");
        customrUser->SetEmail("Hando@gmail.com");
        customrUser->SetName("Dr. Mohamed Handosa");

        auto* debitCard = new DebitCard();
        debitCard->SetOwnerName(customrUser->GetName());
        debitCard->SetCardNumber("4585-8862-1146-8876");
        debitCard->SetExpiryDate("12/29");
        debitCard->SetSecurityCode(111);
        debitCard->SetBillingAddress("23 Galaa St. Mansoura");
        customrUser->AddPaymentCard(*debitCard);

        auto* creditCard = new CreditCard();
        creditCard->SetOwnerName(customrUser->GetName());
        creditCard->SetCardNumber("8685-8452-1826-4486");
        creditCard->SetExpiryDate("10/25");
        creditCard->SetSecurityCode(1117);
        customrUser->AddPaymentCard(*creditCard);
        usernameUserboject_map[customrUser->GetUserName()] = customrUser;
/////////////////////////////
        auto* customrUser1 = new Customer();
        customrUser1->SetUserName("hossam");
        customrUser1->SetPassword("3020");
        customrUser1->SetEmail("HossamSh@gmail.com");
        customrUser1->SetName("Hossam Elshafeey");

        auto* debitCard1 = new DebitCard();
        debitCard1->SetOwnerName(customrUser1->GetName());
        debitCard1->SetCardNumber("4585-8862-1846-8876");
        debitCard1->SetExpiryDate("5/30");
        debitCard1->SetSecurityCode(511);
        debitCard1->SetBillingAddress("25 St. Elnakhel - Elmahalla");
        customrUser1->AddPaymentCard(*debitCard1);

        auto* creditCard1 = new CreditCard();
        creditCard1->SetOwnerName(customrUser->GetName());
        creditCard1->SetCardNumber("2682-8486-1862-8886");
        creditCard1->SetExpiryDate("8/28");
        creditCard1->SetSecurityCode(1117);
        customrUser1->AddPaymentCard(*creditCard1);
        usernameUserboject_map[customrUser1->GetUserName()] = customrUser1;

////////////////////////////////////////

        auto* customrUser2 = new Customer();
        customrUser2->SetUserName("hannen");
        customrUser2->SetPassword("4040");
        customrUser2->SetEmail("Hannenelmtealy@gmail.com");
        customrUser2->SetName("Hannen Elmetwaly");

        auto* debitCard2 = new DebitCard();
        debitCard2->SetOwnerName(customrUser2->GetName());
        debitCard2->SetCardNumber("4585-8862-1846-8876");
        debitCard2->SetExpiryDate("5/30");
        debitCard2->SetSecurityCode(511);
        debitCard2->SetBillingAddress("2 Sea St. - New Damitta");
        customrUser2->AddPaymentCard(*debitCard2);

        auto* creditCard2 = new CreditCard();
        creditCard2->SetOwnerName(customrUser->GetName());
        creditCard2->SetCardNumber("2682-8486-1862-8886");
        creditCard2->SetExpiryDate("8/28");
        creditCard2->SetSecurityCode(1117);
        customrUser2->AddPaymentCard(*creditCard2);
        usernameUserboject_map[customrUser2->GetUserName()] = customrUser2;
        ///////////////////////////////
        auto* customrUser3 = new Customer();
        customrUser3->SetUserName("samah");
        customrUser3->SetPassword("3010");
        customrUser3->SetEmail("samah@gmail.com");
        customrUser3->SetName("Samah Ashraf");

        auto* debitCard3 = new DebitCard();
        debitCard3->SetOwnerName(customrUser3->GetName());
        debitCard3->SetCardNumber("4585-8862-1846-8876");
        debitCard3->SetExpiryDate("5/30");
        debitCard3->SetSecurityCode(511);
        debitCard3->SetBillingAddress("25 St. Elnakhel - Elmahalla");
        customrUser3->AddPaymentCard(*debitCard3);

        auto* creditCard3 = new CreditCard();
        creditCard3->SetOwnerName(customrUser3->GetName());
        creditCard3->SetCardNumber("2682-8486-1862-8886");
        creditCard3->SetExpiryDate("8/28");
        creditCard3->SetSecurityCode(1117);
        customrUser3->AddPaymentCard(*creditCard3);
        usernameUserboject_map[customrUser3->GetUserName()] = customrUser3;

////////////////////////////////////////
        auto* customrUser4 = new Customer();
        customrUser4->SetUserName("mohamed");
        customrUser4->SetPassword("1030");
        customrUser4->SetEmail("mohamed1233@gmail.com");
        customrUser4->SetName("Mohamed Alaa");

        auto* debitCard4 = new DebitCard();
        debitCard4->SetOwnerName(customrUser4->GetName());
        debitCard4->SetCardNumber("4585-8862-1846-8876");
        debitCard4->SetExpiryDate("5/30");
        debitCard4->SetSecurityCode(511);
        debitCard4->SetBillingAddress("25 St. Elnakhel - Elmahalla");
        customrUser4->AddPaymentCard(*debitCard4);

        auto* creditCard4 = new CreditCard();
        creditCard4->SetOwnerName(customrUser4->GetName());
        creditCard4->SetCardNumber("2682-8486-1862-8886");
        creditCard4->SetExpiryDate("8/28");
        creditCard4->SetSecurityCode(1117);
        customrUser4->AddPaymentCard(*creditCard4);
        usernameUserboject_map[customrUser4->GetUserName()] = customrUser4;

////////////////////////////////////////
    }

void AccessSystem() {
    int choice = ShowReadMenu( { "Login", "Customer Sign Up" });
    if (choice == 1)
        DoLogin();
    else
        DoSignUp();
}

void DoLogin() {

    while (true) {
        string userName, pass;
        cout << "Enter user User Name & password: ";
        cin >> userName >> pass;

        if (!usernameUserboject_map.count(userName)) {
            cout << "\nInvalid user User Name or password. Try again\n\n";
            continue;
        }
        User* user_exist = usernameUserboject_map.find(userName)->second;

//        if (pass != user_exist->GetPassword()) {
//            cout << "\nInvalid user User Name or password. Try again\n\n";
//            continue;
//        }
        currentUser = user_exist;
        break;
    }
}

void DoSignUp() {
    string userName;
    while (true) {
        cout << "Enter user name. (No spaces): ";
        cin >> userName;

        if (usernameUserboject_map.count(userName))
            cout << "Already used. Try again\n";
        else
            break;
    }
    currentUser = new Customer();
    currentUser->Read(userName);
    usernameUserboject_map[currentUser->GetUserName()] = currentUser;
}

User* GetCurrentUser() const {
    // For simplicity, I don't return it as const, which is not good
    // One ok way: return as const, and user support clone + copy contstructor. Then caller can make his own copy
    return currentUser;
}
};

#endif //PROJECT_TRAVELER_TRAVELER_USER_MNGR_H
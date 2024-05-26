//
// Created by Omar Elshehawi on 5/6/2024.
//

#ifndef PROJECT_TRAVELER_TRAVELER_USER_H
#define PROJECT_TRAVELER_TRAVELER_USER_H

using namespace std;


enum class UserType {                   // enum or enumeration is a data type consisting of named values like elements, members, etc.,
    CusomterUser = 0, AdminUser = 1     // that represent integral constants.
                                        // It provides a way to define and group integral constants. It also makes the code easy to maintain and less complex.
};

class User {
protected:
    string user_name;
    string password;
    string name;
    string email;
    UserType type = UserType::CusomterUser;

public:
    User(const User&) = delete;
    void operator=(const User&) = delete;

    User() {
    }

    virtual  ~User() {                  // To Allow dynamic casting

    }

    string toString() const {
        ostringstream oss;
        oss << "Name: " << name;
        if(type == UserType::AdminUser)
            oss << " | Admin";
        oss << '\n';
        oss << "Email: " << email << "\n";
        oss << "User name: " << user_name << "\n";
        return oss.str();

    }

    void SetEmail(const string& email) {
        this->email = email;
    }

    void SetName(const string& name) {
        this->name = name;
    }

    void SetPassword(const string& password) {
        this->password = password;
    }

    void SetUserName(const string& userName) {
        user_name = userName;
    }

    void SetType(UserType type) {
        this->type = type;
    }

    UserType GetType() const {
        return type;
    }

    void Read(const string &user_name) {
        SetUserName(user_name);

        string str;

        cout << "Enter password: ";
        cin >> str;
        SetPassword(str);

        cout << "Enter name: ";
        cin >> str;
        SetName(str);

        cout << "Enter email: ";
        cin >> str;
        SetEmail(str);
    }

    const string& GetEmail() const {
        return email;
    }

    const string& GetName() const {
        return name;
    }

    const string& GetPassword() const {
        return password;
    }

    const string& GetUserName() const {
        return user_name;
    }


};


class Admin: public User {
protected:
public:
    Admin(const Admin&) = delete;
    void operator=(const Admin&) = delete;
    Admin() {
        SetType(UserType::AdminUser);
    }
};

#endif //PROJECT_TRAVELER_TRAVELER_USER_H

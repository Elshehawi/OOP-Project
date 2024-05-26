/*
    hi i am omar
    this is teraveler site
    a site that makes ur vecation easier and more fun
    since u here so this is the main file sorce code

    i will follow u to explain the code as we go

    lets start :)
*/

#include <iostream>
#include "Traveler_User_Mngr.h"
#include "Traveler_Cstmr_View.h"
#include "Traveler_Cstmr.h"

using namespace std;

//we will define a class for the site frontend
class TravelerFrontend {
private:
    UsersManager* users_manager;
    TravelerBackend* travelerManager;
    CustomerManager* customer_manager = nullptr;

    void LoadDatabase() {
        users_manager->LoadDatabase();
    }
public:
    TravelerFrontend(const TravelerFrontend&) = delete;
    void operator = (const TravelerFrontend&) = delete;

    TravelerFrontend() : users_manager(new UsersManager()), travelerManager(new TravelerBackend()){
    }

    ~TravelerFrontend() {
        cout << "Destructor: TravelerFrontend\n";

        if (users_manager != nullptr) {
            delete users_manager;
            users_manager = nullptr;
        }
    }

    void Run() {
        LoadDatabase();

        while (true) {
            users_manager->AccessSystem();	// login/signup

            if(users_manager->GetCurrentUser()->GetType() == UserType::CusomterUser) {
                customer_manager = new CustomerManager(users_manager->GetCurrentUser(), *travelerManager);
                CustomerView view(*customer_manager);
                view.Display();
            } else
                assert(false);
        }
    }
};

int main() {
    TravelerFrontend site;
    char a;
    cout << "Are You Dr. Handosa ? (y\\n)\n";
    cin >> a;

    if (a == 'n')
        cout << "Ur User Name is (handosa) \n Ur User Name is (4545) \n";

    site.Run();
    User *user = new Customer();
    dynamic_cast<Customer *>(user);
    return 0;
}
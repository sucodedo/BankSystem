#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../Global.h"
#include "../User.h"

using namespace std;

class ClientListScreen : protected Screen
{
private:
    static void _PrintClientsList(BankClient&Client)
    {
        cout << "| " << left << setw(20) << Client.Get_First_Name();
        cout << "| " << left << setw(20) << Client.Get_Last_Name();
        cout << "| " << left << setw(15) << Client.Get_Phone_Number();
        cout << "| " << left << setw(25) << Client.Get_Email();
        cout << "| " << left << setw(12) << Client.Get_Account_Number();
        cout << "| " << left << setw(12) << Client.Get_PinCode();
        cout << "| " << left << setw(12) << Client.Get_Account_Balance();
    }
public:
    static void ClientsList()
    {
        if (!_CheckAccessRights(User::enPermissions::pListClient))
        {
            return;
        }

        ClientListScreen::_ScreenHeader("\t\tClient List Screen");
        vector<BankClient> vClsList = BankClient::GetClientsList();
        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\tClients Lists: (" << vClsList.size() << ")" << endl;

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "| " << left << setw(20) << "First Name";
        cout << "| " << left << setw(20) << "Last Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(12) << "Acc.. Number";
        cout << "| " << left << setw(12) << "Pin Code";
        cout << "| " << left << setw(12) << "Acc.. Balance";
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        if (vClsList.empty())
        {
            cout << "\n\t\t\t\t\t\t\tEmpty Client List!" << endl;
        }
        else
        {
            for (BankClient& C : vClsList)
            {
                _PrintClientsList(C);
                cout << endl;
            }
        }
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
    }

};
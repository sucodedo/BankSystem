#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../../../Libraries/InputValidate.h"

class DeleteClientScreen : protected Screen
{
private:
    static void _PrintClientInfo(BankClient Client)
    {
        cout << "Client Card" << endl;
        cout << "--------------------";
        cout << "\nFirst Name  : " << Client.Get_First_Name();
        cout << "\nLast Name   : " << Client.Get_Last_Name();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Get_Email();
        cout << "\nPhone       : " << Client.Get_Phone_Number();
        cout << "\nAcc.. Number: " << Client.Get_Account_Number();
        cout << "\nPassword    : " << Client.Get_PinCode();
        cout << "\nBalance     : " << Client.Get_Account_Balance();
        cout << "\n-----------------------" << endl;
    }

public:
    static void ShowDeleteClientScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pDeleteClient))
        {
            return;
        }

        DeleteClientScreen::_ScreenHeader("\t\tDelete Client Screen");

        string AccountNumber = InputValidate::ReadStr("Enter Account Number: ");

        while(!BankClient::IsClientExists(AccountNumber))
        {
            cout << "There is no Account Exists! try again" << endl;
            AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
        }

        BankClient DelClient = BankClient::Find(AccountNumber);

        _PrintClientInfo(DelClient);

        cout << "Delete Client: " << endl;
        char AskForDelete = 'n';
        cout << "Are you sure you want to delete that Client y/n: ";
        cin >> AskForDelete;
        if (AskForDelete == 'Y' || AskForDelete == 'y')
        {
            if (DelClient.Delete())
            {
                cout << "\nClient Deleted Successfully\n" << endl;
                _PrintClientInfo(DelClient);
            }
            else 
            {
                cout << "Something went wrong!?" << endl;
            }
        } 
    }

};
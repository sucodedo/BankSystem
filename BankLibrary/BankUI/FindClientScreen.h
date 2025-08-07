#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../../../Libraries/InputValidate.h"

class FindClientScreen : protected Screen
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
    static void ShowFindClientScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pFindClient))
        {
            return;
        }

        FindClientScreen::_ScreenHeader("\t\tFind Client");

        string AccountNumber = InputValidate::ReadStr("Enter The Account Number: ");

        while(!BankClient::IsClientExists(AccountNumber))
        {
            cout << "Client is not exists! try again" << endl;
            AccountNumber = InputValidate::ReadStr("Enter Account Number: "); 
        }

        BankClient Client = BankClient::Find(AccountNumber);

        if (Client.is_Empty())
        {
            cout << "\nClient Not Found" << endl;
        }
        else 
        {
            cout << "\nClient Found :)\n" << endl;
            _PrintClientInfo(Client);
        }
    }
};
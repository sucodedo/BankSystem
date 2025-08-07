#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../../../Libraries/InputValidate.h"


using namespace std;

class AddNewClientScreen : protected Screen
{
private:
    static void _ReadClientInfo(BankClient& Client)
    {
        Client.First_Name(InputValidate::ReadStr("Enter The First Name: "));
        Client.Last_Name(InputValidate::ReadStr("Enter The Last Name: "));
        Client.Phone_Number(InputValidate::ReadStr("Enter The Phone Number: "));
        Client.Email(InputValidate::ReadStr("Enter The Email: "));
        Client.Set_PinCode(InputValidate::ReadStr("Enter The Pin Code: "));
        Client.Set_Account_Balance(InputValidate::input_Db_Number("Enter Account Balance: ", "Invalid Input! try Again"));
    }

    // Print Bank Client Info
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
    static void ShowAddNewClient()
    {
        if (!_CheckAccessRights(User::enPermissions::pAddNewClient))
        {
            return;
        }

        AddNewClientScreen::_ScreenHeader("\t\tAdd New Client Screen");
        string AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
        while(BankClient::IsClientExists(AccountNumber))
        {
            cout << "Client Exists! Try Again" << endl;
            AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
        }

        BankClient NewClient = BankClient::GetAddNewClient(AccountNumber);

        _ReadClientInfo(NewClient);

        BankClient::enSaveResults SaveResults;
        SaveResults = NewClient.Save();

        switch (SaveResults)
        {
            case BankClient::enSaveResults::svSucceeded:
                cout << "\nClient added succeessfully.\n" << endl;
                _PrintClientInfo(NewClient);
                break;
            case BankClient::enSaveResults::svFailedEmptyObj:
                cout << "Client added Failed" << endl;
                break;
            case BankClient::enSaveResults::svFailedAccountNumberExists:
                cout << "Client already exists!" << endl;
                break;
        }
    }
};
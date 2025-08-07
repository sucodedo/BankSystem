#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../../../Libraries/InputValidate.h"

class UpdateClientInfoScreen : protected Screen
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
    static void ShowUpdateClientInfoScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pUpdateClients))
        {
            return;
        }

        UpdateClientInfoScreen::_ScreenHeader("\t\tUpdate Client Info");

        string AccountNumber = "";
        AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
        while (!BankClient::IsClientExists(AccountNumber))
        {
            cout << "Client is not exists! try again" << endl;
            AccountNumber = InputValidate::ReadStr("Enter Account Number: "); 
        }
        BankClient Client = BankClient::Find(AccountNumber);

        Client.is_Empty() ? cout << "True\n" : cout << "False\n"; 

        _PrintClientInfo(Client);

        char AskForUpdate = InputValidate::ReadChar("Are you sure you want to update this client y/n?: ");

        if (AskForUpdate == 'y' || AskForUpdate == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            _ReadClientInfo(Client);

            BankClient::enSaveResults SaveResults;

            SaveResults = Client.Save();
            switch (SaveResults)
            {
                case BankClient::enSaveResults::svSucceeded:
                    cout << "\nClient updated succeessfully.\n" << endl;
                    _PrintClientInfo(Client);
                    break;
                case BankClient::enSaveResults::svFailedEmptyObj:
                    cout << "Client update Failed" << endl;
                    break;
            }
        }
    }
};
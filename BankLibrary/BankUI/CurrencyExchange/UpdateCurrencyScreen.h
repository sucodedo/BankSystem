#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../Currency.h"
#include "../../../../Libraries/InputValidate.h"

class UpdateCurrecyScreen : protected Screen
{
private:
    static void _PrintCurrencyCard(Currency& CurrencyObj)
    {
        cout << "\nCurrency Card:" << endl;
        cout << "-----------------------\n";
        cout << "Country : " << CurrencyObj.CurrencyCountry() << endl;
        cout << "Code    : " << CurrencyObj.CurrencyCode() << endl;
        cout << "Name    : " << CurrencyObj.CurrencyName() << endl;
        cout << "Rate(1$): " << CurrencyObj.Rate() << endl;
        cout << "-----------------------\n";
    }

public:
    static void ShowUpdateCurrencyScreen()
    {
        _ClearScreen();
        _ScreenHeader("\t\tUpdate Currency Screen");
        string CurrencyCode = InputValidate::ReadStr("Enter Currency Code: ");
        Currency CurrencyObj = Currency::FindByCode(CurrencyCode);
        if (CurrencyObj.is_Empty())
        {
            cout << "Currency Was Not Found!" << endl;
        }
        else 
        {
            _PrintCurrencyCard(CurrencyObj);

            char Answer = InputValidate::ReadChar("\nAre you sure you want to update the rate of this currency y/n?: ");
            
            if (Answer == 'y' || Answer == 'Y')
            {
                cout << "\nUpdate Currency Rate:" << endl;
                cout << "-----------------------\n" << endl;
                CurrencyObj.UpdateRate(InputValidate::input_Number("Enter New Rate: ", "Invalid Number! Try Again "));
                _PrintCurrencyCard(CurrencyObj);
            } 
            else 
                cout << "You canceled this operation" << endl;
        }
    }
};
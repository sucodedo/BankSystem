#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../Currency.h"
#include "../../../../Libraries/InputValidate.h"

class FindCurrencyScreen : protected Screen
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
    static void ShowFindCurrencyScreen()
    {
        _ClearScreen();

        _ScreenHeader("\t\tFind Currency Screen");

        short FindBy = InputValidate::readShortNumBetween(1, 2, "Find By: [1] Code Or [2] Country? ", "Invalid Input! ");
        
        string CurrencyInput = ""; 

        if (FindBy == 1)
        {
            CurrencyInput = InputValidate::ReadStr("Enter Currency Code: ");
            
            Currency CurrencyObj = Currency::FindByCode(CurrencyInput);

            if (!CurrencyObj.is_Empty())
            {
                cout << "\nCurrency Found :-)" << endl;
                _PrintCurrencyCard(CurrencyObj);   
            }
            else 
            {
                cout << "\nCurrency Wan Not Found :-(" << endl;
            }
        }

        else 
        {
            CurrencyInput = InputValidate::ReadStr("Enter Currency Country: ");
            
            Currency CurrencyObj = Currency::FindByCountry(CurrencyInput);

            if (!CurrencyObj.is_Empty())
            {
                cout << "\nCurrency Found :-)" << endl;
                _PrintCurrencyCard(CurrencyObj);   
            }
            else 
            {
                cout << "\nCurrency Wan Not Found :-(" << endl;
            }
        }
    }
};
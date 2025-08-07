#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../Currency.h"
#include "../../../../Libraries/InputValidate.h"

class ExchangeCalculatorScreen : protected Screen
{
private:
    static void _PrintCurrencyCard(Currency& CurrencyObj, string CardTitle)
    {
        cout << "\n" << CardTitle << endl;
        cout << "-----------------------\n";
        cout << "Country : " << CurrencyObj.CurrencyCountry() << endl;
        cout << "Code    : " << CurrencyObj.CurrencyCode() << endl;
        cout << "Name    : " << CurrencyObj.CurrencyName() << endl;
        cout << "Rate(1$): " << CurrencyObj.Rate() << endl;
        cout << "-----------------------\n";
    }

public:
    static void ShowExchangeCalculatorScreen()
    {
        char Answer = 'y';
        while (Answer == 'y' || Answer == 'y')
        {
            _ClearScreen();
            _ScreenHeader("\t\tEchange Caclulator Screen");

            string Currency1 = InputValidate::ReadStr("\nEnter Currency 1 Code: ");
            string Currency2 = InputValidate::ReadStr("\nEnter Currency 2 Code: ");

            Currency FromCurrencyObj = Currency::FindByCode(Currency1);
            Currency ToCurrencyObj = Currency::FindByCode(Currency2);

            float Amount = InputValidate::input_Number("\nEnter Amount To Echange: ", "\nInvalid Num! Try Again: ");

            // cout << Currency::ExchangeCalculator(Currency1, Currency2, Amount) << endl;

            if (FromCurrencyObj.is_Empty() && ToCurrencyObj.is_Empty())
            {
                cout << "Invalid Input Try Another Time" << endl;
            }
            else 
            {
                _PrintCurrencyCard(FromCurrencyObj, "Counvert From:");
                cout << Amount << " " << FromCurrencyObj.CurrencyCode() << " = " << Currency::ExchangeCalculator(Currency1, Currency2, Amount) << " " << ToCurrencyObj.CurrencyCode() << endl;
            }

            Answer = InputValidate::ReadChar("Do you want to perform another calculation y/n? : ");
        }

    }
};
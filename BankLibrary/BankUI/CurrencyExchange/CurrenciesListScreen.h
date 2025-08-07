#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../Currency.h"
#include "../../../../Libraries/InputValidate.h"

class CurrenciesListScreen : protected Screen
{
private:
    static void _PrintCurrencyRecordLine(Currency& CurrencyRecord)
    {
        cout << setw(12) << right << "| " << setw(20) << left << CurrencyRecord.CurrencyCountry();
        cout << setw(12) << right << "| " << setw(10) << left << CurrencyRecord.CurrencyCode();
        cout << setw(12) << right << "| " << setw(20) << left << CurrencyRecord.CurrencyName();
        cout << setw(12) << right << "| " << setw(10) << left << CurrencyRecord.Rate();
        
    }

public:
    static void ShowCurrenciesScreen()
    {
        _ClearScreen();

        vector<Currency> CurrenciesList = Currency::GetCurrenciesList();
        
        string subTite = "";
        
        if (CurrenciesList.size() < 2)
        {
            subTite = "\t\t(" + to_string(CurrenciesList.size()) + ')' + " Currency"; 
        }
        else
            subTite = "\t\t(" + to_string(CurrenciesList.size()) + ')' + " Currencies"; 

        _ScreenHeader("\t\tCurrencies List Screen", subTite);

        cout << setw(10) << right << " " << "_______________________________________________________________";
        cout << "_______________________________________________________________\n\n";

        cout << setw(12) << right << "| " << setw(20) << left << "Country";
        cout << setw(12) << right << "| " << setw(10) << left << "Code";
        cout << setw(12) << right << "| " << setw(20) << left << "Name";
        cout << setw(12) << right << "| " << setw(10) << left << "Rate/(1$)";

        cout << endl;
        cout << setw(10) << right << " " << "_______________________________________________________________";
        cout << "_______________________________________________________________\n\n";

        if (CurrenciesList.empty())
        {
            cout << "\t\t\t\t\t\t\tThere Is No Currencies!" << endl;

            cout << setw(10) << right << " " << "_______________________________________________________________";
            cout << "_______________________________________________________________\n";
        }
        else
        {
            for (Currency& C : CurrenciesList)
            {
                _PrintCurrencyRecordLine(C);
                cout << endl;
            }

            cout << setw(10) << right << " " << "_______________________________________________________________";
            cout << "_______________________________________________________________\n";
        }
        
    }

};
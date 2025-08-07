#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../Currency.h"
#include "../../../Libraries/InputValidate.h"

#include "CurrencyExchange/CurrenciesListScreen.h"
#include "CurrencyExchange/FindCurrencyScreen.h"
#include "CurrencyExchange/UpdateCurrencyScreen.h"
#include "CurrencyExchange/ExchangeCalculatorScreen.h"

class CurrencyExchangeMenueScreen : protected Screen
{
private:
    enum eCurrencyExchangeMenueOptions 
    {
        eCurrenciesList = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenue = 5
    };

    static short _ReadCurrencyExchangeOption()
    {
        return InputValidate::readShortNumBetween(1, 5, "\t\t\t\t\t\tWhat do you want to choose [1-5]?: ", "\n\t\t\t\t\t\t** Invalid Input Enter a number between 1 - 5! try again **\n");
    }

    static void _GoBackToShowCurrencyExchangeMenueScreen()
    {
        char input;
        cout << "\nEnter any Key to go back to Currency Exchange menue: " << endl;
        cin >> input;
        ShowCurrencyExchangeMenueScreen();
    }

    static void _ShowCurrenciesListScreen()
    {
        CurrenciesListScreen::ShowCurrenciesScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        FindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        UpdateCurrecyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        ExchangeCalculatorScreen::ShowExchangeCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenueOption(eCurrencyExchangeMenueOptions Options)
    {
        switch (Options)
        {
        case eCurrencyExchangeMenueOptions::eCurrenciesList:
            _ClearScreen();
            _ShowCurrenciesListScreen();
            _GoBackToShowCurrencyExchangeMenueScreen();
            break;

        case eCurrencyExchangeMenueOptions::eFindCurrency:
            _ClearScreen();
            _ShowFindCurrencyScreen();
            _GoBackToShowCurrencyExchangeMenueScreen();
            break;

        case eCurrencyExchangeMenueOptions::eUpdateRate:
            _ClearScreen();
            _ShowUpdateRateScreen();
            _GoBackToShowCurrencyExchangeMenueScreen();
            break;

        case eCurrencyExchangeMenueOptions::eCurrencyCalculator:
            _ClearScreen();
            _ShowCurrencyCalculatorScreen();
            _GoBackToShowCurrencyExchangeMenueScreen();
            break;

        case eCurrencyExchangeMenueOptions::eMainMenue:
            break;

        default:
            break;
        }
    }

public:
    static void ShowCurrencyExchangeMenueScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pCurrencyexchange))
        {
            return;
        }
        
        _ClearScreen();

        _ScreenHeader("\t\tCurrency Exchange Screen");

        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << "\t\t\tCurrency Exchange Menue" << endl;
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << left << "[01] List Currencies.    " << endl;
        cout << setw(48) << "" << left << "[02] Find Currency.      " << endl;
        cout << setw(48) << "" << left << "[03] Update Rate.        " << endl;
        cout << setw(48) << "" << left << "[04] Currency Calculator." << endl;
        cout << setw(48) << "" << left << "[05] Main Menue.         " << endl;
        cout << setw(48) << "" << "======================================================\n";

        _PerformCurrencyExchangeMenueOption((eCurrencyExchangeMenueOptions) _ReadCurrencyExchangeOption());
    }

};
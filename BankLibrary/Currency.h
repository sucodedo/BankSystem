#pragma once 
#include <iostream>
#include <vector>
#include <fstream>

#include "../../Libraries/StrLib.h"

using namespace std;

class Currency
{
private:
    enum enMode {EmptyMode = 0, UpdateMode = 1};

    enMode _Mode;
    string _CurrencyCountry = "", _CurrencyCode = "", _CurrencyName = "";
    float _Rate = 0;

    // Update Currency 
    void _Update()
    {
        vector<Currency> _CurrenciesList = _LoadCurrenciesFromFile();
        for (Currency& C : _CurrenciesList)
        {
            if (this->_CurrencyCode == C._CurrencyCode)
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyChanges(_CurrenciesList);
    }

    // _ConvertDateLineToRecord
    static Currency _ConvertDateLineToRecord(string Line, string Seperator = "#//#")
    {   
        vector<string> _vCurrencies = Str::split(Line, Seperator);

        return Currency(enMode::UpdateMode, _vCurrencies[0], _vCurrencies[1], _vCurrencies[2], stof(_vCurrencies[3]));
    }

    // _ConvertRecordToDataLine
    static string _ConvertRecordToDataLine(Currency CurrencyRecord, string Seperator = "#//#")
    {
        string DataLine = "";

        DataLine += CurrencyRecord._CurrencyCountry + Seperator;
        DataLine += CurrencyRecord._CurrencyCode + Seperator;
        DataLine += CurrencyRecord._CurrencyName + Seperator;
        DataLine += to_string(CurrencyRecord._Rate);

        return DataLine;
    }

    // Load Currencies From File
    static vector<Currency> _LoadCurrenciesFromFile()
    {
        vector<Currency>_vCurrenciesList;
        fstream File;
        File.open("Currencies.txt", ios::in); // Read Mode
        if (File.is_open())
        {
            string Line = "";

            while (getline(File, Line))
            {
                Currency CurrencyDataLine = _ConvertDateLineToRecord(Line, "#//#");
                _vCurrenciesList.push_back(CurrencyDataLine);
            }
            File.close();
        }
        return _vCurrenciesList;
    }

    // _SaveChanges
    bool _SaveCurrencyChanges(vector<Currency>&Currencies)
    {
        fstream File;
        File.open("Currencies.txt", ios::out); // Write Mode
        if (File.is_open())
        {
            for (Currency& C : Currencies)
            {
                File << _ConvertRecordToDataLine(C) << '\n';   
            }
            File.close();
        } 
        return true;
    }

    static Currency _GetEmptyCurrencyObject()
    {
        return Currency(enMode::EmptyMode, "", "", "", 0);
    }

public:

    // Constractor.
    Currency(enMode Mode, string CurrencyCountry, string CurrencyCode, string CurrencyName, float CurrencyExchangeRate)
    {
        this->_Mode = Mode;
        this->_CurrencyCountry = CurrencyCountry;
        this->_CurrencyCode = CurrencyCode;
        this->_CurrencyName = CurrencyName;
        this->_Rate = CurrencyExchangeRate;
    }

    // Setters && Getters.
    string CurrencyCountry()
    {
        return this->_CurrencyCountry;
    }

    string CurrencyCode()
    {
        return this->_CurrencyCode;
    }

    string CurrencyName()
    {
        return this->_CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        this->_Rate = NewRate;
        _Update();
    }

    float Rate()
    {
        return this->_Rate;
    }

    bool is_Empty()
    {
        return (this->_Mode == enMode::EmptyMode);
    }

    static bool IsCurrencyExists(string CountryCode)
    {
        Currency CurrencyObj = Currency::FindByCode(CountryCode);
        return (!CurrencyObj.is_Empty());
    }

    // Get List Currencies 
    static vector<Currency> GetCurrenciesList()
    {   
        return _LoadCurrenciesFromFile();
    }

    // Find Currency By Country Name
    static Currency FindByCountry(string CurrencyCountry)
    {
        CurrencyCountry = Str::AllLettersToUpper(CurrencyCountry);

        vector<Currency> _CurrenciesList = _LoadCurrenciesFromFile();
        for (Currency& C : _CurrenciesList)
        {
            if (Str::AllLettersToUpper(C._CurrencyCountry) == CurrencyCountry)
            {
                return C;
            }
        }
        return _GetEmptyCurrencyObject();
    }

    // Find Currency By Country Code
    static Currency FindByCode(string CurrencyCode)
    {
        CurrencyCode = Str::AllLettersToUpper(CurrencyCode);

        vector<Currency> _CurrenciesList = _LoadCurrenciesFromFile();
        for (Currency& C : _CurrenciesList)
        {
            if (C._CurrencyCode == CurrencyCode)
            {
                return C;
            }
        }
        return _GetEmptyCurrencyObject();
    }

    // Currency Claculator
    static float ExchangeCalculator(string Currency_From, string Currency_To, float Amount)
    {
        if (Str::AllLettersToUpper(Currency_From) == "USD")
        {
            return Amount * FindByCode(Currency_To).Rate();
        }
        else if (Str::AllLettersToUpper(Currency_To) == "USD")
        {
            return Amount / FindByCode(Currency_From).Rate();
        }
        else
        {
            return Amount / FindByCode(Currency_From).Rate() * FindByCode(Currency_To).Rate();
        }
    }

    float ConvertToUSD(float Amount)
    {
        return (float) Amount / this->Rate();
    }

    float ConvertToOtherCurrency(float Amount, Currency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);
        
        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }
        return (float) AmountInUSD * Currency2.Rate();
    }

};
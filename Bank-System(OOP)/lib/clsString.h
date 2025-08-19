#pragma once
#include <iostream>
#include <vector>

using namespace std;



class clsString
{
private :
    string _Value;

public : 

    clsString()
    {
        _Value = "";
    }
    
    clsString(string Value)
    {
        _Value = Value;
    }

    void SetValue(string Value)
    {
        _Value = Value;
    }

    string GetValue()
    {
        return _Value;
    }

    static short Length(string S1)
    {
        return S1.length();
    }

    short Length()
    {
        return Length(_Value);
    }

    static short CountWords(string S1)
    {
        string delim = " ";
        short pos;
        string sWord;
        short Counter = 0;
    
        while ((pos = S1.find(delim)) != string::npos)
        {
            sWord = S1.substr(0, pos);
    
            if(sWord != "")
            {
                Counter++;
            }
            
            S1.erase(0, pos + delim.length());
        }
    
        if(S1 != "")
        {
            Counter++;
        }
    
        return Counter;

    }

    short CountWrods()
    {
        return CountWords(_Value);
    }

    static string UpperCaseFirstCaracterOfEachWord(string S1)
    {
        bool IsFirstLetter = true;
    
    
        for(int i = 0; i < S1.length(); i++)
        {
            if(S1[i] != ' ' && IsFirstLetter)
            {
                S1[i] =  toupper(S1[i]);
            }
    
            IsFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    void UpperCaseFirstCaracterOfEachWord()
    {
        // no need to return value , this function will directly update the object value 
        _Value = UpperCaseFirstCaracterOfEachWord(_Value);
    }
    
    static string LowerCaseFirstCaracterOfEachWord(string S1)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);

            }

            isFirstLetter = (S1[i] == ' ' ? true : false);

        }

        return S1;
    }

    void LowerCaseFirstCaracterOfEachWord()
    {
        _Value = LowerCaseFirstCaracterOfEachWord(_Value);
    }

    static string UpperAllString(string S1)
   {

        for(int i = 0; i < S1.length(); i++)
        {
                S1[i] =  toupper(S1[i]);
        }
    
        return S1;
    }

    void UpperAllString()
    {
        _Value = UpperAllString(_Value);
    }

    static string LowerAllString(string S1)
    {

        for(int i = 0; i < S1.length(); i++)
        {
                S1[i] =  tolower(S1[i]);
        }
    
        return S1;
    }

    void LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

    static char InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static string InvertAllStringLetters(string S1)
    {
        for(short i = 0 ; i < S1.length(); i++)\
        {
            S1[i] = InvertLetterCase(S1[i]);
        }

        return S1;
    }

    void InvertAllStringLetters()
    {
        _Value = InvertAllStringLetters(_Value);
    }
  
    enum enWhatToCount{SmallLetters =  0, CapitalLetters = 1, All = 3};

    static short CountLetters(string S1, enWhatToCount WhatToCount = All)
    {
        if(WhatToCount == All)
        {
            return S1.length();
        }
        
        short Counter = 0;
    
        for(short i = 0; i < S1.length(); i++)
        {
            if(WhatToCount == SmallLetters && islower(S1[i]))
            {
                Counter++;
            }
            if(WhatToCount == CapitalLetters && isupper(S1[i]))
            {
                Counter++;
            }
        }
    
        return Counter;
    }

    short CountLetters()
    {
        return CountLetters(_Value, All);
    }

    static short CountCapitalLetters(string S1)
    {

        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (isupper(S1[i]))
                Counter++;

        }

        return Counter;
    }

    short CountCapitalLetters()
    {
        return CountCapitalLetters(_Value);
    }

    static short CountSmallLetters(string S1)
    {

        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (islower(S1[i]))
                Counter++;

        }

        return Counter;
    }

    short CountSmallLetters()
    {
        return CountSmallLetters(_Value);
    }
   
    static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
    {

        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }

        }

        return Counter;
    }

    short CountSpecificLetter( char Letter, bool MatchCase = true)
    {
        return CountSpecificLetter(_Value,Letter, MatchCase);
    }

    static bool IsVowel(char char1)
    {
        char1 = tolower(char1);
        if(char1 == 'a' || char1 == 'o'|| char1 == 'i' || char1 == 'u'|| char1 == 'e' )
        {
            return true;
        }

        return false;
    }

    static short CountVowels(string S1)
    {
        short Counter = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if(IsVowel(S1[i]))
            {
                Counter++;
            }
            
        }
        return Counter;
    }

    short CountVowels()
    {
        return CountVowels(_Value);
    }

    static vector <string> SplitString(string S1, string delim)
    {
        vector <string> vString;
        short pos = 0;
        string sWord;
    
        while((pos = S1.find(delim)) != string::npos)
        {
            sWord = S1.substr(0,pos);
            
            if(sWord != "")
            {
                vString.push_back(sWord);
            }
    
            S1.erase(0, pos + delim.length());
        }
    
        if(S1 != "")
        {
            vString.push_back(S1);
        }
    
        return vString;
    }

    vector <string> SplitString()
    {
        return SplitString(_Value, " ");
    }

    static string TrimLeft(string S1)
    {
        for(int i = 0; i < S1.length(); i++)
        {
            if(S1[i] != ' ')
            {
               return S1.substr(i, S1.length() - i);
            }
        }
    
        return "";
    }

    void TrimLeft()
    {
      _Value = TrimLeft(_Value);
    }
    
    static string TrimRight(string S1)
    {

        for (short i = S1.length() - 1; i >= 0; i--)
        {
            if (S1[i] != ' ')
            {
                return S1.substr(0, i + 1);
            }
        }
      return "";
    }
 
    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    static string Trim(string S1)
    {
        return (TrimLeft(TrimRight(S1)));
    }

    void Trim()
    {
        _Value= Trim(_Value);
    }

    static string JoinString(vector<string> vString, string Delim)
    {
        string S1 = "";

        for (string& s : vString)
        {
            S1 = S1 + s + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string JoinString(string arrString[], short Length, string Delim)
    {

        string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());

    }


    static string ReverseWordsInString(string S1)
    {
    
        vector<string> vString;
        string S2 = "";
    
        vString = SplitString(S1, " ");
    
        // declare iterator
        vector<string>::iterator iter = vString.end();
    
        while (iter != vString.begin())
        {
            --iter;
            S2 += *iter + " ";
        }
    
        S2 = S2.substr(0, S2.length() - 1); //remove last space.
    
        return S2;
    }
    
    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
    }
    
    static string ReplaceWord(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {
    
        vector<string> vString = SplitString(S1, " ");
    
        for (string& s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }
            }
        }
    
        return JoinString(vString, " ");
    }
    
    string ReplaceWord(string StringToReplace, string sRepalceTo)
    {
        return ReplaceWord(_Value, StringToReplace, sRepalceTo);
    }
    
    static string RemovePunctuations(string S1)
    {
        string S2 = "";
    
        for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }
    
        return S2;
    }
    
    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }

};
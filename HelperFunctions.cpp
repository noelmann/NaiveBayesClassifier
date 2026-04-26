//
// Created by DerWiggler01 on 26.04.2026.
//

#include "HelperFunctions.h"
#include <string>
#include <vector>
#include <iostream>

std::string HelperFunctions::getInput()
{
    std::string s;
    std::getline(std::cin,s);
    return s;
}

std::string HelperFunctions::convertStringToLower(const std::string& s)
{
    std::string temp;
    for (int i = 0; i < s.length(); i++)
    {
        temp+=tolower(s[i]);
    }

    return temp;
}

std::vector<std::string> HelperFunctions::splitString(const std::string& input, const std::string& d) {
    std::vector<std::string> result;

    size_t start = 0;
    size_t end = input.find(d);

    while (end != std::string::npos) {
        result.push_back(input.substr(start, end - start));
        start = end + d.length();
        end = input.find(d, start);
    }
    result.push_back(input.substr(start));

    return result;
}


std::vector<std::string> HelperFunctions::tokenize(const std::string &s, char d)
{
    std::vector<std::string> substrings;
    std::string temp;
    //cout << s << endl;
    for (int i = 0;i<s.size()+1;i++)
    {
        if (i == s.size() || s[i] == d)
        {
            substrings.push_back(temp);
            //cout << temp << endl;
            temp = "";
        }
        else if (s[i] != d)
        {
            temp+=s[i];
        }
    }
    return substrings;
}
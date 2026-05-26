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

std::string HelperFunctions::getSpamMailPath()
{
    std::cout << "Please enter the full path to the spam mail txt files:" << std::endl;
    std::string spamPath = HelperFunctions::getInput();
    return spamPath;
}

std::string HelperFunctions::getNonSpamMailPath()
{
    std::cout << "Please enter the full path to the non-spam(ham) mail txt files:" << std::endl;
    std::string nonspamPath = HelperFunctions::getInput();
    return nonspamPath;
}

std::string HelperFunctions::getTestSetPath()
{
    std::string path;
    std::cout << "Please enter the path of the testset:" << std::endl;
    getline(std::cin,path);
    return path;
}

std::string HelperFunctions::getClassifierSaveLocation()
{
    std::cout << "Please enter the path where the trained classifier should be saved:" << std::endl;
    std::string saveLocation = HelperFunctions::getInput();
    return saveLocation;
}

std::string HelperFunctions::getLocationOfSavedClassifier()
{
    std::cout << "Please enter the path of the saved classifier:" << std::endl;
    std::string saveLocation = HelperFunctions::getInput();

    return saveLocation;
}

std::string HelperFunctions::getMailToClassify()
{
    std::cout << "Please enter the content of the mail to be classified:" << std::endl;
    std::string mail = HelperFunctions::getInput();

    return mail;
}

int HelperFunctions::getSmoothingParameter()
{
    std::cout << "Please enter an integer value >=1 to be used as the smoothing parameter:";
    int smoothingValue = stoi(HelperFunctions::getInput());
    std::cout << std::endl;
    return smoothingValue;
}

void HelperFunctions::showInfoScreen()
{
    std::cout << "Welcome to a simple naive bayes spam/ham classifier demo with add-k smoothing." << std::endl;
}
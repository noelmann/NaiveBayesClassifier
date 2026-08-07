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

//splits a string at a delimiter string
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

//splits a string at given character
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
    std::cout << R"(Please enter the full path to the spam mail txt files[e.g. D:\NaiveBayesClassifier\SpamTrainingSet]:)" << std::endl;
    std::string spamPath = HelperFunctions::getInput();
    std::cout << std::endl;
    return spamPath;
}

std::string HelperFunctions::getNonSpamMailPath()
{
    std::cout << R"(Please enter the full path to the non-spam(ham) mail txt files[e.g. D:\NaiveBayesClassifier\NonSpamTrainingSet]:)" << std::endl;
    std::string nonspamPath = HelperFunctions::getInput();
    std::cout << std::endl;
    return nonspamPath;
}

std::string HelperFunctions::getTestSetPath()
{
    std::string path;
    std::cout << R"(Please enter the path of the testset[e.g. D:\NaiveBayesClassifier\SpamTestset]:)" << std::endl;
    getline(std::cin,path);
    return path;
}

std::string HelperFunctions::getClassifierSaveLocation()
{
    std::cout << R"(Please enter the path where the trained classifier should be saved[e.g. D:\NaiveBayesClassifier\trainedClassifier.txt]:)" << std::endl;
    std::string saveLocation = HelperFunctions::getInput();
    std::cout << std::endl;
    return saveLocation;
}

std::string HelperFunctions::getLocationOfSavedClassifier()
{
    std::cout << R"(Please enter the path of the saved classifier[e.g. D:\NaiveBayesClassifier\finalClassifier.txt]:)" << std::endl;
    std::string saveLocation = HelperFunctions::getInput();
    std::cout << std::endl;

    return saveLocation;
}

std::string HelperFunctions::getMailToClassify()
{
    std::cout << "Please enter the content of the mail to be classified:" << std::endl;
    std::string mail = HelperFunctions::getInput();
    std::cout << std::endl;

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
    std::cout << "Welcome to a simple naive bayes spam/ham classifier demo with add-k smoothing." << std::endl << std::endl;
}

int HelperFunctions::determineClassificationTask()
{
    std::string input;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "What type of classification task do you choose?" << std::endl;
        std::cout << "[1] Classify dataset"<< std::endl;
        std::cout << "[2] Classify custom text entered via CLI"<< std::endl;
        input = HelperFunctions::convertStringToLower(HelperFunctions::getInput());
        std::cout << std::endl;
        if (input == "1" || input == "2")
        {
            validInput = true;
        }
        else
        {
            std::cout << "Please enter the number of your choice" << std::endl;
            validInput = false;
            continue;
        }
    }

    return std::stoi(input);
}

bool HelperFunctions::useExistingClassifier()
{
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "Do you want to use a classifier stored on disk?" << std::endl;
        std::cout << "Yes(y) or No(n): ";
        std::string input = HelperFunctions::convertStringToLower(HelperFunctions::getInput());
        std::cout << std::endl;
        if (input == "y" || input == "yes")
        {
            validInput = true;
            return true;
        }
        else if (input == "n" || input == "no")
        {
            validInput = true;
            return false;
        }
        else
        {
            std::cout << "Please enter only yes(y) or no(n)" << std::endl << std::endl;
            validInput = false;
            continue;
        }
    }

    return true;
}

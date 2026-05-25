//
// Created by DerWiggler01 on 26.04.2026.
//

#ifndef NAIVEBAYESCLASSIFIER_HELPERFUNCTIONS_H
#define NAIVEBAYESCLASSIFIER_HELPERFUNCTIONS_H
#include <string>
#include <vector>


class HelperFunctions
{
    public:
    static std::string getInput();
    static std::string convertStringToLower(const std::string& s);
    static std::vector<std::string> splitString(const std::string& input, const std::string& d);
    static std::vector<std::string> tokenize(const std::string &s, char d);

    static std::string getSpamMailPath();
    static std::string getNonSpamMailPath();
    static std::string getTestSetPath();
    static std::string getClassifierSaveLocation();
    static std::string getLocationOfSavedClassifier();
    static int getSmoothingParameter();
};


#endif //NAIVEBAYESCLASSIFIER_HELPERFUNCTIONS_H

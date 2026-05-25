//
// Created by DerWiggler01 on 25.05.2026.
//

#ifndef NAIVEBAYESCLASSIFIER_CLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_CLASSIFIER_H
#include <iostream>

class Classifier
{
    public:
    Classifier();
    bool useExistingClassifier();
    bool loadClassifierFromDisk();
    bool trainClassifier();
    bool saveClassifierOnDisk();
    bool classify(const std::string &text);
    void testClassifierOnTestset();
    void showInfoScreen();
    bool loadNonSpamMailFile(const std::string& path);
    bool loadSpamMailFile(const std::string& path);

};


#endif //NAIVEBAYESCLASSIFIER_CLASSIFIER_H

//
// Created by DerWiggler01 on 25.05.2026.
//

#ifndef NAIVEBAYESCLASSIFIER_CLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_CLASSIFIER_H
#include <iostream>
#include <map>

using namespace std;

class Classifier
{
    public:
    Classifier(bool enterVerboseMode);
    bool loadClassifierFromDisk();
    bool trainClassifier();
    bool saveClassifierOnDisk();
    bool classify(const std::string &text);
    void testClassifierOnTestset();
    void showInfoScreen();
    bool loadNonSpamMailFile(const std::string& path);
    bool loadSpamMailFile(const std::string& path);
    void enableVerboseMode();
    void disableVerboseMode();

    private:
    string spamCorpus;
    string nonspamCorpus;
    map<string, double> spamDictionary;
    map<string, double> nonspamDictionary;
    double priorSpam = 0.5;
    double priornotSpam = 1-priorSpam;
    double totalSpamTokenCount = 0;
    double totalnotSpamTokenCount = 0;
    string delimiter = ":<<<|||>>>:";
    bool verbose = false;

};


#endif //NAIVEBAYESCLASSIFIER_CLASSIFIER_H

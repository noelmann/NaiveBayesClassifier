//
// Created by DerWiggler01 on 25.05.2026.
//

#include "Classifier.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <map>
#include "HelperFunctions.h"

using namespace std;

Classifier::Classifier(bool enterVerboseMode)
{
    if (enterVerboseMode)
    {
        enableVerboseMode();
    }
    else
    {
        disableVerboseMode();
    }
}

void Classifier::enableVerboseMode()
{
    verbose = true;
}

void Classifier::disableVerboseMode()
{
    verbose = false;
}

bool Classifier::loadSpamMailFile(const string& path)
{
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string fullFilePath = entry.path().string();

        if (verbose)
        {
            cout << fullFilePath << endl;
        }
        ifstream MyReadFile(fullFilePath);
        string text;

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, text))
        {
            // Output the text from the file
            spamCorpus += text + " ";
            //cout << text << endl;
        }

        // Close the file
        MyReadFile.close();
    }
    return true;
}

bool Classifier::loadNonSpamMailFile(const string& path)
{
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string fullFilePath = entry.path().string();

        if (verbose)
        {
            cout << fullFilePath << endl;
        }
        ifstream MyReadFile(fullFilePath);
        string text;

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, text))
        {
            // Output the text from the file
            nonspamCorpus += text + " ";
            //cout << text << endl;
        }

        // Close the file
        MyReadFile.close();
    }
    return true;
}


bool Classifier::trainClassifier()
{
    //P(A|B)=>P(B|A)*P(A)
    //P(s1,s2,s3...|Spam)*P(Spam)=>P(s1|Spam)*P(s2|Spam)*P(s3|Spam)*P(Spam)
    ///P(s1,s2,s3...|notSpam)*P(notSpam)=>P(s1|notSpam)*P(s2|notSpam)*P(s3|notSpam)*P(notSpam)


    //Ask user for spam mail path txt
    string spamPath = HelperFunctions::getSpamMailPath();
    //Ask user for non spam mail path txt
    string nonspamPath = HelperFunctions::getNonSpamMailPath();

    int k = HelperFunctions::getSmoothingParameter();

    loadSpamMailFile(spamPath);
    loadNonSpamMailFile(nonspamPath);


    vector<string> tokens_spam = HelperFunctions::tokenize(spamCorpus,' ');
    vector<string> tokens_nonspam = HelperFunctions::tokenize(nonspamCorpus,' ');

    for (const string &token : tokens_spam)
    {
        if (spamDictionary[token])
        {
            spamDictionary[token] += 1;
            totalSpamTokenCount += 1;
        }
        else
        {
            spamDictionary[token] = 1+k;
            totalSpamTokenCount += 1+k;
        }
    }

    for (const string &token : tokens_nonspam)
    {
        if (nonspamDictionary[token])
        {
            nonspamDictionary[token] += 1;
            totalnotSpamTokenCount += 1;
        }
        else
        {
            nonspamDictionary[token] = 1+k;
            totalnotSpamTokenCount += 1+k;
        }
    }


    vector<string> combinedCorpusTokens = tokens_spam;
    combinedCorpusTokens.insert(combinedCorpusTokens.begin(), tokens_nonspam.begin(), tokens_nonspam.end());

    for (const string &token : combinedCorpusTokens)
    {
        if (!spamDictionary[token])
        {
            spamDictionary[token] = k;
            totalSpamTokenCount += k;
        }

        if (!nonspamDictionary[token])
        {
            nonspamDictionary[token] = k;
            totalnotSpamTokenCount += k;
        }
    }


    for (const auto &pair : spamDictionary)
    {
        spamDictionary[pair.first] = pair.second/totalSpamTokenCount;
    }

    for (const auto &pair : nonspamDictionary)
    {
        nonspamDictionary[pair.first] = pair.second/totalnotSpamTokenCount;
    }

    priorSpam=totalSpamTokenCount/(totalSpamTokenCount+totalnotSpamTokenCount);
    priornotSpam=totalnotSpamTokenCount/(totalSpamTokenCount+totalnotSpamTokenCount);

    //cout << "PriorSpam:" << priorSpam << endl;
    //cout << "PriorNotSpam:" << priornotSpam << endl;
    return true;
}

bool Classifier::classify(const string &text)
{
    vector<string> input = HelperFunctions::tokenize(text,' ');
    double spamProbability = 0;
    double hamProbability = 0;
    for (const string &token : input)
    {
        if (!spamDictionary[token])
        {
            if (verbose)
            {
                cout << "UNKNOWN TOKEN!" << endl;
            }
        }
        else
        {
            spamProbability += log(spamDictionary[token]);
        }


        if (!nonspamDictionary[token])
        {
            if (verbose)
            {
                cout << "UNKNOWN TOKEN!" << endl;
            }
        }
        else
        {
            hamProbability += log(nonspamDictionary[token]);
        }

    }

        spamProbability+=log(priorSpam);
        hamProbability+=log(priornotSpam);


    //cout << "SpamProbability:" << pow(numbers::e,spamProbability) << endl;
    //cout << "HamProbability:" <<  pow(numbers::e,hamProbability) << endl;

    if (verbose)
    {
        cout << "SpamProbability:" << spamProbability << endl;
        cout << "HamProbability:" <<  hamProbability << endl;
    }


    if (spamProbability > hamProbability)
    {
        cout << "Result:Spam!" << endl << endl;
        return true;
    }
    else
    {
        cout << "Result:Ham!" << endl << endl;
        return false;
    }
    return false;
}

void Classifier::testClassifierOnTestset()
{
    /*string text;
    for (;;)
    {
        cout << "Please enter the mail:" << endl;
        getline(cin,text);
        if (text == "terminate") {
            return;
        }
        classify(text);
    }*/

    double unkCounter = 0;
    double nonUnkCounter = 0;
    double spamCounter = 0;
    double hamCounter = 0;
    double totalCounter = 0;

    string path = HelperFunctions::getTestSetPath();
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string mail;
        string fullFilePath = entry.path().string();

        if (verbose)
        {
            cout << fullFilePath << endl;
        }
        ifstream MyReadFile(fullFilePath);
        string text;

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, text))
        {
            // Output the text from the file
            mail += text + " ";
            //cout << text << endl;
        }
        totalCounter++;
        if (classify(mail)) {
            spamCounter++;
        }
        else {
            hamCounter++;
        }

        vector<string> tokenized = HelperFunctions::tokenize(mail,' ');
        for (const string &token : tokenized)
        {
            if (!spamDictionary[token])
            {
                    unkCounter++;
            }
            else
            {
                nonUnkCounter++;
            }

        }

        // Close the file
        MyReadFile.close();
    }

    cout << "|Classifier Results|" << endl;
    cout << "Totalcount:" << totalCounter << endl;
    cout << "Spamcount:" << spamCounter << endl;
    cout << "Hamcount:" << hamCounter << endl;
    cout << "SpamPercentage:" << spamCounter/totalCounter << endl;
    cout << "HamPercentage:" << hamCounter/totalCounter << endl;
    cout << "UnkCount:" << unkCounter << endl;
    cout << "UnkPercentage:" << unkCounter/(unkCounter+nonUnkCounter) << endl << endl;

}

bool Classifier::saveClassifierOnDisk()
{
    string saveLocation = HelperFunctions::getClassifierSaveLocation();

    ofstream classifierFile(saveLocation);

    // Write to the file
    classifierFile << "spamPrior:" << priorSpam << endl;
    classifierFile << "hamPrior:" << priornotSpam << endl;
    classifierFile << "|||SpamSection|||" << endl;
    for (const auto& pair : spamDictionary)
    {
        classifierFile << pair.first << delimiter << pair.second << endl;
    }


    classifierFile << "|||HamSection|||" << endl;
    for (const auto& pair : nonspamDictionary)
    {
        classifierFile << pair.first << delimiter << pair.second << endl;
    }


    // Close the file
    classifierFile.close();

    return true;
}

bool Classifier::loadClassifierFromDisk()
{
    string saveLocation = HelperFunctions::getLocationOfSavedClassifier();

    ifstream classifierFile(saveLocation);

    spamDictionary.clear();
    nonspamDictionary.clear();
    bool processingSpamSection = false;
    string line;
    int linecount = 0;
    while (getline(classifierFile,line))
    {
        linecount ++;
        if (linecount == 1)
        {
            priorSpam = stod(HelperFunctions::splitString(line,":").at(1));
            if (verbose)
            {
                cout << "read priorSpam" << endl;
            }
            continue;
        }
        else if (linecount == 2)
        {
            priornotSpam = priorSpam = stod(HelperFunctions::splitString(line,":").at(1));
            if (verbose)
            {
                cout << "read priornotSpam" << endl;
            }

            continue;
        }
        else if (line == "|||SpamSection|||")
        {
            processingSpamSection = true;
            continue;;
        }
        else if (line == "|||HamSection|||")
        {
            processingSpamSection = false;
            continue;
        }

        vector<string> s = HelperFunctions::splitString(line,delimiter);
        if (processingSpamSection)
        {
            spamDictionary[s.at(0)]=stod(s.at(1));
        }
        else
        {
            nonspamDictionary[s.at(0)]=stod(s.at(1));
        }
    }

    // Close the file
    classifierFile.close();

    return true;
}
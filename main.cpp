#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

string spamCorpus;
string nonspamCorpus;
map<string, double> spamDictionary;
map<string, double> nonspamDictionary;
double priorSpam = 0.5;
double priornotSpam = 1-priorSpam;
double totalSpamTokenCount = 0;
double totalnotSpamTokenCount = 0;
string delimiter = ":<<<|||>>>:";


enum dialogueState {infoScreen, checkForTrainedClassifier, loadClassifier, trainNewClassifier, useClassifier};

dialogueState dialogueState = infoScreen;

string getInput()
{
    string s;
    getline(cin,s);
    return s;
}

string convertStringToLower(const string& s)
{
    string temp;
    for (int i = 0; i < s.length(); i++)
    {
        temp+=tolower(s[i]);
    }

    return temp;
}

std::vector<std::string> splitString(const std::string& input, const std::string& d) {
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


vector<string> tokenize(const string &s, char d)
{
    vector<string> substrings;
    string temp;
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


bool useExistingClassifier()
{
    bool validInput = false;
    while (!validInput)
    {
        cout << "Do you want to use a classifier stored on disk?" << endl;
        cout << "Yes(y) or No(n): ";
        string input = convertStringToLower(getInput());
        cout << endl;
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
            validInput = false;
            continue;
        }
    }

    return true;
}

string getSpamMailPath()
{
    cout << "Please enter the full path to the spam mail txt files:" << endl;
    string spamPath = getInput();
    return spamPath;
}

string getNonSpamMailPath()
{
    cout << "Please enter the full path to the non-spam mail txt files:" << endl;
    string nonspamPath = getInput();
    return nonspamPath;
}

bool loadSpamMailFile(const string& path)
{
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string fullFilePath = entry.path().string();

        cout << fullFilePath << endl;
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

bool loadNonSpamMailFile(const string& path)
{
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string fullFilePath = entry.path().string();

        cout << fullFilePath << endl;
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

bool trainClassifier(int k)
{
    //P(A|B)=>P(B|A)*P(A)
    //P(s1,s2,s3...|Spam)*P(Spam)=>P(s1|Spam)*P(s2|Spam)*P(s3|Spam)*P(Spam)
    ///P(s1,s2,s3...|notSpam)*P(notSpam)=>P(s1|notSpam)*P(s2|notSpam)*P(s3|notSpam)*P(notSpam)


    //Ask user for spam mail path txt
    string spamPath = getSpamMailPath();
    //Ask user for non spam mail path txt
    string nonspamPath = getNonSpamMailPath();
    loadSpamMailFile(spamPath);
    loadNonSpamMailFile(nonspamPath);


    vector<string> tokens_spam = tokenize(spamCorpus,' ');
    vector<string> tokens_nonspam = tokenize(nonspamCorpus,' ');

    for (string token : tokens_spam)
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

    for (string token : tokens_nonspam)
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

    for (string token : combinedCorpusTokens)
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


    for (auto pair : spamDictionary)
    {
        spamDictionary[pair.first] = pair.second/totalSpamTokenCount;
    }

    for (auto pair : nonspamDictionary)
    {
        nonspamDictionary[pair.first] = pair.second/totalnotSpamTokenCount;
    }

    priorSpam=totalSpamTokenCount/(totalSpamTokenCount+totalnotSpamTokenCount);
    priornotSpam=totalnotSpamTokenCount/(totalSpamTokenCount+totalnotSpamTokenCount);

    cout << "PriorSpam:" << priorSpam << endl;
    cout << "PriorNotSpam:" << priornotSpam << endl;
    return true;
}

bool classify(string text)
{
    vector<string> input = tokenize(text,' ');
    double spamProbability = 0;
    double hamProbability = 0;
    for (string token : input)
    {
        if (!spamDictionary[token])
        {
            cout << "UNKNOWN TOKEN!" << endl;
        }
        else
        {
            spamProbability += log(spamDictionary[token]);
        }


        if (!nonspamDictionary[token])
        {
            cout << "UNKNOWN TOKEN!" << endl;
        }
        else
        {
            hamProbability += log(nonspamDictionary[token]);
        }

    }
    spamProbability+=log(priorSpam);
    hamProbability+=log(priornotSpam);

    cout << "SpamProbability:" << (spamProbability) << endl;
    cout << "HamProbability:" <<  (hamProbability) << endl;

    if (spamProbability > hamProbability)
    {
        cout << "Spam!" << endl;
        return true;
    }
    else
    {
        cout << "Ham!" << endl;
        return false;
    }
    return false;
}

void testClassifier()
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
    double totalCounter = 0;
    string path;
    cout << "Please enter the folder path:" << endl;
    getline(cin,path);
    for (const auto & entry : filesystem::directory_iterator(path))
    {
        string mail;
        string fullFilePath = entry.path().string();

        cout << fullFilePath << endl;
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

        vector<string> tokenized = tokenize(mail,' ');
        for (string token : tokenized)
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

    cout << "Totalcount:" << totalCounter << endl;
    cout << "Spamcount:" << spamCounter << endl;
    cout << "SpamPercentage:" << spamCounter/totalCounter << endl;
    cout << "UnkCount:" << unkCounter << endl;
    cout << "UnkPercentage:" << unkCounter/(unkCounter+nonUnkCounter) << endl;

}

bool saveClassifierOnDisk()
{
    cout << "Please enter the path where the trained classifier should be saved" << endl;
    string saveLocation = getInput();

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

bool loadClassifierFromDisk()
{
    cout << "Please enter the path of the saved classifier" << endl;
    string saveLocation;
    saveLocation = getInput();

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
             priorSpam = stod(splitString(line,":").at(1));
            cout << "read priorSpam" << endl;
            continue;
        }
        else if (linecount == 2)
        {
             priornotSpam = priorSpam = stod(splitString(line,":").at(1));
            cout << "read priornotSpam" << endl;
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

        vector<string> s = splitString(line,delimiter);
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

void getPaths()
{

}

void showInfoScreen()
{

}

void dialogueManager()
{
    for (;;)
    {
        switch (dialogueState)
        {
            case infoScreen:
                showInfoScreen();
                dialogueState = checkForTrainedClassifier;
                break;

            case checkForTrainedClassifier:
                if (useExistingClassifier())
                {
                    dialogueState = loadClassifier;
                }
                else
                {
                    dialogueState = trainNewClassifier;
                }
                break;

            case loadClassifier:
                try
                {
                    loadClassifierFromDisk();
                    dialogueState = useClassifier;
                }
                catch (exception& e)
                {
                    cout << e.what() << endl;
                }
                break;

            case trainNewClassifier:
                //Estimate probabilities with MLE and use add-k smoothing
                trainClassifier(1);
                cout << "Training completed" << endl;
                saveClassifierOnDisk();
                break;


            case useClassifier:
                testClassifier();
                break;
        }
    }
}

int main()
{
    //saveClassifierOnDisk();

    if(useExistingClassifier())
    {
        loadClassifierFromDisk();
    }
    else
    {
        //Ask user for spam mail path txt
        string spamPath = getSpamMailPath();
        //Ask user for non spam mail path txt
        string nonspamPath = getNonSpamMailPath();
        //Read both files
        loadSpamMailFile(spamPath);
        loadNonSpamMailFile(nonspamPath);
        //Estimate probabilities with MLE and use add-k smoothing
        trainClassifier(1);
        cout << "Training completed" << endl;
        saveClassifierOnDisk();
        /*cout << "SpamMailProbabilities:" << endl;

        int c = 0;
        for (auto pair : spamDictionary)
        {
            cout << pair.first << ":" << pair.second << endl;
            if (c==20)
            {
                break;
            }
            c++;
        }

        c=0;
        cout << "NonSpamMailProbabilities:" << endl;
        for (auto pair : nonspamDictionary)
        {
            cout << pair.first << ":" << pair.second << endl;
            if (c==20)
            {
                break;
            }
            c++;
        }*/
    }

    for (;;)
    {
        getchar();
        testClassifier();
    }

    //Ask user for new sample path
    //Use Classifier and output result



    cout << "Greetings!" << endl;
    return 0;
}
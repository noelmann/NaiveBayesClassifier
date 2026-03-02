#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
string spamCorpus;
string nonspamCorpus;
map<string, double> spamDictionary;
map<string, double> nonspamDictionary;
double priorSpam = 0.5;
double priornotSpam = 1-priorSpam;
int totalSpamTokenCount = 0;
int totalnotSpamTokenCount = 0;

vector<string> tokenize(string s, char delimiter)
{
    vector<string> substrings;
    int startIndex = 0;
    int endIndex = s.length();
    for (int i = 0;i<s.length();i++)
    {
        if (s[i] == ' ')
        {

            endIndex = i;

            string sub;
            for (int j = startIndex;j<endIndex;j++)
            {
                sub+=s[j];
            }
            if (!sub.empty())
            {
                substrings.push_back(sub);
            }

            startIndex=endIndex+1;
        }
        else if (i == s.length()-1)
        {
            endIndex = s.length();
            string sub;
            for (int j = startIndex;j<endIndex;j++)
            {
                sub+=s[j];
            }

            if (!sub.empty())
            {
                substrings.push_back(sub);
            }

            startIndex=endIndex+1;
        }
    }

    return substrings;
}

bool hasTrainedClassifier()
{
    //TODO("implementation");
    return false;
}

bool useExistingClassifier()
{
    cout << "Do you want to use the already trained classifier?[if not then a new classifier will be trained and overwrite the old one]" << endl;
    cout << "Yes(y) or No(n): ";
    char input = getchar();
    if (input == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

string getSpamMailPath()
{
    cout << "Please enter the full path to the spam mail txt file:" << endl;
    string spamPath;
    getline(cin,spamPath);
    return spamPath;
}

string getNonSpamMailPath()
{
    cout << "Please enter the full path to the non-spam mail txt file:" << endl;
    string nonspamPath;
    getline(cin,nonspamPath);
    return nonspamPath;
}

bool loadSpamMailFile(const string& path)
{
    ifstream MyReadFile(path);
    string text;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, text))
    {
        // Output the text from the file
        spamCorpus += text;
    }

    // Close the file
    MyReadFile.close();
    return true;
}

bool loadNonSpamMailFile(const string& path)
{
    ifstream MyReadFile(path);
    string text;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyReadFile, text))
    {
        // Output the text from the file
        nonspamCorpus += text;

    }

    // Close the file
    MyReadFile.close();
    return true;
}

bool preprocessText(string text)
{
    /*for (string t : spamCorpus)
    {

    }*/

    return true;
}

bool trainClassifier()
{
    //P(A|B)=>P(B|A)*P(A)
    //P(s1,s2,s3...|Spam)*P(Spam)=>P(s1|Spam)*P(s2|Spam)*P(s3|Spam)*P(Spam)
    ///P(s1,s2,s3...|notSpam)*P(notSpam)=>P(s1|notSpam)*P(s2|notSpam)*P(s3|notSpam)*P(notSpam)
    ///
    return true;
}

bool saveClassifierOnDisk()
{
    return true;
}

int main()
{
    //Check if user has already trained a classifier

    if (hasTrainedClassifier())
    {
        //If yes then ask him if he wants to use it or train a new classifier that will overwrite the old one
        useExistingClassifier();
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
        //Estimate probabilities with MLE and use laplace smoothing


    }

    //Ask user for new sample path
    //Use Classifier and output result



    cout << "Greetings!" << endl;
    return 0;
}
#include <iostream>
#include "Classifier.h"
#include "DialogueManager.h"

using namespace std;

int main()
{
    //creates a classifier object with the verbose mode set to disabled
    Classifier classifier = Classifier(false);
    DialogueManager dialogueManager = DialogueManager();
    dialogueManager.manageDialogue(classifier);
    return 0;
}
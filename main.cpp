#include <iostream>
#include "Classifier.h"
#include "DialogueManager.h"

using namespace std;

int main()
{
    Classifier classifier = Classifier();
    DialogueManager dialogueManager = DialogueManager();
    dialogueManager.manageDialogue(classifier);
    return 0;
}
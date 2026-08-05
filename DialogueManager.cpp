//
// Created by DerWiggler01 on 25.05.2026.
//

#include "DialogueManager.h"
#include "Classifier.h"
#include <iostream>
#include "HelperFunctions.h"

using namespace std;

DialogueManager::DialogueManager()
{
    dState = infoScreen;
}

DialogueManager::dialogueState DialogueManager::getDialogueState()
{
    return dState;
}

void DialogueManager::setDialogueState(dialogueState state)
{
    dState = state;
}

void DialogueManager::manageDialogue(Classifier& classifier)
{
    for (;;)
    {
        switch (getDialogueState())
        {
            case infoScreen:
                HelperFunctions::showInfoScreen();
                setDialogueState(checkForTrainedClassifier);
                break;

            case checkForTrainedClassifier:
                if (classifier.useExistingClassifier())
                {
                    setDialogueState(loadClassifier);
                }
                else
                {
                    setDialogueState(trainNewClassifier);
                }
                break;

            case loadClassifier:
                try
                {
                    classifier.loadClassifierFromDisk();
                    setDialogueState(determineClassificationTask);
                }
                catch (exception& e)
                {
                    cout << e.what() << endl;
                }
                break;

            case trainNewClassifier:
                //Estimate probabilities with MLE and use add-k smoothing
                classifier.trainClassifier();
                cout << "Training completed" << endl;
                classifier.saveClassifierOnDisk();
                setDialogueState(determineClassificationTask);
                break;

            case determineClassificationTask:
            {
                const int c = classifier.determineClassificationTask();
                if (c==1)
                {
                    setDialogueState(classifyTestset);
                }
                else if (c==2)
                {
                    setDialogueState(useClassifier);
                }
                else
                {
                    setDialogueState(classifyTestset);
                }
                break;
            }

            case classifyTestset:
                classifier.testClassifierOnTestset();
                setDialogueState(determineClassificationTask);
                break;

            case useClassifier:
                string mail = HelperFunctions::getMailToClassify();
                classifier.classify(mail);
                setDialogueState(determineClassificationTask);
                break;

        }
    }
}

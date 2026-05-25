//
// Created by DerWiggler01 on 25.05.2026.
//

#ifndef NAIVEBAYESCLASSIFIER_DIALOGUEMANAGER_H
#define NAIVEBAYESCLASSIFIER_DIALOGUEMANAGER_H
#include "Classifier.h"


class DialogueManager
{
    public:
    enum dialogueState {infoScreen, checkForTrainedClassifier, loadClassifier, trainNewClassifier, classifyTestset, useClassifier, continueClassifierUse};
    DialogueManager();
    dialogueState getDialogueState();
    void setDialogueState(dialogueState state);
    void manageDialogue(Classifier classifier);

};


#endif //NAIVEBAYESCLASSIFIER_DIALOGUEMANAGER_H

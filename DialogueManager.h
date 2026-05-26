//
// Created by DerWiggler01 on 25.05.2026.
//

#ifndef NAIVEBAYESCLASSIFIER_DIALOGUEMANAGER_H
#define NAIVEBAYESCLASSIFIER_DIALOGUEMANAGER_H
#include "Classifier.h"


class DialogueManager
{
    public:
    DialogueManager();
    void manageDialogue(Classifier classifier);
    private:
    enum dialogueState {infoScreen, checkForTrainedClassifier, loadClassifier, trainNewClassifier, classifyTestset, useClassifier};
    void setDialogueState(dialogueState state);
    dialogueState getDialogueState();
    dialogueState dState;

};


#endif //NAIVEBAYESCLASSIFIER_DIALOGUEMANAGER_H

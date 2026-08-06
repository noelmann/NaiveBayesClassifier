cmake_minimum_required(VERSION 4.1)
project(NaiveBayesClassifier)

set(CMAKE_CXX_STANDARD 20)

add_executable(NaiveBayesClassifier main.cpp
        HelperFunctions.cpp
        HelperFunctions.h
        DialogueManager.cpp
        DialogueManager.h
        Classifier.cpp
        Classifier.h
        README.md)


# Simple Naive Bayes spam/ham classifier with add-K smoothing



# What is it?
A command line application written in C++ that is intended to show the effectiveness of Naive Bayes for text classification purposes.

# How to install it.
1. Clone the repository.
2. Build the project(for example with MinGW-w64).
- Launch the MinGW-w64 shell
- Go into the folder of the cloned repository.
- Run: "cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=/c/Qt/6.9.3/mingw_64 -B build"(your QT path may be different)
- Finally run : "cmake --build build"
3. Optionally: Move finalClassifier.txt (its a pretrained spam/ham classifier) to the build folder

# How to use it.
You can load the pretrained spam classifier and test it on your own testset or train your own classifier. The adjustable smoothing value allows you to see how it affects the performance of the classifier.

# Can I use the code for my own project?
Of course.
As long as you reference this repository.

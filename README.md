# DFA Analyzer
DFA-Analyzer is a C++ library that allows you to create, load, and analyze Deterministic Finite Automata (DFA). The library is designed to work with DFAs where the number of states is between 1 and 10, and the alphabet is a subset of lowercase English letters.

## Features
- Load DFAs from text files with a specific format
- Set and modify start and accept states of the DFA
- Check if a given input string is accepted by the DFA
- Convert the DFA's transition table to a string representation

## Usage
Include the header file DFA.h in your project and create an instance of the DFAnalyzer class.
```
#include "DFA.h"

int main() {
    DFAnalyzer analyzer;
    analyzer.Load("M1.txt");
    analyzer.ModifyAcceptState('0');
    analyzer.ModifyAcceptState('3');
    analyzer.ModifyAcceptState('3');
    analyzer.SetStartState('1');
    
    std::cout << analyzer.IsAccepted("aab") << std::endl;
    std::cout << analyzer.IsAccepted("aba") << std::endl;
    std::cout << analyzer.IsAccepted("bab") << std::endl;
    std::cout << analyzer.IsAccepted("bbb") << std::endl;
    
    return 0;
}
```

## Getting Started
These instructions will help you compile and run the project on your local machine.

### Prerequisites
- A C++ compiler that supports C++11 standard
- The source code files: main.cpp, DFAnalyzer.h, and any input files containing DFA instructions

### Compiling the Project
To compile the project, navigate to the directory containing the source code files and run the following command:
```g++ -std=c++11 -o dfa main.cpp```
This command tells the compiler to use the C++11 standard, which is necessary because of the for-each loop used in the project. The -o dfa flag indicates that the output executable should be named "dfa".

### Running the Executable
After compiling the project, you can run the "dfa" executable by entering the following command:
`./dfa`

## Input File Format
The input file should contain instructions for the DFA's transitions, with one instruction per line. Each instruction should be in the following format:

`state[symbol]+state`

where `state` is a digit character and `symbol` is a lowercase letter character. An instruction should be a string of at least one lowercase letter enclosed between two digit characters. Spaces between characters should be ignored, but other characters should make the instruction set invalid.

Follow any prompts in the program to load a DFA from a file, set the start state, modify accept states, and check if input strings are accepted by the DFA.

## DFA Input File Example
```
1a3
1b0
0a2
0b1
2a0
2b3
3a1
3b2
```

## Author
👤  Jaleel Bennett

## Show your support
Give a ⭐️ if this project helped you!
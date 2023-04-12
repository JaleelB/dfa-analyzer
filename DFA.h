
#ifndef HEADER_DFAANALYZER
#define HEADER_DFAANALYZER
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <cmath>


class DFAnalyzer {
    private:
        // A 2D array representing the transition table for the DFA. The first dimension represents the states (0 to 9), 
        // and the second dimension represents the lowercase letter symbols (a to z).
        std::string transitions[10][26];
        
        // An array representing the accept states of the DFA, where each element corresponds to a state.
        bool acceptStates[10];
        
        // The start state of the DFA, represented as a character.
        char startState;
        
        // A boolean flag indicating if the DFA is valid.
        bool isValidDFA;

        // A helper function that validates if a given instruction string follows the correct format.
        bool isValidInstruction(const std::string &instruction) {
            // Ensure that the instruction has at least three characters.
            if (instruction.length() < 3) return false;
            
            // Ensure that the first and last characters are digits.
            if (!isdigit(instruction[0]) || !isdigit(instruction[instruction.length() - 1])) return false;
            
            // Ensure that all characters between the first and last characters are lowercase letters.
            for (int i = 1; i < instruction.length() - 1; i++) {
                if (!islower(instruction[i])) return false;
            }
            
            return true;
        }

    public:
        // The default constructor initializes the DFA that recognizes the language consisting only of the empty string.
        DFAnalyzer() {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 26; ++j) {
                    transitions[i][j] = '\0';
                }
                acceptStates[i] = false;
            }

            startState = '0';
            acceptStates[0] = true;
            isValidDFA = true;
        }


        // The copy constructor creates a new DFAnalyzer object that is a copy of another DFAnalyzer object.
        DFAnalyzer(const DFAnalyzer &other) {
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 26; ++j) {
                    transitions[i][j] = other.transitions[i][j];
                }
                acceptStates[i] = other.acceptStates[i];
            }
            startState = other.startState;
            isValidDFA = other.isValidDFA;
        }

        // The assignment operator assigns the values of another DFAnalyzer object to the current DFAnalyzer object.
        DFAnalyzer &operator=(const DFAnalyzer &other) {
            if (this == &other) return *this;
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 26; ++j) {
                    transitions[i][j] = other.transitions[i][j];
                }
                acceptStates[i] = other.acceptStates[i];
            }
            startState = other.startState;
            isValidDFA = other.isValidDFA;
            return *this;
        }

        // The destructor is empty, as there are no dynamically allocated resources to release.
        ~DFAnalyzer() {
        }

        // The Load method reads instructions from a file and constructs a DFA if the instructions are valid.
        void Load(const std::string& filename) {
          
            isValidDFA = true;

            std::ifstream inputFile(filename);

            if (!inputFile.is_open()) {
                std::cout << "file not opening" << std::endl;
                isValidDFA = false;
                return;
            }

            std::string line;
            while (std::getline(inputFile, line)) {
                // Remove spaces from the line.
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

                if (!isValidInstruction(line)) {
                    isValidDFA = false;
                    return;
                }

                char initialState = line[0];
                char finalState = line[line.length() - 1];

                for (size_t i = 1; i < line.length() - 1; ++i) {
                    char symbol = line[i];
                    transitions[initialState - '0'][symbol - 'a'] = std::string(1, finalState); // Overwrite the existing transition.
                }
            }

            inputFile.close();
        }



        // The SetStartState method sets the start state of the DFA if the given state is a digit and the DFA is valid.
        void SetStartState(char state) {
            if (isValidDFA && isdigit(state)) {
                startState = state;
            }
        }

        // The ModifyAcceptState method adds or removes a state from the accept states if the given state is a digit and the DFA is valid.
        void ModifyAcceptState(char state) {
            if (isValidDFA && isdigit(state)) {
                acceptStates[state - '0'] = !acceptStates[state - '0'];
            }
        }

        // The IsAccepted method checks if the DFA accepts a given input string.
        bool IsAccepted(const std::string& input) {
            if (!isValidDFA || startState == '\0') {
                return false;
            }

            int currentState = startState - '0';
            for (char symbol : input) {
                if (!islower(symbol)) {
                    return false;
                }

                int transitionIndex = symbol - 'a';
                if (transitions[currentState][transitionIndex].empty()) {
                    return false;
                }

                bool foundTransition = false;
                for (char nextState : transitions[currentState][transitionIndex]) {
                    if (nextState != '\0') {
                        currentState = nextState - '0';
                        foundTransition = true;
                        break;
                    }
                }

                if (!foundTransition) {
                    return false;
                }
            }

            return acceptStates[currentState];
        }


        // The ToString method returns a string representation of the DFA's transition table as a set of 3-tuples.
        std::string ToString() const {
            if (!isValidDFA) return "Invalid DFA";

            std::stringstream ss;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 26; j++) {
                    if (!transitions[i][j].empty()) {
                        ss << "(" << i << ", " << static_cast<char>('a' + j) << ", " << transitions[i][j] << ")" << std::endl;
                    }
                }
            }
            return ss.str();
        }
};

#endif 




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
        // The default constructor initializes the DFA as invalid and the start state as empty/undefined.
        DFAnalyzer() {
            isValidDFA = false;
            startState = '\0';
            for (int i = 0; i < 10; ++i) {
                acceptStates[i] = false;
            }
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
        void Load(const std::string &fileName) {
            std::ifstream inFile(fileName);

            // If the file cannot be opened, mark the DFA as invalid and return.
            if (!inFile) {
                isValidDFA = false;
                return;
            }

            std::string line;
            while (std::getline(inFile, line)) {
                // Remove spaces from the line.
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                // If the line is not a valid instruction, mark the DFA as invalid and return.
                if (!isValidInstruction(line)) {
                    isValidDFA = false;
                    return;
                }

                // Extract the initial state, symbols, and destination state from the instruction.
                char initialState = line[0];
                std::string symbols = line.substr(1, line.length() - 2);
                char destinationState = line[line.length() - 1];

                // Update the transition table for each symbol in the instruction.
                for (const char &symbol : symbols) {
                    transitions[initialState - '0'][symbol - 'a'] = std::string(1, destinationState);
                }
            }

            // Close the file and mark the DFA as valid.
            inFile.close();
            isValidDFA = true;
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
        bool IsAccepted(const std::string &input) {
            // If the DFA is not valid or the start state is not defined, return false.
            if (!isValidDFA || startState == '\0') return false;

            // Start at the initial state and process each symbol in the input string.
            char currentState = startState;
            for (const char &symbol : input) {
                // If a symbol is not a lowercase letter, return false.
                if (!islower(symbol)) return false;
                
                // Update the current state based on the transition table.
                currentState = transitions[currentState - '0'][symbol - 'a'][0];
            }

            // Check if the final state is an accept state.
            return acceptStates[currentState - '0'];
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
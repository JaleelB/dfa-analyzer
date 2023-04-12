#include <iostream>
#include "DFA.h"

int main() {
    DFAnalyzer m;
    m.Load("./data/M1.txt");
    m.ModifyAcceptState('0');
    m.ModifyAcceptState('3');
    m.ModifyAcceptState('3');
    m.SetStartState('1');

    std::cout << std::boolalpha; // Enable boolalpha flag to display true/false instead of 1/0

    std::cout << "m.IsAccepted(\"aab\"): " << m.IsAccepted("aab") << std::endl;
    std::cout << "m.IsAccepted(\"aba\"): " << m.IsAccepted("aba") << std::endl;
    std::cout << "m.IsAccepted(\"bab\"): " << m.IsAccepted("bab") << std::endl;
    std::cout << "m.IsAccepted(\"bbb\"): " << m.IsAccepted("bbb") << std::endl;

    std::cout << std::endl;
    std::cout << "DFA Transition Table:" << std::endl;
    std::cout << m.ToString() << std::endl;

    return 0;
}

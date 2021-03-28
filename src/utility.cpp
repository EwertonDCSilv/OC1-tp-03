#include "utility.hpp"

std::vector<std::string> splitInput(std::string inputLine){
    std::stringstream ss(inputLine);
    std::string word;
    std::vector<std::string> values;
    while (ss >> word) {
        values.push_back(word);
    }

    // Retornando vector para valores de entrada
    return values;
}

#include <iostream>
#include "utility.hpp"
#include "cache.hpp"
#include "memory.hpp"

#define MEMORY_BLOCKS 4096  // DEFINIDO NO EXERCICIO
#define CACHE_BLOCKS 256    // DEFINIDO NO EXERCICIO
#define WORDS 4             // 64 BLOCOS QUE LEVAM 4 PALAVRAS
#define SIZEWORDS 64        // 4 PALAVRAS

int main(){

    // Variaveis de memoria
    Memory memory = Memory(MEMORY_BLOCKS, SIZEWORDS);
    DataCache cache = DataCache(CACHE_BLOCKS, WORDS, SIZEWORDS);
    
    memory.showValues();
    cache.showValues();

    // Variaveis de controle
    int numberReads       = 0;       // Numero de operacoes de Leitura
    int numberWrites      = 0;       // Numero de operacoes de escrita
    int numberHits        = 0;       // Numero de operacoes de Hits
    int numberMisses      = 0;       // Numero de operacoes de Misses
    int numberHitsRate    = 0;       // Numero de operacoes de Hits Rate
    int numberMissesRate  = 0;       // Numero de operacoes de Misses Rate

    // Variaveis de input
    int numberAddresses   = 0;       // Numero de endereços (0 <= N <= 2^12)
    int typeOperator      = 0;       // Tipo de operação (0 para leitura e 1 para escrita)
    int data              = 0;       // Dado para operacao de escrita
    std::vector<std::string> values; // Vector para facilitar recebimento das entradas
    std::string inputLine;           // String temporaria para receber entrada

    // Recebendo entrada
    while(std::getline(std::cin, inputLine)){
        
        // Tratando string de entrada 
        values = splitInput(inputLine);
        
        // Convertendo valores de string para int
        numberAddresses = std::stoi(values[0]); 
        typeOperator = std::stoi(values[1]); 

        // Caso operador seja de escrita
        if (values.size() == 3){
            // Convertendo bit-string para int
            data = std::stoi(values[2].c_str(), 0, 2);
            
            // Incrementando contador de escrita
            numberWrites++;
        }else{
            // Incrementando contador de leitura
            numberReads++;
        }
 
        // Imprimindo a saida
        std::cout << "numberAddresses: " << numberAddresses << std::endl;
        std::cout << "typeOperator: " << typeOperator << std::endl;
        std::cout << "data: " << data << std::endl;
        std::cout << "----------------------------------------"<< std::endl;

        // Redefinindo valor das variaveis
        numberAddresses = 0;
        typeOperator    = 0;
        data            = 0;
        inputLine       = "";
    }

    // Imprimindo contagens da simulacao
    std::cout << "READS: "    << numberReads      << std::endl;
    std::cout << "WRITES: "   << numberWrites     << std::endl;
    std::cout << "HITS: "     << numberHits       << std::endl;
    std::cout << "MISSES: "   << numberMisses     << std::endl;
    std::cout << "HIT RATE:"  << numberHitsRate   << std::endl;
    std::cout << "MISS RATE:" << numberMissesRate << std::endl;
    std::cout << ""                               << std::endl;

    // Imprimindo valores da simulacao
    for (auto value: values){
        std::cout << value << ' ';
    }
    std::cout << std::endl;
    return 0;
}   
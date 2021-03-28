#include <iostream>
#include <bitset>
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
    float numberReads       = 0.0;   // Numero de operacoes de Leitura
    float numberWrites      = 0.0;   // Numero de operacoes de escrita
    float numberHits        = 0.0;   // Numero de operacoes de Hits
    float numberMisses      = 0.0;   // Numero de operacoes de Misses

    // Variaveis de input              
    int numberAddresses   = 0;       // Numero do endereços (0 <= N <= 2^12)
    int typeOperator      = 0;       // Tipo de operação (0 para leitura e 1 para escrita)
    int data              = 0;       // Dado para operacao de escrita
    std::vector<std::string> values; // Vector para facilitar recebimento das entradas
    std::string inputLine;           // String temporaria para receber entrada
    std::string bitAddresses;        // Numero do endereço binario

    // Recebendo entrada
    while(std::getline(std::cin, inputLine)){
        
        // Tratando string de entrada 
        values = splitInput(inputLine);
        
        // Convertendo valores de string para int
        numberAddresses = std::stoi(values[0]); 
        typeOperator = std::stoi(values[1]); 

        // Convertendo valores para string de bits
        bitAddresses = std::bitset< 32 >( numberAddresses ).to_string();

        // Caso operador seja de escrita
        if (values.size() == 3){
            // Convertendo bit-string para int
            data = std::stoi(values[2].c_str(), 0, 2);
            
            std::cout << "values[2]: " << values[2] << std::endl;
            // Incrementando contador de escrita
            numberWrites++;
        }else{
            // Incrementando contador de leitura
            numberReads++;
        }
 
        // Imprimindo a saida
        std::cout << "numberAddresses: " << numberAddresses << std::endl;
        std::cout << "bitAddresses: " << bitAddresses << std::endl;
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
    std::cout << "READS: "    << numberReads               << std::endl;
    std::cout << "WRITES: "   << numberWrites              << std::endl;
    std::cout << "HITS: "     << numberHits                << std::endl;
    std::cout << "MISSES: "   << numberMisses              << std::endl;
    std::cout << "HIT RATE:"  << numberHits/numberReads    << std::endl;
    std::cout << "MISS RATE:" << numberMisses/numberWrites << std::endl;
    std::cout << ""                                        << std::endl;

    // Imprimindo valores da simulacao
    for (auto value: values)
        std::cout << value << ' ';
    std::cout << std::endl;
    
    
    
    return 0;
}   
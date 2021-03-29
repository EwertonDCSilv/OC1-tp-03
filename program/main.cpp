#include <iostream>
#include <bitset>
#include "utility.hpp"
#include "cache.hpp"

#define MEMORY_BLOCKS 4096  // DEFINIDO NO EXERCICIO
#define CACHE_BLOCKS 256    // DEFINIDO NO EXERCICIO
#define WORDS 4             // 64 BLOCOS QUE LEVAM 4 PALAVRAS
#define SIZEWORDS 32        // 4 PALAVRAS
#define CPU_SIZE 12         // 12 bits

int main(){

    // Variaveis de memoria
    Memory memory = Memory(MEMORY_BLOCKS, SIZEWORDS);
    DataCache cache = DataCache(CACHE_BLOCKS,16, WORDS, SIZEWORDS);
    
    // Variaveis de controle
    float numberReads       = 0.0;   // Numero de operacoes de Leitura
    float numberWrites      = 0.0;   // Numero de operacoes de escrita
    float numberHits        = 0.0;   // Numero de operacoes de Hits
    float numberMisses      = 0.0;   // Numero de operacoes de Misses

    // Variaveis de input              
    int numberAddresses   =  0;      // Numero do endereços (0 <= N <= 2^12)
    int typeOperator      =  0;      // Tipo de operação (0 para leitura e 1 para escrita)
    std::string dataInput = "";      // Dado para operacao de escrita
    std::string dataRead  = "";      // Dado para operacao de escrita
    std::vector<std::string> values; // Vector para facilitar recebimento das entradas
    std::string inputLine;           // String temporaria para receber entrada
    std::string bitAddresses;        // Numero do endereço binario
    
    bool boolWritter;

    // Recebendo entrada
    while(std::getline(std::cin, inputLine)){
        
        // Checando se input e valido
        if (inputLine.empty()){
            break;
        }

        // Tratando string de entrada 
        values = splitInput(inputLine);
        
        // Convertendo valores de string para int
        numberAddresses = std::stoi(values[0]); 
        typeOperator    = std::stoi(values[1]); 
        
        cache.showValues(numberAddresses);
        memory.showValues(numberAddresses);

        // Caso operador seja de escrita
        if (values.size() == 3){
            // Incrementando contador de escrita
            numberWrites++;

            // Variavel com dado
            dataInput   = values[2];

            // Escrevendo dado na cache
            boolWritter = cache.write(memory, numberAddresses, dataInput);

            // Verificando write back
            if(boolWritter == false){
                cache.loadMemory(numberAddresses);
                boolWritter = cache.write(memory, numberAddresses, dataInput);
            }             
        }else{
            // Incrementando contador de leitura
            numberReads++;

            // Escrevendo dado na cache
            dataRead = cache.read(numberAddresses);
            
            // Caso ocorra um misses
            if(dataRead == "-1"){
                // Incrementado contador de misses
                numberMisses++;

                // Buscando dado na memoria
                dataRead = memory.read(numberAddresses);

                // Inserindo dado ausente na cache
                cache.loadMemory(numberAddresses);
                boolWritter = cache.write(memory, numberAddresses, dataRead);
            }else{
                // Incrementado contador de hits
                numberHits++;
            }
        }

        // Imprimindo estado dos dados
        cache.showValues(numberAddresses);
        memory.showValues(numberAddresses);
 
        // Imprimindo a saida
        std::cout << "numberAddresses: " << numberAddresses     << std::endl;
        std::cout << "typeOperator: "    << typeOperator        << std::endl;
        std::cout << "dataInput: "       << dataInput           << std::endl;
        std::cout << "dataRead: "        << dataRead            << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "**************************************\n" << std::endl;

        // Redefinindo valor das variaveis
        numberAddresses = 0;
        typeOperator    = 0;
        inputLine       = "";
        dataInput       = "";
        dataRead        = "";
        boolWritter     = false;
        values.clear();
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
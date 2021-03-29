#include <iostream>
#include <iomanip>
#include <bitset>
#include "utility.hpp"
#include "cache.hpp"

#define MEMORY_BLOCKS 4096  // 
#define CACHE_BLOCKS 256    // 
#define WORDS 4             // 
#define SIZEWORDS 32        // 

int main(){

    // Variaveis de memoria
    Memory memory = Memory(MEMORY_BLOCKS, SIZEWORDS);
    DataCache cache = DataCache(CACHE_BLOCKS,16, WORDS, SIZEWORDS);
    
    // Variaveis de controle
    float numberReads       = 0.0;     // Numero de operacoes de Leitura
    float numberWrites      = 0.0;     // Numero de operacoes de escrita
    float numberHits        = 0.0;     // Numero de operacoes de Hits
    float numberMisses      = 0.0;     // Numero de operacoes de Misses

    // Variaveis de input              
    int numberAddresses   =  0;        // Numero do endereços (0 <= N <= 2^12)
    int typeOperator      =  0;        // Tipo de operação (0 para leitura e 1 para escrita)
    std::string dataInput = "";        // Dado para operacao de escrita
    std::string dataRead  = "";        // Dado para operacao de escrita
    std::vector<std::string> values;   // Vector para facilitar recebimento das entradas
    std::vector<std::string> results;  // Vector para facilitar recebimento das entradas
    std::string inputLine;             // String temporaria para receber entrada
    std::string bitAddresses;          // Numero do endereço binario
    std::string rowResult  = "";       // Numero do endereço binario
    std::string typeResult = "";       // Numero do endereço binario
    
    bool boolWritter;

    // Recebendo entrada
    while(std::getline(std::cin, inputLine)){
        
        // Checando se input e valido
        if (inputLine.empty())
            break;
        
        // Tratando string de entrada 
        values = splitInput(inputLine);
        
        // Convertendo valores de string para int
        numberAddresses = std::stoi(values[0]); 
        typeOperator    = std::stoi(values[1]); 
        
        // Caso operador seja de escrita
        if (values.size() == 3){
            // Incrementando contador de escrita
            numberWrites++;
            
            // Definindo tipo de resultado
            typeResult = "W";

            // Variavel com dado
            dataInput   = values[2];

            // Escrevendo dado na cache
            boolWritter = cache.write(memory, numberAddresses, dataInput);

            // Verificando write back
            if(boolWritter == false){
                cache.activeCache(numberAddresses);
                boolWritter = cache.write(memory, numberAddresses, dataInput);
            }             

            // Concatenando string de saida pra leitura
            rowResult = std::to_string(numberAddresses) + " " + std::to_string(typeOperator)+ " " + dataInput + " " + typeResult;

        }else{
            // Incrementando contador de leitura
            numberReads++;

            // Escrevendo dado na cache
            dataRead = cache.read(numberAddresses);
            
            // Caso ocorra um misses
            if(dataRead == "-1"){
                // Incrementado contador de misses
                numberMisses++;

                // Definindo tipo de resultado
                typeResult = "MISS";

                // Buscando dado na memoria
                dataRead = memory.read(numberAddresses);

                // Inserindo dado ausente na cache
                cache.activeCache(numberAddresses);
                boolWritter = cache.write(memory, numberAddresses, dataRead);
            }else{
                // Incrementado contador de hits
                numberHits++;

                // Definindo tipo de resultado
                typeResult = "HIT";
            }
            // Concatenando string de saida pra leitura
            rowResult = std::to_string(numberAddresses) + " " + std::to_string(typeOperator)+ " " + typeResult;
        }
        
        // Concatenando resultado em vector
        results.push_back(rowResult);

        // Redefinindo valor das variaveis
        numberAddresses = 0;
        typeOperator    = 0;
        inputLine       = "";
        dataInput       = "";
        dataRead        = "";
        rowResult       = "";
        boolWritter     = false;
        values.clear();
    }

    // Definindo precisao para float
    std::cout << std::setprecision(1);

    // Imprimindo valores da simulacao
    for (auto result: results)
        std::cout << result << std::endl;
    
    // Imprimindo contagens da simulacao
    std::cout << ""                                        << std::endl;
    std::cout << "READS: "    << numberReads               << std::endl;
    std::cout << "WRITES: "   << numberWrites              << std::endl;
    std::cout << "HITS: "     << numberHits                << std::endl;
    std::cout << "MISSES: "   << numberMisses              << std::endl;
    std::cout << "HIT RATE:"  << numberHits/numberReads    << std::endl;
    std::cout << "MISS RATE:" << numberMisses/numberWrites << std::endl;
    
    return 0;
}   
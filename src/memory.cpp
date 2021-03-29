#include "memory.hpp"

/*
*  @Method: Construtor da classe Memory
*  @params: int blocks:    numero de blocos cache
*  @params: int sizeWords: comprimento das palavras
*/
Memory::Memory(int blocks, int sizeWords){
     // Definindo valores padrao
    this->blocks = blocks;
    this->sizeWords = sizeWords;
    this->realSize = blocks/sizeWords;

    // Alocando memoria para dados da cache 2d-matrix
    this->data      = new char*[this->realSize];
    for(int i = 0; i < this->realSize; i++){
        this->data[i] = new char[this->sizeWords+1];
        
        // Limpando a memoria
        for(int j = 0; j < this->sizeWords; j++)
            this->data[i][j] = '0';
        this->data[i][this->sizeWords] = '\0';
    }    
}

/*
*  @Method: Funcao que imprime valores de um endereco
*  @params: int address:    numero do endereco de memoria
*/
void Memory::showValues(int address = -1){
    int indexMemoryData = 0;
    
    std::cout << "blocks: "    << this->blocks << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;
    std::cout << "realSize: " << this->realSize << std::endl;

    if (address != -1){
        indexMemoryData =  getIndexData(address);
        std::cout << "index memory: " << indexMemoryData << std::endl;
        std::cout << "data: "         << this->data[indexMemoryData] << std::endl;
    }
    std::cout << "----------------------------------------"<< std::endl;
}

/*
*  @Method: Funcao de escrita na memoria cache
*  @params: int indexMemoryData:    indice do endereco de memoria
*  @params: std::string data   :    string contendo dado de escrita
*/
void Memory::write(int indexMemoryData, std::string data){
    strcpy(this->data[indexMemoryData],data.c_str());
}

/*
*  @Method: Funcao de leitura na memoria cache
*  @params: int address     :    numero do endereco de memoria
*/
std::string Memory::read(int address){
    int indexMemoryData = this->getIndexData(address);
    return std::string(this->data[indexMemoryData]);
}

/*
*  @Method: Funcao retorna o indice do bloco da memoria
*  @params: int address:    numero do endereco de memoria
*/
int Memory::getIndexData(int address){
    int index = (address - (address % this->sizeWords))/this->sizeWords;
    return index;
}

/*
*  @Method: Funcao de ativação de bloco da cache
*  @params: int address : numero do endereco de memoria
*/
Memory::~Memory(){
    /*for(int i = 0; i < this->realSize; i++){
        delete[] this->data[i];
    }    
    delete[] this->data;*/
}
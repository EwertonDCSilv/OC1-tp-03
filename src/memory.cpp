#include "memory.hpp"

Memory::Memory(int blocks, int sizeWords){
    
    // Valor deafult de inicializacao
    std::string defaultValue = "00000000000000000000000000000000";
    
    this->blocks = blocks;
    this->sizeWords = sizeWords;
    this->realSize = blocks/sizeWords;

    // Alocando memoria para dados da cache 3d-matrix
    this->data      = new char*[this->realSize];
    for(int i = 0; i < this->realSize; i++){
        this->data[i] = new char[this->sizeWords+1];
        for(int j = 0; j < this->sizeWords; j++){
            this->data[i][j] = '0';
        }
        this->data[i][this->sizeWords] = '\0';
    }    
}

void Memory::showValues(int address = -1){
    std::cout << "blocks: "    << this->blocks << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;
    std::cout << "realSize: " << this->realSize << std::endl;

    if (address != -1){
        int indexMemoryData = 0;

        indexMemoryData =  getIndexData(address);
        std::cout << "index memory: " << indexMemoryData << std::endl;
        std::cout << "data: "         << this->data[indexMemoryData] << std::endl;
    }
    std::cout << "----------------------------------------"<< std::endl;
}

void Memory::write(int indexMemoryData, std::string data){
    strcpy(this->data[indexMemoryData],data.c_str());
}

std::string Memory::read(int address){
    int indexMemoryData = this->getIndexData(address);
    return std::string(this->data[indexMemoryData]);
}

int Memory::getIndexData(int address){
    int index = (address - (address % this->sizeWords))/this->sizeWords;
    return index;
}

Memory::~Memory(){
    /*for(int i = 0; i < this->realSize; i++){
        delete[] this->data[i];
    }    
    delete[] this->data;*/
}
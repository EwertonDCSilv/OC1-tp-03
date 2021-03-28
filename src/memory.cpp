#include "memory.hpp"

Memory::Memory(int blocks, int sizeWords){
    this->blocks = blocks;
    this->sizeWords = sizeWords;
    this->realSize = blocks/sizeWords;

    // Alocando memoria para dados da cache 3d-matrix
    this->data      = new char*[realSize];
    for(int i = 0; i < realSize; i++){
        this->data[i] = new char[sizeWords];
    }    
}

void Memory::showValues(int address = -1){
    std::cout << "blocks: " << this->blocks << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;

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

int Memory::getIndexData(int address){
    int index = (address - (address % this->sizeWords))/this->sizeWords;
    return index;
}

Memory::~Memory(){
    //delete this->data;
}
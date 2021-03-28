#include "memory.hpp"

Memory::Memory(int blocks, int sizeWords){
    this->blocks = blocks;
    this->sizeWords = sizeWords;
    
}

void Memory::showValues(){
    std::cout << "blocks: " << this->blocks << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;
    std::cout << "----------------------------------------"<< std::endl;

}

Memory::~Memory(){
    //delete this->data;
}
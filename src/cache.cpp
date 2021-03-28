#include "cache.hpp"

DataCache::DataCache(int blocks, int blockSize, int words, int sizeWords){
    this->blocks    = blocks;
    this->blockSize = blockSize;
    this->words     = words;
    this->sizeWords = sizeWords;

    // Alocando memoria metadados da cache
    this->tag       = new int[blocks];
    this->index     = new int[blocks];
    this->validity  = new int[blocks];
    this->modified  = new int[blocks];

    // Alocando memoria para dados da cache 3d-matrix
    this->data      = new char**[blocks];
    for(int i = 0; i < blocks; i++){

        // Limapndo memoria
        this->tag[i]      = 0;
        this->index[i]    = 0;
        this->validity[i] = 0;
        this->modified[i] = 0;

        this->data[i] = new char*[words];
        for(int j = 0; j < words; j++){
            this->data[i][j] = new char[sizeWords];
        }
    }
    
    // Calculando offeset, index e tag
    this->shiftOffset = log2(this->blockSize);
    this->shiftIndex  = log2(this->blocks);
    this->shiftTag    = this->blockSize - (this->shiftOffset + this->shiftIndex);

}

void DataCache::showValues(int address = -1){
    std::cout << "blocks: "    << this->blocks << std::endl;
    std::cout << "words: "     << this->words << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;
    std::cout << "offset: "    << this->shiftOffset << std::endl;
    std::cout << "index: "     << this->shiftIndex << std::endl;
    std::cout << "tag: "       << this->shiftTag << std::endl;


    if (address != -1){
        int tag = 0;
        int indexBlock = 0;
        int offset = 0;

        indexBlock =  getIndexBlock(address);
        offset     =  getOffset(indexBlock);
        
        std::cout << "indexBlock: " << indexBlock << std::endl;
        std::cout << "offset: "     << offset << std::endl;
        std::cout << "data: "       << this->data[indexBlock][offset] << std::endl;
        std::cout << "tag: "        << this->tag[indexBlock] << std::endl;
        std::cout << "index: "      << this->index[indexBlock] << std::endl;
        std::cout << "validity: "   << this->validity[indexBlock] << std::endl;
        std::cout << "modified: "   << this->modified[indexBlock] << std::endl;
    }

    std::cout << "----------------------------------------"<< std::endl;

}

int DataCache::getOffset(int address){
    return address & (this->blockSize - 1);
}

int DataCache::getIndexBlock(int address){
    return address >> this->shiftOffset;
}

int DataCache::getTagBlock(int indexBlock){
    return indexBlock >> this->shiftIndex;
}

bool DataCache::write(Memory memory, int address, std::string data){
    
    int tag = 0;
    int indexBlock = 0;
    int indexMemoryData = 0;
    int offset = 0;

    indexBlock =  getIndexBlock(address);
    tag        =  getTagBlock(indexBlock);
    offset     =  getOffset(indexBlock);

    if( this->tag[indexBlock] == tag && this->validity[indexBlock] == 1){
        // Salvando na memoria
        indexMemoryData = memory.getIndexData(address);
        memory.write(indexMemoryData, data);
        this->modified[indexBlock] = 1;

        // Salvando na cache
        strcpy(this->data[indexBlock][offset], data.c_str());
        return true;
    }
    return false;
}

void DataCache::loadMemory(int address){
   
    int tag = 0;
    int indexBlock = 0;

    indexBlock =  getIndexBlock(address);  //Obtendo valor do indece do bloco de memoria
    tag        =  getTagBlock(indexBlock); //Obtendo valor da tag do bloco de memoria
    
    this->modified[indexBlock] = 0;
    this->validity[indexBlock] = 1;
    this->tag[indexBlock] = tag;
}

DataCache::~DataCache(){
    //delete this->data;
    delete[] this->tag;
    delete[] this->index;
    delete[] this->validity;
    delete[] this->modified;

    /*
        this->data      = new char**[blocks];
    for(int i = 0; i < blocks; i++){

        // Limapndo memoria
        this->tag[i]      = 0;
        this->index[i]    = 0;
        this->validity[i] = 0;
        this->modified[i] = 0;

        this->data[i] = new char*[words];
        for(int j = 0; j < words; j++){
            this->data[i][j] = new char[sizeWords];
        }
    }
    */
}
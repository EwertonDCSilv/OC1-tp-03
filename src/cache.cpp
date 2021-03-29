#include "cache.hpp"

DataCache::DataCache(int blocks, int blockSize, int words, int sizeWords){
    
    // Valor deafult de inicializacao
    std::string defaultValue = "00000000000000000000000000000000";

    this->blocks    = blocks;
    this->blockSize = blockSize;
    this->words     = words;
    this->sizeWords = sizeWords+1;

    // Alocando memoria metadados da cache
    this->tag       = new int[this->blocks];
    this->index     = new int[this->blocks];
    this->validity  = new int[this->blocks];
    this->modified  = new int[this->blocks];

    // Alocando memoria para dados da cache 3d-matrix
    this->data      = new char**[this->blocks];
    for(int i = 0; i < this->blocks; i++){

        // Limapndo memoria
        this->tag[i]      = 0;
        this->index[i]    = 0;
        this->validity[i] = 0;
        this->modified[i] = 0;

        this->data[i] = new char*[this->words];
        for(int j = 0; j < this->words; j++){
            this->data[i][j] = new char[this->sizeWords+1];
            for(int k = 0; k < this->sizeWords; k++){
                this->data[i][j][k] = '0';
            }
            this->data[i][j][this->sizeWords] = '\0';
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
        int offset = 0;

        offset     =  getOffset(address);
        
        std::cout << "indexoffset: " << offset << std::endl;
        std::cout << "data: "        << this->data[offset] << std::endl;
        std::cout << "tag: "         << this->tag[offset] << std::endl;
        std::cout << "index: "       << this->index[offset] << std::endl;
        std::cout << "validity: "    << this->validity[offset] << std::endl;
        std::cout << "modified: "    << this->modified[offset] << std::endl;
    }

    std::cout << "----------------------------------------"<< std::endl;

}

int DataCache::getOffset(int address){
    return address & (this->blockSize - 1);
}

int DataCache::getIndexBlock(int address){
    
    int mask  = 0;

    mask     = (1 << this->shiftIndex) - 1;
    address  = address >> this->shiftOffset;
    return address & mask;
}

int DataCache::getTagBlock(int address){
    address = address >> this->shiftOffset;
    return address >> this->shiftIndex;
}

bool DataCache::write(Memory memory, int address, std::string data){
    
    int tag = 0;
    int indexBlock = 0;
    int indexMemoryData = 0;
    int offset = 0;

    indexBlock =  getIndexBlock(address);
    tag        =  getTagBlock(address);
    offset     =  getOffset(address);

    std::cout << "Calculado indexBlock: "    << indexBlock << std::endl;
    std::cout << "Calculado tag: "           << tag << std::endl;
    std::cout << "Calculado offset: "        << offset << std::endl;
    std::cout << "¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨\n: " << std::endl;


    if( this->tag[offset] == tag && this->validity[offset] == 1){
        // Salvando na memoria
        indexMemoryData = memory.getIndexData(address);
        memory.write(indexMemoryData, data);
        this->modified[offset] = 1;

        // Salvando na cache
        strcpy(this->data[offset][0], data.c_str());
        return true;
    }
    return false;
}

std::string DataCache::read(int address){
    
    int tag = 0;
    //int indexBlock = 0;
    int offset = 0;
    std::string result = "-1";

    //indexBlock =  getIndexBlock(address);
    tag        =  getTagBlock(address);
    offset     =  getOffset(address);

    if( this->tag[offset] == tag && this->validity[offset] == 1){
        // Retornando dado da cache
        std::cout << "Leitura da cache: " << this->data[offset][0] << std::endl;
        result = std::string(this->data[offset][0]);
    }
    return result;
}

void DataCache::loadMemory(int address){
   
    int tag = 0;
    int offset = 0;

    //indexBlock =  getIndexBlock(address);  //Obtendo valor do indece do bloco de memoria
    tag        =  getTagBlock(address); //Obtendo valor da tag do bloco de memoria
    offset     =  getOffset(address);
    
    this->modified[offset] = 0;
    this->validity[offset] = 1;
    this->tag[offset] = tag;
}

DataCache::~DataCache(){
    //delete this->data;
    /*delete[] this->tag;
    delete[] this->index;
    delete[] this->validity;
    delete[] this->modified;

    for(int i = 0; i < blocks; i++){
        for(int j = 0; j < words; j++){
            delete [] this->data[i][j];
        }
        delete [] this->data[i];
    }
    delete [] this->data;*/

}
#include "cache.hpp"

DataCache::DataCache(int blocks, int words, int sizeWords){
    this->blocks = blocks;
    this->words = words;
    this->sizeWords = sizeWords;
}

void DataCache::showValues(){
    std::cout << "blocks: " << this->blocks << std::endl;
    std::cout << "words: " << this->words << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;
    std::cout << "----------------------------------------"<< std::endl;

}

void DataCache::write(int address, std::string data){
    /*
    address = int(address)
    offset = self.get_offset(address)
    address = address >> self.offset_shift

    block = self.get_block(address)
    address = address >> self.index_shift

    tag = address

    entry = None
    if block.tag == tag and block.valid:
        entry = block
        entry.modified = 1

    if entry:
        entry.data[offset] = data

    return True if entry else False
    */
}

DataCache::~DataCache(){
    //delete this->data;
}
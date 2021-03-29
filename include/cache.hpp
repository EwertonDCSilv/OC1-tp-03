#include <string>
#include <cmath>
#include <sstream>
#include <cmath>
#include <vector>
#include <iostream>
#include "memory.hpp"

class DataCache{
protected:
    int blocks;
    int blockSize;
    int words;
    int sizeWords;
    int shiftOffset;
    int shiftIndex;
    int shiftTag;
    char ***data;
    int *tag;
	int *index;
	int *validity;
	int *modified;

public:
    DataCache(int blocks, int blockSize, int words, int sizeWords);
    ~DataCache();
    void showValues(int address);
    int getOffset(int address);
    int getIndexBlock(int address);
    int getTagBlock(int address);
    bool write(Memory memory, int address, std::string data);
    std::string read(int address);
    void loadMemory(int address);
};
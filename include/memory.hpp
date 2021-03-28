#include <string>
#include <sstream>
#include <string.h>
#include <vector>
#include <map>
#include <iostream>

class Memory{
protected:
    int blocks;
    int sizeWords;
    int realSize;
    char **data; 

public:
    Memory(int blocks, int sizeWords);
    ~Memory();
    void showValues(int address);
    void write(int indexMemoryData, std::string data);
    int getIndexData(int address);
};

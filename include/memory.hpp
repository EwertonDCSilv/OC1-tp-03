#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

class Memory{
protected:
    int blocks;
    int sizeWords;
    std::map<int,int> data; 

public:
    Memory(int blocks, int sizeWords);
    ~Memory();
    void showValues();
};

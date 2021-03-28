#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

class DataCache{
protected:
    int blocks;
    int words;
    int sizeWords;
    //std::map<int,int> data;
    char ***data;
    int *tag;
	int *index;
	int *validity;
	int *dirty;

public:
    DataCache(int blocks, int words, int sizeWords);
    ~DataCache();
    void showValues();
    void write(int address, std::string data);
};

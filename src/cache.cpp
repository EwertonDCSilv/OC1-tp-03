#include "cache.hpp"

/*
*  @Method: Construtor da classe DataCache
*  @params: int blocks:    numero de blocos cache
*  @params: int blockSize: tamaho do bloco em bytes
*  @params: int words:     numero de palavras em cada bloco
*  @params: int sizeWords: comprimento das palavras
*/
DataCache::DataCache(int blocks, int blockSize, int words, int sizeWords){
    // Definindo valores padrao
    this->blocks    = blocks;
    this->blockSize = blockSize;
    this->words     = words;
    this->sizeWords = sizeWords+1;

    // Alocando memoria metadados da cache
    this->index     = new int [this->blocks];
    this->validity  = new int [this->blocks];
    this->modified  = new int [this->blocks];
    this->tag       = new int*[this->blocks];

    // Alocando memoria para dados da cache 2d e 3d-matrix
    this->data      = new char**[this->blocks];
    for(int i = 0; i < this->blocks; i++){
        // Limapndo memoria
        this->tag[i]      = new  int[this->words];
        this->index[i]    = 0;
        this->validity[i] = 0;
        this->modified[i] = 0;

        this->data[i] = new char*[this->words];
        for(int j = 0; j < this->words; j++){
            this->data[i][j] = new char[this->sizeWords+1];
            
            // Limapndo memoria
            for(int k = 0; k < this->sizeWords; k++)
                this->data[i][j][k] = '0';
            this->data[i][j][this->sizeWords] = '\0';
            this->tag[i][j] = 0;
        }
    }
    
    // Calculando offeset, index e tag
    this->shiftOffset = log2(this->blockSize);
    this->shiftIndex  = log2(this->blocks);
    this->shiftTag    = this->blockSize - (this->shiftOffset + this->shiftIndex);
}

/*
*  @Method: Funcao que imprime valores de um endereco
*  @params: int address:    numero do endereco de memoria
*/
void DataCache::showValues(int address = -1){
    int offset = 0;

    std::cout << "blocks: "    << this->blocks << std::endl;
    std::cout << "words: "     << this->words << std::endl;
    std::cout << "sizeWords: " << this->sizeWords << std::endl;
    std::cout << "offset: "    << this->shiftOffset << std::endl;
    std::cout << "index: "     << this->shiftIndex << std::endl;
    std::cout << "tag: "       << this->shiftTag << std::endl;

    if (address != -1){
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

/*
*  @Method: Funcao retorna o offeset do endereco
*  @params: int address:    numero do endereco de memoria
*/
int DataCache::getOffset(int address){
    return address % this->words;
}

/*
*  @Method: Funcao retorna o indice do bloco da cache
*  @params: int address:    numero do endereco de memoria
*/
int DataCache::getIndexBlock(int address){
    return address % this->blocks;
}

/*
*  @Method: Funcao de escrita na memoria cache
*  @params: Memory memory   :    Objeto da classe memoria
*  @params: int address     :    numero do endereco de memoria
*  @params: std::string data:    string contendo dado de escrita
*/
bool DataCache::write(Memory memory, int address, std::string data){
    
    int indexBlock      = 0;
    int indexMemoryData = 0;
    int offset          = 0;

    // Obtendo valores de indice e offset
    indexBlock =  getIndexBlock(address);
    offset     =  getOffset(address);

    // Verificando se dado esta na cache
    if( this->tag[indexBlock][offset] == address && this->validity[indexBlock] == 1){
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

/*
*  @Method: Funcao de leitura na memoria cache
*  @params: int address     :    numero do endereco de memoria
*/
std::string DataCache::read(int address){
    
    int indexBlock     =    0;
    int offset         =    0;
    std::string result = "-1";// Valor padrao de retorno

    // Obtendo valores de incide e offset
    indexBlock =  getIndexBlock(address);
    offset     =  getOffset(address);

    // Verifica se dado existe na memoria cache
    if( this->tag[indexBlock][offset] == address && this->validity[indexBlock] == 1){
        // Retornando dado da cache
        result = std::string(this->data[indexBlock][offset]);
    }
    return result;
}

/*
*  @Method: Funcao de ativação de bloco da cache
*  @params: int address : numero do endereco de memoria
*/
void DataCache::activeCache(int address){
    
    int indexBlock = 0;
    int offset = 0;
    
    // Obtendo valores de incide e offset
    indexBlock =  getIndexBlock(address);  //Obtendo valor do indece do bloco de memoria
    offset     =  getOffset(address);  //Obtendo valor do indece do bloco de memoria
    
    // Definindo valores dos metados da cache
    this->modified[indexBlock]    = 0;
    this->validity[indexBlock]    = 1;
    this->tag[indexBlock][offset] = address;
}

/*
*  @Method: Destrutor da classe DataCache
*/
DataCache::~DataCache(){
    // Destruindo 1d-matrix
    delete[] this->index;
    delete[] this->validity;
    delete[] this->modified;

    for(int i = 0; i < blocks; i++){
        // Destruindo 3d-matrix
        for(int j = 0; j < words; j++){
            delete [] this->data[i][j];
        }
        // Destruindo 2d-matrix
        delete [] this->data[i];
        delete[] this->tag[i];
    }
    
    // Destruindo 1d-matrix
    delete[] this->tag;
    delete [] this->data;
}
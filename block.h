#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <iostream>
#include "picosha2.h"

typedef std::vector<std::string> DATA;

class Block
{
public:
    Block() {};
    Block(int id, const DATA &data) : _data(data), _id(id) {nonce = -1; _hash = this->calculateHash();};
    Block(int id, const DATA &data, const std::string hash) : _data(data), _id(id), _hash(hash){nonce = -1;};
//    Block(int id, const DATA &data, const std::string &hash, const std::string &prevBlockHash) : _data(data), _id(id), _hash(hash), _prevBlockHash(prevBlockHash){nonce = -1;};


    std::string getHash() const noexcept {return _hash;};
    int getID() const noexcept {return _id;};
    DATA getData() const noexcept {return _data;};
    std::string getPrevHash() const noexcept {return _prevBlockHash;};

    void setPrevHash(std::string prevHash) {this->_prevBlockHash = prevHash;};
    void setHash() {this->_hash = calculateHash();};
    void mineHash(int diff);

private:
    DATA _data;
    int _id;
    int nonce;
    std::string _prevBlockHash;
    std::string _hash = "";
    std::string calculateHash();
};

#endif // BLOCK_H

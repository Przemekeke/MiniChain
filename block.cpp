#include "block.h"


void Block::mineHash(int diff)
{
    char tmp[diff + 1];
    for (int i = 0; i < diff; i++){
        tmp[i] = '0';
    }
    tmp[diff] = '\0';
    std::string expected(tmp);
    std::string tmpHash = "";
    do{
        //std::cout << tmpHash.substr(0,diff) << std::endl;
        nonce++;
        tmpHash = calculateHash();
    } while(tmpHash.substr(0,diff) != expected);
    _hash = tmpHash;
    std::cout << "Block mined: " << tmpHash << std::endl;

}
/*
std::string Block::getData()
{
    std::stringstream ss;
    for (auto line : _data){
        std::cout << line << "\n";
        ss << line << "\n";
    }
    return(ss.str());
}*/

std::string Block::calculateHash()
{
   std::stringstream ss;
   std::copy(_data.begin(), _data.end(), std::ostream_iterator<std::string>(ss));
   ss << _id << _prevBlockHash << nonce;

   return picosha2::hash256_hex_string(ss.str());
}

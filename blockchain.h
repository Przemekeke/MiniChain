#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "block.h"
#include "json.hpp"

using json = nlohmann::json;

class Blockchain
{
public:
    Blockchain();
    void readFromDisk(std::string path);
    void mineBlock(const DATA &data);
    void addBlock(const DATA &data);
    void addBlock(int id, const DATA &data, const std::string hash);

    std::string getStatistics();
    Block getBlock();

    void saveToFile(std::string path);
    bool readFromFile(std::string path);
    bool checkIntegrity();

private:
    std::vector<Block> blocks;
    int difficulty;

};

#endif // BLOCKCHAIN_H

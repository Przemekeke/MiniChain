#include "blockchain.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdint>

Blockchain::Blockchain()
{
    blocks.emplace_back(Block(0,DATA{"GENESIS"}));
    blocks.back().setHash();
    this->difficulty = 2;

}

void Blockchain::mineBlock(const DATA &data)
{
    blocks.emplace_back(blocks.size() + 1, data);
    if (blocks.size())
        blocks.back().setPrevHash((blocks.end() - 2)->getHash());
    blocks.back().mineHash(difficulty);
}

void Blockchain::addBlock(int id, const DATA &data, const std::string hash)
{
     blocks.emplace_back(id, data, hash);
     if(id > 1)
        blocks.back().setPrevHash((blocks.end() - 2)->getHash());

}

void Blockchain::addBlock(const DATA &data)
{
     blocks.emplace_back(blocks.size(), data);
     if(blocks.size())
        blocks.back().setPrevHash((blocks.end() - 2)->getHash());

}

std::string Blockchain::getStatistics()
{
    std::stringstream ss;
    ss << "number of blocks: " << blocks.size() << std::endl;
    ss << "Size in bytes " << sizeof(blocks) << std::endl;
    return (ss.str());
}

void Blockchain::saveToFile(std::string path)
{
    json j;
    Block tmpBlock;
    DATA data;
    std::ofstream o(path);
    for (unsigned int i = 0; i < blocks.size(); i++){
        tmpBlock = blocks.at(i);
        data =  tmpBlock.getData();
        std::string _sind = std::to_string(i);
        j["block" + _sind]["header"]["id"] = tmpBlock.getID();
        j["block" + _sind]["header"]["hash"] = tmpBlock.getHash();
        j["block" + _sind]["header"]["Previous block hash"] = tmpBlock.getPrevHash();
        for (unsigned int n = 0; n < data.size(); n++){
            j["block" + _sind]["body"]["Data Frame " + std::to_string(n)] = data[n];
        }
    }
    o << std::setw(4) << j << std::endl;
    o.close();
}

bool Blockchain::readFromFile(std::string path)
{
    json j;
    std::ifstream file(path);
    if(file.good()){
        if(!blocks.empty())
            blocks.clear();
        file >> j;
        for (auto const & block : j){
            DATA tmpData;
            for (auto const & data : block["body"].items()){
                tmpData.push_back(data.value());
            }
            this->addBlock((int)block["header"]["id"], std::move(tmpData), block["header"]["hash"]);
        }
        file.close();
        return true;
    }
    else{
        std::cout << "JSON DOESN'T EXISTS" << std::endl;
        file.close();
        return false;
    }
}

bool Blockchain::checkIntegrity()
{
    if (!blocks.empty()){
        for (unsigned int i = 1; i < blocks.size() - 1; i++){
            if(blocks[i].getHash() != blocks[i + 1].getPrevHash())
                return false;
        }
    }
    return true;
}




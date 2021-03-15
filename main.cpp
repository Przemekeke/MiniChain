#include <iostream>
#include <blockchain.h>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc > 2){
        if (std::string(argv[1]) != "-p" && std::string(argv[1]) != "-a")
            cout << "Usage to add block to block chain: -p [path_to_json_file] -a [Block Data Add, ...] "  << (std::string(argv[1]) != "-a") << std::endl;

        Blockchain bChain = Blockchain();
        if (std::string(argv[1]) == "-a"){
            DATA tmpData;
            for ( int i = 2; i < argc; i++){
                tmpData.push_back(argv[i]);
            }
            bChain.addBlock(tmpData);
        }
        else if(std::string(argv[1]) == "-p" && std::string(argv[3]) == "-a"){
            if (bChain.readFromFile(argv[2]))
                std::cout << "file read correctly \n";
            else
                std::cout << "fail to read file \n Block Chain will be created and written to file";
            DATA tmpData;
            for ( int i = 4; i < argc; i++){
                tmpData.push_back(argv[i]);
            }
            bChain.addBlock(tmpData);
            bChain.saveToFile(argv[2]);
            std::cout << "file " << argv[0] << "saved\n";
        }
    }
    else{
        cout <<  "Usage to add block to block chain: -p [path_to_json_file] -a [Data, ...] \nRunning example with mining blocks...\n";

        Blockchain myBlockChain = Blockchain();

        myBlockChain.mineBlock(DATA{"Block 1", "Przemek"});
        myBlockChain.mineBlock(DATA{"Block 2", "Jack"});
        myBlockChain.mineBlock(DATA{"Block 3", "Mary"});

        myBlockChain.saveToFile("test.json");
        bool read = myBlockChain.readFromFile("test.json");
        if (read)
            std::cout << "file read correctly \n";
        else
            std::cout << "fail to read file \n";
        myBlockChain.mineBlock(DATA{"Block 4", "Jason"});
        myBlockChain.saveToFile("test2.json");
        cout << "integrity " << myBlockChain.checkIntegrity() << endl;
        cout << "statistic " << myBlockChain.getStatistics();
    }
    return 0;
}

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "DSString.h"
#include "DSVector.h"
#include "IndexEntry.h"
#include "Indexer.h"

#include <fstream>
#include <iostream>


int testFunc(){
    return Catch::Session().run();
}
int main(int argc, char** argv) {
    if(argc == 1){
        testFunc();
        return 0;
    }
    else {
        /*std::ofstream outputstream(argv[2]);
        outputstream << "Hello, World!" << std::endl;
        outputstream.close();
        std::cout << "Hello and wrote sample output file." << std::endl;
         */
        DSString file1 = argv[2];//keyword file name
        DSString file2 = argv[1];//book text file name
        DSString file3 = argv[3];//output file name


        Indexer myIndex(file1,file2);
        myIndex.setKeywordsList();
        myIndex.searchBook();
        myIndex.createIndex(file3);
        return 0;
    }
}

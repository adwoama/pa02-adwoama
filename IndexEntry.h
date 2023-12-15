//
// Created by robot on 3/2/2021.
//

#ifndef INC_21S_AUTO_IDX_INDEXENTRY_H
#define INC_21S_AUTO_IDX_INDEXENTRY_H
#include "DSString.h"
#include "DSVector.h"
class IndexEntry{
private:
    DSString word;
    DSVector <int> pages;

public:
    //constructors
    IndexEntry();
    IndexEntry (DSString);
    //operator
    IndexEntry& operator=(const IndexEntry);
    bool operator==(const IndexEntry&)const;
    //accessor
    DSString getWord();
    int getNumPages();
    int getPageAt(int);
    DSVector<int>& getPagesList();
    //mutator
    void addPage(int pageNum);
    void setWord(DSString newWord);
    //print
    void printPages(std::ostream& outS = cout);
    friend std::ostream& operator<< (std::ostream& outS, const IndexEntry& n);
};
#endif //INC_21S_AUTO_IDX_INDEXENTRY_H

//
// Created by robot on 2/25/2021.
//

#ifndef INC_20F_AUTO_IDX_INDEXER_H
#define INC_20F_AUTO_IDX_INDEXER_H

#include "DSVector.h"
#include "DSString.h"
#include "IndexEntry.h"

class Indexer{
private:
    DSVector <IndexEntry> index;
    DSString keyWordFile, bookFile;
    DSVector <DSString> keywords;

public:
    //constructors
    Indexer();
    Indexer(DSString, DSString);

    //accessors
    DSString getKeyWordFile();
    DSString getBookFile();

    //mutators
    void setKeyWordFile(DSString);
    void setBookFile(DSString);

    //indexing methods
    void setKeywordsList();
    void searchBook();
    void createIndex(DSString);


};
#endif //INC_20F_AUTO_IDX_INDEXER_H

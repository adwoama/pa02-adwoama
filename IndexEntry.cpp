//
// Created by robot on 3/2/2021.
//

#include "IndexEntry.h"

#include "DSVector.h"
#include "DSString.h"
//++++++++++ CONSTRUCTORS ++++++++++
IndexEntry::IndexEntry(){
    word = "";
}//Default Constructor
IndexEntry::IndexEntry (DSString newWord){
    word = newWord;
}

//++++++++++ OPERATORS ++++++++++
IndexEntry& IndexEntry::operator=(const IndexEntry copy){
    word = copy.word;
    pages = copy.pages;
    return *this;
}
bool IndexEntry::operator==(const IndexEntry& comp)const{
    if((word == comp.word)&&(pages==comp.pages))
        return true;
    return false;
}

//++++++++++ ACCESSORS ++++++++++
DSString IndexEntry::getWord(){
    return word;
}//getWord
int IndexEntry::getNumPages(){
    return pages.getSize();
}//getNumPages
int IndexEntry::getPageAt(int loc){
    return pages[loc];
}//getPageAt
DSVector<int>& IndexEntry::getPagesList(){
    return pages;
}//getPagesList

//++++++++++ MUTATORS ++++++++++
void IndexEntry::addPage(int pageNum){

    if(pages.contains(pageNum)<0)
    pages.pushback(pageNum);
}//addPages
void IndexEntry::setWord(DSString newWord){
    word = newWord;
}//setWord

//++++++++++ PRINTERS ++++++++++
void IndexEntry::printPages(std::ostream& outS){
    int i;
    int wrap = 0;
    for(i =0; i<pages.getSize(); i++){
        if(i<pages.getSize()-1)
        outS << pages[i]  << ", ";
        else
            outS << pages[i];
        wrap++;
        if(wrap >= 35){//keeps output line from being over 70 characters
            outS << endl << "    ";
            wrap = 0;
        }
    }


}//printPages
std::ostream& operator<< (std::ostream& outS, const IndexEntry& n){
    outS << n.word;
    return outS;
}//operator<<

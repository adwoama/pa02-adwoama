//
// Created by robot on 2/25/2021.
//

#include "Indexer.h"
#include "DSVector.h"
#include "DSString.h"

#include <fstream>
#include <cctype>
#include <exception>

//++++++++++ CONSTRUTORS ++++++++++
Indexer::Indexer(){
    keyWordFile = "";
    bookFile = "";
}
Indexer::Indexer(DSString kwFile, DSString bFile){
    keyWordFile = kwFile;
    bookFile = bFile;
}

//++++++++++ ACCESSORS ++++++++++
DSString Indexer::getKeyWordFile(){
    return keyWordFile;
}
DSString Indexer::getBookFile(){
    return bookFile;
}

//++++++++++ MUTATORS ++++++++++
void Indexer::setKeyWordFile(DSString kwFile){
    keyWordFile = kwFile;
}
void Indexer::setBookFile(DSString bFile){
    bookFile = bFile;
}

//++++++++++ OTHER ++++++++++
void Indexer::setKeywordsList(){
    char *holder = new char[80];

    ifstream  inFS;
    inFS.open(keyWordFile.c_str());
    if(!inFS.is_open()){
        cout << "setKeyWordsList() failed to open: " << keyWordFile << endl;
        throw ios_base::failure("bad file name");
    }
    while(!inFS.eof()) {

        inFS.getline(holder, 80);
        //cout << "line before editing: " << holder << ", length: " << strlen(holder) << endl;

        DSString toAdd = holder;
        //cout <<"line as DSString: " << toAdd.c_str() << ", length: " << toAdd.getLength() <<endl;
        toAdd = toAdd.setLowerCase();
        //cout << "all lowercase: " << toAdd << endl;
        toAdd = toAdd.removePunct();
        //cout << "no punct: " << toAdd << endl;

        //cout << holder << endl;
        //cout << "KeyWord: " << toAdd << ", c_str: " << toAdd.c_str()<< ", size:" << toAdd.getLength() <<endl;
        keywords.pushback(toAdd);

    }
    inFS.close();
    cout << "printing keyword list..." << endl;
    keywords.print();
    delete [] holder;
}//setKeyWordsList()
void Indexer::searchBook(){
    //cout << "in searchBook()" << endl;
    char *holder = new char[80];
    int pageNumber = 0;
    ifstream  inFS;
    inFS.open(bookFile.c_str());
    if(!inFS.is_open()){
        cout << "searchBook() failed to open: " << bookFile << endl;
        throw ios_base::failure("bad file name");
    }
    else{
        cout << "searchBook() successfully opened: " << bookFile << endl;
    }
    DSString line;
    inFS.getline(holder, 80);
    //cout << "first line: " << holder << endl;
    do{

        line = holder;
        if(line[0] == '<'){//change page
            char charHolder;
            DSString numHolder = "";
            charHolder = line[0];
            int spot = 1;
            while(charHolder != '>'){
                numHolder = numHolder + line.substring(spot,1);
                spot++;
                charHolder = line[spot];
            }
            pageNumber = atoi(numHolder.c_str());
            //cout << "page num line: " << line << endl;
            //cout << "string page: " << numHolder << ", page: " << pageNumber << endl;
        }
        line = line.removePunct();
        line = line.setLowerCase();

        for(int i = 0; i < keywords.getSize(); i++){
            //cout << line << endl;
            //cout << "searching for: " << keywords.get(i)<< endl;
            //cout << line.find(keywords.get(i)) << endl;
            if(line.find(keywords.get(i))>=0){
                IndexEntry entry(keywords.get(i));//make IndexEntry of word if it is found on the line

                if(index.contains(entry) <0){//if not in list add entry to list and set page
                    entry.addPage(pageNumber);
                    index.pushback(entry);
                    //cout <<"1 found: "<< entry.getWord()<< endl;
                }
                else{
                    index.get(index.contains(entry)).addPage(pageNumber);//if already in the index list add a page
                    //cout <<"2 found: "<< entry.getWord() << endl;
                }
            }//if keyword is on this line
        }
        //cout << "line: " << line << endl;
        inFS.getline(holder, 80);

    }while(line != "<-1>" && pageNumber != -1 && !inFS.eof());
    inFS.close();
    cout << "printing unsorted index..." << endl;
    index.print();
    delete [] holder;
}//searchBook()

void Indexer::createIndex(DSString outFile){
    //TODO
    ofstream outFS;
    outFS.open(outFile.c_str());
    if(!outFS.is_open()){
        cout << "creatIndex() failed to open: " << outFile << endl;
        throw ios_base::failure("bad file name");
    }
    else{
        cout << "createIndex() successfully opened: " << bookFile << endl;
    }
    DSVector <IndexEntry> sorted;
    sorted.pushback(index.get(0));
    //cout << "index size: " << index.getSize() << endl;
    for(int i=1; i<index.getSize();i++){
        //iterate through sorted and insert once alphetically greater
        //cout << "find order of: " << index.get(i) << ", loop: " << i << endl;
        for(int j=0; j<sorted.getSize();j++){
            if((sorted.get(j).getWord().alphaCompare(index.get(i).getWord()))>=0){
                //cout << "inserting: " << index.get(i) << ", at: " << j << endl;
                sorted.insert(j,index.get(i));
                j = sorted.getSize();//breaks inner for loop
            }
            else if(j == (sorted.getSize()-1)){//if reached end and still not found spot, place at end of list
                //cout << "pushing: " << index.get(i) << endl;
                sorted.insert(j+1,index.get(i));
                j = sorted.getSize();
            }
        }

    }//for loop organizes index in alpha order
    //set index = sorted
    index = sorted;
    cout << endl << "printing sorted index list..." << endl;
    index.print();
    //iterate through organized index to print to output file
    char first = index.get(0).getWord().operator[](0);//sets first index marker
    outFS <<"["<<first<<"]"<< endl;
    for(int i=0; i<index.getSize();i++){
        if(first != index.get(i).getWord().operator[](0)){
            first = index.get(i).getWord().operator[](0);//if in a new letter range print index marker
            outFS << endl <<"["<<first<<"]"<< endl;
        }
        outFS << index.get(i) <<": ";
        index.get(i).printPages(outFS);
        outFS << endl;
    }
    outFS.close();
}//createIndex(DSString outFile)
//
// Created by robot on 2/3/2021.
//

#ifndef DSSTRING
#define DSSTRING

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

class DSString{

private:
    /**
     *  You will need to add some private data members here.
     *  This is up to your discretion.  However, we **strongly**
     *  encourage you to implement your string class as a wrapper
     *  for typical null-terminated c-strings.  In doing this, you
     *  may use c-sting functions in the methods in this class such
     *  as:
     *    * strlen(...)
     *    * strcpy(...)
     *    * strcmp(...)
     *    * strncpy(...)
     *    * strcat(...)
     *    * strncat(...)
     *
     *    A quick google search will return plenty of references on
     *    the c-string functions.
     **/
    char* data;

public:

    /**
     * Constructors and destructor
     *
     * Make sure you do proper memory management.
     **/
    DSString(){
        data = nullptr;
    }//DSString()
    DSString(const char* n){
        data = new char[strlen(n)+1];
        strcpy(data, n);
        data[strlen(n)] = '\0';
    }//DSString(const char* n)
    DSString(const DSString& n){
        data = new char[strlen(n.data)+1];
        strcpy(data,n.data);
        data[strlen(n.data)] = '\0';
    }//DSString(const DSString& n)
    ~DSString(){
        delete [] data;
    }//DSString deconstruct

    /**
     * Standard relational operators.  You are free to expand this
     * list if you'd like.
     *
     * Note that for each operator, there are two overloaded versions:
     *    one that takes a String object
     *    one that takes a null-terminated c-string
     *
     **/
    DSString& operator= (const char* d){
        if(data != nullptr)
            delete [] data;
        int length = strlen(d);
        data = new char[length+1];
        strcpy(data, d);
        data[length] = '\0';
        return* this;
    }//operator= w/ const char*
    DSString& operator= (const DSString& d){
        if(data != nullptr)
            delete [] data;
        data = new char[strlen(d.data)+1];
        strcpy(data, d.data);
        data[strlen(d.data)] = '\0';
        return *this;
    }//operator= w/ const DSString&
    DSString operator+ (const DSString& n){
        char result [strlen(data)];
        //result = data;
        strcpy(result,data);
        DSString addStr;
        addStr = strcat(result,n.data);
        return addStr;
    }//operator+ w/ DSString&
    DSString operator+ (const char* n){
        char result [strlen(data)];
        //result = data;
        strcpy(result,data);
        DSString addStr;
        addStr = strcat(result,n);
        return addStr;
    }//operator+ w/ DSString

    DSString& operator+= (const char* n){
        char* result = data;
        result = strcat(data,n);
        data = result;
        return* this;
    }//operator += w/ const char*
    DSString& operator+= (const DSString& n){
        char* result = data;
        result = strcat(data,n.data);
        data = result;
        return* this;
    }//operator += w/ DSString&



    bool operator== (const char* n) const{
        if(strcmp(data,n)==0)
            return true;
        else
            return false;
    }//operator== w/ const char*
    bool operator== (const DSString& n) const{
        if(strcmp(data,n.data)==0)
            return true;
        else
            return false;
    }//operator== w/ const DString&
    bool operator!= (const char* n) const{
        if(strcmp(data,n)==0)
            return false;
        else
            return true;
    }//operator!= w/ const char*
    bool operator!= (const DSString& n)const {
        if(strcmp(data,n.data)==0)
            return false;
        else
            return true;
    }//operator!= w/ const DSString&
    bool operator> (const DSString& n)const{
        if(strcmp(data,n.data)>0)
            return true;
        else
            return false;
    }//operator> w/ const DSString&
    bool operator> (const char* n)const{
        if(strcmp(data,n)>0)
            return true;
        else
            return false;
    }//operator> w/ const char*
    bool operator< (const DSString&n)const{
        if(strcmp(data,n.data)<0)
            return true;
        else
            return false;
    }//operator< w/ const DSString&
    bool operator< (const char* n)const{
        if(strcmp(data,n)<0)
            return true;
        else
            return false;
    }//operator< w/ const char*

    char& operator[] (const int n) {
        return data[n];
    }//operator[] w/ const int
    /**
     * getLength() returns the number (count) of characters in the string.
     **/
    int getLength()const{
        return strlen(data);
    }//getLength

    /**
     * The substring method returns a string object that contains a
     * sequence of characters from this string object.
     *
     * param start - the index of where to start
     * param numChars - the number (count) of characters to copy into
     *    the substring
     **/
    DSString substring(int start, int numChars){
        char* addTo = new char[numChars+1];
        strncpy(addTo,data+start,numChars);
        addTo[numChars]='\0';
        DSString result(addTo);
        if(addTo != nullptr )
        delete [] addTo;
        return result;
    }//substring

    /**
     * the c_str function returns a null-terminated c-string holding the
     * contents of this object.
     **/
    char* c_str(){
        return data;
    }//c_str

    /**
     * Overloaded stream insertion operator to print the contents of this
     * string to the output stream in the first argument.
     **/
    friend std::ostream& operator<< (std::ostream& outS, const DSString& n){
        outS << n.data;
        return outS;
    }//operator<<
    friend std::istream& operator>> (std::istream& inS, const DSString& n){
        inS >> n.data;
        return inS;
    }//operator>>
    /**
     *
     * @param key word being searched for
     * @param word string that is being searched in
     * @return location of first letter in word if found or -1 if not found
     */
    int find(const char* key){
        int wLength = strlen(key);
        for(int i=0; i<(this->getLength()-wLength+1); i++){
            if(this->substring(i,wLength)==key)
                return i;
        }//check every spot for the key word
        return -1;//keyword not found
    }//find w/ const char*
    /**
     *
     * @param key word being searched for
     * @param string being searched in
     * @return location of first letter in key or -1 if not found
     */
    int find(const DSString& key){
        int wLength = key.getLength();
        for(int i=0; i<this->getLength()-wLength+1; i++){
            //cout << substring(i,wLength) << "/";
            if(this->substring(i,wLength)==key)
                return i;
        }//check every spot for the key word
        return -1;//keyword not found
    }//find w/ DSString&


    //You are free to add more functionality to the class.  For example,
    //you may want to add a find(...) function that will search for a
    //string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.
    /*
    friend void getlineDS(istream& inS, DSString& output, const char end='\n') {
        //TODO write getline function :(
        output = "";
        char letter = ' ';
        //getline(inS, word, end);
        do {
            inS >> letter;
            if (inS.bad()) {
                letter = end;//if stream error occurs, stop tryiing to read
            }
            if (letter != end) {
                char *word = " ";
                word[0] = letter;
                output += word;
            }
        } while (letter != end);
    }
    */
    /**
     * helps compare words in terms of alphabetical order as opposed to over all value
     * @param word2 word to be compared to this
     * @return 1 if this after(greater than) word2 alphabetically, -1 for the opposite, 0 for equal
     */
    int alphaCompare(DSString word2){
        bool equal = true;
        int length1 = strlen(data);
        int length2 = word2.getLength();
        if(word2.find("/r")>=0){
            word2 =word2.substring(0,word2.getLength()-1);
        }
        for(int i=0; i<length1 && i<length2; i++){
            if(this->substring(i,1)>word2.substring(i,1))
                return 1;//this is greater than word2

            else if(this->substring(i,1)<word2.substring(i,1))
                return -1;//this is less than word2
        }//read until end of shortest word
        if(length1<length2)
            return -1;//values were equal but this was shorter

        else if(length1>length2)
            return 1;//values were equal but this was longer

        else
            return 0;
    }//alpha compare

    DSString removePunct(){
        int length = strlen(data);
        DSString newString = "";
        for(int i =0; i<length; i++){
            if(!ispunct(data[i]))
                newString = newString + this->substring(i,1);
        }

        return newString;
    }//removePunct()

    DSString setLowerCase(){
        int length = strlen(data);
        DSString newString = *this;
        for(int i =0; i<length; i++){
            char ch = data[i];
            if(isupper(ch) && isalpha(data[i])) {
                newString.data[i] = ch+32;//convert uppercase to lowercase
            }
            else {
                newString.data[i] = ch;
            }
        }

        return newString;
    }//setLowerCase()

};
#endif
//
// Created by robot on 2/25/2021.
//

#ifndef INC_20F_AUTO_IDX_DSVECTOR_H
#define INC_20F_AUTO_IDX_DSVECTOR_H
#include <exception>
#include <fstream>
#include <iostream>

using namespace std;

template<class T>
class DSVector{
private:
    T* d;//array that will hold our data T
    int cap;//maximum spots in the array
    int size;//number of values
    void grow();
public:
    DSVector();//default constructor
    DSVector(int initSize);
    DSVector(const DSVector<T>& val);//copy constructor
    ~DSVector();//destructor
    //TODO add destructor
    //Operators
    DSVector<T>& operator = (const DSVector<T>& val);
    bool operator==(const DSVector<T>& val)const;
    T& operator[](int location)const;
    //Accessor methods
    int getCap();
    int getSize();
    T& get(int loc);
    //Mutator methods
    void set(int loc, T val);
    void deleteAt(int loc);//removes element at loc
    T& pop();//removes element at the end;
    void pushback(T val);
    void insert(int loc, T val);
    //Other
    int contains(T val);
    void print(std::ostream& outS = cout);
};

//++++++++++ CONSTRUCTOR IMPLEMENTATION
template<class T>
DSVector<T>::DSVector(){
    d = new T[10];
    size = 0;
    cap = 10;

}//DSVector()
template<class T>
DSVector<T>::DSVector(int initSize){
    if(d != nullptr)
        delete [] d;
    d = new T[initSize];
    size = 0;
    cap = initSize;//sets cap to array size
}//DSVector(int initSize = 10)
template<class T>
DSVector<T>::DSVector(const DSVector<T>& val){
    //if(d != nullptr)
    //delete [] d;
    d = new T[val.cap];
    for(int i = 0; i < val.size; i++)
        d[i] = val[i];
    size = val.size;
    cap = val.cap;
}
template<class T>
DSVector<T>::~DSVector(){
    delete [] d;
}
//++++++++++ OPERATOR IMPLEMENTATION
template<class T>
DSVector<T>& DSVector<T>::operator=(const DSVector& val){
    if(d != nullptr)
        delete [] d;
    d = new T[val.cap];
    for(int i = 0; i < val.size; i++)
        d[i] = val[i];
    size = val.size;
    cap = val.cap;
    return *this;
}//operator =
template<class T>
bool DSVector<T>::operator==(const DSVector<T>& val)const{
    bool equal = true;
    for(int i = 0; i < val.size; i++) {
        if(d[i] != val[i])
            equal = false;
    }
    return equal;
}
template<class T>
T& DSVector<T>::operator[](int location)const{
    if(location > cap || location < 0)
        throw out_of_range("bad location value");
    return d[location];
}//operator[]
//ACCESSOR METHOD IMPLEMENTATION
/**
 * tells capacity of vector
 * @return current maximum capacity of array d
 */
template<class T>
int DSVector<T>::getCap(){
    return cap;
}
/**
 * tells size of vector
 * @return number of values in array
 */
template<class T>
int DSVector<T>::getSize(){
    return size;
}
/**
 * accesses a value in the vector
 * @param loc the location of array to be accessed
 * @return the value at that location of the array
 */
template<class T>
T& DSVector<T>::get(int loc){
    if(loc > cap || loc < 0)
        throw out_of_range("bad loc value");
    return d[loc];
}//get(int loc)

//++++++++++ MUTATOR METHOD IMPLEMENTATION
/**
 * sets an element to a certain value
 * @param loc the location of arra d to be accessed
 * @param val value to set that array to
 */
template<class T>
void DSVector<T>::set(int loc, T val){
    if(loc > cap || loc < 0)
        throw out_of_range("bad loc value");
    d[loc] = val;
}
/**
 * deletes a value from array
 * @param loc location of value in array d to be deleted
 */
template<class T>
void DSVector<T>::deleteAt(int loc) {
    if(loc > cap || loc < 0)
        throw out_of_range("bad loc value");
    T* temp = new T[cap];
    int j =0;//spot in temp vector

    for(int i=0; i<size; i++){
        if(i != loc){
            temp[j] = d[i];
            j++;
        }//adds all values not a location to be deleted
    }//iterates through d
    delete [] d;
    d = temp;
    size--;
}//deleteAt(int loc)
/**
 * removes last value of array d
 * @return returns the value that was removed
 */
template<class T>
T& DSVector<T>::pop() {
    /* T* temp = new T[cap];
    for(int i=0; i<size-1; i++){
            temp[i] = d[i];
    }//iterates through d
    T popped = d[size-1];
    delete [] d;
    d = temp;
    size--;
    return popped;
     */
    size--;
    return d[size];
}
/**
 * adds a value to the end of array d
 * @param val is the value to be added
 */
template<class T>
void DSVector<T>::pushback(T val){
    if(size == cap)
        this->grow();
    d[size++] =val;
}//pushback(T val)
/**
 *
 * @param loc
 * @param val
 */
template<class T>
void DSVector<T>::insert(int loc, T val){
    if(size == cap)
        this->grow();
    T* temp = new T[size+1];
    int dLoc = 0;
    for(int i=0; i< size+1; i++){
        if(i == loc)
            temp[i] = val;
        else{
            temp[i] = d[dLoc];
            dLoc++;
        }
    }
    size++;
    delete [] d;
    d = temp;
}//insert

//OTHER METHODS IMPLEMENTATION
/**
 * checks if val is included in the vector
 * @param val val to check for
 * @return true if val is present in list, false otherwise
 */
template<class T>
int DSVector<T>::contains(T val){
    int found = -1;
    for(int i=0; i<size; i++){
        if (d[i] == val) {
            found = i;
            return found;
        }
    }
    return found;
}
/**
 * prints the contents of the vector
 * T must have an overloaded operator <<
 */
template<class T>
void DSVector<T>::print(std::ostream& outS){
    for(int i=0; i<size; i++)
        outS << d[i] << endl;
}//void print
/**
 * doubles the capacity of the vector, to be called if size = capacity
 */
template<class T>
void DSVector<T>::grow(){
    T* temp = new T[2*cap];
    for(int i=0; i<cap; i++)
        temp[i] = d[i];
    cap *= 2;
    delete[] d;
    d = temp;
}//grow()
#endif //INC_20F_AUTO_IDX_DSVECTOR_H
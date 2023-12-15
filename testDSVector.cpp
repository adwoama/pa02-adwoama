//
// Created by robot on 2/25/2021.
//
#include "catch.hpp"
#include "DSVector.h"
#include <iostream>

using namespace std;
//TEST_CASE 1
TEST_CASE("DSVectors can return member values"){
    DSVector <int> vector1(11);
    SECTION("Implement getSize()"){
        CHECK((vector1.getSize() == 0));
    }//S1
    SECTION("Implement getCap()"){
        CHECK((vector1.getCap() == 11));
    }//S2
    SECTION("Implement get() to return a value"){
        vector1.pushback(1);
        vector1.pushback(0);
        vector1.set(1,2);
        CHECK((vector1.get(0) == 1));
        CHECK((vector1.get(1) == 2));
    }//S3
    DSVector <int> vector2(4);
    SECTION("Implement deleteAt() and pop()"){
        vector2.pushback(0);
        vector2.pushback(1);
        vector2.pushback(2);
        vector2.pushback(3);
        vector2.pushback(4);
        vector2.deleteAt(2);

        CHECK((vector2.get(2) == 3));
        CHECK((vector2.pop() == 4));
    }
    //cout << "finished accessing check" << endl;
}//End of TEST_CASE 1

//TEST_CASE 2
/*TEST_CASE("DSVectors can be edited"){
    cout << "inside editing check" << endl;
    DSVector <int> vector2(3);
    cout << "initialized vector 2" << endl;
    SECTION("Implement set()"){
        vector2.pushback(0);
        vector2.pushback(0);
        vector2.set(0, 1);
        vector2.set(1, 2);
        cout<< vector2.get(0) << endl;
        cout<< vector2.get(1) << endl;
        //CHECK((vector2.get(0) == 1));
        //CHECK((vector2.get(1) == 2));
    }//S1
    SECTION("Implement pushback()"){
        vector2.pushback(3);
        vector2.pushback(4);
        cout<< vector2.get(2) << endl;
        cout<< vector2.get(3) << endl;
        //CHECK((vector2.get(2) == 3));
        //CHECK((vector2.get(3) == 4));
    }//S2
    SECTION("Implement deleteAt()"){
        vector2.deleteAt(0);
        cout<< vector2.get(0) << endl;
        //CHECK((vector2.get(0) == 2));
    }

}//End of TEST_CASE 2
*/


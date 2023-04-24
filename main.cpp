#include <iostream>

#include "StringCreaterPieceByPiece.h"

int main()
{

    StringCreaterPieceByPiece sc(2);

    sc.addPiece("test");
    sc.addPiece();
    sc.addPiece("football");

    for (int i = 0; i < 3; i++) {
        sc[i].printAll();
    }

    sc[1] <<  " friends ";
    sc[1].printAll();
    " Hello " >> sc[1];

    "10" >> sc[2];

    //for (int i = 0; i < 3; i++) {
    //    sc[i].printAll();
    //}

    MyString result1 = sc.getString(); // test Hello friends 10football
    std::cout << "Res1: " << result1 << std::endl;

    sc.swap(1, 2);
    MyString result2 = sc.getString(); // test10football Hello friends
    std::cout << "Res2: " << result2 << std::endl;

    sc.remove(1);
    MyString result3 = sc.getString(); // test                     Hello friends
    std::cout << "Res3: " << result3 << std::endl;


    sc.addPiece("deletNoDelete");
    sc[3].printAll();
    sc[3].removeFirstKSymbols(5);
    sc[3].removeLastKSymbols(3);
    "right_" >> sc[3];
    sc[3] << " left";
    sc[3].printAll();
    MyString result4 = sc.getString();
    std::cout << "Res3: " << result4 << std::endl;
}

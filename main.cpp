#include <iostream>

#include "StringCreaterPieceByPiece.h"

int main()
{

    StringCreaterPieceByPiece sc(2);

    sc.addPiece("test");
    sc.addPiece();
    sc.addPiece("football");

    sc[1] <<  " friends ";
    " Hello " >> sc[1];

    "10" >> sc[2];

    for (int i = 0; i < 3; i++) {
        sc[i].printAll();
    }

    MyString result1 = sc.getString(); // test Hello friends 10football
    std::cout << "Res1: " << result1 << std::endl;

    sc.swap(1, 2);
    MyString result2 = sc.getString(); // test10football Hello friends
    std::cout << "Res2: " << result2 << std::endl;

    sc.remove(1);
    MyString result3 = sc.getString(); // test                     Hello friends
    std::cout << "Res3: " << result3 << std::endl;
}

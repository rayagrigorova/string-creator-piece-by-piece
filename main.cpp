#include <iostream>

#include "StringCreaterPieceByPiece.h"

int main() {
    StringCreaterPieceByPiece sc(2);

    sc.addPiece("test");
    sc.addPiece();
    sc.addPiece("football");

    sc[1] <<  " friends ";
    " Hello " >> sc[1];

    123456 >> sc[2];

    MyString result1 = sc.getString(); // test Hello  friends 123456football
    std::cout << "Res1: " << result1 << std::endl;

    sc.swap(1, 2); // Swap ' Hello  friends ' and '123456football'
    MyString result2 = sc.getString(); // test123456football Hello friends
    std::cout << "Res2: " << result2 << std::endl;

    sc.remove(1); // Remove '123456football'
    MyString result3 = sc.getString(); // test                     Hello friends
    std::cout << "Res3: " << result3 << std::endl;

    sc.addPiece("deletNoDelete");

    sc[3].removeFirstKSymbols(5); // NoDelete
    sc[3].removeLastKSymbols(3); // NoDel
    "right_" >> sc[3]; // right_NoDel
    sc[3] << " left"; // right_NoDel left
    sc[3].removeFirstKSymbols(1); // ight_NoDel left
    6 >> sc[3]; // 6ight_NoDel left
    sc[3].removeLastKSymbols(1); // 6ight_NoDel lef
    sc[3] << "*"; // 6ight_NoDel lef*

    sc.addPiece(" ___sss____", 1); // replace the deleted piece 

    MyString result4 = sc.getString();

    std::cout << "Res4: " << result4 << std::endl;
    std::cout << "Size: " << sc.length() << std::endl; // 47
}

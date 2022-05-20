#include "MList.h"


int main()
{
//    MatrixList consoleMatrix;
//    consoleMatrix.setFileName("a");
//    consoleMatrix.addItem();
//    consoleMatrix.setFileName("b");
//    consoleMatrix.addItem();
//    consoleMatrix.setFileName("c");
//    consoleMatrix.removeItem(1);
//    consoleMatrix.setFileName("d");
//    consoleMatrix.addItem();
//    consoleMatrix.print_list();
//    consoleMatrix.sort(typeSort::bubble);
//    consoleMatrix.print_list();

    MatrixList fileMatrix(typeLoader::fileLoader);
    fileMatrix.setFileName("dataMatrix_3.txt");
    fileMatrix.addItem();
    fileMatrix.setFileName("dataMatrix_1.txt");
    fileMatrix.addItem();
    fileMatrix.setFileName("dataMatrix_2.txt");
    fileMatrix.addItem();
    fileMatrix.print_list();
    fileMatrix.sort(typeSort::quick);
    fileMatrix.print_list();
    return 0;
}

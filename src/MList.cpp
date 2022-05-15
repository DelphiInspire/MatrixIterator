#include "IteratorInterface.h"
MatrixList::MatrixList(): head{nullptr}
{
    matrixConsoleLoader = new ConsoleLoader();
    matrixFileLoader = new FileLoader();
    matrixQuickSorter = new QuickSort();
    matrixShellSorter = new ShellSort();
    matrixBubbleSorter = new BubbleSort();
};
//-1. Add item
void MatrixList::addItem(typeLoader type)
{
    switch (type) {
        case(typeLoader::consoleLoader):
        {
            addItem(matrixConsoleLoader);
        }break;
        case(typeLoader::fileLoader):
        {
            addItem(matrixFileLoader);
        }break;
        default:
        {
            return;
        }
    }
}
void MatrixList::addItem(ILoader* loader)
{
    auto node = new matrixNode(loader->loadMatrix());
    //connection with old node
    node->nextNodeMatrix = head;
    //new node became head
    head = node;
}
//-2.Sort Items

void MatrixList::sort(typeSort type)
{
    switch (type)
    {
        case(typeSort::quick):
        {
            sort(matrixQuickSorter);
        }break;
        case(typeSort::shell):
        {
            sort(matrixShellSorter);
        }break;
        case(typeSort::bubble):
        {
            sort(matrixBubbleSorter);
        }break;
        default:
        {
            return;
        }
    }
}



void MatrixList::remove()
{
    if(head)
    {
        matrixNode* nHead = head->nextNodeMatrix;
        delete head;
        head = nHead;
    }
}

MatrixList::~MatrixList()
{
    delete matrixConsoleLoader;
    delete matrixFileLoader;
    delete matrixQuickSorter;
    delete matrixShellSorter;
    delete matrixBubbleSorter;
    while(head)
    {
        remove();
    }
}




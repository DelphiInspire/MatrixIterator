#ifndef MATRIXITERATOS_ITERATORINTERFACE_H
#define MATRIXITERATOS_ITERATORINTERFACE_H
#include "Sorter.h"
//#include "IteratorInterface.h"

enum class typeLoader{consoleLoader = 0, fileLoader};
enum class typeSort{quick = 0, shell, bubble};

class IteratorInterface
{
public:
    virtual IteratorInterface& first() = 0;
    virtual IteratorInterface& next() = 0;
    virtual ~IteratorInterface(){};
};

class MatrixList
{
private:
    struct matrixNode
    {
        explicit matrixNode(Matrix data):storageMatrix{std::move(data)}, nextNodeMatrix{nullptr}{};
        Matrix storageMatrix;
        matrixNode* nextNodeMatrix;
        ~matrixNode(){};
    };
public:
    class Iterator: public IteratorInterface
    {
    public:
        Iterator(matrixNode* initNode): iteratorNode{initNode}{};
        Iterator& first() override
        {
            return *this;
        };
        Iterator& next() override
        {
            iteratorNode = iteratorNode->nextNodeMatrix;
            return *this;
        };
        Matrix operator*() const {return iteratorNode->storageMatrix;};
    private:
        matrixNode* iteratorNode;
    };
public:
    MatrixList();
    void addItem(typeLoader type);
    void sort(typeSort type);

    Iterator begin() {return Iterator(head);};
    Iterator end(){return Iterator(nullptr);};
    void remove();
    void loadMatrix();
    size_t getSize() const {return size;};
    ~MatrixList();
private:
    void addItem(ILoader* loader);
    void sort(ISorter* sorter);
private:
    matrixNode* head;
    ISorter* matrixQuickSorter;
    ISorter* matrixShellSorter;
    ISorter* matrixBubbleSorter;
    ILoader* matrixConsoleLoader;
    ILoader* matrixFileLoader;
    size_t size;
};






#endif //MATRIXITERATOS_ITERATORINTERFACE_H

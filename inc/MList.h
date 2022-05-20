#ifndef MATRIXITERATOS_MLIST_H
#define MATRIXITERATOS_MLIST_H

#include "Loader.h"
#include "IIterator.h"
#include "Sorter.h"
#include "string"


enum class typeLoader{consoleLoader = 0, fileLoader};
enum class typeSort{quick = 0, shell, bubble};

constexpr size_t initCapacity = 10; //default capacity MList
constexpr size_t maxInitSize = 10; //max default MList size
constexpr size_t zeroSize = 0; // empty MList size init

class MatrixList
{
private:
    class FIterator: public IteratorInterface
    {
    public:
        explicit FIterator(containerCell* initNode): iteratorNode{initNode}{};
        FIterator& first() override{return *this;};
        FIterator& next() override
        {
            ++iteratorNode;
            return *this;
        };
        bool operator!=(const FIterator& rhsIterator) const
        {
            return !(*this == rhsIterator);
        }
        bool operator==(const FIterator& rhsIterator) const
        {
            return (iteratorNode == rhsIterator.iteratorNode);
        }
        containerCell& operator*() const
        {
            return *iteratorNode;
        };
    private:
        containerCell* iteratorNode;
    };
public:
    using iterator = FIterator;
public:
    explicit MatrixList(typeLoader loader = typeLoader::consoleLoader, typeSort sorter =typeSort::quick);
    void addItem();
    void sort();
    iterator begin();
    iterator end();
    void removeItem(size_t index);
    Matrix& operator[](size_t);
    void print_list();
    size_t size() const {return containerSize;};
    void setFileName(const std::string& filename);
    ~MatrixList();
private:
    void checkValidIndex(size_t index) const;
    void sortersInit();

    void loadersInit();
    void reallocMemory();
private:
    containerCell* containerData;
    size_t containerSize;
    size_t maxSize;
    size_t capacity;
    typeLoader tLoader;
    typeSort tSorter;
    ISorter* matrixSorter;
    ILoader* matrixLoader;
private:
    containerCell* iteratorNode;
};

#endif //MATRIXITERATOS_MLIST_H

#ifndef MATRIXITERATOS_MLIST_H
#define MATRIXITERATOS_MLIST_H

#include "string"

class ISorter;
class ILoader;
class Matrix;
class FIterator;

enum class typeLoader{consoleLoader = 0, fileLoader};
enum class typeSort{quick = 0, shell, bubble};

constexpr size_t initCapacity = 10; //default capacity MList
constexpr size_t maxInitSize = 10; //max default MList size
constexpr size_t zeroSize = 0; // empty MList size init

class MatrixList
{
public:
    using iterator = FIterator;
public:
    explicit MatrixList(typeLoader loader = typeLoader::consoleLoader, typeSort sorter =typeSort::quick);
    void addItem();
    void sort();
    void removeItem(size_t index);
    void print_list();
    size_t size() const {return containerSize;};
    void setFileName(const std::string& filename);
    Matrix& operator[](size_t);
    ~MatrixList();
public:
    iterator begin();
    iterator end();
private:
    void checkValidIndex(size_t index) const;
    void sortersInit();
    void loadersInit();
    void reallocMemory();
private:
    Matrix* containerData;
    size_t containerSize;
    size_t maxSize;
    size_t capacity;
    typeLoader tLoader;
    typeSort tSorter;
    ISorter* matrixSorter;
    ILoader* matrixLoader;
};

#endif //MATRIXITERATOS_MLIST_H

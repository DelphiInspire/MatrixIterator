#ifndef MATRIXITERATOS_MLIST_H
#define MATRIXITERATOS_MLIST_H
//#include "Sorter.h"
//#include "Loader.h"
#include "Loader.h"
#include "IIterator.h"
#include "Sorter.h"
#include "string"
enum class typeLoader{consoleLoader = 0, fileLoader};
enum class typeSort{quick = 0, shell, bubble};

class MatrixList
{
public:
    using iterator = fIterator;
public:
    explicit MatrixList(typeLoader loader = typeLoader::consoleLoader);
    void addItem();
    void sort(typeSort type);
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
    void sortersInit(typeSort tSort);
    void loadersInit();
    void reallocMemory();
private:
    containerCell* containerData;
    size_t containerSize;
    size_t maxSize;
    size_t capacity;
    typeLoader tLoader;
    ISorter* matrixSorter;
    ILoader* matrixLoader;
    private:
    containerCell* iteratorNode;

};

#endif //MATRIXITERATOS_MLIST_H

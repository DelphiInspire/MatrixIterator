#include "MList.h"
#include "iostream"


MatrixList::MatrixList(typeLoader loader):tLoader{loader}, capacity{10}, maxSize{10}, containerSize{0}
{
    containerData = new containerCell[capacity];
    loadersInit();
};

MatrixList::iterator MatrixList::begin()
{
    return fIterator(containerData);
}

MatrixList::iterator MatrixList::end()
{
    return fIterator(&containerData[containerSize]);
}
//-1. Add item
void MatrixList::addItem()
{
    if(containerSize == maxSize)
    {
        reallocMemory();
    }
    containerData[containerSize] = matrixLoader->loadMatrix();
    ++containerSize;
}

void MatrixList::reallocMemory()
{
    containerCell* buffer{containerData};
    containerData = new containerCell [maxSize + capacity];
    for(size_t i = 0, end = maxSize; i < maxSize; ++i)
    {
        containerData[i] = buffer[i];
    }
    maxSize += capacity;
    delete [] buffer;
}

void MatrixList::sortersInit(typeSort tSort)
{
    switch (tSort)
    {
        case(typeSort::quick):
        {
            matrixSorter = new QuickSort();;
        }break;
        case(typeSort::shell):
        {
            matrixSorter = new ShellSort();;
        }break;
        case(typeSort::bubble):
        {
            matrixSorter = new BubbleSort();
        }break;
        default:
        {
            return;
        }
    }
}

void MatrixList::loadersInit()
{
    switch(tLoader)
    {
        case(typeLoader::fileLoader):
        {
            matrixLoader = new FileLoader();
        }break;
        case(typeLoader::consoleLoader):
        {
            matrixLoader = new ConsoleLoader();
        }break;
        default:
        {
            return;
        }
    }
}

Matrix& MatrixList::operator[](size_t index)
{
    checkValidIndex(index);
    return containerData[index].second;
}

void MatrixList::removeItem(size_t index)
{
    checkValidIndex(index);
    size_t ShiftPoint{index};
    while(ShiftPoint <= containerSize - 2)
    {
        containerData[ShiftPoint] = containerData[ShiftPoint + 1];
        ++ShiftPoint;
    }
    containerData[containerSize - 1].second.~Matrix();
    containerData[containerSize - 1].first.clear();
    --containerSize;
}

void MatrixList::sort(typeSort type)
{
    sortersInit(type);
    matrixSorter->sort(begin(), end());
    delete matrixSorter;
}

void MatrixList::print_list()
{
    for(size_t i = 0; i<containerSize; ++i)
    {
        std::cout << containerData[i].first << " ";
    }
    std::cout << std::endl;
}

void MatrixList::setFileName(const std::string &filename)
{
    matrixLoader->setFileName(filename);
}

void MatrixList::checkValidIndex(size_t index) const
{
    if(index >= containerSize)
    {
        throw MemoryAllow();
    }
}

MatrixList::~MatrixList()
{
    delete matrixLoader;
    delete [] containerData;
}




////#include "MList.h"
#include "IIterator.h"

class ISorter
{
public:
    virtual void sort(fIterator startIt, fIterator endIt) = 0;
protected:
    virtual std::tuple<float, float> GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp) const;
    virtual void try_shift_value(containerCell * array, size_t position, size_t interval);
    int size_estimation(fIterator startIt, fIterator endIt);
    virtual void swap(containerCell * input_1, containerCell * input_2);
public:
    virtual ~ISorter(){};
};

class QuickSort: public ISorter
{
public:
    QuickSort() { };
    void sort(fIterator startIt, fIterator endIt) override;
private:
    void Qsort(containerCell * sortList, int low, int high);
    int partition(containerCell * arrangeList, int low, int high);
private:
    int startListPos;
    int stopListPos;
};

class BubbleSort: public ISorter
{
public:
    void sort(fIterator startIt, fIterator endIt) override;
};

class ShellSort: public ISorter
{
public:
    void sort(fIterator startIt, fIterator endIt) override;
};






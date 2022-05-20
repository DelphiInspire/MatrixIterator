#include "IIterator.h"

class ISorter
{
public:
    virtual void sort(containerCell* matrixContainer, int size) = 0;
protected:
    virtual std::tuple<float, float> GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp) const;
    virtual void try_shift_value(containerCell* array, size_t position, size_t interval);
    virtual void swap(containerCell * input_1, containerCell * input_2);
public:
    virtual ~ISorter(){};
};

class QuickSort: public ISorter
{
public:
    QuickSort() = default;
    void sort(containerCell* startIt, int size) override;
    ~QuickSort(){};
private:
    void Qsort(containerCell* sortList, int low, int high);
    int partition(containerCell* arrangeList, int low, int high);
private:
    int startListPos;
    int stopListPos;
};

class BubbleSort: public ISorter
{
public:
    BubbleSort() = default;
    void sort(containerCell* startIt, int size) override;
};

class ShellSort: public ISorter
{
public:
    ShellSort() = default;
    void sort(containerCell* startIt, int size) override;
};






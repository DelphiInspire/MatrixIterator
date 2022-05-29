#include <tuple>

class Matrix;
class IteratorInterface;

class ISorter
{
public:
    virtual void sort(Matrix* matrixContainer, int size) = 0;
    virtual ~ISorter(){};
protected:
    virtual std::tuple<float, float> GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp) const;
    virtual void try_shift_value(Matrix* array, size_t position, size_t interval);
    virtual void swap(Matrix* input_1, Matrix* input_2);
protected:
    int sortSize;
    IteratorInterface* startPoint;
    IteratorInterface* stopPoint;
};

class QuickSort: public ISorter
{
public:
    QuickSort() = default;
    void sort(Matrix* startIt, int size) override;
    ~QuickSort(){};
private:
    void Qsort(Matrix* sortList, int low, int high);
    int partition(Matrix* arrangeList, int low, int high);
private:
    int startListPos;
    int stopListPos;
};

class BubbleSort: public ISorter
{
public:
    BubbleSort() = default;
    void sort(Matrix* startIt, int size) override;
};

class ShellSort: public ISorter
{
public:
    ShellSort() = default;
    void sort(Matrix* startIt, int size) override;
};







#include "Sorter.h"
#include "Matrix.h"

void ISorter::swap(Matrix * input_1, Matrix * input_2){
    Matrix buffer = *input_1;
    *input_1 = *input_2;
    *input_2 = buffer;
}

void ISorter::try_shift_value(Matrix* sortList, size_t position, size_t interval)
{
    for (int left_counter = position - interval, right_counter = position; left_counter >= 0; right_counter = left_counter, left_counter -= interval)
    {
        auto [left_Matrix, right_Matrix] = GetComparisonValues(sortList[left_counter],
                                                                            sortList[right_counter]);
        if(right_Matrix <= left_Matrix)
        {
            swap(&sortList[right_counter], &sortList[left_counter]);
        }
    }
}

std::tuple<float, float> ISorter::GetComparisonValues(const Matrix& lcomp, const Matrix& rcomp) const
{
    float lDiagonalsSum{lcomp.getSumDiagonalsResult()};
    float rDiagonalsSum{rcomp.getSumDiagonalsResult()};
    //choose the way to comparison
    if (lDiagonalsSum != rDiagonalsSum) {
        return std::make_tuple(lDiagonalsSum, rDiagonalsSum);
    }
    else
    {
        float lTraceSum{lcomp.getMajorDiagonalSum()};
        float rTraceSum{rcomp.getMajorDiagonalSum()};
        return std::make_tuple(lTraceSum, rTraceSum);
    }
}

int QuickSort::partition(Matrix* arrangeList, int low, int high)
{
    int position = low - 1;
    for (size_t i = low; i < high; ++i) {
        //choose the way to comparison
        auto [step_comparator, pivot] = GetComparisonValues(arrangeList[i],
                                                                        arrangeList[high]);
        //rearranging array
        if (step_comparator <= pivot)
        {
            position++;
            swap(&arrangeList[position], &arrangeList[i]);
        }
    }
    swap(&arrangeList[position + 1], &arrangeList[high]);
    return (position + 1);
}

void QuickSort::sort(Matrix* startIt, int size)
{
    startListPos = 0;
    stopListPos = size - 1;
    Qsort(startIt, startListPos, stopListPos);
}

void QuickSort::Qsort(Matrix* sortList, int low, int high)
{
    if(low < high)
    {
        int pi = partition(sortList, low, high);
        Qsort(sortList, low, pi - 1);
        Qsort(sortList, pi + 1, high);
    }
}

void BubbleSort::sort(Matrix* startIt, int size)
{
    size_t stop_pos = size;
    Matrix* sortList = startIt;
    for (size_t run_counter = 0; run_counter < stop_pos - 1; run_counter++)
    {
        for (size_t counter = 0; counter < stop_pos - run_counter - 1; counter++)
        {
            auto [l_member, r_member] = GetComparisonValues(sortList[counter],
                                                            sortList[counter + 1]);
            if (l_member >= r_member)
            {
                swap(&sortList[counter], &sortList[counter + 1]);
            }
        }
    }
}

void ShellSort::sort(Matrix* startIt, int size)
{
    constexpr size_t step_modificator{2};
    Matrix* sortList = startIt;
    size_t interval{static_cast<size_t>(size / step_modificator)};
    bool success_check_sort{false};
    while(!success_check_sort)
    {
        if(interval == 1)
        {
            success_check_sort = true;
        }
        for(size_t left_counter = 0, right_counter = interval;  right_counter < size; left_counter++, right_counter = left_counter + interval)
        {
            auto [left_Matrix, right_Matrix] = GetComparisonValues(sortList[left_counter],
                                                                   sortList[right_counter]);
            if (left_Matrix >= right_Matrix)
            {
                try_shift_value(sortList, right_counter, interval);
            }
        }
        interval = static_cast<size_t>(interval / step_modificator);
    }
}


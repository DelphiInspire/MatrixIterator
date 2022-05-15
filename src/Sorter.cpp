#include "Sorter.h"

void ISorter::swap(containerCell * input_1, containerCell * input_2){
    containerCell buffer = *input_1;
    *input_1 = *input_2;
    *input_2 = buffer;
}

void ISorter::try_shift_value(containerCell* sortList, size_t position, size_t interval)
{
    for (int left_counter = position - interval, right_counter = position; left_counter >= 0; right_counter = left_counter, left_counter -= interval)
    {
        auto [left_Matrix, right_Matrix] = GetComparisonValues(sortList[left_counter].second,
                                                                            sortList[right_counter].second);
        if(right_Matrix <= left_Matrix)
        {
            swap(&sortList[right_counter], &sortList[left_counter]);
        }
    }
}

int ISorter::size_estimation(fIterator startIt, fIterator endIt) {
    size_t counter{0};
    while (startIt != endIt) {
        startIt.next();
        ++counter;
    }
    return counter;
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

int QuickSort::partition(containerCell * arrangeList, int low, int high)
{
    int position = low - 1;
    for (size_t i = low; i < high; ++i) {
        //choose the way to comparison
        auto [step_comparator, pivot] = GetComparisonValues(arrangeList[i].second,
                                                                        arrangeList[high].second);
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

void QuickSort::sort(fIterator startIt, fIterator endIt)
{
    startListPos = 0;
    stopListPos = size_estimation(startIt, endIt) - 1;
    containerCell* a = &(*startIt);
    Qsort(a, startListPos, stopListPos);
}

void QuickSort::Qsort(containerCell * sortList, int low, int high)
{
    if(low < high)
    {
        int pi = partition(sortList, low, high);
        Qsort(sortList, low, pi - 1);
        Qsort(sortList, pi + 1, high);
    }
}

void BubbleSort::sort(fIterator startIt, fIterator endIt)
{
    size_t stop_pos = size_estimation(startIt, endIt);
    containerCell* sortList = &(*startIt);
    for (size_t run_counter = 0; run_counter < stop_pos - 1; run_counter++)
    {
        for (size_t counter = 0; counter < stop_pos - run_counter - 1; counter++)
        {
            auto [l_member, r_member] = GetComparisonValues(sortList[counter].second,
                                                            sortList[counter + 1].second);
            if (l_member >= r_member)
            {
                swap(&sortList[counter], &sortList[counter + 1]);
            }
        }
    }
}

void ShellSort::sort(fIterator startIt, fIterator endIt)
{
    constexpr size_t step_modificator{2};
    size_t size = size_estimation(startIt, endIt);
    containerCell * sortList = &(*startIt);
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
            auto [left_Matrix, right_Matrix] = GetComparisonValues(sortList[left_counter].second,
                                                                   sortList[right_counter].second);
            if (left_Matrix >= right_Matrix)
            {
                try_shift_value(sortList, right_counter, interval);
            }
        }
        interval = static_cast<size_t>(interval / step_modificator);
    }
}


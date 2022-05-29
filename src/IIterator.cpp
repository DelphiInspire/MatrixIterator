#include "IIterator.h"
#include "Matrix.h"

FIterator::FIterator(Matrix *initNode):iteratorNode{initNode}{};


FIterator &FIterator::first(){return *this;};

FIterator& FIterator::next()
{
    ++iteratorNode;
    return *this;
};

bool FIterator::operator!=(const FIterator &rhsIterator) const
{
    return !(*this == rhsIterator);
}

bool FIterator::operator==(const FIterator &rhsIterator) const
{
    return (iteratorNode == rhsIterator.iteratorNode);
}

Matrix& FIterator::operator*() const
{
    return *iteratorNode;
};



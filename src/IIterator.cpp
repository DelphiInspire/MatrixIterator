#include "IIterator.h"
#include "Exception.h"

fIterator::fIterator(containerCell* initNode) : iteratorNode{initNode}{};

fIterator& fIterator::first()
{
    return *this;
};

fIterator& fIterator::next()
{
    ++iteratorNode;
    return *this;
};

containerCell& fIterator::operator*() const
{
    return *iteratorNode;
};

bool fIterator::operator!=(const fIterator& rhsIterator)  const
{
    if(iteratorNode != rhsIterator.iteratorNode)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool fIterator::operator==(const fIterator & rhsIterator) const
{
    return (!operator!=(rhsIterator));
}


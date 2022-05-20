#ifndef MATRIXITERATOS_IITERATOR_H
#define MATRIXITERATOS_IITERATOR_H

#include "Matrix.h"
class IteratorInterface
{
public:
    virtual IteratorInterface& first() = 0;
    virtual IteratorInterface& next() = 0;
    virtual ~IteratorInterface(){};
};

//class FIterator: public IteratorInterface
//{
//public:
//    FIterator(containerCell* initNode);
//    FIterator& first() override;
//    FIterator& next() override;
//    bool operator!=(const FIterator&) const;
//    bool operator==(const FIterator&) const;
//    containerCell& operator*() const;
//private:
//    containerCell* iteratorNode;
//};

#endif //MATRIXITERATOS_IITERATOR_H

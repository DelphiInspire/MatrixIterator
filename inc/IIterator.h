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

class fIterator: public IteratorInterface
{
public:
    fIterator(containerCell* initNode);
    fIterator& first() override;
    fIterator& next() override;
    bool operator!=(const fIterator&) const;
    bool operator==(const fIterator&) const;
    containerCell& operator*() const;
private:
    containerCell* iteratorNode;
};

#endif //MATRIXITERATOS_IITERATOR_H

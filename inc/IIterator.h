#ifndef MATRIXITERATOS_IITERATOR_H
#define MATRIXITERATOS_IITERATOR_H

class IteratorInterface
{
public:
    virtual IteratorInterface& first() = 0;
    virtual IteratorInterface& next() = 0;
    virtual ~IteratorInterface(){};
};

#endif //MATRIXITERATOS_IITERATOR_H

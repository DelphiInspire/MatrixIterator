#ifndef MATRIXITERATOS_IITERATOR_H
#define MATRIXITERATOS_IITERATOR_H
class Matrix;


class IteratorInterface
{
public:
    virtual IteratorInterface& first() = 0;
    virtual IteratorInterface& next() = 0;
    virtual ~IteratorInterface(){};
};


class FIterator: public IteratorInterface
{
public:
    explicit FIterator(Matrix* initNode);
    FIterator& first() override;
    FIterator& next() override;
    bool operator!=(const FIterator& rhsIterator) const;
    bool operator==(const FIterator& rhsIterator) const;
    Matrix& operator*() const;
private:
    Matrix* iteratorNode;
};

#endif //MATRIXITERATOS_IITERATOR_H

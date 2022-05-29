#ifndef FILESSORT_EXCEPTION_H
#define FILESSORT_EXCEPTION_H

class Exception
{
private:
    const char* explanation;
public:
    Exception() {};
    Exception(const char* const msg) : explanation{ msg } {};

    virtual const char* what() const
    {
        return explanation;
    }

    virtual ~Exception() {};
};

class InputVerificationException : public Exception
{
public:
    InputVerificationException() : Exception{ "Wrong char input verification" }{};
    ~InputVerificationException() {};
};

class MemoryAllocException : public Exception
{
public:
    MemoryAllocException() : Exception{ "Bad memory allocation" } {};
    ~MemoryAllocException() {};
};


class PlusMinusException : public Exception
{
public:
    PlusMinusException() :
            Exception{ "Illegal plus/minus operation, matrix dimensions must be equal" } {};
    ~PlusMinusException() {};
};

class OverflowException : public Exception
{

public:
    OverflowException() : Exception{ "Overflow error" } {};
    ~OverflowException() {};
};

class MultiplyException : public Exception
{
public:
    MultiplyException() : Exception{ "Illegal multiply operation, check right dimension of matrix"} {};
    ~MultiplyException() {};
};

class DivideException : public Exception
{
public:
    DivideException() :
            Exception{ "Illegal divide operation, check right dimension of matrix" } {};
    ~DivideException() {};
};

class SquareFormVerification: public Exception
{
public:
    SquareFormVerification(): Exception{"Square form matrix is needed"}{};
    ~SquareFormVerification(){};
};

class MemoryAllow: public Exception
{
public:
    MemoryAllow(): Exception("Error range array!"){};
    ~MemoryAllow(){};
};

class PathEmpty:public Exception
{
public:
    PathEmpty(): Exception("Path to file is empty"){};
    ~PathEmpty(){};
};

#endif //FILESSORT_EXCEPTION_H


#include "fstream"
#include <vector>
class Matrix;

class ILoader
{
public:
    virtual Matrix loadMatrix() = 0;
    virtual std::vector<Matrix>& getCache();
    virtual void setFileName(const std::string& fileName);
    virtual void clear_cache();
    virtual ~ILoader(){};
protected:
    virtual void cacheMatrix(const Matrix& cacheCandidate);
    virtual std::tuple<bool, size_t> isInCache(const Matrix& inputMatrix) const;
protected:
    std::vector<Matrix> cacheBuffer;
    std::string name;
};

class ConsoleLoader: public ILoader
{
public:
    ConsoleLoader() = default;
    Matrix loadMatrix() override;
    ~ConsoleLoader() override{};
};

class FileLoader: public ILoader
{
public:
    FileLoader() = default;
    explicit FileLoader(const std::string& fileName);
    Matrix loadMatrix() override;
    ~FileLoader() override{};
private:
    std::filesystem::path path;
};






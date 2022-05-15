#include "Matrix.h"
#include "fstream"
#include <vector>
#include<map>

class ILoader
{
public:
    virtual containerCell loadMatrix() = 0;
    virtual void clear_cache() = 0;
    virtual std::vector<containerCell> getCache() const = 0;
    virtual void setFileName(const std::string& fileName) = 0;
protected:
    virtual std::tuple<bool, size_t> isInCache(const std::vector<containerCell>&, const std::string& name);
    std::string filename;
public:
    virtual ~ILoader(){};
};

class ConsoleLoader: public ILoader
{
public:
    containerCell loadMatrix() override;
    std::vector<containerCell> getCache() const override {return cacheBuffer;};
    void setFileName(const std::string& fileName) override;
    void clear_cache() override;
private:
    std::vector<containerCell> cacheBuffer;
    std::string filename;
};

class FileLoader: public ILoader
{
public:
    FileLoader() = default;
    explicit FileLoader(std::string fileName):filename{std::move(fileName)}{};
    containerCell loadMatrix() override;
    std::vector<containerCell> getCache() const override {return cacheBuffer;};
    void clear_cache() override;
    void setFileName (const std::string& file_name) override;
private:
    std::vector<containerCell> cacheBuffer;
    std::filesystem::path path;
    std::string filename;
};






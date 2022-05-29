#include "Loader.h"
#include "Matrix.h"
#include "iostream"

std::tuple<bool, size_t> ILoader::isInCache(const Matrix& comparisonMatrix) const
{

    for (size_t searcher_id = 0, stopPos = cacheBuffer.size(); searcher_id < stopPos; ++searcher_id)
    {
        if (cacheBuffer.at(searcher_id) == comparisonMatrix)
        {
             return std::make_tuple(true, searcher_id);
        }
    }
    return std::make_tuple(false, 0);
}

void ILoader::clear_cache()
{
    if (!cacheBuffer.empty())
    {
        cacheBuffer.clear();
    }
}

std::vector<Matrix>& ILoader::getCache()
{
    return cacheBuffer;
}

void ILoader::cacheMatrix(const Matrix &cacheCandidate)
{
    auto [isPresent, where] = isInCache(cacheCandidate);
    if(!isPresent)
    {
        cacheBuffer.emplace_back(cacheCandidate);
    }
}

void ILoader::setFileName(const std::string &fileName)
{
    name = fileName;
}

Matrix ConsoleLoader::loadMatrix()
{
    std::string getter_matrix;
    std::string MatrixName;

    std::cout << "Please enter matrix:" << std::endl;
    std::cin >> getter_matrix;

    Matrix processMatrix(getter_matrix.c_str());
    cacheMatrix(processMatrix);
    return processMatrix;
}

FileLoader::FileLoader(const std::string& fileName): path{std::filesystem::absolute(fileName)}{};

Matrix FileLoader::loadMatrix()
{
    path = std::filesystem::absolute(name);
    if(path.empty())
    {
        throw PathEmpty();
    }
    std::ifstream read_thread;
    std::string getter_matrix;
    read_thread.open(path);
    if (read_thread.is_open())
    {
        read_thread >> getter_matrix;
    }
    read_thread.close();
    Matrix processMatrix(getter_matrix.c_str());

    cacheMatrix(processMatrix);
    return processMatrix;
}

#include "Loader.h"
#include "iostream"

std::tuple<bool, size_t> ILoader::isInCache(const std::vector<containerCell>& cache, const std::string& name)
{

    for (size_t searcher_id = 0; searcher_id < cache.size(); ++searcher_id)
    {
        if (cache.at(searcher_id).first == name)
        {
             return std::make_tuple(true, searcher_id);
        }
    }
    return std::make_tuple(false, 0);
}

void ConsoleLoader::setFileName(const std::string &fileName)
{
    filename = fileName;
}

containerCell ConsoleLoader::loadMatrix()
{
    std::string getter_matrix;
    std::string MatrixName;
    std::cout << "Please enter matrix:" << std::endl;
    std::cin >> getter_matrix;

    Matrix processMatrix(getter_matrix.c_str());

    auto [isPresent, where] = isInCache(cacheBuffer, filename);
    if(!isPresent)
    {
        cacheBuffer.emplace_back(std::make_pair(filename, processMatrix));
        return std::make_pair(cacheBuffer.back().first, cacheBuffer.back().second);
    }
    else
    {
        return std::make_pair(filename, std::move(processMatrix));
    }
}

void ConsoleLoader::clear_cache()
{
    if (!cacheBuffer.empty())
    {
        cacheBuffer.clear();
    }
}

containerCell FileLoader::loadMatrix()
{
    if(filename.empty())
    {
        throw PathEmpty();
    }
    auto [isPresent, where] = isInCache(cacheBuffer, filename);
    if(!isPresent) {
        std::ifstream read_thread;
        std::string getter_matrix;
        read_thread.open(path);
        if (read_thread.is_open()) {
            read_thread >> getter_matrix;
        }
        read_thread.close();
        cacheBuffer.emplace_back(std::make_pair(path, Matrix(getter_matrix.c_str())));
        return cacheBuffer.at(cacheBuffer.size() - 1);
    }
    else
    {
        return cacheBuffer.at(where);
    }
}

void FileLoader::setFileName(const std::string &file_name)
{
    filename = file_name;
    path = std::filesystem::absolute(file_name);
}

void FileLoader::clear_cache()
{

    if(!cacheBuffer.empty())
    {
        cacheBuffer.clear();
    }
}
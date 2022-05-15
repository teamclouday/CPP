#include <iostream>
#include <concepts>
#include <string>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <vector>
#include <list>
#include <algorithm>
#include <mutex>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <future>
#include <random>
#include <optional>

namespace fs = std::filesystem;

template<typename T>
std::ostream& operator<<(std::ostream& ost, const std::vector<T>& v)
{
    ost << "[ ";
    for(auto& e : v)
        ost << e << " ";
    ost << "]";
    return ost;
}

template<typename T, typename K>
std::ostream& operator<<(std::ostream& ost, const std::unordered_map<T, K>& v)
{
    ost << "[\n";
    for(auto& e : v)
        ost << e.first << " => " << e.second << "\n";
    ost << "]";
    return ost;
}

struct Entry
{
    std::string name;
    int number;
};

bool operator<(const Entry& x, const Entry& y)
{
    return x.name < y.name;
}

std::ostream& operator<<(std::ostream& ost, const Entry& e)
{
    ost << "(" << e.name << ", " << e.number << ")";
    return ost;
}

template<typename... T>
void print(T&&... args)
{
    (std::cout << ... << args);
}

template<typename... T>
void println(T&&... args)
{
    (std::cout << ... << args) << std::endl;
}

template<typename Target=std::string, typename Source=std::string>
void convert(Source src)
{
    Target res;
    std::stringstream interpret;
    if(!(interpret << src) || !(interpret >> res) || !(interpret >> std::ws).eof())
        throw std::runtime_error("convert failed");
    return res;
}

void printdir(const fs::path& p)
{
    try
    {
        if(fs::is_directory(p))
        {
            println(p);
            for(const auto& x : fs::directory_iterator{p})
                println(x.path());
        }
    }
    catch(const fs::filesystem_error& err)
    {
        std::cerr << err.what() << std::endl;
    }
}

std::optional<fs::path> get_dir_first(const fs::path& p)
{
    try
    {
        if(fs::is_directory(p))
        {
            for(const auto& x : fs::directory_iterator{p})
            {
                if(fs::is_regular_file(x.path()))
                    return x.path();
            }
        }
    }
    catch(const fs::filesystem_error& err)
    {
        std::cerr << err.what() << std::endl;
    }
    return {};
}


int main()
{
    /* std::ios_base::sync_with_stdio(false); */

    std::string b("testb");
    println(b);

    std::string a{"test"};
    println(a);

    std::vector<int> c{1,2,3,4,5,6,7};
    println(c);

    return 0;
}

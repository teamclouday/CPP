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


// int main()
// {
//     std::ios_base::sync_with_stdio(false);

//     std::default_random_engine re;
//     std::uniform_int_distribution dist{0, 1000};
//     auto roll = [&](){return dist(re);};

//     std::vector<int> numbers(10);
//     auto sz = numbers.size();
//     for(size_t i = 0; i < numbers.size(); i++)
//         numbers[i] = roll();
    
//     println("Vector:\n", numbers);
//     std::sort(std::execution::par, numbers.begin(), numbers.end());
//     println("Sorted:\n", numbers);
//     println("Sum: ", std::accumulate(numbers.begin(), numbers.end(), 0));
//     auto vec = &numbers[0];
//     auto f1 = std::async(std::accumulate<int*, int>, vec, vec + sz/4, 0);
//     auto f2 = std::async(std::accumulate<int*, int>, vec + sz/4, vec + sz/2, 0);
//     auto f3 = std::async(std::accumulate<int*, int>, vec + sz/2, vec + sz*3/4, 0);
//     auto f4 = std::async(std::accumulate<int*, int>, vec + sz*3/4, vec + sz, 0);
//     println("Async Sum: ", f1.get() + f2.get() + f3.get() + f4.get());

//     println("Current Path: ", fs::absolute(fs::path(".")));
//     println("Current Folder:");
//     printdir(fs::path("."));
//     auto file = get_dir_first(fs::path(".") / fs::path("bin"));
//     if(file.has_value())
//         println("Size of excutable (KB): ", fs::file_size(file.value()) / 1024);

//     return 0;
// }

std::mutex mu;
int val = 0;

void funEven()
{
    while(val <= 100)
    {
        mu.lock();
        if(val % 2 == 0)
            std::cout << val++ << ",";
        mu.unlock();
    }
}

void funOdd()
{
    while(val <= 100)
    {
        mu.lock();
        if(val % 2)
            std::cout << val++ << ",";
        mu.unlock();
    }
}

int main()
{
    std::thread t2(funEven);
    std::thread t1(funOdd);
    
    t1.join();
    t2.join();

    std::cout << '\n';
    return 0;
}

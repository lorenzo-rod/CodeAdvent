#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    int sum = 0;
    bool is_mul_valid = true;
    std::ifstream file("Day3Input.txt");

    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string input = oss.str();

    std::regex pattern(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
    std::regex pattern_mul(R"(mul\((\d{1,3}),(\d{1,3})\))");

    std::smatch match;
    std::vector<std::pair<int, int>> matches_mul;
    std::smatch match_mul;

    auto search_start = input.cbegin();

    std::vector<std::string> results;

    while (std::regex_search(search_start, input.cend(), match, pattern))
    {
        results.push_back(match[0]);
        search_start = match.suffix().first;
    }

    auto res_it = results.begin();
    while (res_it != results.end())
    {
        std::string text = (*res_it);
        if (text == "do()")
        {
            is_mul_valid = true;
            res_it++;
        }
        else if (text == "don't()")
        {
            is_mul_valid = false;
            res_it++;
        }
        else
        {
            if (is_mul_valid)
            {
                auto search_start_mul = text.cbegin();
                while (std::regex_search(search_start_mul, text.cend(), match_mul, pattern_mul))
                {
                    int x = std::stoi(match_mul[1]);
                    int y = std::stoi(match_mul[2]);
                    sum += x * y;
                    break;
                }
            }
            res_it++;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
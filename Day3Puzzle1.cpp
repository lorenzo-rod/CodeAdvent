#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    int sum = 0;
    std::ifstream file("Day3Input.txt");

    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    std::string input = oss.str();

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    std::vector<std::pair<int, int>> matches;
    std::smatch match;
    auto search_start = input.cbegin();

    while (std::regex_search(search_start, input.cend(), match, pattern))
    {
        int x = std::stoi(match[1]);
        int y = std::stoi(match[2]);
        matches.emplace_back(x, y);

        search_start = match.suffix().first;
    }

    for (const auto &m : matches)
    {
        sum += m.first * m.second;
    }

    std::cout << sum << std::endl;

    return 0;
}
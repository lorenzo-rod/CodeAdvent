#include <iostream>
#include <vector>

std::vector<std::vector<int>> getDifferencesVector(std::vector<std::vector<int>> reports);

std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<int>> &vec);

bool isRowSafeWithoutDampener(std::vector<int> row);

bool isRowSafeWithDampener(std::vector<int> row);

int getSignChangeIndex(std::vector<int> row);

int main()
{
    std::vector<std::vector<int>> test_input = {{7, 6, 4, 2, 1},
                                                {1, 2, 7, 8, 9},
                                                {9, 7, 6, 2, 1},
                                                {1, 3, 2, 4, 5},
                                                {8, 6, 4, 4, 1},
                                                {1, 3, 6, 7, 9}};

    std::vector<std::vector<int>> differences_vector;
    int num_safe = 0;

    differences_vector = getDifferencesVector(test_input);

    for (const auto &row : differences_vector)
    {
        if (isRowSafeWithoutDampener(row))
        {
            num_safe++;
        }
        else if (isRowSafeWithDampener(row))
        {
            num_safe++;
        }
    }

    std::cout << num_safe << std::endl;
}

std::vector<std::vector<int>> getDifferencesVector(std::vector<std::vector<int>> reports)
{
    std::vector<std::vector<int>> differences_vector{};
    std::vector<int> differences;
    for (const auto &report : reports)
    {
        differences = {};
        for (auto it = report.begin(); it != report.end() - 1; it++)
        {
            differences.push_back(*it - *(it + 1));
        }
        differences_vector.push_back(differences);
    }

    return differences_vector;
}

bool isRowSafeWithoutDampener(std::vector<int> row)
{
    int abs_level;
    for (auto it = row.begin(); it != row.end(); it++)
    {
        abs_level = std::abs(*it);
        if (abs_level > 3)
        {
            return false;
        }
        else if (abs_level < 1)
        {
            return false;
        }
        else if (it != row.end() - 1)
        {
            if ((*it * *(it + 1)) <= 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool isRowSafeWithDampener(std::vector<int> row)
{
    int sign_change_index = getSignChangeIndex(row);
    if (sign_change_index == -1)
    {
        return false;
    }
    else
    {
        int new_element = row[sign_change_index] + row[sign_change_index + 1];
        row.erase(row.begin() + sign_change_index);
        row.erase(row.begin() + sign_change_index + 1);
        row.insert(row.begin() + sign_change_index, new_element);
        return isRowSafeWithoutDampener(row);
    }
}

int getSignChangeIndex(std::vector<int> row)
{
    for (int i = 0; i < row.size() - 1; i++)
    {
        if (row[i] * row[i + 1] <= 0)
        {
            return i;
        }
    }
    return -1;
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<int>> &vec)
{
    for (const auto &inner_vec : vec)
    {
        for (const auto &elem : inner_vec)
        {
            os << elem << " ";
        }
        os << std::endl;
    }
    return os;
}

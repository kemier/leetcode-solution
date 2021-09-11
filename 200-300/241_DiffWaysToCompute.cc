#include <vector>
#include <iostream>
#include <string>
#include <cctype>

class Solution //以运算符为界，两边分治
{
public:
    std::vector<int> diffWaysToCompute(std::string input)
    {
        int number = 0;
        if (tryIfNumber(input, &number))
        {
            return {number};
        }
        std::vector<int> result;
        for (auto i = 0; i < input.size(); ++i)
        {
            auto c = input[i];
            if (isOperator(c))
            {
                auto leftResult = diffWaysToCompute(input.substr(0, i));
                auto rightResult = diffWaysToCompute(input.substr(i + 1));
                for (const auto &left : leftResult)
                {
                    for (const auto &right : rightResult)
                    {
                        if (c == '+')
                        {
                            result.emplace_back(left + right);
                        }
                        else if (c == '-')
                        {
                            result.emplace_back(left - right);
                        }
                        else if (c == '*')
                        {
                            result.emplace_back(left * right);
                        }
                    }
                }
            }
        }
        return result;
    }

private:
    bool tryIfNumber(const std::string &str, int *number) const
    {
        *number = 0;
        for (const auto &c : str)
        {
            if (std::isdigit(c))
            {
                *number = *number * 10 + (c - '0');
            }
            else
            {
                *number = 0;
                return false;
            }
        }
        return true;
    }

    bool isOperator(const char &c) const
    {
        return c == '+' || c == '-' || c == '*';
    }
};

int main()
{
    Solution sln;

    std::vector<std::string> inputs{"2-1-1", "2*3-4*5"};

    auto print_v = [](const std::vector<int> &computes) {
        std::cout << "[";
        for (const auto &c : computes)
        {
            std::cout << c << ", ";
        }
        std::cout << "]" << std::endl;
    };

    for (auto &input : inputs)
    {
        print_v(sln.diffWaysToCompute(input));
    }
}
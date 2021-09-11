#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class Solution
{

public:
    vector<vector<string>> answer;
    string digits;

    long target;

    void recurse(int index, long previousOperand, long currentOperand, long value, vector<string> &ops)
    {
        string nums = digits;

        // Done processing all the digits in num
        if (index == nums.length())
        {

            // If the final value == target expected AND
            // no operand is left unprocessed
            if (value == target && currentOperand == 0)
            {
                answer.push_back(vector<string>(ops.begin(), ops.end()));
            }
            return;
        }

        // Extending the current operand by one digit
        currentOperand = currentOperand * 10 + atoi(&(nums.at(index)));
        string current_val_rep = to_string(currentOperand);
        int length = nums.length();

        // To avoid cases where we have 1 + 05 or 1 * 05 since 05 won't be a
        // valid operand. Hence this check
        if (currentOperand > 0)
        {

            // NO OP recursion
            recurse(index + 1, previousOperand, currentOperand, value, ops);
        }

        // ADDITION
        ops.push_back("+");
        ops.push_back(current_val_rep);
        recurse(index + 1, currentOperand, 0, value + currentOperand, ops);
        ops.erase(ops.end() - 1);
        ops.erase(ops.end() - 1);

        if (ops.size() > 0)
        {

            // SUBTRACTION
            ops.push_back("-");
            ops.push_back(current_val_rep);
            recurse(index + 1, -currentOperand, 0, value - currentOperand, ops);
            ops.erase(ops.end() - 1);
            ops.erase(ops.end() - 1);

            // MULTIPLICATION
            ops.push_back("*");
            ops.push_back(current_val_rep);
            recurse(
                index + 1,
                currentOperand * previousOperand,
                0,
                value - previousOperand + (currentOperand * previousOperand),
                ops);
            ops.erase(ops.end() - 1);
            ops.erase(ops.end() - 1);
        }
    }

    vector<vector<string>> addOperators(string num, int target)
    {

        if (num.length() == 0)
        {
            vector<vector<string>> tmp;
            return tmp;
        }

        target = target;
        digits = num;
        vector<string> ops;
        recurse(0, 0, 0, 0, ops);
        return answer;
    }
};

int main()
{
    Solution solution;
    string nums = "123";
    int target = 6;
    vector<vector<string>> ans = solution.addOperators(nums, target);
    vector<vector<string>>::iterator iter;
    vector<string>::iterator iter2;
    for (iter = ans.begin(); iter != ans.end(); ++iter)
    {
        for (iter2 = iter->begin(); iter2 != iter->end(); ++iter2)
        {
            cout << *iter2 << " ";
        }
        cout << endl;
    }
    return 0;
}
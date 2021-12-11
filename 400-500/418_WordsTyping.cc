#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    int wordsTyping(vector<string> &sentence, int rows, int cols)
    {
        string str;
        for (auto val : sentence)
            str += val + " ";
        int len = str.size(), start = 0;
        for (int i = 0; i < rows; i++)
        {
            start += cols;
            if (str[start % len] == ' ')
            {
                start++;
                continue;
            }
            while (start > 0 && str[(start - 1) % len] != ' ')
                start--;
        }
        return start / len;
    }
};
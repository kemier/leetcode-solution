#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution //DFS+回溯
{
public:
    vector<string> generatePalindromes(string s)
    {
        vector<string> ret;
        string line(s);
        unordered_map<char, int> hash;
        for (auto val : s)
        {
            ++hash[val];
        }
        int odd_num = 0;
        char odd_char = ' ';
        for (auto it = hash.begin(); it != hash.end(); ++it)
        {
            if (it->second % 2 != 0)
            {
                ++odd_num;
                odd_char = it->first;
            }
        }
        if (odd_num > 1)
        {
            return {};
        }
        else if (odd_num == 1)
        {
            line[s.length() / 2] = odd_char;
            --hash[odd_char];
        }
        generatePalindromes(ret, line, 0, hash);
        return ret;
    }

private:
    void generatePalindromes(vector<string> &ret, string &line, int index,
                             unordered_map<char, int> &hash)
    {
        int length = line.length();
        if (index == length / 2)
        {
            ret.push_back(line);
            return;
        }
        for (auto it = hash.begin(); it != hash.end(); ++it)
        {
            if (it->second > 0)
            {
                line[index] = line[length - 1 - index] = it->first;
                it->second -= 2;
                generatePalindromes(ret, line, index + 1, hash);
                it->second += 2;
            }
        }
    }
};
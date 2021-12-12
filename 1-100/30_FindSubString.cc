#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution //哈希+滑动窗口
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        vector<int> res;
        int i, j;
        int word_size = words[0].size();
        int string_size = s.size(), longs = words.size() * word_size;
        string temp;
        unordered_map<string, int> count;
        auto it = count.end();
        for (i = words.size() - 1; i >= 0; i--)
        {
            if (it == count.find(words[i]))
                count.insert({words[i], 1});
            else
                count[words[i]]++;
            words.pop_back();
        } //创建哈希表
        for (i = 0; i <= string_size - longs; i++, temp.clear())
        {
            temp.assign(s, i, word_size);
            if (count.find(temp) == it)
                continue;                               //减小内存消耗
            unordered_map<string, int> temp_map(count); //复制哈希表
            for (j = 0; j <= longs; j += word_size, temp.clear())
            {
                temp.assign(s, i + j, word_size);
                if (temp_map.end() == temp_map.find(temp) || !temp_map[temp])
                    break;
                else
                    temp_map[temp]--;
            }
            if (j == longs)
                res.push_back(i);
        }
        return res;
    }
};

#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    string rearrangeString(string str, int k) {
        if(k==0) return str;
        int len = str.size();
        string result;
        map<char, int> hash;
        for(auto ch: str) hash[ch]++;
        priority_queue<pair<int, char>> que;
        for(auto val: hash) que.push(make_pair(val.second, val.first));
        while(!que.empty())
        {
            vector<pair<int, int>> vec;
            int cnt = min(k, len);
            for(int i =0; i < cnt; i++, len--)
            {
                if(que.empty()) return "";
                auto val = que.top();
                que.pop();
                result += val.second;
                if(--val.first>0) vec.push_back(val);
            }
            for(auto val: vec) que.push(val);
        }
        return result;
    }
};
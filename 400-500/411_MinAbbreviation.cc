#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        int len = target.size();
        if(len == 0) {
            return "";
        }
        vector<string> dic;
        for(string s : dictionary) {    // only the word that has the same length is possible to cause conflict
            if(s.size() == len) {
                dic.push_back(s);
            }
        }
        int len_d = dic.size();
        if(len_d == 0) {
            return to_string(len);
        }
        string res = target;
        dfs("", 0, target, 0, dic, res, len);
        return res;
    }
private:
    void dfs(string cur, int cur_len, string& target, int pos, vector<string>&dic, string &res, int& minlen) {
        if(pos >= (int)target.size()) {
            if(cur_len < minlen) {         // if cur_len >= minLen, do nothing
                bool f = true;             // indicates whether valid
                for(string s:dic) {
                    if(check(s,cur)) {
                        f = false;
                        break;
                    }
                }
                if(f) {
                    res = cur;
                    minlen = cur_len;
                }
            }
            return;
        }
        if(minlen == cur_len) {
            return;  
        }
        if(cur.empty() || !isdigit(cur.back())) {                               // try to replace some characters
            for(int i = target.size() - 1; i >= pos; --i) {
                 string add = to_string(i - pos + 1);
                 dfs(cur + add, cur_len + 1, target, i + 1, dic, res, minlen);
            }
        }
        dfs(cur + target[pos], cur_len + 1, target, pos + 1, dic, res, minlen); // do not replace anything
    }
    
    bool check(string s1, string s2) {
        int len1 = s1.size();
        int len2 = s2.size();
        int l = 0 , r = 0;
        while(l < len1 && r < len2) {
            if(isdigit(s2[r])) {
                int dis = 0;
                while(r < len2 && isdigit(s2[r])) {
                    dis = dis * 10 + s2[r++] - '0';
                }
                l += dis;
            }
            else if (s2[r] == '0') {
                return false;
            }
            else {
                if(s1[l] == s2[r]) {
                    l++;
                    r++;
                }
                else{
                    return false;
                }
            }
         }
         if(l >= len1 && r >= len2) {
            return true;
         }
         return false;
    }
};
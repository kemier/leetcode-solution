#include <string>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
  public:
   int lengthOfLongestSubstringKDistinct(string s, int k) {
    int n = s.length();
    if (n < k+1) return n;
 
    int left = 0;
    int right = 0;
    //K-V：K是对应字符，V是最后一次出现的位置。
    map<char, int> hashmap= map<char, int>();
 
    int max_len = 0;
 
    while (right < n) {
        //符合要求就继续向右扩
        if (hashmap.size() < k+1){
            hashmap.insert(make_pair(s.at(right), right++));
        }
        if (hashmap.size() == k+1) {
            int index=hashmap.begin()->second;
            hashmap.erase(hashmap.begin());
            left = index + 1;
        }
      max_len = max(max_len, right - left);
    }
    return max_len;
  }
};
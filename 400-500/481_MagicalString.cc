#include <bits/stdc++.h>

using namespace  std;

class Solution {
public:
    int magicalString(int n) {
        if (n <= 3) return 1;                  
        // 构造两个长度在增长的字符串, 使用两个指针分别指向这两个字符串末尾, i指向较短的字符串末尾
        string str = "122"; // 接下来在字符串str末尾加数字来扩展它
        int i = 2; // 一开始较短和较长字符串都置为"122", i指向较短的字符串末尾
        while (str.size() < n)
        {
            char lastCh = str.back();
            if (str[i] == '1') // 新插入到末尾的字符(digit)需出现1次
            {
                if (lastCh == '1') str.append("2");
                else str.append("1");                
            }
            else {             // 新插入到末尾的字符(digit)需出现2次
                if (lastCh == '1') str.append("22");
                else str.append("11");
            }            
            i++;
        }        
        int count1 = count(str.begin(), str.begin() + n, '1'); /* 使用str.begin() + n, 而不是str.end()的原因是: 此时str.size()可能 > n */
        return count1;
    }
};


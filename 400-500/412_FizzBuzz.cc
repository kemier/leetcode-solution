#include <vector>
#include <string>

using namespace std;
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> a;
        for(int i=1;i<=n;i++)
        {
            if(i%3==0&&i%5==0)
                a.push_back("FizzBuzz"); //.push_back() 末尾添加字符串
            else if(i%3==0)
                a.push_back("Fizz");
            else if(i%5==0)
                a.push_back("Buzz");
            else
                a.push_back(to_string(i)); //to_string() 将整型转化为字符串
        }
        return a;
    }
};


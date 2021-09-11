#include <vector>

using namespace std;
class Solution
{
public:
    bool isPrime(int x)
    {
        for (int i = 2; i * i <= x; ++i)
        {
            if (x % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    int countPrimes(int n)
    {
        int ans = 0;
        for (int i = 2; i < n; ++i)
        {
            ans += isPrime(i);
        }
        return ans;
    }

    int countPrimes2(int n) //厄拉多塞筛法
    {
        int count = 0;
        //初始默认所有数为质数
        vector<bool> signs(n, true);
        for (int i = 2; i < n; i++)
        {
            if (signs[i])
            {
                count++;
                for (int j = i + i; j < n; j += i)
                {
                    //排除不是质数的数
                    signs[j] = false;
                }
            }
        }
        return count;
    }
    int countPrimes3(int n) //优化厄拉多塞筛法中signs使用位图bitmap表示
    {
        int count = 0;
        //一个 int 变量不知道占多少字节（但请注意，这里采用了常量）
        const int size = sizeof(int) * 8;
        vector<int> signs(n / size + 1, 0);
        for (int i = 2; i < n; i++)
        {
            //将元素和需确定得数字经行按位或运算，如果值改变，说明不存在该数字（未登记该数字），则其为质数。
            //在C++中，其提供了 bitset 来操作位，在此便不做介绍了。如果用了，可读性肯定会更好。
            //(当某个数为 2 的 n 次方时（n为自然数），其 & (n - 1) 所得值将等价于取余运算所得值)
            //*如果 x = 2^n ，则 x & (n - 1) == x % n
            //下面判断可以写成
            //if ((signs[i / size] & (1 << (i % 32))) == 0)
            if ((signs[i / size] & (1 << (i & (size - 1)))) == 0)
            {
                count++;
                for (int j = i + i; j < n; j += i)
                {
                    //登记该数字
                    signs[j / size] |= 1 << (j & (size - 1));
                }
            }
        }
        return count;
    }
};

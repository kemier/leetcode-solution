class Solution //递归
{
public:
    int addDigits(int num)
    {
        while (num >= 10)
        {
            int next = 0;
            while (num != 0)
            {
                next = next + num % 10;
                num /= 10;
            }
            num = next;
        }
        return num;
    }
};

class Solution //数学方法
{
public:
    int addDigits(int num)
    {
        return (num - 1) % 9 + 1;
    }
};

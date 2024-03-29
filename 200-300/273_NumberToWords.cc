#include <string>
using namespace std;

class Solution
{
public:
    string numberToWords(int num)
    {
        if (num == 0)
        {
            return "Zero";
        }
        else
        {
            return helper(num).substr(1);
        }
    }

    string helper(int num)
    {
        string result = "";
        if (num / 1000000000 > 0)
        {
            result += helper(num / 1000000000) + getWord(0) + getWord(1000000000) + helper(num % 1000000000);
        }
        else if (num / 1000000 > 0)
        {
            result += helper(num / 1000000) + getWord(0) + getWord(1000000) + helper(num % 1000000);
        }
        else if (num / 1000 > 0)
        {
            result += helper(num / 1000) + getWord(0) + getWord(1000) + helper(num % 1000);
        }
        else if (num / 100 > 0)
        {
            result += getWord(0) + getWord(num / 100) + getWord(0) + getWord(100) + helper(num % 100);
        }
        else if (num >= 20)
        {
            result += getWord(0) + getWord((num / 10) * 10) + helper(num % 10);
        }
        else if (num > 0)
        {
            result += getWord(0) + getWord(num);
        }
        else
        {
            return "";
        }
        return result;
    }

    string getWord(int num)
    {
        switch (num)
        {
        case 0:
            return " ";
        case 1:
            return "One";
        case 2:
            return "Two";
        case 3:
            return "Three";
        case 4:
            return "Four";
        case 5:
            return "Five";
        case 6:
            return "Six";
        case 7:
            return "Seven";
        case 8:
            return "Eight";
        case 9:
            return "Nine";
        case 10:
            return "Ten";
        case 11:
            return "Eleven";
        case 12:
            return "Twelve";
        case 13:
            return "Thirteen";
        case 14:
            return "Fourteen";
        case 15:
            return "Fifteen";
        case 16:
            return "Sixteen";
        case 17:
            return "Seventeen";
        case 18:
            return "Eighteen";
        case 19:
            return "Nineteen";
        case 20:
            return "Twenty";
        case 30:
            return "Thirty";
        case 40:
            return "Forty";
        case 50:
            return "Fifty";
        case 60:
            return "Sixty";
        case 70:
            return "Seventy";
        case 80:
            return "Eighty";
        case 90:
            return "Ninety";
        case 100:
            return "Hundred";
        case 1000:
            return "Thousand";
        case 1000000:
            return "Million";
        case 1000000000:
            return "Billion";
        default:
            return " ";
        }
    }
};
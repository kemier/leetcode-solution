#include <cmath>

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n==0) return 1;
        // if(n==1) return 10;
        int dp[n+1];
        dp[0]=0;dp[1]=0; /// dp is the repeat of count i;
        for(int i = 2 ; i <= n ;i++ ){
            dp[i] = dp[i-1]*10+(9*pow(10,i-2) - dp[i-1])*(i-1);
            // (9*pow(10,i-2) - dp[i-1]) 指的是无重复的个数
        }
        int sum = 0 ; 
        for(int i = 0 ; i < n+1;i++){
            sum+=dp[i];
        }
        return pow(10,n)-sum;
    }
};


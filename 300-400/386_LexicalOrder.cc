#include <vector>

using namespace std;


class Solution {
public:
    vector<int>ans;
    int n;
    vector<int> lexicalOrder(int n) {
        this->n=n;
        for(int i=1;i<=9;i++){
            if(i>n)break;
            ans.push_back(i);
            dfs(i);
        }
        return ans;
    }
    void dfs(int head){
        head*=10;
        for(int i=0;i<=9;i++){
            if(head+i>n)return;
            ans.push_back(head+i);
            dfs(head+i);
        }
    }
};


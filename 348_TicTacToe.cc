#include <vector>

using namespace std;

class TicTacToe {
public:
    /** Initialize your data structure here. */
    TicTacToe(int n):mp(vector<vector<int>>(n, vector<int>(n, 0))), N(n) {
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        mp[row][col] = player;
        int i;
        for(i=0; i<N; i++) if(mp[row][i]!=player) break;
        if(i==N) return player;
        for(i=0; i<N; i++) if(mp[i][col]!=player) break;
        if(i==N) return player;
        if(row==col)
            for(i=0; i<N; i++) if(mp[i][i]!=player) break;
        if(i==N) return player;
        if(row+col==N-1)
            for(i=0; i<N; i++) if(mp[N-i-1][i]!=player) break;
        if(i==N) return player;
        return false;
    }
private:
    vector<vector<int>> mp;
    int N;
};
 
/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */
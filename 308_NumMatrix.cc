#include <vector>
#include <iostream>
using namespace std;

/*
  Given a 2D matrix, find the sum of the elements inside the rectangle defined
  by its upper left corner(row1, col1) and lower right corner(row2, col2).
  For exmaple:
  Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]]
  sumRegion(2, 1, 4, 3) -> 8
  update(3, 2, 2)
  sumRegion(2, 1, 4, 3) -> 10
  Note:
    The matrix is only modifiable by the update function
    You may assume the number of calls to update and sumRegion function is distributed evenly.
    You may assume that row1 <= row2 and col1 <= col2.
*/
class NumMatrix
{
private:
    vector<vector<int>> newMatrix;

public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        for (int i = 0; i < matrix.size(); ++i)
        {
            newMatrix.push_back(vector<int>(matrix[0].size() + 1, 0));
        }
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                newMatrix[i][j + 1] = newMatrix[i][j] + matrix[i][j];
            }
        }
    }
    void update(int row, int col, int val)
    {
        int diff = val - (newMatrix[row][col + 1] - newMatrix[row][col]);
        for (int i = col + 1; i < newMatrix[row].size(); ++i)
        {
            newMatrix[row][i] += diff;
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int sum = 0;
        for (int i = row1; i <= row2; ++i)
        {
            sum += newMatrix[i][col2 + 1] - newMatrix[i][col1];
        }
        return sum;
    }
};

int main(void)
{
    vector<vector<int>> matrix_test{
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}};
    NumMatrix matrix(matrix_test);
    cout << matrix.sumRegion(2, 1, 4, 3) << endl;
    matrix.update(3, 2, 2);
    cout << matrix.sumRegion(2, 1, 4, 3) << endl;
}
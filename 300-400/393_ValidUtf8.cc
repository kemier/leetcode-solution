#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
   bool validUtf8(vector<int> data) {

    // Number of bytes in the current UTF-8 character
    int numberOfBytesToProcess = 0;

    // For each integer in the data array.
    for (int i = 0; i < data.size(); i++) {

      // Get the binary representation. We only need the least significant 8 bits
      // for any given number.
      string binRep = dec2bin(data[i]);
      binRep =binRep.length() >= 8? binRep.substr(0,8):string(8-binRep.length(),'0') + binRep;
      // If this is the case then we are to start processing a new UTF-8 character.
      if (numberOfBytesToProcess == 0) {

        // Get the number of 1s in the beginning of the string.
        for (int j = 0; j < binRep.length(); j++) {
          if (binRep.at(j) == '0') {
            break;
          }

          numberOfBytesToProcess += 1;
        }

        // 1 byte characters
        if (numberOfBytesToProcess == 0) {
          continue;
        }

        // Invalid scenarios according to the rules of the problem.
        if (numberOfBytesToProcess > 4 || numberOfBytesToProcess == 1) {
          return false;
        }

      } else {

        // Else, we are processing integers which represent bytes which are a part of
        // a UTF-8 character. So, they must adhere to the pattern `10xxxxxx`.
        if (!(binRep.at(0) == '1' && binRep.at(1) == '0')) {
          return false;
        }
      }

      // We reduce the number of bytes to process by 1 after each integer.
      numberOfBytesToProcess -= 1;
    }

    // This is for the case where we might not have the complete data for
    // a particular UTF-8 character.
    return numberOfBytesToProcess == 0;
  }


    string dec2bin(int decVal)
    {
        string value = "";
        bool isMinus = false;
        if (decVal < 0)
        {
            isMinus = true;
        }
        while (decVal > 0)
        {
            if (decVal % 2)
                value = '1' + value;
            else
                value = '0' + value;
            decVal = decVal / 2;
        }
        if (isMinus)
            value = '-' + value;
        return value;
    }

};









class Solution2 {//位操作
public:
    bool validUtf8(vector<int>& data) {
        int c = 0;
        for(const int& num : data)
        {
            if(c == 0)
            {
                if((num >> 5) == 0b110) c = 1;
                else if((num >> 4) == 0b1110) c = 2;
                else if((num >> 3) == 0b11110) c = 3;
                else if((num >> 7)) return false;
            }
            else
            {
                if((num >> 6) != 0b10) return false;
                --c;
            }
        }
        return c == 0;
    }
};



int main(){
    vector<int> data{197, 130, 1};
    Solution solution;
    bool res=solution.validUtf8(data);
    cout<<boolalpha<<res<<endl;
}

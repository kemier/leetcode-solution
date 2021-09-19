class Solution{

public:
    int lastRemaining(int n) {
        int count = n;
        int first = 1;
        int diff = 1;
        bool isFromLeft = true;
        while (count > 1) {
            if (isFromLeft) {
                first += diff;
            } else {
                if ((count & 1) == 1) {
                    first += diff;
                }
            }

            count >>= 1;
            diff <<= 1;
            isFromLeft = !isFromLeft;
        }

        return first;
    }
};
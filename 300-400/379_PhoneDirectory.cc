class PhoneDirectory {
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers){
        n = maxNumbers;
        available = new int[n];
        isAvailable = new int[n]; 
        for(int i = 0; i < n; i++)
            available[i] = i, isAvailable[i] = 1;
    }
    
    ~PhoneDirectory()
    {
        delete [] available;
        delete [] isAvailable;
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if(n <= 0) return -1;
        int ans = available[--n];
        isAvailable[ans] = 0;
        return ans;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return isAvailable[number];
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if(isAvailable[number]) return;
        available[n++] = number;
        isAvailable[number] = 1;
    }
private:
    int *available, *isAvailable;
    int n;
};
 
/**
 * Your PhoneDirectory object will be instantiated and called as such:
 * PhoneDirectory obj = new PhoneDirectory(maxNumbers);
 * int param_1 = obj.get();
 * bool param_2 = obj.check(number);
 * obj.release(number);
 */
#include <unordered_map>
#include <string>

using namespace std;

class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        if(hash.count(message) == 0 || timestamp -hash[message] >= 10)
        {
            hash[message] = timestamp;
            return true;
        }
        return false;
    }
private:
    unordered_map<string, int> hash;
};
 
/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */
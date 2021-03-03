#include <vector>
#include <string>

using namespace std;

class Codec
{
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string> &strs)
    {
        string result;
        for (auto str : strs)
            result += to_string((int)str.size()) + "$" + str;
        return result;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s)
    {
        vector<string> result;
        int len = s.size(), pos = 0;
        while (pos < len)
        {
            int k = s.find('$', pos), num = stoi(s.substr(pos, k - pos));
            result.push_back(s.substr(k + 1, num));
            pos = k + num + 1;
        }
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
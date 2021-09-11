#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class ValidWordAbbr
{
public:
    ValidWordAbbr(vector<string> &dictionary)
    {
        for (auto str : dictionary)
        {
            if (str.size() <= 2)
                continue;
            int num = str.size() - 2;
            string abb = str[0] + to_string(num) + str[str.size() - 1];
            hash[abb].push_back(str);
        }
    }

    bool isUnique(string word)
    {
        int num = word.size() - 2;
        string abb = word[0] + to_string(num) + word[word.size() - 1];
        if (hash[abb].size() > 1)
            return false;
        if (hash[abb].size() == 1)
            return word == hash[abb][0];
        return true;
    }

private:
    unordered_map<string, vector<string>> hash;
};

// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");
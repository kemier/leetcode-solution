#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;
class Trie
{
private:
    bool isEnd;
    Trie *next[26];

public:
    Trie()
    {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }

    void insert(string word)
    {
        Trie *node = this;
        for (char c : word)
        {
            if (node->next[c - 'a'] == NULL)
            {
                node->next[c - 'a'] = new Trie();
            }
            node = node->next[c - 'a'];
        }
        node->isEnd = true;
    }

    bool search(string word)
    {
        Trie *node = this;
        for (char c : word)
        {
            node = node->next[c - 'a'];
            if (node == NULL)
            {
                return false;
            }
        }
        return node->isEnd;
    }

    bool startsWith(string prefix)
    {
        Trie *node = this;
        for (char c : prefix)
        {
            node = node->next[c - 'a'];
            if (node == NULL)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Trie *obj = new Trie();
    obj->insert("hello");
    obj->insert("heximal");
    cout << boolalpha << obj->search("hello") << endl;
    cout << boolalpha << obj->startsWith("hell") << endl;
    cout << boolalpha << obj->startsWith("wor") << endl;
    return 0;
}
#include <string>
#include <memory>
using namespace std;

class WordDictionary //Trie树实现此功能
{
public:
    /** Initialize your data structure here. */
    WordDictionary() : root_(std::make_shared<TrieNode>())
    {
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        auto res = root_;
        for (auto c : word)
        {
            if (res->children_[c - 'a'] == nullptr)
            {
                res->children_[c - 'a'] = std::make_shared<TrieNode>();
            }
            res = res->children_[c - 'a'];
        }
        res->isWord_ = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word)
    {
        return find(root_, word, 0);
    }

private:
    struct TrieNode
    {
        TrieNode() : isWord_(false), children_(26, nullptr)
        {
        }
        bool isWord_;
        vector<std::shared_ptr<TrieNode>> children_;
    };

    bool find(std::shared_ptr<TrieNode> res, string &prefix, int idx)
    {
        if (res != nullptr)
        {
            if (prefix.size() == idx)
            {
                return res->isWord_;
            }
            if (prefix[idx] == '.')
            {
                for (auto child : res->children_)
                {
                    if (find(child, prefix, idx + 1))
                    {
                        return true;
                    }
                }
            }
            else
            {
                return find(res->children_[prefix[idx] - 'a'], prefix, idx + 1);
            }
        }
        return false;
    }

    std::shared_ptr<TrieNode> root_;
};
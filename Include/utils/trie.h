#ifndef TRIE_H
#define TRIE_H
#include<vector>
#include<string>
struct TrieNode{
    TrieNode* children[26];
    bool isended;
    TrieNode(){
        isended = false;
        for(int i=0;i<26;i++) children[i] = nullptr;
    }
};
class Trie{
private:
    TrieNode* root;
    void collectwords(TrieNode* node,std::string prefix,std::vector<std::string>& result) const;
public:
    Trie();
    void insert(const std::string& word);
    std::vector<std::string> searchbyprefix(const std::string& prefix) const;
};
#endif
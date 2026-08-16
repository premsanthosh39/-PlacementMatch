#include "utils/trie.h"
#include<algorithm>
#include<cctype>

Trie::Trie(){ 
    root = new TrieNode();
}

std::string toLowerTrie(std::string s){
    std::transform(s.begin(),s.end(),s.begin(),::tolower);
    return s;
}

void Trie::insert(const std::string& word){
    std::string w = toLowerTrie(word);
    TrieNode* current = root;
    for(char ch:w){
        if(ch < 'a' || ch > 'z') continue;
        int index = ch - 'a';
        if(current->children[index] == nullptr){
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isended = true;
}


void Trie::collectwords(TrieNode* node, std::string prefix, std::vector<std::string>& results) const {
    if (node->isended) results.push_back(prefix);
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            collectwords(node->children[i], prefix + char('a' + i), results);
        }
    }
}

std::vector<std::string> Trie::searchbyprefix(const std::string& prefix) const {
    std::string p = toLowerTrie(prefix);
    TrieNode* current = root;
    for (char ch : p) {
        if (ch < 'a' || ch > 'z') continue;
        int index = ch - 'a';
        if (current->children[index] == nullptr) return {};
        current = current->children[index];
    }
    std::vector<std::string> results;
    collectwords(current, p, results);
    return results;
}
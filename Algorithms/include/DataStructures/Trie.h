#pragma once
#include<vector>
#include<string>
namespace algo
{
    // add Trie for any kind of symbol
    // currently only lowercase letters are supported
    class Trie
    {/*
    public:
        enum class TrieType
        {
            LowerLetters = 1,
            UpperLetters = 2,
            Digits = 4,
            Other = 8
        };*/
    private:
        
        struct Node
        {
            std::vector<Node*> alphabet;
            bool word_end;
            Node();
        };
        static int index_of_char(char ch);
        void add_word(Node*& curr_node, const std::string& word, int index);
        bool find_word(Node* const& curr_node, const std::string& word, int index) const;

        //TrieType m_type;
        static const int AlphabetSize = 26;
        Node* m_root;

    public:
        
        Trie();
        //Trie(TrieType type = TrieType::LowerLetters);
        void add_word(const std::string& word);
        bool find_word(const std::string& word) const;
    };
}
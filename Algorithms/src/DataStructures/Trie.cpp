#include<DataStructures/Trie.h>
namespace algo
{
    Trie::Node::Node()
        : alphabet(AlphabetSize, nullptr)
        , word_end(false)
    {
    }
    /*Trie::Trie(TrieType type)
        : m_type(type)
    {
    }*/
    int Trie::index_of_char(char ch)
    {
        return ch - 'a';
    }
    void Trie::add_word(Node*& curr_node, 
                        const std::string& word, 
                        int index)
    {
        if (curr_node == nullptr)
        {
            curr_node = new Node();
        }
        if (word.size() == index)
        {
            curr_node->word_end = true;
            return;
        }
        Node*& next = curr_node->alphabet[index_of_char(word[index])];
        return add_word(next, word, index + 1);
    }
    bool Trie::find_word(Node* const& curr_node, 
                        const std::string& word, 
                        int index) const
    {
        if (curr_node == nullptr)
        {
            return false;
        }
        if (index == word.size())
        {
            return curr_node->word_end;
        }
        Node* next = curr_node->alphabet[index_of_char(word[index])];
        return find_word(next, word, index + 1);
    }
    Trie::Trie()
        : m_root(nullptr)
    {
    }
    void Trie::add_word(const std::string& word)
    {
        return add_word(m_root, word, 0);
    }
    bool Trie::find_word(const std::string& word) const
    {
        return find_word(m_root, word, 0);
    }
}
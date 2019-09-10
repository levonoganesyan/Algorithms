#pragma once

namespace algo
{
    template<typename T>
    class RBTree
    {
        struct Node
        {
            Node* left;
            Node* right;
            Node* father;
            T value;
            bool red;
            Node(T value, bool red, Node* left = nullptr,
                                    Node* right = nullptr,
                                    Node* father = nullptr)
                : value(value)
                , red(red)
                , left(left)
                , right(right)
                , father(father)
            {

            }
        };
        Node* m_root;
        
        void fix_insertion(Node* root);
    public:
        RBTree();
        void insert(const T& value);
        void erase(const T& value);
    };
}


namespace algo 
{
    template<typename T>
    inline void RBTree<T>::fix_insertion(Node* temp)
    {
        if (temp == m_root)
        {
            temp->red = false;
            return;
        }
        while (temp->parent->red)
        {
            if (temp->parent->parent->left == temp->parent)
            {
                if (temp->parent->parent->right)
                {
                    if (temp->parent->parent->right->red)
                    {
                        temp->parent->red = false;
                        temp->parent->parent->right->red = false;
                        temp->parent->parent->red = true;
                        temp = temp->parent->parent;
                    }
                }
                else // if (!temp->parent->parent->right)
                {
                    // TODO
                }
            }
        }
    }
    template<typename T>
    RBTree<T>::RBTree()
        : m_root(nullptr)
    {

    }

    template<typename T>
    inline void RBTree<T>::insert(const T& value)
    {
        Node* temp(value, true);
        if (root == nullptr)
        {
            root = temp;
        }
        else
        {
            Node* p = m_root;
            Node* q = nullptr;
            while (p != nullptr)
            {
                q = p;
                if (p->value > temp.value)
                {
                    p = p->left;
                }
                else
                {
                    p = p->right;
                }
            }
            temp.parent = q;
            if (q.value > temp.value)
            {
                q->left = temp;
            }
            else
            {
                q->right = temp;
            }
            fix_insertion(temp);
        }
    }

    template<typename T>
    inline void RBTree<T>::erase(const T& value)
    {
    }

}
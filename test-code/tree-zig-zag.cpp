

#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    Node* left;
    Node* right;

    int data;
};

class StackBase
{
public:
    StackBase()
        {

        }

    virtual void push(Node* root) = 0;

    Node* pop()
    {
        Node* n = stackInternal.back();
        stackInternal.pop_back();

        return n;
    }

    bool empty()
        {
            return stackInternal.empty();
        }

protected:
    vector<Node*> stackInternal;
};

class StackL : public StackBase
{
public:
    StackL()
        {

        }

    void push(Node* root)
        {
            if (root != nullptr)
            {
                stackInternal.push_back(root->left);
                stackInternal.push_back(root->right);
            }
        }
};

class StackR : public StackBase
{
public:
    StackR()
        {

        }

    void push(Node* root)
        {
            if (root != nullptr)
            {
                stackInternal.push_back(root->right);
                stackInternal.push_back(root->left);
            }
        }
};

void work(StackBase* stPop, StackBase* stPush)
{
    while (!stPop->empty())
    {
        Node* n = stPop->pop();
        stPush->push(n);
    }
}

Node* buildTree()
{
    return new Node();
}

int main()
{
    Node* root = buildTree();
    StackBase* stL = new StackL();
    StackBase* stR = new StackR();
    bool lr = false;

    while (!stL->empty() && !stR->empty())
    {
        if (lr)
        {
            work(stL, stR);
        }
        else
        {
            work(stR, stL);
        }
    }

    return 0;
}

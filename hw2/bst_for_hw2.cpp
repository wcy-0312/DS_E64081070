#include <iostream>
#include <queue>
using namespace std;

class BST;
class TreeNode
{
private:
    TreeNode *leftChild;
    TreeNode *rightChild;
    TreeNode *parent;
    int key;

public:
    TreeNode() : leftChild(0), rightChild(0), parent(0), key(0){}; //key : value stored in node
    TreeNode(int a) : leftChild(0), rightChild(0), parent(0), key(a){};

    int GetKey() { return key; }
    friend class BST;  // share private member with BST class
};

class BST
{
private:
    TreeNode *root;  // root of bst 
    TreeNode *LeftMost(TreeNode *current);  // return leftmost node in bst 
    TreeNode *Successor(TreeNode *current);  // return next node of bst inorder (inorder successor)

public:
    BST() : root(0){};

    TreeNode *Search(int key);  // search bst from root, return node contain key, not found return null
    TreeNode *Search_Subtree(TreeNode *current, int KEY); // search bst from current node, return node contain key, not found return null
    void Insert(int key); // insert new node into bst
    void Delete(int KEY);  // delete node from bst
    void InorderPrint();  // print bst inorder
    void PreorderPrint(TreeNode *current);  // print bst preorder
    void PostorderPrint(TreeNode *current);  // print bst postorder
    void LevelorderPrint();  // print bst levelorder
    bool check_contain_index(int n, int index);  // check if the number contain index
    void Delete_Broccoli(int index);  
    TreeNode *path_to_sword(int sword);  // print the path to sword from root
    void path_to_meaty(TreeNode *current, int meaty);  // print the path to meaty from current node
    void print_shortest_path(int sword, int meaty);  

    TreeNode *GetRoot()
    {
        return root;
    }
};

TreeNode *BST::Search(int KEY)
{
    TreeNode *current = root;

    while (current != NULL && KEY != current->key)
    {
        if (KEY < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return current;
}

TreeNode *BST::Search_Subtree(TreeNode *current, int KEY)
{
    while (current != NULL && KEY != current->key)
    {
        if (KEY < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return current;
}

void BST::Insert(int key)
{
    TreeNode *p = root, *pp = 0; // pp: parent of pointer
    TreeNode *newNode = new TreeNode(key);

    while (p)
    {
        pp = p;
        if (newNode->key < pp->key)
            p = p->leftChild;
        else
            p = p->rightChild;
    }

    newNode->parent = pp;

    if (root)
    {
        if (newNode->key < pp->key)
            pp->leftChild = newNode;
        else
            pp->rightChild = newNode;
    }
    else
        this->root = newNode;
}

TreeNode *BST::LeftMost(TreeNode *current)
{
    while (current->leftChild)
        current = current->leftChild;

    return current;
}

TreeNode *BST::Successor(TreeNode *current)
{
    if (current->rightChild)
        return LeftMost(current->rightChild);

    TreeNode *successor = current->parent;
    while (successor != NULL && current == successor->rightChild)
    {
        current = successor;
        successor = successor->parent;
    }
    return successor;
}

void BST::PreorderPrint(TreeNode *current)
{
    if (current)
    {
        cout << current->key << " ";
        PreorderPrint(current->leftChild);
        PreorderPrint(current->rightChild);
    }
}

void BST::InorderPrint()
{
    TreeNode *current = new TreeNode;
    current = LeftMost(root);
    while (current)
    {
        cout << current->key << " ";
        current = Successor(current);
    }
}

void BST::PostorderPrint(TreeNode *current)
{
    if (current)
    {
        PostorderPrint(current->leftChild);
        PostorderPrint(current->rightChild);
        cout << current->key << " ";
    }
}

void BST::LevelorderPrint() // use queue
{
    queue<TreeNode *> q;
    q.push(this->root);

    while (!q.empty())
    {
        TreeNode *current = q.front();
        q.pop();
        cout << current->key << " ";

        if (current->leftChild)
            q.push(current->leftChild);
        if (current->rightChild)
            q.push(current->rightChild);
    }
}

void BST::Delete(int KEY)
{
    TreeNode *delete_node = Search(KEY);
    if (delete_node == NULL)
    {
        cout << "data not found" << endl;
        return;
    }

    TreeNode *p = 0, *cp = 0;
    if (delete_node->leftChild == NULL || delete_node->rightChild == NULL)
    {
        p = delete_node;
    }
    else
    {
        p = Successor(delete_node);
    }

    if (p->leftChild)
        cp = p->leftChild;
    else
        cp = p->rightChild;

    if (cp)
        cp->parent = p->parent;

    if (p->parent == NULL)
        this->root = cp;
    else if (p == p->parent->leftChild)
        p->parent->leftChild = cp;
    else
        p->parent->rightChild = cp;

    if (p != delete_node)
        delete_node->key = p->key;

    delete p;
    p = 0;
}

void BST::Delete_Broccoli(int index)
{
    TreeNode *current = new TreeNode;
    current = LeftMost(root);
    while (current)
    {
        if (check_contain_index(current->key, index))  // check if current key contains index
        {
            cout << "Number " << current->key << " is deleted." << endl;
            Delete(current->key);  // delete
        }
        current = Successor(current);
    }
}

bool BST::check_contain_index(int n, int index)
{
    if (n < 10)
        return n == index;
    if (n % 10 == index)
        return true;
    else
        return check_contain_index(n / 10, index);
}

void BST::print_shortest_path(int sword, int meaty)
{
    TreeNode *current = path_to_sword(sword);
    while (Search_Subtree(current, meaty) == NULL)  // check if subtree contains meaty
    {
        cout << current->key << "->";
        current = current->parent;  // move to parent
    }
    path_to_meaty(current, meaty); 
}

TreeNode *BST::path_to_sword(int sword)
{
    TreeNode *current = root;
    while (current != NULL && sword != current->key)
    {
        cout << current->key << "->";
        if (sword < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return current;
}

void BST::path_to_meaty(TreeNode *current, int meaty)
{
    while (current != NULL && meaty != current->key)
    {
        cout << current->key << "->";
        if (meaty < current->key)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    cout << current->key << endl;
}
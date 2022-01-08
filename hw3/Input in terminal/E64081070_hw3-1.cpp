#include<iostream>
#include<string>
#include <unordered_map>
using namespace std;

struct Node
{
    int data;
    Node *leftChild, *rightChild;
};

Node* newNode(int n){
    Node* node = new Node;
    node->data = n;
    node->leftChild = node->rightChild = NULL;
    return node;
}



Node* buildTree(int inorder[], int p_order[], int indexStart, int indexEnd, string order, int* pIndex, unordered_map<int, int>& mp){

    if(indexStart > indexEnd) return NULL;
    
    int curr = p_order[*pIndex];
    
    Node* node = newNode(curr);
    if(order == "preorder-inorder") (*pIndex)++;
    if(order == "postorder-inorder") (*pIndex)--;
    

    if(indexStart == indexEnd) return node; // this node has no children

    int inorderIndex = mp[curr];

    if(order == "preorder-inorder"){
        node->leftChild = buildTree(inorder, p_order, indexStart, inorderIndex-1, order, pIndex, mp);
        node->rightChild = buildTree(inorder, p_order, inorderIndex+1, indexEnd, order, pIndex, mp);
    }
    if(order == "postorder-inorder"){
        node->rightChild = buildTree(inorder, p_order, inorderIndex+1, indexEnd, order, pIndex, mp);
        node->leftChild = buildTree(inorder, p_order, indexStart, inorderIndex-1, order, pIndex, mp);
    }
    
    return node;
}

Node* buildTreeWrap(int inorder[], int preorder[], string order, int len){
    unordered_map<int ,int> mp;
    int index;
    if(order == "preorder-inorder") index = 0;
    else if(order == "postorder-inorder") index = len-1;
    for(int i=0; i<len; i++) mp[inorder[i]] = i;
    return buildTree(inorder, preorder, 0, len-1, order, &index, mp);
}

void printPreorder(Node* node){
    if(!node) return;
    cout << node->data << " ";
    printPreorder(node->leftChild);
    printPreorder(node->rightChild);
}

void printPostorder(Node* node){
    if(!node) return;
    printPostorder(node->leftChild);
    printPostorder(node->rightChild);
    cout << node->data << " ";
}

int main(){
    int m; // number of test dataset
    int len; // number of nodes in binary tree
    static string order[1000]; // preorder-inorder or postorder-inorder
    int p_order[1000]={0}, inorder[1000]={0};
    Node* root[1000];
    cin >> m;
    for(int i=0; i<m; i++){
        cin >> order[i];
        cin >> len;
        for(int j=0; j<len; j++) cin >> p_order[j];
        for(int j=0; j<len; j++) cin >> inorder[j];

        root[i] = buildTreeWrap(inorder, p_order, order[i], len);
        
    }
    cout << endl;
    for(int i=0; i<m; i++){
        if(order[i]=="preorder-inorder") printPostorder(root[i]);
        else if(order[i]=="postorder-inorder") printPreorder(root[i]);
        cout << endl;
    }
    

    

    return 0;
}
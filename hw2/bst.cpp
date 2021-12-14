#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "bst_for_hw2.cpp"

void BST_operation(int n);
BST BST_insert(BST T);
BST BST_delete(BST T);
void BST_search(BST T);
void BST_print(BST T);

void find_meaty();

int main()
{
    int n;
    while (1)
    {
        // choose part
        cout << "(1)Binary searching Tree." << endl;
        cout << "(2)Finding Meaty." << endl;
        cout << "(0)Escape and face to music next year." << endl;
        cin >> n;
        if (n == 1)
        { 
            BST_operation(n);  // into part1
        }
        else if (n == 2)
        {
            find_meaty();  // into part2
        }
        else // n==0
        {
            break;
        }
    }

    return 0;
}

void BST_operation(int n)
{
    BST T;  // create bst
    char c;
    while (1)
    {
        // choose operation
        cout << "(I)nsert a number." << endl;
        cout << "(D)elete a number." << endl;
        cout << "(S)earch a number." << endl;
        cout << "(P)rint 4 kinds of orders." << endl;
        cout << "(R)eturn" << endl;
        cin >> c;
        switch (c)
        {
        case 'i':  // insert element into bst
            T = BST_insert(T); 
            break;
        case 'd':  // delete element from bst
            T = BST_delete(T);
            break;
        case 's':  // search bst from bst
            BST_search(T);
            break;
        case 'p':  // print bst in 4 kinds of order
            BST_print(T);
            break;
        case 'r':  // back to choose part
            return;
        default:
            break;
        }
    }
}

BST BST_insert(BST T)
{
    int n;
    cout << "Enter numbers: ";
    while (1)
    {
        cin >> n;
        if (T.Search(n) == NULL) // No same key
        {
            if (n != -1)  // stop when read -1
            {
                T.Insert(n);  // insert to bst
                cout << "Number " << n << " is inserted." << endl;
            }
            else
                break;
        }
        else
            cout << "Error. Number " << n << " exists." << endl;
    }

    return T;
}

BST BST_delete(BST T)
{
    int n;
    cout << "Enter numbers to deleted : ";
    while (1)
    {
        cin >> n;
        if (T.Search(n)) // if key exists
        {
            T.Delete(n); // delete from bst tree
            cout << "Number " << n << " is deleted." << endl;
        }
        else
        {
            if (n != -1)  // stop when read -1
                cout << "Number " << n << " is not exist." << endl;
            else
                break;
        }
    }

    return T;
}

void BST_search(BST T)
{
    int n;
    cout << "Enter elements to searching : ";
    while (1)
    {
        cin >> n;
        if (T.Search(n)) // if key exists
            cout << "Bingo! " << n << " is found." << endl;
        else
        {
            if (n != -1)  // stop when read -1
                cout << "SORRY. " << n << " is not found." << endl;
            else
                break;
        }
    }
}

void BST_print(BST T)
{
    TreeNode *root = T.GetRoot(); // get the root of bst
    cout << "The tree in prefix order : ";
    T.PreorderPrint(root);  // prefix order
    cout << endl;
    cout << "The tree in infix order : ";
    T.InorderPrint();  // infix order
    cout << endl;
    cout << "The tree in post order : ";
    T.PostorderPrint(root);  // post order
    cout << endl;
    cout << "The tree in level order : ";  
    T.LevelorderPrint();  // level order
    cout << endl;
}

void find_meaty()
{
    BST T;  // create bst
    int n, sword, meaty, broccoli_index;
    string filename, str;
    cout << "Please input the map file: ";
    cin >> filename;

    ifstream ifs(filename, ifstream::in);  // create filestream
    while (ifs >> str)  // readfile word by word
    {
        n = stoi(str);  // change type from string to int
        T.Insert(n);    // insert element into bst
    }
    cout << "Load file success.\n"
         << endl;
    cout << "Please input the sword location: ";
    cin >> sword;
    cout << "Please input the Meaty's location: ";
    cin >> meaty;
    cout << "Please input the broccoli traps' index (0~9): ";
    cin >> broccoli_index;
    cout << endl;
    T.Delete_Broccoli(broccoli_index);  // delete trap
    cout << endl;
    cout << "Capoo successfully found his favorite meaty<3.\n" << endl;
    cout << "Shortest path to find the meaty :" << endl;
    T.print_shortest_path(sword, meaty);  // print shortest path to find meaty

    return;
}

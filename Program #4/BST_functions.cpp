/*
 * Kobe Davis
 * Prof. Fant
 * CS163
 * Assignment #4
 *
 * This file (BST_functions.cpp) will hold the definitions of the functions found in 
 * the header file (BST_header.h).
 */

#include "BST_header.h"

using namespace std;

//constructor for tree class
tree::tree()
{
    root = NULL;//making sure the root of the tree isn't garabage
    if(!load())//loading data from external file into BST data structure
    {
        cout << "Load failed." << endl;//error message
    }
}

//destructor for tree class
tree::~tree()
{
    remove_all(root);//recursive function which removes all nodes in tree
}

//load function that takes data in the external file CS_term.txt and inserts it into the
//BST using the insert function, this function is called in the constructor so that the data
//is loaded upon creation of the tree
int tree::load()
{
    int return_value = 0;
    ifstream bst_in; bst_in.open("CS_term.txt");//opening the file and giving it to a variable
    char title[100]; char definition[10000];//temporary variables to store the data
    info from_file;//temporary info object to store data

    bst_in.get(title, 100, ':'); bst_in.ignore(100, ':');//initial check for data in file so eof triggers
    while(!bst_in.eof())//check for empty file
    {
        bst_in.get(definition, 10000, '\n'); bst_in.ignore(100, '\n');//grabbing data pertaining to definition of cs term

        if(!from_file.create(title, definition))//create function is used to give the collected data to the temporary info object
        {
            return 0;//if creation fails
        }
        if(!insert(root, from_file))//using insert function to take the info object just created and place its data inside the BST
        {
            return 0;//if insert fails
        }

        bst_in.get(title, 100, ':'); bst_in.ignore(100, ':');//grabbing the name of the cs term
        return_value = 1;//insert succeeded
    }
    return return_value;
}

//this is the wrapper function for insert
int tree::insert(info to_add)
{
    return insert(root, to_add);//calling recursive function and handing it the root of the BST and the data to add
}

//insert function below, this function will travel as far down as it can (in the appropriate direct of course) and create the data at a leaf.
int tree::insert(node *& root, info to_add)
{
    if(!root)//insert has recursively reach a dead end and will now create a new node and place the given data in this location
    {
        root = new node;//creating a new node to place data in
        root->cs_term.copy(to_add);//copying the data handed in through the argument into this node
        root->left = NULL;//setting both children to NULL because the insert was at a leaf
        root->right = NULL;
        return 1;//insert was a success
    }
    if(to_add.compare(root->cs_term) == 1)//calling the compare function to determine if the insert function should traverse left or right
    {
        return insert(root->left, to_add);//compare function determined traversal left was appropriate because the value of the cs term handed from the argument was less than the current nodes data
    }
    return insert(root->right, to_add);//compare function determined traversal right was approproate because of greater data value
}

//wrapper function for the recursive remove function
int tree::remove(info match)
{
    if(!root)//check to see if the tree even exists
    {
        return 0;//tree didn't exist
    }
    return remove(root, match);//call to recursive function, hands in the root to the BST and an info object to find the data set for removal
}

//recursive function for removal, remove function will remove specified data (if it exists) and do so with 4 cases.
//the first case being that the node set for removal does not have any children, the second being that the node set for
//removal only has a left child, the third case being the opposite of the second case, and the fourth case being that
//the node set for removal has both children. in the fourth case, a separate function (inorder_successor) is called to find 
//a node that can and will replace the node set for removal.
int tree::remove(node *& root, info match)
{
    if(!root)
    {
        return 0;
    }  
    if(match.compare(root->cs_term) == 1)//compare function determines that the term being searched for is of a lower value than the one currently at
    {
        return remove(root->left, match);//recursive call to remove function which places us in the current node's left child
    }
    else if(match.compare(root->cs_term) == 2)//compare function determines that the term  being searched for is of a greater value than the one currently at
    {
        return remove(root->right, match);//recursive call to remove function which places us in the current node's right child
    }
    else//else describes the case where the compare function returns a 0, meaning that the term being searched for and the current node's data matches
    {
        if(!root->left && !root->right)//first case: leaf
        {
            delete root;
            root = NULL;
        }
        else if(!root->left && root->right)//second case: no left child, only right child
        {
            node * temp = root->right;//connecting up subtree before removal occurs
            delete root;
            root = temp;
        }
        else if(root->left && !root->right)//third case: no right child, only left child
        {
            node * temp = root->left;//connecting up subtree before removal occurs
            delete root;
            root = temp;
        }
        else if(root->left && root->right)//fourth case: both children exist
        {
            node * temp = inorder_successor(root->right);//calling a function which will return a pointer to the node that will replace the node soon-to-be deleted (I.O.S.)
            temp->left = root->left;//connecting up subtrees before removal occurs
            temp->right = root->right;
            delete root;
            root = temp;
        }
        return 1;//removal was successful
    }
    return 0;//removal failed
}

//this function is recursive, it is called in the remove function to find the inorder successor of the node set to be removed
//this function will recurse until the I.O.S. is found
node * tree::inorder_successor(node *& root)
{
    if(!root->left)//I.O.S. is found
    {
        node * temp = root;
        root = root->right;
        return temp;//return a pointer to the I.O.S.
    }
    return inorder_successor(root->left);//recursive call to this function, continues until the I.O.S. is found
}

//wrapper function for the recursive retrieve function
int tree::retrieve(info &match)
{
    if(!root)//does the tree even exist?
    {
        return 0;//tree doesn't exist
    }
    return retrieve(root, match);//call to recursive retrieve function
}

//retrieve function takes a user specified string and attempts to find a match for it in the BST
//it does so by comparing the value of the argument handed data to the value of the data it is currently at
int tree::retrieve(node *& root, info &match)
{
    if(!root)//have we traversed to far?
    {
        return 0;
    }
    if(match.compare(root->cs_term) == 1)//user given data is less than the data in the node we are currently at
    {
        return retrieve(root->left, match);//recursive call but starting at this node's left child
    }
    else if(match.compare(root->cs_term) == 2)//user given data is greater than the data in the node we are currently at
    {
        return retrieve(root->right, match);//recursive call but starting at this node's right child
    }
    else//match is found by the compare function
    {
        match.clear();//clearing the info object (match) so that nothing wierd happens if data is already in this
        match.copy(root->cs_term);//copies data from found data into the info object handed by argument
        return 1;
    }
}

//wrapper function for the recursive get_height function
int tree::get_height()
{
    return get_height(root);//call to the recursive get_height function
}

//recursive get height function, uses the max function cstdlib which determines which path the function is returning from is larger
int tree::get_height(node * root)
{
    if(!root)//does tree exist?
    {
        return 0;
    }
    return max(get_height(root->left), get_height(root->right)) + 1;//recursive call which uses max function after each return
}

//wrapper function for recursive is_efficient function
bool tree::is_efficient()
{
    if(!root)//does tree exist
    {
        return false;
    }
    int efficient = 0;//temp int variable to hold the changed value inside recursive is_efficient function
    is_efficient(root, efficient);// call to recursive function is_efficient
    if(efficient)//if efficient temp var is 1 then that means the tree isn't efficient
    {
        return false;//not efficient
    }
    return true;//efficient
}

//this function will determine if the current BST is balanced or not
int tree::is_efficient(node * root, int &efficient)
{
    if(!root)//does tree exist
    {
        return 0;
    }
    int left_height = is_efficient(root->left, efficient);//go left first and find the height of that path
    int right_height = is_efficient(root->right, efficient);//go right second and find the height of that path
    if(abs(left_height - right_height) > 1)//if difference between two heights is greater than 1
    {
        efficient = 1;//tree is imbalanced
    }
    return max(left_height, right_height) + 1;//pick the greatest of the two heights found in any one particular subtree
}

//wrapper function to call the recursive display_all function
int tree::display_all()
{
    if(!root)//does tree exist
    {
        return 0;
    }
    return display_all(root);//call to recursive display function
}

//display_all function will recursively travel the BST and display the data in alphabetical order
int tree::display_all(node * root)
{
    if(!root)//does tree exist
    {
        return 0;
    }
    display_all(root->left);//go left first, recursive call to the function
    root->cs_term.display(96, 123); cout << endl;//display leaving the left side
    display_all(root->right);//go right after left, recursive call to function
    return 1;
}

//wrapper function for the display_range function, receives and upper and lower bound for what data should be displayed, and hands it to the recursive function
int tree::display_range(char lower, char upper)
{
    if(!root)//does tree exist?
    {
        return 0;
    }
    return display_range(root, lower, upper);//call to the recursive function
}

//recursive function display_range will only display data (in alpgabetical order) that is between the bounds handed in through the argument
int tree::display_range(node * root, char lower, char upper)
{
    if(!root)//does tree exist
    {
        return 0;
    }
    display_range(root->left, lower, upper);//this is all the same as the initial display function except that certain data is not displayed because it does not meet the criteria given
    root->cs_term.display(lower, upper); cout << endl;
    display_range(root->right, lower, upper);
    return 1;
}

//this function will recursively remove all nodes in the BST. 
//it is placed inside the destructor.
int tree::remove_all(node *& root)
{
    if(!root)//does tree exist?
    {
        return 0;
    }

    remove_all(root->left);//go all the way left first
    remove_all(root->right);//take right immediately after returning from left

    delete root;//when the recursive function has gone as far as it can, it will start deleting nodes on return
    root = NULL;
    return 1;
}

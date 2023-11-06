/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

// Write your code below this line

SymNode::SymNode()
{
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;

}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;

};
int Height(SymNode* node){
    if (node == NULL){
        return -1;
    }
    else if (node->left == NULL && node->right == NULL){
        return 0;
    }
    else{
        return 1 + std::max(Height(node->left),Height(node->right));
    }
    return -1;
}

SymNode *SymNode::LeftLeftRotation()
{


    SymNode *parent = par;
    SymNode *current = this;
    //SymNode *child = left;

    parent->left = current->right;
    if (current->right != NULL)
    {
        current->right->par = parent;
    }

    current->right = parent;
    current->par = parent->par;
    parent->par = current;

    // Updating the heights, make sure to check for NULLs
    if (current->right != NULL)
    {
        current->right->height = Height(current->right);
    }
    current->height = Height(current);
    if (parent->left != NULL)
    {
        parent->left->height = Height(parent->left);
    }
    parent->height = Height(parent);

    return current;
};

SymNode *SymNode::RightRightRotation()
{

    SymNode *parent = par;
    SymNode *current = this;
    //SymNode *child = right;

    parent->right = current->left;
    if (current->left != NULL)
    {
        current->left->par = parent;
    }

    current->left = parent;
    current->par = parent->par;
    parent->par = current;

    // Updating the heights, make sure to check for NULLs
    if (current->left != NULL)
    {
        current->left->height = Height(current->left);
    }
    current->height = Height(current);
    if (parent->right != NULL)
    {
        parent->right->height = Height(parent->right);
    }
    parent->height = Height(parent);

    return current;
};

SymNode *SymNode::LeftRightRotation()
{
    SymNode *parent = par;
    SymNode *current = this;
    SymNode *child = right;

    current->right = child->left;
    if (child->left != NULL)
    {
        child->left->par = current;
    }

    child->left = current;
    child->par = parent->par;
    parent->left = child->right;
    if (child->right != NULL)
    {
        child->right->par = parent;
    }
    child->right = parent;
    current->par = child;
    parent->par = child;

    // Updating the heights, make sure to check for NULLs
    if (child->left != NULL)
    {
        child->left->height = Height(child->left);
    }
    if (child->right != NULL)
    {
        child->right->height = Height(child->right);
    }
    current->height = Height(current);
    parent->height = Height(parent);
    child->height = Height(child);

    return child;
}

SymNode *SymNode::RightLeftRotation()
{
    SymNode *parent = par;
    SymNode *current = this;
    SymNode *child = left;

    current->left = child->right;
    if (child->right != NULL)
    {
        child->right->par = current;
    }

    child->right = current;
    child->par = parent->par;
    parent->right = child->left;
    if (child->left != NULL)
    {
        child->left->par = parent;
    }
    child->left = parent;
    current->par = child;
    parent->par = child;

    // Updating the heights, make sure to check for NULLs
    if (child->left != NULL)
    {
        child->left->height = Height(child->left);
    }
    if (child->right != NULL)
    {
        child->right->height = Height(child->right);
    }
    current->height = Height(current);
    parent->height = Height(parent);
    child->height = Height(child);

    return child;
}

SymNode::~SymNode()
{
    if (left != NULL && right != NULL && par!=NULL)
    {
        delete left;
        delete right;
    }
    left = NULL;
    right = NULL;
    // delete this;
}

// void printIO(SymNode *root)
// {
//     if (root == nullptr)
//         return;

//     // First recur on left subtree
//     cout << "(";
//     printIO(root->left);

//     // Now deal with the root
//     cout <<root->key;

//     // Then recur on right subtree
//     printIO(root->right);
//    cout<<")";

// }



// int main()
// {
//     SymNode *s1 = new SymNode("a");
//     SymNode *s2 = new SymNode("b");
//     SymNode *s3 = new SymNode("c");
//     SymNode *s4 = new SymNode("d");
//     SymNode *s5 = new SymNode("e");
//     s1->right = s2;
//     s2->par = s1;
//     s2->right = s3;
//     s3->par = s2;
//     s3->right = s4;
//     s4->par = s3;
//     s4->right = s5;
//     s5->par = s4;
//     printIO(s1);
//     cout<<endl;
//     cout<<s2->RightRightRotation()->right->key<<endl;
//     printIO(s2);
//     cout<<endl;
// }
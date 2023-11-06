/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"


// Write your code below this line

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;

    // root->par = NULL;
};

// void printIO(SymNode *root)
// {
//     if (root == NULL)
//         return;

//     // First recur on left subtree
//     cout << "(";
//     printIO(root->left);

//     // Now deal with the root
//     cout << root->key;

//     // Then recur on right subtree
//     printIO(root->right);
//     cout << ")";
// }

int Height1(SymNode *node)
{
    if (node == NULL)
    {
        return -1;
    }
    else if (node->left == NULL && node->right == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(Height1(node->left), Height1(node->right));
    }
    return -1;
}
int BalanceFactor(SymNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        return Height1(node->left) - Height1(node->right);
    }
    return 0;
};

void SymbolTable::insert(string k)
{

    if (root == NULL)
    {
        root = new SymNode(k);
        size++;
        root->height = 0;
    }
    else if (root->key > k)
    {
        if (root->left == NULL)
        {
            root->left = new SymNode(k);
            root->left->par = root;
            size++;
            root->height = Height1(root);
            root->left->height = 0;
        }
        else
        {
            SymbolTable *temp = new SymbolTable();
            temp->root = root->left;
            temp->insert(k);
            size++;
            root->left = temp->root;
            if (temp->root != NULL)
            {
                temp->root->par = root;
            }
            root->height = Height1(root);
            root->left->height = Height1(root->left);
        }
    }
    else if (root->key < k)
    {
        if (root->right == NULL)
        {
            root->right = new SymNode(k);
            root->right->par = root;
            size++;
            root->height = Height1(root);
            root->right->height = 0;
        }
        else
        {
            SymbolTable *temp = new SymbolTable();
            temp->root = root->right;
            temp->insert(k);
            size++;
            root->right = temp->root;
            if (temp->root != NULL)
            {
                temp->root->par = root;
            }
            root->height = Height1(root);
            root->right->height = Height1(root->right);
        }
    }

    if (BalanceFactor(root) < -1)
    {

        if (k > root->right->key)
        {
            if (!root->par)
            {
                root = root->right->RightRightRotation();
            }
            else if (root->par->left == root)
            {

                SymNode *r = root->par;
                SymNode *res = root->right->RightRightRotation();
                r->left = res;
                res->par = r;
                root = res;
            }
            else if (root->par->right == root)
            {
                SymNode *r = root->par;
                SymNode *res = root->right->RightRightRotation();
                r->right = res;
                res->par = r;
                root = res;
            }
        }
        else if (k < root->right->key)
        {
            if (!root->par)
            {
                SymNode *res = root->right->RightLeftRotation();
                root = res;
            }
            else if (root->par->left == root)
            {
                SymNode *r = root->par;
                SymNode *res = root->right->RightLeftRotation();
                r->left = res;
                res->par = r;
                root = res;
            }
            else if (root->par->right == root)
            {

                SymNode *r = root->par;
                SymNode *res = root->right->RightLeftRotation();
                r->right = res;
                res->par = r;
                root = res;
            }
        }
    }
    else if (BalanceFactor(root) > 1)
    {

        if (k < root->left->key)
        {
            if (!root->par)
            {
                SymNode *res = root->left->LeftLeftRotation();
                root = res;
            }
            else if (root->par->left == root)
            {

                SymNode *r = root->par;
                SymNode *res = root->left->LeftLeftRotation();
                r->left = res;
                res->par = r;
                root = res;
            }
            else if (root->par->right == root)
            {

                SymNode *r = root->par;
                SymNode *res = root->left->LeftLeftRotation();
                r->right = res;
                res->par = r;
                root = res;
            }
        }
        else if (k > root->left->key)
        {
            if (!root->par)
            {
                root = root->left->LeftRightRotation();
            }
            else if (root->par->left == root)
            {

                SymNode *r = root->par;
                SymNode *res = root->left->LeftRightRotation();
                r->left = res;
                res->par = r;
                root = res;
            }
            else if (root->par->right == root)
            {

                SymNode *r = root->par;
                SymNode *res = root->left->LeftRightRotation();
                r->right = res;
                res->par = r;
                root = res;
            }
        }
    }
}
SymNode *successor(SymNode *node)
{
    if (node->right == NULL)
    {
        return node;
    }
    else
    {
        SymNode *temp = node->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    return node;
}
SymNode *searchNode(SymNode *node, string k)
{
    if (node->key == k)
    {
        return node;
    }
    else if (k < node->key)
    {
        return searchNode(node->left, k);
    }
    else if (node->key < k)
    {
        return searchNode(node->right, k);
    }
    return node;
}

void SymbolTable::remove(string k)
{
    // CASE 1 WHEN NODE IS LEAF NODE
    if (root->key == k && root->left == NULL && root->right == NULL)
    {
        root = NULL;
        delete root;
        size--;
    }
    // CASE 2 WHEN NODE HAS ONLY ONE CHILD
    else if (root->key == k && root->left != NULL && root->right == NULL)
    {

        root = root->left;
        delete root->par;
        size--;
    }
    else if (root->key == k && root->left == NULL && root->right != NULL)
    {

        root = root->right;
        delete root->par;
        size--;
    }
    // CASE 3 NODE HAS 2 CHIILDREN
    else if (root->key == k)
    {
        SymNode *temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        root->key = temp->key;
        temp->key = k;
        root->address = temp->address;
        if (temp->par->right == temp)
        {
            if (temp->left == NULL && temp->right == NULL)
            {
                temp->par->right = NULL;
                while (temp->par != root)
                {
                    temp->par->height = Height1(temp->par);
                    temp->par = temp->par->par;
                }
                root->height = Height1(root);
                size--;
            }
            else
            {
                temp->par->right = temp->right;
                temp->right->par = temp->par;
                while (temp->par != root)
                {
                    temp->par->height = Height1(temp->par);
                    temp->par = temp->par->par;
                }
                root->height = Height1(root);
                size--;
            }
        }
        else
        {
            if (temp->left == NULL && temp->right == NULL)
            {
                temp->par->left = NULL;
                while (temp->par != root)
                {
                    temp->par->height = Height1(temp->par);
                    temp->par = temp->par->par;
                }
                root->height = Height1(root);
                size--;
            }
            else
            {
                temp->par->left = temp->right;
                temp->right->par = temp->par;
                while (temp->par != root)
                {
                    temp->par->height = Height1(temp->par);
                    temp->par = temp->par->par;
                }
                root->height = Height1(root);
                size--;
            }
        }
    }
    else
    {
        if (k < root->key)
        {
            SymbolTable *temp = new SymbolTable();
            temp->root = root->left;
            temp->remove(k);
            root->left = temp->root;
            if (temp->root != NULL)
            {
                temp->root->par = root;
            }
            size--;
        }
        else if (k > root->key)
        {
            SymbolTable *temp = new SymbolTable();
            temp->root = root->right;
            temp->remove(k);
            root->right = temp->root;
            if (temp->root != NULL)
            {
                temp->root->par = root;
            }
            size--;
        }
    }
    if (BalanceFactor(root) < -1)
    {

        if (k < root->key)
        {
            if (Height1(root->right->left) > Height1(root->right->right))
            {
                if (!root->par)
                {
                    SymNode *res = root->right->RightLeftRotation();
                    root = res;
                    if (root->left){
                        root->left->par =res;
                    }
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->right->RightLeftRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                    if (root->left){
                        root->left->par =res;
                    }
                }
                else if (root->par->right == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->right->RightLeftRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                    if (root->left){
                        root->left->par =res;
                    }
                }
            }
            else
            {
                if (!root->par)
                {
                    SymNode *res = root->right->RightRightRotation();
                    root = res;
                    if (root->left){
                        root->left->par =res;
                    }
                    
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->right->RightRightRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                    if (root->left){
                        root->left->par =res;
                    }
                }
                else if (root->par->right == root)
                {
                    SymNode *r = root->par;
                    SymNode *res = root->right->RightRightRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                    if (root->left){
                        root->left->par =res;
                    }
                }
            }
        }
        else
        {
            if (k > root->right->key)
            {
                if (!root->par)
                {
                    SymNode *res = root->right->RightRightRotation();
                    root = res;
                    
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->right->RightRightRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                }
                else if (root->par->right == root)
                {
                    SymNode *r = root->par;
                    SymNode *res = root->right->RightRightRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                }
            }
            else if (k < root->right->key)
            {
                if (!root->par)
                {
                    SymNode *res = root->right->RightLeftRotation();
                    root = res;
                }
                else if (root->par->left == root)
                {
                    SymNode *r = root->par;
                    SymNode *res = root->right->RightLeftRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                }
                else if (root->par->right == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->right->RightLeftRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                }
            }
        }
    }
    else if (BalanceFactor(root) > 1)
    {
        if (k > root->key)
        {
            if (Height1(root->left->left) > Height1(root->left->right))
            {
                if (!root->par)
                {
                    SymNode *res = root->left->LeftLeftRotation();
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
                if (!root->par)
                {
                    SymNode *res = root->left->LeftLeftRotation();
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftLeftRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
                else if (root->par->right == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftLeftRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
            }
            else
            {
                if (!root->par)
                {
                    SymNode *res = root->left->LeftRightRotation();
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftRightRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
                else if (root->par->right == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftRightRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                    if (root->right){
                        root->right->par = res;
                    }
                }
            }
        }
        else
        {
            if (k < root->left->key)
            {
                if (!root->par)
                {
                    SymNode *res = root->left->LeftLeftRotation();
                    root = res;
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftLeftRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                }
                else if (root->par->right == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftLeftRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                }
            }
            else if (k > root->left->key)
            {
                if (!root->par)
                {
                    root = root->left->LeftRightRotation();
                }
                else if (root->par->left == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftRightRotation();
                    r->left = res;
                    res->par = r;
                    root = res;
                }
                else if (root->par->right == root)
                {

                    SymNode *r = root->par;
                    SymNode *res = root->left->LeftRightRotation();
                    r->right = res;
                    res->par = r;
                    root = res;
                }
            }
        }
    }
}

int SymbolTable::search(string k)
{
    SymbolTable *temp = new SymbolTable();
    if (root == NULL)
    {
        return -2;
    }
    if (k < root->key && !root->left)
    {
        return -2;
    }
    if (k > root->key && !root->right)
    {
        return -2;
    }
    if (root->key == k)
    {
        return root->address;
    }
    else if (k < root->key)
    {
        temp->root = root->left;
        return temp->search(k);
    }
    else if (root->key < k)
    {

        temp->root = root->right;
        return temp->search(k);
    }
    return -2;
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *node;
    node = searchNode(root, k);
    node->address = idx;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

void Deletepostorder(SymNode* node){
    if (node==NULL){
        return;
    }
    Deletepostorder(node->left);
    Deletepostorder(node->right);
    delete node;
}
SymbolTable::~SymbolTable()
{
    Deletepostorder(root);
}

// int main()
// {
//     SymbolTable *sym = new SymbolTable();

//     sym->insert("e");

//     sym->insert("c");

//     sym->insert("b");

//     sym->insert("a");
//     sym->insert("g");
//     sym->insert("d");
//     sym->insert("f");
//     sym->insert("h");
//     sym->insert("i");
//     // std::cout << sym->get_root()->key << endl;
//     //  printInorder(sym->get_root());
//     //  std::cout << sym->search("f")<<endl;
//     //  std::cout << sym->search("a")<<endl;
//     //  std::cout << sym->search("b")<<endl;
//     //  std::cout << sym->search("c")<<endl;
//     //  std::cout << sym->search("d")<<endl;
//     //  std::cout << sym->search("e")<<endl;
//     //  std::cout << sym->get_size()<<endl;
//     //  sym->remove("e");
//     printIO(sym->get_root());
//     // cout << endl;
//     //  std::cout << sym->get_size();
//     std::cout << endl;
//     sym->remove("i");
//     printIO(sym->get_root());
//     std::cout << endl;
//     sym->remove("c");
//     printIO(sym->get_root());
//     std::cout << endl;
//     sym->remove("b");
//     printIO(sym->get_root());
//     std::cout << endl;
//     sym->remove("a");
//     // cout << sym->get_root()->height << " hehe" << endl;
//     printIO(sym->get_root());
//     std::cout << endl;
//     sym->remove("g");
//     //  printIO(sym->get_root());
//     // //sym->remove("x");
//     // //printIO(sym->get_root());
//     printIO(sym->get_root());
//     std::cout << "\n"
//               << sym->get_root()->key << " " << sym->get_root()->left->par->key << " " << sym->get_root()->right->par->key;
//     std::cout << sym->get_root()->key;
//     sym->assign_address("f", 100);
//     cout << sym->search("z") << endl;
// }


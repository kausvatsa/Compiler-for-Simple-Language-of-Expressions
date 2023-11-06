/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line

Parser::Parser()
{
    symtable = new SymbolTable();
    last_deleted = 0;
}

void Parser::parse(vector<string> expression)
{
    ExprTreeNode *rt = new ExprTreeNode();
    rt->type = "t";
    rt->id = ":=";
    rt->right = new ExprTreeNode();
    ExprTreeNode *temp = rt->right;
    //cout<<expression[0]<<endl;
    if (expression[0] == "del")
    {
        //cout<<expression[2]<<endl;
        rt->left = new ExprTreeNode();
        rt->left->id = "del";
        rt->left->type = "DEL";
        rt->right->id = expression[2];
        //cout<<"hallo"<<endl;
        last_deleted = symtable->search(expression[2]);
        // cout<<last_deleted<<endl;
        symtable->remove(expression[2]);
        //cout<<"hallo"<<endl;
        

    }
    else
    {
        rt->left = new ExprTreeNode();
        rt->left->id = expression[0];
        if (expression[0] != "ret")
        {
            rt->left->type = "VAR";
            symtable->insert(expression[0]);
            
        }
        else
        {
            rt->left->type = "RET";
        }
        vector<ExprTreeNode *> v;
        v.push_back(rt);
        for (int i = 2; i < expression.size(); i++)
        {
            if (expression[i] == "(")
            {
                temp->left = new ExprTreeNode();
                v.push_back(temp);
                temp = temp->left;
            }
            else if (expression[i] == "+" || expression[i] == "-" || expression[i] == "*" || expression[i] == "/")
            {
                if (expression[i] == "+")
                {
                    temp->type = "ADD";
                }
                if (expression[i] == "-")
                {
                    temp->type = "SUB";
                }
                if (expression[i] == "*")
                {
                    temp->type = "MUL";
                }
                if (expression[i] == "/")
                {
                    temp->type = "DIV";
                }
                temp->id = expression[i];
                temp->right = new ExprTreeNode();
                v.push_back(temp);
                temp = temp->right;
            }
            else if (expression[i] == ")")
            {
                temp = v[v.size() - 1];
                v.pop_back();
            }
            else
            {
                if (expression[i][0] > '9')
                {
                    temp->type = "VAR";
                    temp->id = expression[i];
                    temp = v[v.size() - 1];
                    v.pop_back();
                }
                else
                {
                    temp->type = "VAL";
                    temp->id = expression[i];
                    temp->num = stoi(expression[i]);
                    temp = v[v.size() - 1];
                    v.pop_back();
                }
            }
        }
    }
    expr_trees.push_back(rt);
}

Parser::~Parser()
{
    //delete symtable;
    ExprTreeNode*node;
    while(expr_trees.empty()!=true){
        node = expr_trees[expr_trees.size()-1];
        expr_trees.pop_back();
        delete node;
    }
}

// int main()
// {
//     Parser *p = new Parser;
//     vector<string> vec1;
//     vec1.push_back("a");
//     vec1.push_back(":=");
//     vec1.push_back("(");
//     vec1.push_back("(");
//     vec1.push_back("0");
//     vec1.push_back("+");
//     vec1.push_back("2");
//     vec1.push_back(")");
//     vec1.push_back("+");
//     // vec1.push_back("(");
//     vec1.push_back("12");
//     // vec1.push_back(")");
//     vec1.push_back(")");
    
//     p->parse(vec1);
//     cout<<p->expr_trees[p->expr_trees.size()-1]->id<<endl;
//     // b=(((2×a)+(a-7))-(12))
//     vector<string> vec2;
//     vec2.push_back("b");
//     vec2.push_back(":=");
//     vec2.push_back("(");
//     vec2.push_back("(");
//     vec2.push_back("(");
//     vec2.push_back("2");
//     vec2.push_back("*");
//     vec2.push_back("a");
//     vec2.push_back(")");
//     vec2.push_back("+");
//     vec2.push_back("(");
//     vec2.push_back("a");
//     vec2.push_back("-");
//     vec2.push_back("7");
//     vec2.push_back(")");
//     vec2.push_back(")");
//     vec2.push_back("-");
//     // vec2.push_back("(");
//     vec2.push_back("12");
//     // vec2.push_back(")");
//     vec2.push_back(")");

//     p->parse(vec2);
//     cout<<p->expr_trees[p->expr_trees.size()-1]->id<<endl;

//     vector<string> vec3;
//     vec3.push_back("c");
//     vec3.push_back(":=");
//     vec3.push_back("(");
//     vec3.push_back("b");
//     vec3.push_back("/");
//     vec3.push_back("a");
//     vec3.push_back(")");

//     p->parse(vec3);
//     cout<<p->expr_trees[p->expr_trees.size()-1]->id<<endl;

//     vector<string> vec4;
//     vec4.push_back("c");
//     vec4.push_back(":=");
//     vec4.push_back("(");
//     vec4.push_back("1");
//     vec4.push_back("+");
//     vec4.push_back("2");
//     vec4.push_back(")");

//     p->parse(vec4);
//     cout<<p->expr_trees[p->expr_trees.size()-1]->id<<endl;

//     vector<string> vec5;
//     vec5.push_back("del");
//     vec5.push_back(":=");
//     vec5.push_back("c");

//     p->parse(vec5);
//     cout<<p->expr_trees[p->expr_trees.size()-1]->id<<endl;

// }
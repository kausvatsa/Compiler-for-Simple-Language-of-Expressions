/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

// Write your code below this line

EPPCompiler::EPPCompiler()
{
    targ = Parser();
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    targ = Parser();
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = 0; i < memory_size; i++)
    {
        mem_loc.push_back(memory_size - i - 1);
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    ofstream Myfile;
    Myfile.open(output_file);
    for (int i = 0; i < code.size(); i++)
    {
        targ.parse(code[i]);
        // cout << "oii" << endl;
        generate_targ_commands();
    }
}
void postorder(ExprTreeNode *node, vector<string> &v)
{

    if (node == NULL)
    {
        return;
    }
    postorder(node->right, v);
    postorder(node->left, v);
    if (node->type == "VAR")
    {
        v.push_back(node->id);
    }
    else if (node->type == "VAL")
    {
        v.push_back(node->id);
    }
    else if (node->type != "RET" && node->type != "DEL")
    {
        v.push_back(node->id);
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> result;
    ExprTreeNode *node = targ.expr_trees[targ.expr_trees.size() - 1];
    postorder(node->right, result);
    result.push_back(node->left->id);
    write_to_file(result);
    return result;

}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream Myfile;
    Myfile.open(output_file, std::ios::app);
    for (int j = 0; j < commands.size() - 1; j++)
    {
        if (commands[j] == "+")
        {
            Myfile << "ADD" << endl;
        }
        else if (commands[j] == "-")
        {
            Myfile << "SUB" << endl;
        }
        else if (commands[j] == "*")
        {
            Myfile << "MUL" << endl;
        }
        else if (commands[j] == "/")
        {
            Myfile << "DIV" << endl;
        }
        else if (commands[j][0] > '9')
        {
            int i = targ.symtable->search(commands[j]);
            if (i == -2)
            {
                i = targ.last_deleted;
            }

            Myfile << "PUSH "
                   << "mem[" << to_string(i) << "]" << endl;
        }
        else
        {
            Myfile << "PUSH " << commands[j] << endl;
        }
    }
    if (commands[commands.size() - 1] != "ret" && commands[commands.size() - 1] != "del")
    {
        int i;
        if (targ.symtable->search(commands[commands.size() - 1]) == -1)
        {
            i = mem_loc[mem_loc.size() - 1];
            targ.symtable->assign_address(commands[commands.size() - 1], mem_loc[mem_loc.size() - 1]);
            mem_loc.pop_back();
        }
        else
        {
            i = targ.symtable->search(commands[commands.size() - 1]);
        }
        Myfile << "mem[" << to_string(i) << "] = POP" << endl;
    }
    else if (commands[commands.size() - 1] == "del")
    {
        int i = targ.last_deleted;
        mem_loc.push_back(i);
        Myfile << "DEL = mem[" << to_string(i) << "]" << endl;
    }
    else if (commands[commands.size() - 1] == "ret")
    {
        Myfile << "RET = POP" << endl;
    }
    Myfile.close();
}

EPPCompiler::~EPPCompiler()
{

}
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

// int main(){
//    vector<string>v1 =  {"x", ":=" ,"(","3", "+", "(","5","*","2",")",")"};
//     vector<string>v2 =  {"y", ":=", "(","1","+","2",")"};
//     vector<string>v3 =  {"z", ":=", "(","x","*","y",")"};
//     vector<string>v4 =  {"w", ":=", "(","(","z","*","z",")", "-", "1000",")"};
//     vector<string>v5 =  {"del", ":=","z"};
//     vector<string>v6 =  {"ret", ":=", "(", "w", "+", "7", ")"};
//     EPPCompiler compiler("outputFile3.txt",10);
//     vector<vector<string>> code;
//     code.push_back(v1);
//     code.push_back(v2);
//     code.push_back(v3);
//     code.push_back(v4);
//     code.push_back(v5);
//     code.push_back(v6);
//     compiler.compile(code);
//     printIO(compiler.targ.symtable->get_root());
// }

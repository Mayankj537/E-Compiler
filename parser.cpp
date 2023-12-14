/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your expression below this line
ExprTreeNode* buildExpressionTree(vector<string>& expression, int& index) {
    if (index >= expression.size()) {
        return nullptr;
    }

    string token = expression[index];
    index++;
    ExprTreeNode* node = new ExprTreeNode();
    if(token == "(") {
        node->left = buildExpressionTree(expression,index);
        if(index<expression.size()) {
            if (expression[index] == "+") {
                node->type = "ADD";
                index++;
                node->right = buildExpressionTree(expression,index);
            } else if (expression[index] == "-") {
                node->type = "SUB";
                index++;
                node->right = buildExpressionTree(expression,index);
            } else if (expression[index] == "*") {
                node->type = "MUL";
                index++;
                node->right = buildExpressionTree(expression,index);
            } else if (expression[index] == "/") {
                node->type = "DIV";
                index++;
                node->right = buildExpressionTree(expression,index);
            }
        }
        index++;
    }
    else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        node->type = "VAL";
        node->num=std::stoi(token);
    } 
    else if (token[0] <= 'z' && token[0]>= 'A'){
        // Handle variables.
        node->type = "VAR";
        node->id=token;
    }
    
    else if (index<expression.size() && token == ")") {
        // If the current token is '(', create a left child and descend.
        index++;
    }
 return node;

}
Parser::Parser(){
    symtable=new SymbolTable();
    
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* root=new ExprTreeNode();
    root->type="EQUAL";
    if(expression[0]=="ret"){
        root->left=new ExprTreeNode();
        root->left->type="RET";
        expression.erase(expression.begin(),expression.begin()+2);
        int index=0;
        root->right=buildExpressionTree(expression,index);
        expr_trees.push_back(root);
        return;
    }
    else if(expression[0]=="del"){
        root->left=new ExprTreeNode();
        root->left->type="DEL";
        expression.erase(expression.begin(),expression.begin()+2);
        root->right=new ExprTreeNode();
        root->right->type="VAR";
        root->right->id=expression[0];
        expr_trees.push_back(root);
        last_deleted=symtable->search(root->right->id);
        symtable->remove(root->right->id);
        return;
    }
    else{
        root->left=new ExprTreeNode();
        root->left->type="VAR";
        root->left->id=expression[0];
        symtable->insert(expression[0]);
        expression.erase(expression.begin(),expression.begin()+2);
        int index=0;
        root->right=buildExpressionTree(expression,index);
        expr_trees.push_back(root);
        return;
    }
}

Parser::~Parser(){
    // // Clean up the expr_trees vector
    //  for (auto tree : expr_trees) {
    //     delete tree;
    // }
    //  expr_trees.clear();

    // // // Clean up the SymbolTable
    //  delete symtable;
}
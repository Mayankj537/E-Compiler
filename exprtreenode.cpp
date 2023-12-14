/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="";
    id="";
    left=nullptr;
    right=nullptr;
    num=0;

}

ExprTreeNode::ExprTreeNode(string t,int v){
    type="";
    id="";
    left=nullptr;
    right=nullptr;
    num=0;
}

ExprTreeNode::~ExprTreeNode(){
    
}


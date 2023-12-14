/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line
int getHeight(SymNode* node){
    if(node==nullptr){
        return 0;
    }
    return node->height;
}
void updateHeight(SymNode* node) {
    if (node != nullptr) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}
SymNode::SymNode(){
    key="undef";
    height=1;
}

SymNode::SymNode(string k){
    key=k;
    height=1;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* newRoot = this->left;
    this->left = newRoot->right;
    newRoot->right = this;

    // Update heights
    updateHeight(this);
    updateHeight(newRoot);

    return newRoot;

}

SymNode* SymNode::RightRightRotation(){
     SymNode* newRoot = this->right;
    this->right = newRoot->left;
    newRoot->left = this;

    // Update heights
    updateHeight(this);
    updateHeight(newRoot);

    return newRoot;
}

SymNode* SymNode::LeftRightRotation(){
     if (left == nullptr)
        return this;

    left = left->RightRightRotation();
    return LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
   if (right == nullptr)
        return this;

    right = right->LeftLeftRotation();
    return RightRightRotation();
}

SymNode::~SymNode(){
}
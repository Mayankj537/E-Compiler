/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line
SymNode* findMin(SymNode* root){
    SymNode* temp=root;
    while(temp->left!=nullptr){
        temp=temp->left;
    }
    return temp;
}
SymNode* searchInBST(SymNode* &root,string k){
    if(root==nullptr){
        return nullptr;
    }
    else if(root->key==k){
        return root;
    }
    else if(root->key>k){
        return searchInBST(root->left,k);
    }
    return searchInBST(root->right,k);
}
int get_Height(SymNode* node){
    if(node==nullptr){
        return 0;
    }
    return node->height;
}
int getBalance(SymNode* node) {
    if (node == nullptr)
        return 0;
    return get_Height(node->left) - get_Height(node->right);
}
void update_height(SymNode* node) {
    if (node != nullptr) {
        node->height = 1 + std::max(get_Height(node->left), get_Height(node->right));
    }
}
SymNode* Insert(SymNode* node, string k) {
    if (node == nullptr) {
        SymNode* newNode = new SymNode(k);
        newNode->height = 1; // Set height to 1 for new leaf node
        return newNode;
    }

    if (k < node->key) {
        node->left = Insert(node->left, k);
    } else if (k > node->key) {
        node->right = Insert(node->right, k);
    } else {
        return node;  
    }

    update_height(node);

    int balance = getBalance(node);

    if (balance > 1) {
        if (k < node->left->key) {
            return node->LeftLeftRotation();
        } else {
            return node->LeftRightRotation();
        }
    }
    if (balance < -1) {
        if (k > node->right->key) {
            return node->RightRightRotation();
        } else {
            return node->RightLeftRotation();
        }
    }

    return node;
}

SymNode* recremove(SymNode* node, const string& k) {
    if (node == nullptr) {
        return nullptr;
    }

    if (k < node->key) {
        node->left = recremove(node->left, k);
    } else if (k > node->key) {
        node->right = recremove(node->right, k);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            // Node has one child or no child
            SymNode* temp = (node->left) ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }

            delete temp;
        } else {
            SymNode* successor = findMin(node->right);
            node->key = successor->key;
            node->right = recremove(node->right, successor->key);
            update_height(node);
        }
    }

    if (node == nullptr) {
        return nullptr; // If the tree had only one node, no need for further balancing
    }

    update_height(node);

    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->left) >= 0) {
            return node->LeftLeftRotation();
        } else {
            return node->LeftRightRotation();
        }
    }
    if (balance < -1) {
        if (getBalance(node->right) <= 0) {
            return node->RightRightRotation();
        } else {
            return node->RightLeftRotation();
        }
    }

    return node;
}

SymbolTable::SymbolTable(){
}

void SymbolTable::insert(string k){
    root = Insert(root, k);
    size++;
}

void SymbolTable::remove(string k){
    root=recremove(root,k);
    size--;
}

int SymbolTable::search(string k){
    SymNode* res=searchInBST(root,k);
    if(res){
        return res->address;
    }
    else{
        return -2;
    }
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* res=searchInBST(root,k);
        res->address=idx;
        return;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}
void destroyTree(SymNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
SymbolTable::~SymbolTable(){
    destroyTree(root);
}
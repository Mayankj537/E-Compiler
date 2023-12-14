/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
vector<string> postorderTraversal(ExprTreeNode* node) {
    vector<string> postorderNodes;

    if (node == nullptr) {
        return postorderNodes;
    }
    vector<string> leftTraversal = postorderTraversal(node->right);
    vector<string> rightTraversal = postorderTraversal(node->left);

    postorderNodes.insert(postorderNodes.end(), leftTraversal.begin(), leftTraversal.end());
    postorderNodes.insert(postorderNodes.end(), rightTraversal.begin(), rightTraversal.end());

    if (node->type == "VAR") {
        postorderNodes.push_back(node->id);
    } else if (node->type == "VAL") {
        postorderNodes.push_back(to_string(node->num));
    } else if (node->type == "ADD") {
        postorderNodes.push_back("+");
    } else if (node->type == "SUB") {
        postorderNodes.push_back("-");
    } else if (node->type == "MUL") {
        postorderNodes.push_back("*");
    } else if (node->type == "DIV") {
        postorderNodes.push_back("/");
    }

    return postorderNodes;
}


EPPCompiler::EPPCompiler(){

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file=out_file;
    memory_size=mem_limit;
    for(int i=0;i<memory_size+1;i++){
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    ofstream(this->output_file.c_str());

    for(int i=0;i<code.size();i++){
            targ.parse(code[i]);
            vector<string>to_write=generate_targ_commands();
            write_to_file(to_write);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> res;
    if(targ.expr_trees.back()->left->type=="RET"){
        vector<string> post = postorderTraversal(targ.expr_trees.back()->right);
            for (int i = 0; i < post.size(); i++) {
            string to_push = post[i];

            if (to_push == "+") {
            res.push_back("ADD");
            } else if (to_push == "-") {
            res.push_back("SUB");
            } else if (to_push == "*") {
            res.push_back("MUL");
            } else if (to_push == "/") {
                res.push_back("DIV");
            } else if (isdigit(to_push[0]) || (to_push[0] == '-' && isdigit(to_push[1]))) {
            res.push_back("PUSH " + to_push);
        }else{
            int Address=targ.symtable->search(to_push);
            res.push_back("PUSH mem["+std::to_string(Address)+"]");
        }
        
    }
    res.push_back("RET = POP");
        return res;
    }
    else if(targ.expr_trees.back()->left->type=="DEL"){
        int id=mem_loc.size();
        for(int i=0;i<mem_loc.size();i++){
            if(targ.last_deleted<mem_loc[i]){
                id=i;
                break;
            }
        }
        mem_loc.insert(mem_loc.begin(),targ.last_deleted);
        res.push_back("DEL = mem["+ to_string(targ.last_deleted)+"]");
        return res;
    }
    else{
            vector<string> post = postorderTraversal(targ.expr_trees.back()->right);
            for (int i = 0; i < post.size(); i++) {
            string to_push = post[i];

            if (to_push == "+") {
            res.push_back("ADD");
            } else if (to_push == "-") {
            res.push_back("SUB");
            } else if (to_push == "*") {
            res.push_back("MUL");
            } else if (to_push == "/") {
                res.push_back("DIV");
            } else if (isdigit(to_push[0]) || (to_push[0] == '-' && isdigit(to_push[1]))) {
            res.push_back("PUSH " + to_push);
        }else{
            int Address=targ.symtable->search(to_push);
            res.push_back("PUSH mem["+std::to_string(Address)+"]");
        }
            }
        int addr=targ.symtable->search(targ.expr_trees.back()->left->id);
        if(addr>=0){
            res.push_back("mem["+ std::to_string(addr)+"] = POP");
            
        }
        else if(addr==-1){
            mem_loc.pop_back();
            int index=memory_size-mem_loc.size();
            targ.symtable->assign_address(targ.expr_trees.back()->left->id,index);
            res.push_back("mem["+ std::to_string(index)+"] = POP");


        }
        else if(addr==-2){
            targ.symtable->insert(targ.expr_trees.back()->left->id);
            mem_loc.pop_back();
            int index=memory_size-mem_loc.size();
            targ.symtable->assign_address(targ.expr_trees.back()->left->id,index);
            res.push_back("mem["+ std::to_string(index)+"] = POP");

    }
    return res;
}
    }


void EPPCompiler::write_to_file(vector<string> commands){
    ofstream outfile;
    outfile.open(output_file, ios::app);

    if (!outfile.is_open()) {
        return;
    }

    for (const string& command : commands) {
        outfile << command << endl;
    }

    // Close the file
    outfile.close();

}

EPPCompiler::~EPPCompiler(){

}
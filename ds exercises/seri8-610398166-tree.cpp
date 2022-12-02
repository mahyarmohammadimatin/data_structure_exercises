#include <iostream>
#include<string>
using namespace std;

class Node{
public:
    Node * left=0;
    Node * right=0;
    int flag=0;
};

class Tree{
public:
    Node * root=new Node;
    void preOrderTrv(Node *,string);
    void add(string s);
};

int main(){
     int n;cin>>n;
     Tree myTree;
     string s;
     for(int i=0;i<n;i++){
        cin>>s;
        myTree.add(s);
     }
     myTree.preOrderTrv(myTree.root,"");
}

void Tree::add(string s){
    Node * cur=root;
    for(int i=0;i<s.size();i++){
        if(s[i]=='0'){
            if(cur->left==0) cur->left=new Node;
            cur=cur->left;
        }
        else if(s[i]=='1'){
            if(cur->right==0) cur->right=new Node;
            cur=cur->right;
        }
    }
    cur->flag++;
}

void Tree::preOrderTrv(Node * curRoot,string result){
    for(int i=0;i<curRoot->flag;i++) cout<<result<<' ';
    if(curRoot->left!=0) preOrderTrv(curRoot->left,result+'0');
    if(curRoot->right!=0) preOrderTrv(curRoot->right,result+'1');
}

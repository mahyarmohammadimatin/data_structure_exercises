#include<iostream>
using namespace std;

class Node{
public:
    Node(int v){
        value = v;
    }

    int value=-1;
    int height=1;
    int subNodes=1;
    int count=1;

    Node *right = 0;
    Node *left = 0;

};

class AVLTree{
public:
    AVLTree(int value){
        root = new Node(value);
    }
    Node* root;
    Node* rightRotate(Node *node);
    Node* leftRotate(Node *node);
    Node* search(int value,Node * start);
    Node* insert(Node* node, int value);
    int height(Node* node){
        if(node==0) return 0;
        return node->height;
    }
    int getSub(Node *node){
        if(node==0) return 0;
        return node->subNodes;
    }
    int findKth(int k,Node* start){
        if(getSub(start->left) >= k){
            return findKth(k,start->left);
        }
        else if(getSub(start->left) + start->count < k){
            return findKth(k-getSub(start->left) - start->count,start->right);
        }
        else return start->value;
    }
    int getBalance(Node *node);
    void preorder(Node* start);
};

int inter(string s){
    int c=1;
    if(s[0]=='-'){
        s=s.substr(1,s.size()-1);
        c=-1;
    }
    int re=0;
    for(int i=0;i<s.size();i++) re = re*10 + s[i]-'0';
    return re*c;
}

int main(){
    int* input = new int [100000];

    string s;int n=0;
    while(true){
        cin>>s;
        if(s=="q") break;
        input[n]=inter(s);
        n++;
    }
    AVLTree tree(input[0]);cout<<input[0]<<endl;
    tree.insert(tree.root,20);
    tree.insert(tree.root,30);
    Node* r=tree.root;
    double a;
    for(int i=1;i<n;i++){
        tree.root = tree.insert(r,input[i]);
        r=tree.root;
        if(r->subNodes%2==1) cout<<tree.findKth(r->subNodes/2+1,r)<<endl;
        else {
            a=(tree.findKth(r->subNodes/2+1,r)+tree.findKth(r->subNodes/2,r))/2.0;
            cout<<a<<endl;
        }
    }


    return 0;
}

Node* AVLTree :: search(int value,Node * start){
    if(start==0) return start;
    if(start->value==value) return start;
    if(value < start->value) return search(value,start->left);
    return search(value,start->right);
}

void AVLTree :: preorder(Node* start){
    if(start!=0){
        cout<<"v:"<<start->value<<", h:"<<start->height<<", subnode: "<<start->subNodes<<endl;
        preorder(start->left);
        preorder(start->right);
    }
}

int AVLTree :: getBalance(Node *node){
    if (node == 0) return 0;
    return height(node->left) - height(node->right);
}

Node* AVLTree :: insert(Node* node, int value){//in function az geeks for geeks copy shode :).
    if (node == 0)
        return new Node(value);

    node->subNodes++;

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else{
        node->count++;
        return node;
    }


    node->height = 1 + max(height(node->left),height(node->right));

    int balance = getBalance(node);


    if (balance > 1) if(value < node->left->value) return rightRotate(node);

    // Right Right Case
    if (balance < -1) if(value > node->right->value){
        return leftRotate(node);

    }

    // Left Right Case
    if (balance > 1) if( value > node->left->value)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1) if(value < node->right->value){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


Node* AVLTree :: rightRotate(Node *node){
    Node* child = node->left;
    Node* grandChild = child->right;

    node->left = grandChild;
    child->right=node;

    node->subNodes = node->count + getSub(node->left) + getSub(node->right);
    child->subNodes = child->count + getSub(child->left) + getSub(child->right);

    node->height = max(height(node->left),height(node->right)) + 1;
    child->height = max(height(child->left),height(child->right)) + 1;

    return child;
}

Node* AVLTree :: leftRotate(Node *node)  {
    Node* child = node->right;
    Node* grandChild = child->left;

    node->right = grandChild;
    child->left = node;

    node->subNodes = node->count + getSub(node->left) + getSub(node->right);
    child->subNodes = child->count + getSub(child->left) + getSub(child->right);

    node->height = max(height(node->left),height(node->right)) + 1;
    child->height = max(height(child->left),height(child->right)) + 1;

    return child;
}


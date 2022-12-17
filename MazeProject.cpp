#include<iostream>
using namespace std;

#define maxint 2147483647


template <typename T>
class Node{
public:
    Node(T a){
        data=a;
    }
    T data;
    Node* next=0;
    Node* prev=0;
};

template <typename T>
class list{
public:
    void push(T data){
        size++;
        Node<T>* a= new Node<T>(data);
        if(start==0){
            start=a;
            end=a;
            return;
        }
        end->next=a;
        a->prev=end;
        end=end->next;
        end->next=0;
    }
    int insert(T data){
        Node<T>* a= new Node<T>(data);
        size++;
        if(start==0){
            start=a;
            end=a;
            return 0;
        }
        int pos=0;
        Node<T>* cur=start;
        while(cur->data < a->data){
            pos++;
            cur=cur->next;
            if(cur==0) break;
        }
        if(cur==0){
            a->prev=end;
            end->next=a;
            end=a;
        }
        else if(cur==start){
            a->next=start;
            start->prev=a;
            start=a;
        }
        else{
            cur->prev->next=a;
            a->prev=cur->prev;
            a->next=cur;
            cur->prev=a;
        }
        end->next=0;
        return pos;
    }
    void indexInsert(T data,int index){
        size++;
        Node<T>* newnode = new Node<T>(data);
        if(size==1){start=newnode;end=newnode;return;}
        if(index==0){
            newnode->next=start;
            start->prev=newnode;
            start=newnode;
            return;
        }
        if(index>=size-1){
            newnode->prev=end;
            end->next=newnode;
            end=newnode;
            return;
        }
        Node<T>* cur=start;
        for(int i=0;i<index;i++) cur=cur->next;
        cur=cur->prev;
        newnode->next=cur->next;
        newnode->prev=cur;
        cur->next=newnode;
        newnode->next->prev=newnode;
    }
    T deleter(T data){
        Node<T>* cur=start;
        while(!(cur->data==data) && cur!=0) cur=cur->next;
        if(cur==start){
            start=start->next;
            start->prev=0;
        }
        else if(cur==end){
            end=end->prev;
            end->next=0;
        }
        else{
            cur->prev->next=cur->next;
            cur->next->prev=cur->prev;
        }
        size--;
        T returned=cur->data;
        delete cur;
        return returned;
    }
    T indexDeleter(int index){
        T re;
        Node<T>* cur=start;
        if(index==0){
            re=start->data;
            if(start==end) {size--;start=0;end=0;return re;}
            start=start->next;
            start->prev=0;
        }
        else if(index>=size-1){
            cur=end;
            re=end->data;
            end=end->prev;
            end->next=0;

        }
        else{
            for(int i=0;i<index;i++) cur=cur->next;
            re=cur->data;
            cur->prev->next=cur->next;
            cur->next->prev=cur->prev;
        }
        delete cur;
        size--;
        return re;
    }
    void display(){
        Node<T>* cur = start;
        for(int i=0;i<size;i++){
            cout<<cur->data;
            cur=cur->next;
        }
        cout<<endl;
    }
    int search(T data){
        Node<T>* cur=start;
        int i=0;
        while(!(cur->data==data)) {cur=cur->next;i++;if(cur==0)break;}
        if(cur==0) return -1;
        return i;
    }
    T operator[](int a){
        Node<T>* cur=start;
        for(int i=0;(i<size && i<a);i++) cur=cur->next;
        return cur->data;
    }
    list<T> operator+ (list<T> other){
        list<T> re;
        for(int i=0;i<this->len();i++) re.push(this->slicing(i,i+1)[0]);
        for(int i=0;i<other.len();i++) re.push(other.slicing(i,i+1)[0]);
        return re;
    }
    list<T> slicing(int a,int b,int step=1){
        list<T> re;
        Node<T>* cur = start;
        int i=0;
        while(i<a) {cur=cur->next;i++;}
        while(i<b && i<size){
            re.push(cur->data);
            for(int j=0;j<step;j++) {cur=cur->next;i++;}
        }
        return re;
    }
    bool isEmpty(){return start==0;}
    int len(){return size;}
private:
    int size=0;
    Node<T>* start=0;
    Node<T>* end=0;
};

class MazeBlock{
public:
    MazeBlock(int id1=0,int weight1=0){
        id = id1;
        weight = weight1;
        watched = false;
        dst=maxint;
    }
    int id;
    int weight; //block weight.
    int dst; //distance from start.
    bool watched; //if watched, get true.
    char before='*';
    bool operator< (const MazeBlock other){
        if(this->dst == other.dst) return (this->id < other.id);
        return (this->dst < other.dst);
    }
    bool operator== (const MazeBlock other){return (this->dst==other.dst && this->id==other.id);}
    friend ostream& operator<< (ostream& os,MazeBlock a) {
        if(a.dst!=maxint)
        return os << "(" << a.dst <<","<<a.id<<")";
        return os << "(" << '*' <<","<<a.id<<")";
    }
};


class BTNode{
public:
    list<MazeBlock> data;
    list<BTNode*> ptrs;
    BTNode * fp=0; //father pointer.
    bool isLeaf(){return ptrs.isEmpty();}
};

class BTree{
public:
    BTree(MazeBlock a=MazeBlock(),int d=3){
        root = new BTNode();
        root->data.push(a);
        degree=d;
    }
    void insert(MazeBlock a){insHelper(a,root);}
    void deleter(MazeBlock a);
    int minKey(){return (degree%2==0) ? degree/2-1 : degree/2;}
    BTNode* giveMax(BTNode* start){
        while(!start->isLeaf()) start=start->ptrs[start->data.len()];
        return start;
    }
    BTNode* giveMin(){
        BTNode* start=root;
        while(!start->isLeaf()) start=start->ptrs[0];
        return start;
    }
    BTNode * root;
private:
    int degree;
    void insHelper(MazeBlock a,BTNode* start);
    void handleExtra(BTNode* start);
    void fixMissed(BTNode*);
    void barrow(BTNode* dad,int poor,int rich);
    void combine(BTNode* dad,int a,int b);
    int whenBorn(BTNode* a){
        int i=0;
        while(a->fp->ptrs[i]!=a)i++;
        return i;
    }
};

class Maze{
public:
    Maze(int a,int b){
        n=a;
        m=b;
        maze = new MazeBlock* [n];
        for(int i=0;i<n;i++)
            maze[i] = new MazeBlock [m];
    }
    MazeBlock ** maze;
    void mazeSolver(int);
    void display(){
        if(maze[n-1][end].before=='*'){
            cout<<"NO PATH AVAILABLE..."<<endl;
            return;
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                cout<<maze[i][j].weight<<' ';
            cout<<endl;
        }
    }
    void path(){
        int i=n-1;
        int j=end;
        if(maze[n-1][end].before=='*') return;
        while(i!=0){
            maze[i][j].weight=-1;
            if(maze[i][j].before=='U') i--;
            else if(maze[i][j].before=='D') i++;
            else if(maze[i][j].before=='L') j--;
            else if(maze[i][j].before=='R') j++;
        }
        maze[0][start].weight=-1;
    }
private:
    int n,m;
    int start=0;
    int end=0;
    BTree updated;
};

int main(){
    int a,b;
    cin>>a>>b;
    int w;
    Maze myMaze = Maze(a,b); //make our maze a*b.
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            cin>>w; //this is weight in our block.
            myMaze.maze[i][j] = MazeBlock(i*b+j,w);
            if(i==0 && w!=0) myMaze.maze[i][j].dst=0;
        }
    }
    myMaze.mazeSolver(3);
    myMaze.path();
    myMaze.display();
}


void Maze::mazeSolver(int treeDegree){
    while(maze[0][start].weight==0)start++;
    while(maze[n-1][end].weight==0)end++;
    updated = BTree(maze[0][start],treeDegree);
    int i=0;
    int j=start;
    while(i!=n-1){
        //up
        if(i-1>=0)if(!maze[i-1][j].watched && maze[i-1][j].weight!=0 && maze[i][j].dst+maze[i-1][j].weight<maze[i-1][j].dst){
            updated.deleter(maze[i-1][j]);
            maze[i-1][j].dst=maze[i][j].dst+maze[i-1][j].weight;
            maze[i-1][j].before='D';
            updated.insert(maze[i-1][j]);
        }
        //down
        if(i+1<n)if(!maze[i+1][j].watched && maze[i+1][j].weight!=0 && maze[i][j].dst+maze[i+1][j].weight<maze[i+1][j].dst){
                updated.deleter(maze[i+1][j]);
                maze[i+1][j].dst=maze[i][j].dst+maze[i+1][j].weight;
                maze[i+1][j].before='U';
                updated.insert(maze[i+1][j]);
        }
        //left
        if(j-1>=0)if(!maze[i][j-1].watched && maze[i][j-1].weight!=0 && maze[i][j].dst+maze[i][j-1].weight<maze[i][j-1].dst){
            updated.deleter(maze[i][j-1]);
            maze[i][j-1].dst=maze[i][j].dst+maze[i][j-1].weight;
            maze[i][j-1].before='R';
            updated.insert(maze[i][j-1]);
        }
        //right
        if(j+1<m)if(!maze[i][j+1].watched && maze[i][j+1].weight!=0 && maze[i][j].dst+maze[i][j+1].weight<maze[i][j+1].dst){
            updated.deleter(maze[i][j+1]);
            maze[i][j+1].dst=maze[i][j].dst+maze[i][j+1].weight;
            maze[i][j+1].before='L';
            updated.insert(maze[i][j+1]);
        }
        maze[i][j].watched=true;
        if(updated.root->isLeaf() && updated.root->data.len()==1) break;
        updated.deleter(maze[i][j]);
        int id = updated.giveMin()->data[0].id;
        j=id%m;
        i=id/m;
    }
}

void BTree::combine(BTNode* dad,int a,int b){
    BTNode*lefter=dad->ptrs[a];
    BTNode*righter=dad->ptrs[b];
    BTNode* newnode = new BTNode();
    newnode->data=lefter->data+dad->data.slicing(a,a+1)+righter->data;
    newnode->ptrs=lefter->ptrs+righter->ptrs;
    newnode->fp=dad;

    for(int i=0;i<lefter->ptrs.len();i++) lefter->ptrs[i]->fp=newnode;
    for(int i=0;i<righter->ptrs.len();i++) righter->ptrs[i]->fp=newnode;

    dad->data.indexDeleter(a);
    dad->ptrs.indexDeleter(b);
    dad->ptrs.indexDeleter(a);
    dad->ptrs.indexInsert(newnode,a);
}

void BTree::barrow(BTNode* dad,int poor,int rich){
    BTNode*p=dad->ptrs[poor];
    BTNode*r=dad->ptrs[rich];
    if(poor<rich){
        p->data.push(dad->data[poor]);
        dad->data.indexDeleter(poor);
        dad->data.indexInsert(r->data.indexDeleter(0),poor);
        if(!r->isLeaf()){
            p->ptrs.push(r->ptrs.indexDeleter(0));
            p->ptrs[p->data.len()-1]->fp=p;
        }
    }
    else{
        p->data.indexInsert(dad->data[rich],0);
        dad->data.indexDeleter(rich);
        dad->data.indexInsert(r->data.indexDeleter(r->data.len()-1),rich);
        if(!r->isLeaf()){
            p->ptrs.indexInsert(r->ptrs.indexDeleter(r->ptrs.len()-1),0);
            p->ptrs[0]->fp=p;
        }
    }
}

void BTree::fixMissed(BTNode* a){
    //case0: it's root.
    if(a==root){
        if(a->data.len()==0){
            root=a->ptrs[0];

            delete a;
        }
        return;
    }

    if(a->data.len()>=minKey()) return;

    BTNode* dad=a->fp;
    int i=whenBorn(a);
    BTNode* leftBro;
    BTNode* rightBro;

    //case1: we have 2 brother.
    if(i-1>=0 && i+1<dad->ptrs.len()){
        leftBro=dad->ptrs[i-1];
        rightBro=dad->ptrs[i+1];
        //case1.1: if left brother can barrow us.
        if(leftBro->data.len() > minKey()) barrow(dad,i,i-1);

        //case1.2: if right brother can barrow us.
        else if(rightBro->data.len() > minKey()) barrow(dad,i,i+1);

        //case1.3: if we can't barrow from any of our brother
        else combine(dad,i-1,i);
    }

    //case2: we have younger brother.
    else if(i-1>=0){
        leftBro=dad->ptrs[i-1];
        //case2.1: if left brother can barrow us.
        if(leftBro->data.len() > minKey()) barrow(dad,i,i-1);

        //case2.2: if we can't barrow from left brother.
        else combine(dad,i-1,i);
    }

    //case3: we have older brother.
    else{
        rightBro=dad->ptrs[i+1];
        //case3.1: if right brother can barrow us.
        if(rightBro->data.len() > minKey()) barrow(dad,i,i+1);

        //case3.2: if we can't barrow from right brother.
        else  combine(dad,i,i+1);
    }
    fixMissed(dad);
}

void BTree::deleter(MazeBlock target){
    BTNode* cur=root;
    int i=0;
    //find the node with that data
    while(cur->data.search(target)==-1){
        i=0;
        while(cur->data[i]<target){
            i++;
            if(i==cur->data.len())break;
        }
        if(cur->isLeaf())return;
        cur=cur->ptrs[i];
    }
    i=cur->data.search(target);//save where is our data to delete
    if(cur->isLeaf()){
        cur->data.indexDeleter(i);
        fixMissed(cur);
    }
    else{
        BTNode* predcur = giveMax(cur->ptrs[i]);
        cur->data.indexDeleter(i);
        cur->data.indexInsert(predcur->data.indexDeleter(predcur->data.len()-1),i);//delete last index(predcur) and add it to our node.
        fixMissed(predcur);
    }
    root->fp=0;
}

void BTree::insHelper(MazeBlock a,BTNode* start){
    if(!start->isLeaf()){
        int i=0;
        while(start->data[i] < a) {i++;if(i==start->data.len())break;}
        insHelper(a,start->ptrs[i]);
    }
    else{
        start->data.insert(a);

        //if we have empty space available.
        if(start->data.len()<degree) return;

        //if we don't have space to add.
        else handleExtra(start);
    }
}

void BTree::handleExtra(BTNode* start){

    //split node and make 2 new node
    BTNode* leftChild=new BTNode();
    BTNode* rightChild=new BTNode();

    leftChild->data=start->data.slicing(0,degree/2);
    rightChild->data=start->data.slicing(degree/2+1,degree);

    if(!start->isLeaf()){
        leftChild->ptrs=start->ptrs.slicing(0,degree/2+1);
        rightChild->ptrs=start->ptrs.slicing(degree/2+1,degree+1);
        for(int i=0;i<leftChild->ptrs.len();i++) leftChild->ptrs[i]->fp=leftChild;
        for(int i=0;i<rightChild->ptrs.len();i++) rightChild->ptrs[i]->fp=rightChild;
    }

    leftChild->fp=start->fp;
    rightChild->fp=start->fp;
    //our 2 nodes are ready.

    //now we should add middle data to father.
    if(start->fp==0){
        BTNode* newnode=new BTNode();
        newnode->data.push(start->data[degree/2]);
        leftChild->fp=newnode;
        rightChild->fp=newnode;
        newnode->ptrs.push(leftChild);
        newnode->ptrs.push(rightChild);
        root = newnode;
    }
    else{
        int where = start->fp->data.insert(start->data[degree/2]);
        start->fp->ptrs.indexDeleter(where);
        start->fp->ptrs.indexInsert(leftChild,where);
        start->fp->ptrs.indexInsert(rightChild,where+1);
        if(start->fp->data.len()==degree) handleExtra(start->fp);
    }
}



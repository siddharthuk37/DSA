#include<bits/stdc++.h>
using namespace std;
#define MAX_TREE_HT 100
class queuenode
{
    public :
    char data;
    unsigned  freq ;
    queuenode *left , *right ;
};
class Queue
{
    public :
    int front , rear , capacity ;
    queuenode **arr ;
};
queuenode * newnode(char c, unsigned f )
{
    queuenode *q= new queuenode[(sizeof(queuenode))] ;
    q->data=c;
    q->freq=f;
    q->left= q->right= NULL ;
    return q ;
}
Queue * createqueue(int capa)
{
    Queue *temp= new Queue[(sizeof(Queue))] ;
    temp->front =temp->rear=-1 ;
    temp->capacity= capa ;
    temp->arr= new queuenode*[temp->capacity*sizeof(queuenode*)] ;
    return temp ;
}
int isthesizeone (Queue *q)
{
    return (q->front==q->rear) &&( q->front!=-1) ;
}
int isempty(Queue *q)
{
    return q->front==-1;
}
int isfull(Queue *q)
{
    return q->rear==q->capacity-1 ;
}
void enqueue(Queue *q , queuenode *item )
{
    if (isfull(q))
    {
        return ;
    }
    q->arr[++q->rear]= item ;
    if (q->front==-1)
    {
        q->front++;
    }
}
queuenode * dequeue(Queue *q)
{
    if (isempty(q))
    {
        return NULL ;
    }
    queuenode *t= q->arr[q->front] ;
    if (q->front==q->rear)
    {
        q->front=q->rear=-1 ;
    }
    else
    {
        q->front++;
    }
    return t;
}
queuenode * getfront(Queue * q)
{
    if (isempty(q))
    {
        return NULL ;
    }
    return q->arr[q->front] ;
}
queuenode* getmin(Queue *fq, Queue *sq)
{
    if (isempty(fq))
    {
        return dequeue(sq) ;
    }
    if (isempty(sq))
    {
        return dequeue(fq);
    }
    if (getfront(fq)->freq < getfront(sq)->freq)
    {
        return dequeue(fq);
    }
        return dequeue(sq) ;
    
}
isleaf(queuenode *root)
{
    return !(root->left) && !(root->right);
}
void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout << arr[i];
    cout << endl;
}
queuenode* buildhuffmantree(char data[],int freq[], int n )
{
    queuenode *left, *right, *top ;
    Queue *fq= createqueue(n);
    Queue *sq= createqueue(n);
    for (int i = 0; i < n; i++)
    {
        enqueue(fq,newnode(data[i],freq[i])) ;
        cout<<"FQ+=== "<<fq->arr[fq->rear]->freq;
    }
    // cout<<fq->rear<<" fq rear ";
    // cout<<fq->arr[3]->data<<" data";
    while (!(isempty(fq))&& isthesizeone(sq))
    {
    cout<<" INside while :";
        left= getmin(fq,sq);
        cout<<"Afrer ";
        right= getmin(fq,sq);
        top=newnode('$',left->freq+right->freq) ;
        top->left=left;
        top->right=right ;
        cout<<"top= "<<top->freq ;

        enqueue(sq,top);
        cout<<"Is empty fq = "<<isempty(fq)<<"is sz ="<<isthesizeone(sq);
    }
    // cout<<"Huffman tree builded !! ";
    cout<<sq->arr[sq->rear]->freq<<" freq ";
    return dequeue(sq) ;
}
void printcodes(queuenode *root , int arr[], int top )
{
     cout<<"Print code called \n";
    // cout<<root->data<<"  data ";
    if (root->left)
    {
        
        arr[top]=0;
        printcodes(root->left,arr,top+1) ;
    }
    if (root->right)
    {
        arr[top]=1;
        printcodes(root->right,arr,top+1) ;
    }
    if (isleaf(root))
    {
        
        cout<<root->data<<" : ";
        printArr(arr,top);
    }   
}
void huffmancodes(char data[], int freq[],int n )
{
    queuenode *root= buildhuffmantree(data,freq,n) ;
    int arr[MAX_TREE_HT], top=0 ;
   
    printcodes(root,arr,top) ;
   
}
int main()
{
     char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);
    huffmancodes(arr, freq, size);
    return 0;
     
}
//min heap
#define HEAP_TYPE 0
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct node{
    int value;
    char data;
    node* left = NULL;
    node* right = NULL;
};

struct heap{
    node** array; //array of pointers to the nodes
    int count;//current size of the heap
    int capacity;//allowed max size of the heap
    int heapType;
};

heap* createHeap(int capacity, int heapType){
    cout<<"creating heap..."<<endl;
    heap* h = (heap *)malloc(sizeof(heap));
    h->capacity = capacity;
    h->count = 0;
    h->heapType = heapType;

    h->array = (node **)malloc(capacity*sizeof(node*));
    return h;
    cout<<"created heap..."<<endl;
}

int leftChild(heap* h, int i){
    if(i >= h->capacity || i<0 || 2*i+1>=h->capacity)
        return -1;
    else
    {
        return 2*i+1;
    }
}

int rightChild(heap *h, int i)
{
    if (i >= h->capacity || i < 0 || 2 * i + 2 >= h->capacity)
        return -1;
    else
    {
        return 2 * i + 2;
    }
}

int parent(heap* h, int i){
    if(i<=0 || i>=h->capacity)
        return -1;
    else
    {
        return (i-1)/2;
    }
}

void percolateDown(heap* h, int i){
    // cout<<"percolating down at - "<<i<<endl;
    int min = i;
    int l = leftChild(h,i);
    int r = rightChild(h,i);
    if(l!=-1 && h->array[l]->value < h->array[min]->value)
        min = l;
    if(r!=-1 && h->array[r]->value < h->array[min]->value)
        min = r;
    
    if(min!=i){
        //swaping the data
        // int temp_v = h->array[min]->value;
        // int temp_d = h->array[min]->data;
        // node* temp_l = h->array[min]->left;
        // node* temp_r = h->array[min]->right;
        // h->array[min]->value = h->array[i]->value;
        // h->array[min]->data = h->array[i]->data;
        // h->array[min]->left = h->array[i]->left;
        // h->array[min]->right = h->array[i]->right;
        // h->array[i]->value = temp_v;
        // h->array[i]->data = temp_d;
        // h->array[i]->left = temp_l;
        // h->array[i]->right = temp_r;

        node* temp = h->array[min];
        h->array[min] = h->array[i];
        h->array[i] = temp;

        percolateDown(h, min);
    }
    return;
}

void buildMinHeap(heap* h){
    cout<<"building min heap"<<endl;
    int last_non_leaf_element = h->count-1;
    int i = parent(h, last_non_leaf_element);

    while(i>=0){
        percolateDown(h, i);
        i--;
    }
}

void insert(heap* h, node* nw){
    // cout<<"inserting..."<<endl;
    // cout<<h->count<<" "<<h->capacity<<endl;
    if(h->count >= h->capacity)
        return;
    
    // node nw; //already created tree type node
    // nw.data = data;
    // nw.value = value;
    h->count++;
    h->array[h->count-1] = nw;
    // cout<<nw->data<<endl;

    int i = h->count-1;
    int par = parent(h, i);
    while(i>=0 && par>=0){
        if(h->array[par]->value <= h->array[i]->value )
            break;
        
        //swaping
        // int temp_v = h->array[par]->value;
        // int temp_d = h->array[par]->data;
        // node *temp_l = h->array[par]->left;
        // node *temp_r = h->array[par]->right;
        // h->array[par]->value = h->array[i]->value;
        // h->array[par]->data = h->array[i]->data;
        // h->array[par]->left = h->array[i]->left;
        // h->array[par]->right = h->array[i]->right;
        // h->array[i]->value = temp_v;
        // h->array[i]->data = temp_d;
        // h->array[i]->left = temp_l;
        // h->array[i]->right = temp_r;
        
        // cout<<"swaping..."<<endl;
        node* temp = h->array[par];
        h->array[par] = h->array[i];
        h->array[i] = temp;

        i = par;
        par = parent(h, i);
    }
    cout <<"inserted - "<< h->array[i]->data << " " << h->array[i]->value << " " << h->array[i]->left << " " << h->array[i]->right << " "<<endl;
}

void displayHeap(heap* h){
    int n = h->count;
    for(int i=0; i<n; i++){
        cout << h->array[i]->data << " " << h->array[i]->value << " " << h->array[i]->left <<" " <<h->array[i]->right<< " "<<endl;
    }
    cout<<endl;
}

node* extractMin(heap* h){
    // cout<<"extracting min..."<<endl;
    if(h->count<=0)
        return NULL;

    node* min_node = h->array[0];
    h->array[0] = h->array[h->count-1];
    h->count--;
    // cout<<"percolating starts"<<endl;
    percolateDown(h, 0);
    // cout<<"after percolating"<<endl;
    // cout<<min_node->data<<" "<<min_node->value<<endl;
    return min_node;
}

int main(){

    int n = 6;
    heap* h = createHeap(n, HEAP_TYPE);

    // cout<<"creating node to insert..."<<endl;
    node* nw = (node *)malloc(sizeof(node));
    nw->left = NULL;
    nw->right = NULL;
    nw->data = 'a';
    nw->value = 12;
    // cout << "created node..." << endl;
    // cout<<nw->data<< " "<<nw->value<<endl;
    insert(h, nw);

    node *nw1  = (node *)malloc(sizeof(node));
    nw1->left = NULL;
    nw1->right = NULL;
    nw1->data = 'b';
    nw1->value = 2;
    insert(h, nw1);

    node *nw2  = (node *)malloc(sizeof(node));
    nw2->left = NULL;
    nw2->right = NULL;
    nw2->data = 'c';
    nw2->value = 7;
    insert(h, nw2);

    node *nw3  = (node *)malloc(sizeof(node));
    nw3->left = NULL;
    nw3->right = NULL;
    nw3->data = 'd';
    nw3->value = 13;
    insert(h, nw3);

    node *nw4  = (node *)malloc(sizeof(node));
    nw4->left = NULL;
    nw4->right = NULL;
    nw4->data = 'e';
    nw4->value = 14;
    insert(h, nw4);

    node *nw5  = (node *)malloc(sizeof(node));
    nw5->left = NULL;
    nw5->right = NULL;
    nw5->data = 'f';
    nw5->value = 85;
    insert(h, nw5);

    // buildMinHeap(h);
    displayHeap(h);
    cout<<"======================================================"<<endl;
    for(int i=1; i<n; i++){
        node* temp = (node *)malloc(sizeof(node));
        temp->left = extractMin(h);
        cout<<"left - "<<temp->left->data<<" "<<temp->left->value<<endl;
        temp->right = extractMin(h);
        cout << "right - " << temp->right->data << " " << temp->right->value << endl;
        temp->value = temp->left->value + temp->right->value;
        // temp->data = *strcat(&temp->left->data, &temp->right->data);
        temp->data = '*';

        insert(h, temp);
        cout << "inserted - " << temp->data << " " << temp->value << endl;
    }
    cout << "======================================================" << endl;

    displayHeap(h);

    return 0;
}


#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int p;

struct node{
	int p;
	int val;
};

struct heap{
	node* array;
	int count;
	int capacity;
	int heapType;
};

//O(1)
heap* create_heap(int capacity,int heapType)
{
	heap* h =  (heap *)malloc(capacity*sizeof(heap));
	if(h==NULL){
		cout<<"memory error"<<endl;
		return h;
	}
	h->array = (node *)malloc(capacity*sizeof(node));
	for(int i=0;i<capacity;i++){
		h->array[i].p = 10;
		h->array[i].val = 0;
	}
	h->capacity = capacity;
	h->count = 0;//1 is min-heap
	p = capacity;//priority value
	h->heapType = heapType;
	return h;
}

int parent(heap* h,int index){
	if(index<=0 || index>h->count){
		return -1;
	}
	return (index-1)/2;
}

void insert(heap* h,int ele){
	//todo:add resizing of heap
	if(h->count==h->capacity)
		return;
	h->array[h->count].p = p;
	h->array[h->count].val = ele;
	h->count++;

	int parentIndex = parent(h,h->count-1);
	int parent = h->array[parentIndex].p;
	int currentIndex = h->count-1;
	int current = h->array[currentIndex].p;

	while(parent>current && parentIndex>=0){
		node temp = h->array[parentIndex];
		h->array[parentIndex] = h->array[currentIndex];
		h->array[currentIndex] = temp;

		currentIndex = parentIndex;//
		parentIndex = (parentIndex-1)/2;
		parent = h->array[parentIndex].p;//
		current = h->array[currentIndex].p; 
	}
}

void display(heap* h){
	cout<<endl;
	for(int i=0;i<h->count;i++){
		cout<<h->array[i].p<<':'<<h->array[i].val<<" ";
	}
	cout<<endl;
}


int main(){

	heap *h = create_heap(5,1);
	(h!=NULL && p)?cout<<"created":cout<<"not created";
	cout<<"value of p : "<<p<<endl;
	display(h);
	// cout<<--h->count<<endl;//to prevent an extra element to be created
	//I am unable to find out why it is being created
	insert(h,10);
	p--;
	insert(h,20);
	p--;
	insert(h,15);
	p--;
	insert(h,11);
	p--;
	insert(h,13);
	p--;
	display(h);

	//now if we delete based on priority this would come out as a stack would

	return 0;
}
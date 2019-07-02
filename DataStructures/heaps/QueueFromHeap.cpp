#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int p;//priority variable

struct node{
	int p;
	int val;
};

struct heap{
	node *array;
	int heapType;
	int count;
	int capacity;
};

heap* create_heap(int heapType,int capacity){
	heap *h = (heap *)malloc(capacity*sizeof(heap));
	if(h == NULL)
		return h;
	p = 0;//for greater values each time insertion takes place
	h->array = (node *)malloc(capacity*sizeof(node));
	h->capacity = capacity;
	h->count = 0;
	h->heapType = heapType;//1 means min heap
	return h;
}

int findParent(heap *h,int i){
	if(i<=0 || i>=h->count)
		return -1;
	return (i-1)/2;
}

int left_child(heap* h,int i){
	if(i<0 || i>=h->count || 2*i+1>=h->count)
		return -1;
	return 2*i+1;
}

int right_child(heap* h,int i){
	if(i<0 || i>=h->count || 2*i+2>=h->count)
		return -1;
	return 2*i+2;
}

void min_heapify(heap *h,int i){
	// cout<<"inside min-heapify"<<endl;
	if(i<0 || i>=h->count)
		return;
	int min = i;
	int l = left_child(h,min);
	int r = right_child(h,min);
	// cout<<min<<' '<<l<<' '<<r<<endl;
	// cout<<h->array[min].p<<' '<<h->array[l].p<<' '<<h->array[r].p<<' '<<endl;
	if(l!=-1 && h->array[l].p < h->array[min].p)
		min = l;
	if(r!=-1 && h->array[r].p < h->array[min].p)
		min = r;

	if(min!=i){
		node temp = h->array[min];
		h->array[min] = h->array[i];
		h->array[i] = temp;
		min_heapify(h,i);
	}
}

int extract_min(heap* h){
	int min = h->array[0].val;
	node temp = h->array[0];
	h->array[0] = h->array[h->count-1];
	h->array[h->count-1] = temp;
	h->count--;
	min_heapify(h,0);
	return min;
}

void insert(heap *h,int ele){//basically enqueue
	//todo:add resizing of heap
	if(h->count == h->capacity){
		cout<<"overflow"<<endl;
		return;
	}

	h->array[h->count].p = p;
	h->array[h->count].val = ele;
	h->count++;

	//todo:here parent index takes care of no cases
	int currentIndex = (h->count-1);
	//todo:it doesn't check for -1 return from findParent
	int parentIndex = findParent(h,currentIndex);
	int parent = h->array[parentIndex].p;
	int current = h->array[currentIndex].p;
	while(parent > current && parentIndex>=0){
		node temp = h->array[parentIndex];
		h->array[parentIndex] = h->array[currentIndex];
		h->array[currentIndex] = temp;

		currentIndex = parentIndex;
		//todo:it doesn't check for -1 return from findParent
		parentIndex = findParent(h,currentIndex);
		parent = h->array[parentIndex].p;
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
	heap * h = create_heap(1,5);
	(h!=NULL)?cout<<"created":cout<<"not created";

	display(h);
	insert(h,10);
	p++;
	insert(h,20);
	p++;
	insert(h,15);
	p++;
	insert(h,11);
	p++;
	insert(h,13);
	p++;
	display(h);

	//same order as a queue
	cout<<extract_min(h)<<endl;
	cout<<extract_min(h)<<endl;
	cout<<extract_min(h)<<endl;
	return 0;
}
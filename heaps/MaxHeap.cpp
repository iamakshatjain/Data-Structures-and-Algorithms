//here we implement the max_heap
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct heap{
	int* array;//we store as array
	int count;//this denotes the current size of the heap
	int capacity;
	int heapType;
};

heap* create_heap(int capacity,int heapType){
	heap *h;
	h = (heap*)malloc(sizeof(heap));
	if(h==NULL){
		cout<<"heap not created"<<endl;
		return h;	
	}
	h->capacity = capacity;
	h->array = (int *)malloc(sizeof(int)*h->capacity);
	h->heapType = heapType;
	h->count=0;
	return h;
}

int left_child(heap *h,int i){
	if(i<0 || i>h->count || (2*i+1)>=h->count)
		return -1;
	else
		return 2*i + 1;
}

int right_child(heap *h,int i){
	if(i<0 || i>h->count || (2*i+2)>=h->count)
		return -1;
	else
		return 2*i + 2;
}

int parent(heap *h,int i){
	if(i<=0 || i>h->count)
		return -1;
	else
		return (i-1)/2;
}

void swap(heap* h,int i, int j){
	int temp;
	temp = h->array[i];
	h->array[i]=h->array[j];
	h->array[j]=temp;
}

//max_heapify
//if only one particular element is to be heapified
void percolate_down(heap *h,int i){
	//ith element is to be max_heapified
	int l = left_child(h,i);
	int r = right_child(h,i);
	int max = i;//initializing 
	if(l!=-1 && h->array[l]>h->array[max])
		max = l;
	if(r!=-1 && h->array[r]>h->array[max])
		max = r;

	if(max!=i){
		swap(h,i,max);
		percolate_down(h,max);
	}

	return;
}

void display(heap *h){
	if(h==NULL)
		return;
	cout<<endl;
	for(int i=0;i<h->count;i++)
	{
		cout<<h->array[i]<<" ";
	}
	cout<<endl;
}

int delete_max(heap *h){
	int max = h->array[0];//maximum element
	swap(h,0,h->count-1);
	percolate_down(h,0);
	h->count--;//reduce the number of elements in heap
	//althought we didn't actually delete the element but, the next time it would be overwritten
	return max;
}

void resize_heap(heap *h){
	int *oldArray = h->array;
	h->array = (int *)malloc(sizeof(int)*h->capacity*2);

	for(int i=0;i<h->capacity;i++){
		h->array[i] = oldArray[i];
	}

	h->capacity = 2*h->capacity;
	free(oldArray);
}

void insert(heap *h,int ele){
	if(h->count == h->capacity)//we need to resize only once
		resize_heap(h);
	h->count++;
	h->array[h->count-1] = ele;//inserted element
	// display(h);
	// int i = parent(h,h->count-1);
	int i = h->count-1;
	while(i>=0 && h->array[parent(h,i)]<h->array[i]){
		// percolate_down(h,i);
		//instead of percolate down we could also check for just the particular element
		//any element that comes down would obviously be greater
		// if parent(i) is smaller then we swap
		// if()
		swap(h,i,parent(h,i));
		i=parent(h,i);
	}
}

void destroy_heap(heap *h){
	if(h->array==NULL)
		return;

	free(h->array);//because we gave it space seperately. It is a pointer in itself
	free(h);
	h=NULL;
	// cout<<h<<endl; 	
}

void build_max_heap(heap *h,int* arr,int n){
	while(n > h->capacity)//nice one
		resize_heap(h);

	h->array = arr;//both are pointers
	h->count = n;

	int i = parent(h,h->count-1);//the first non-leaf node
	while(i>=0){
		percolate_down(h,i);
		i--;
	}
}

//O(nlogn)
void heapsort(heap *h){
	if(h==NULL)
		return;
	int oldCount = h->count;
	while(h->count>1){
		swap(h,0,h->count-1);
		h->count--;//we must reduce the count before percolation
		percolate_down(h,0);
	}
	h->count = oldCount;
}

int find_element(heap *h,int ele){
	for(int i=0;i<h->count;i++){
		if(h->array[i] == ele)
			return i;
	}
	cout<<"wrong element"<<endl;
	return -1;
}

void delete_index(heap *h,int i){
	h->array[i] = h->array[h->count-1];
	h->count--;//reduce size;
	percolate_down(h,i);
}

void delete_element(heap *h,int ele){
	int i = find_element(h,ele);
	if(i == -1)
		return;
	delete_index(h,i);
}

int main(){
	heap* h;
	h=create_heap(11,0);
	// //we enter already max heap for now
	// for(int i=0;i<11;i++)
	// {
	// 	cin>>h->array[i];
	// 	h->count++;
	// }
	// 31 1 21 9 10 12 18 3 2 8 7
	//ans : 31 10 21 9 8 12 18 3 2 1 7

	//31 10 16 9 8 14 12 3 1 5 7 

	// display(h);
	int n;
	cout<<"enter the number of elements : ";
	cin>>n;
	int *arr = (int *)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	build_max_heap(h,arr,n);
	cout<<"max heap built";
	display(h);
	// heapsort(h);
	// cout<<"heapsort done";
	// display(h);
	// build_max_heap(h,arr,n);
	// cout<<"max heap built";
	int ele;
	cout<<"enter the element to delete : ";
	cin>>ele;
	delete_element(h,ele);
	display(h);
	
	return 0;
}
//AC
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void printElements(int arr[], int l, int r){
	for(int i = 0; i <= r; i++){
		cout<<arr[i]<<' ';
	}
	cout<<endl;
}

void display(int arr[], int l, int r){
	for(int i = l; i <= r; i++){
		cout<<arr[i]<<' ';
	}
	cout<<endl;
}

void swap(int *a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int l, int r){
	// cout<<"l : "<<l<<" r : "<<r<<endl;
	int pivot = arr[r];
	int j = l-1;
	for(int i=l; i<r; i++){
		if(arr[i] <= pivot){
			++j;
			swap(arr+j, arr+i);
		}
	}
	++j;
	swap(arr+j, arr+r);
	return j-l+1; //this is the actual positon
}
	
void printKSmallest(int arr[], int l, int r, int k){
	if(k <= 0)
		return;

	int pivot = arr[r];
	int pos = partition(arr, l, r);//this is the actual position (1 based index)
	// cout<<"position : "<<pos<<" k : "<<k<<endl;
	// display(arr, l, r);
	if(pos == k){
		// cout<<"case 1 "<<endl;
		int pos_index = pos-1+l;//this is the main thing here the position returned from the partition is not the actual index
		printElements(arr, l, pos_index);
		return;
	}

	if(pos > k){
		// cout<<"case 2 "<<pos-l<<' '<<k-1<<endl;
		int pos_index = pos-1+l;
		printKSmallest(arr, l, pos_index-1, k);
		return;
	}

	if(pos < k){
		// cout<<"case 3 "<<pos-l<<' '<<k-1<<endl;
		int pos_index = pos-1+l;
		//we have now removed position number of elements from the array
		printKSmallest(arr, pos_index+1, r, k-pos);
		return;
	}

}

int main(){

	int arr[] = {5, 6, 3, 2, 1, 0, 10, 9, 8};
	int n = 9;

	int k = 9;
	printKSmallest(arr, 0, n-1, k);

	return 0;
}
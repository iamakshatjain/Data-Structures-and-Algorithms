//WA
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
	cout<<"l : "<<l<<" r : "<<r<<endl;
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
	return j; //this is the actual positon
}
	
void printKSmallest(int arr[], int l, int r, int k){

	int pivot = arr[r];
	int pos = partition(arr, l, r);//this is the actual position (1 based index)
	cout<<"position : "<<pos<<" k : "<<k<<endl;
	// display(arr, l, r);
	if(pos-l == k-1){
		cout<<"case 1 "<<endl;
		printElements(arr, l, pos);
		return;
	}

	if(pos-l > k-1){
		cout<<"case 2 "<<pos-l<<' '<<k-1<<endl;
		printKSmallest(arr, l, pos-1, k);
		return;
	}

	if(pos-l < k-1){
		cout<<"case 3 "<<pos-l<<' '<<k-1<<endl;
		printKSmallest(arr, pos+1, r, k-pos-1);
		return;
	}

}

int main(){

	int arr[] = {5, 6, 3, 2, 1, 0, 10, 9, 8};
	int n = 9;

	int k = 6;
	printKSmallest(arr, 0, n-1, k);

	return 0;
}
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void swap(int arr[],int i,int j){
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

//O(n^2) or O(n+d) - when presorted
void insertion_sort(int arr[],int n){
	int pivot,j;
	for(int i=1;i<n;i++){
		pivot = arr[i];
		j = i;
		for(;j>=1 && arr[j-1]>pivot;j--){
			swap(arr,j,j-1);
		}
		arr[j] = pivot;
	}
}

void display_arr(int arr[],int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<' ';
	}

	cout<<endl;
}

int main(){

	int n = 5;
	int arr[n] = {15,9,8,5,4};

	display_arr(arr,n);
	insertion_sort(arr,n);
	display_arr(arr,n);

	return 0;
}
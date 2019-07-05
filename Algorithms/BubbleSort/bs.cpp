#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void swap(int arr[],int i,int j){
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void bubble_sort(int arr[],int n){
	for(int i=0;i<n-1;i++){//since the last left element would automatically be sorted
		for(int j=0;j<n-i-1;j++){//each time the maximum element goes to its place
			if(arr[j]>arr[j+1])
				swap(arr,j,j+1);
		}
	}
}

void display_arr(int arr[],int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<' ';
	}

	cout<<endl;
}


int main(){
	int n = 7;
	int arr[n] = {15,13,9,8,5,6,7};

	display_arr(arr,n);
	bubble_sort(arr,n);
	display_arr(arr,n);

	return 0;
}
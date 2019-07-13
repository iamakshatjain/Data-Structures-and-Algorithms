#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void swap(int arr[],int i,int j){
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

//O(n^2)
void selection_sort(int arr[],int n){
	int min;
	for(int i=0;i<n;i++){
		min = i;
		for(int j=i;j<n;j++){
			if(arr[j]<arr[min])
				min = j;
		}

		swap(arr,i,min);
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
	selection_sort(arr,n);
	display_arr(arr,n);

	return 0;
}
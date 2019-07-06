#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void display_arr(int arr[],int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<' ';
	}

	cout<<endl;
}

void counting_sort(int a[],int n,int b[],int k){
	int c[k] = {0};

	//O(n)
	for(int i=0;i<n;i++){
		c[a[i]]++;
	}

	//O(k)
	for(int i=1;i<k;i++){
		c[i] = c[i] + c[i-1];
	}	

	for(int i=n-1;i>=0;i--){
		b[c[a[i]]-1] = a[i];//since the indexes in c would be >=1
		c[a[i]]--;
	}
}

int main(){

	int n = 10;
	int k = 11;//elements are from 0 to k-1 
	int arr[n] = {10,9,8,7,6,8,5,2,8,3};
	int sorted_arr[n] = {0};
	display_arr(arr,n);
	counting_sort(arr,n,sorted_arr,k);
	display_arr(sorted_arr,n);

	return 0;
}
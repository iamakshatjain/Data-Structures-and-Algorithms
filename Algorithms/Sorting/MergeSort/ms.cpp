#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void display_arr(int arr[],int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<' ';
	}

	cout<<endl;
}

void merge(int arr[],int l,int midr, int r){

	int i = l;
	int j = midr;
	int n = r-l+1;
	int arrn[n] = {0};
	int itr = 0;
	while(i<j && i<=midr-1 && j<=r && itr<n){
		if(arr[i]<=arr[j]){
			arrn[itr] = arr[i];
			i++;
			itr++;
		}
		else{
			arrn[itr] = arr[j];
			j++;
			itr++;
		}
	}

	while(i<=midr-1 || j<=r){
		if(i<=midr-1){
			arrn[itr] = arr[i];
			itr++;
			i++;
		}

		if(j<=r){
			arrn[itr] = arr[j];
			itr++;
			j++;
		}
	}

	i=l;
	itr=0;
	for(;i<=r && itr<n;){
		arr[i] = arrn[itr];
		i++;
		itr++;
	}
}

void merge_sort(int arr[],int l,int r){
	if(l>=r)
		return;

	else{
		int mid = (l+r)/2;
		merge_sort(arr,l,mid);
		merge_sort(arr,mid+1,r);
		merge(arr,l,mid+1,r);
	}
}

int main(){

	int n = 7;
	int arr[n] = {15,9,8,5,4,65,8};

	display_arr(arr,n);
	merge_sort(arr,0,n-1);
	display_arr(arr,n);

	return 0;
}
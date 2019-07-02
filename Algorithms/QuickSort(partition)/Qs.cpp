#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int a[],int p,int r){
	//here r denotes the actual ending index
	int pivot = a[r];
	int i = p-1;
	for(int j=p;j<r;j++){
		if(a[j]<=pivot){
			i++;
			swap(a+j,a+i);
		}
	}
	swap(a+i+1,a+r);
	return i+1;
}


void quick_sort(int a[],int p,int r){
	//we apply quick sort here
	if(p>r)
		return;
	else{
		int q=partition(a,p,r);
		quick_sort(a,p,q-1);
		quick_sort(a,q+1,r);
	}

}


void display(int arr[],int n){
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main(){
    int n;
    cout<<"enter the number of elements : "<<endl;
    cin>>n;

    int arr[n]={0};

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    quick_sort(arr,0,n-1);   
    display(arr,n);
    return 0;
}
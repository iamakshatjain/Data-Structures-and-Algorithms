#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int binarySearchIncreasing( int ele, int arr[], int l, int r ){
	if( l > r )
		return 0;

	int mid = ( l + r )/2;

	if( arr[mid] == ele )
		return 1;

	if( arr[mid] < ele )
		return binarySearchIncreasing( ele, arr, mid + 1, r );

	else
		return binarySearchIncreasing( ele, arr, l, mid - 1 );
}

int binarySearchDecreasing( int ele, int arr[], int l, int r ){
	if( l > r )
		return 0;

	int mid = ( l + r )/2;

	if( arr[mid] == ele )
		return 1;

	if( arr[mid] > ele )
		return binarySearchDecreasing( ele, arr, mid + 1, r );

	else
		return binarySearchDecreasing( ele, arr, l, mid - 1 );
}

int findPivot( int arr[], int l, int r ){
	if( l == r )
		return l;

	int mid = ( l + r )/2;

	if( ( arr[mid - 1] < arr[mid] || mid == l ) && ( arr[mid + 1] < arr[mid] || mid == r ) )
		return mid;

	if( arr[mid - 1] < arr[mid] || mid == l )
		return findPivot( arr, mid+1, r );

	else
		return findPivot( arr, l , mid - 1 );

}

int bitonicSearch( int ele, int arr[], int n){

	int pivot = findPivot( arr, 0, n-1 );
	cout<<"Pivot : "<<pivot<<endl;

	if( binarySearchIncreasing( ele, arr, 0, pivot - 1 ) || binarySearchDecreasing( ele, arr, pivot + 1, n-1) )
		return 1;
	else
		return 0;

}

int main(){

	int n = 10;
	int arr[] = {4, 5, 6, 8, 9, 5, 4, 3, 2, 1};

	int ele;
	cout<<"Enter the element to search : ";
	cin>>ele;

	bitonicSearch( ele, arr, n ) ? cout<<"Exists" : cout<<"Doesn't exists";
	return 0;

}
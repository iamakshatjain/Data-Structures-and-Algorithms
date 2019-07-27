#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int binarySearch( int ele, int arr[], int l, int r ){
	if( l > r )
		return 0;

	int mid = ( l + r )/2;

	if( arr[mid] == ele )
		return 1;

	if( arr[mid] < ele )
		return binarySearch( ele, arr, mid + 1, r );

	else
		return binarySearch( ele, arr, l, mid - 1 );
}


int findPivot( int arr[], int l, int r ){
	if( l == r )
		return l;

	int mid = ( l + r )/2;
	int first = arr[l];

	if( ( arr[mid] > arr[mid - 1] || mid == l ) && ( arr[mid + 1] < arr[mid] || mid == r  ) ){
		return mid;
	}

	if( arr[mid] < first )
		return findPivot( arr, l, mid - 1 );

	else
		return findPivot( arr, mid + 1, r );

}
	
int findElement(int ele, int arr[], int n ){

	int pivot = findPivot( arr, 0, n-1 );
	cout<<"Pivot is : "<<pivot<<endl;

	if( binarySearch( ele, arr, 0, pivot ) || binarySearch( ele, arr, pivot+1, n-1 ))
		return 1;

	else
		return 0;
}

int main(){

	int n = 7;
	int arr[] = { 4, 5, 6, 7, 1, 2, 3 };

	int ele; // find this element in arr
	cout << "enter element to find : ";
	cin >> ele;

	findElement(ele,arr,n) ? cout<<"exists" : cout<<"doesn't exists" ;

	return 0;

}
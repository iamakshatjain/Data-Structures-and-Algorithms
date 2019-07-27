#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int MaxDifference( int arr[], int n ){

	if( n == 1 )
		return 0;

	int min = arr[0];
	int max_diff = arr[1] - arr[0];

	for( int i = 0; i < n ; i++ ){
		if( arr[i] - min > max_diff )
			max_diff = arr[i] - min;

		if( arr[i] < min )
			min = arr[i];
	}	

	return max_diff;
}

int main(){

	int n = 7;
	int arr[] = {2, 3, 10, 6, 4, 8, 1};

	cout<<MaxDifference( arr, n )<<endl;

	return 0;
}
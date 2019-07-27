#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int CountFactorialTrailingZeros( int n ){

	int count = 0;
	for(int i = 5; n/i > 0 ; i*=5 ){
		count+=(n/i);
	}
	return count;
}

int main(){

	int n;
	cout<<"Enter N : ";
	cin>>n;
	cout<<"Number of zeros in n! : "<<CountFactorialTrailingZeros( n )<<endl;

	return 0;
}
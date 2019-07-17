#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct bloom_filter {
	int size;
	int* bloom;//stores one or zero
};

bloom_filter* createBloomFilter(int size){
	bloom_filter* bloom = (bloom_filter*)malloc(sizeof(bloom_filter));
	bloom->size = size;
	bloom->bloom = (int*)malloc(sizeof(int)*size);
	for(int i=0;i<size;i++)
		bloom->bloom[i] = 0;

	return bloom;
}

int firstHash(int key,int size){
	return (key-1)%size;
}

int secondHash(int key,int size){
	return (key)%size;
}

int thirdHash(int key,int size){
	return (key+1)%size;
}

void bloomInsert(int key,bloom_filter* bloom){
	//first hash
	int fhash = firstHash(key,bloom->size);
	//second hash
	int shash = secondHash(key,bloom->size);
	//third hash
	int thash = thirdHash(key,bloom->size);

	bloom->bloom[fhash] = 1;
	bloom->bloom[shash] = 1;
	bloom->bloom[thash] = 1;
	cout<<"inserted"<<endl;
}

void bloomSearch(int key,bloom_filter* bloom){
	//first hash
	int fhash = firstHash(key,bloom->size);
	//second hash
	int shash = secondHash(key,bloom->size);
	//third hash
	int thash = thirdHash(key,bloom->size);

	if(bloom->bloom[fhash] && bloom->bloom[shash] && bloom->bloom[thash]){
		cout<<"May or maynot exist"<<endl;
		return;
	}
	cout<<"Doesn't exist"<<endl;	
}

//to create bloomDelete maintain a seperate array with similar structure

int main(){
	bloom_filter* f1 = createBloomFilter(15);
	cout<<f1->size<<endl;
	bloomInsert(5,f1);
	bloomInsert(6,f1);
	bloomInsert(8,f1);
	bloomInsert(1,f1);
	bloomInsert(9,f1);
	bloomSearch(11,f1);
	bloomSearch(7,f1);

	return 0;
}
#include<bits/stdc++.h>
#include<iostream>
#define LOAD_FACTOR 1 //maximum number of elements in the list related to each node of the table

using namespace std;

struct node{ //node of the chains
	// int key; //if the key and data is different
	int data;//considering the data is the key
	node* next;
};

struct table_node{//try to make this with the node type itself
	int bcount; //number of elements attached or number of elements in the block
	int hkey; //the hashed index or key related to it
	node* next;
};

struct hash_table{
	int tsize; //size of the table
	int count;
	table_node* list;
};

int generate_hash(int key,int n){//this would return the hash key
	return key%n;
}

hash_table* createHashTable(int size){ //here this size is the total number of elements to accomadate
	hash_table* table = (hash_table	*)malloc(sizeof(hash_table));
	if(!table){
		cout<<"Memory error"<<endl;
		return table;
	}

	table->tsize = size/LOAD_FACTOR; //try keeping size to be multiple of loadfactor
	table->count = 0;
	table->list = (table_node *)malloc(sizeof(table_node)*table->tsize);
	if(!table->list){
		cout<<"Memory error"<<endl;
		return NULL;
	}

	cout<<"Table size : "<<table->tsize<<endl;
	for(int i=0;i<table->tsize;i++){
		table->list[i].hkey = i;
		table->list[i].bcount = 0;
		table->list[i].next = NULL;
	}
	return table;	
}

int hashSearch(int data,hash_table* table){
	int hash_key = generate_hash(data,table->tsize);

	table_node* hkey_node = &(table->list[hash_key]);//remember doing this way
	if(hkey_node->bcount == 0)
		return 0;

	node* itr = hkey_node->next;
	while(itr){//don't write itr->next otherwise it won't check till the last element
		if(itr->data == data)
			return 1;
		itr = itr->next;
	}
	return 0;
}

void hashInsert(int data,hash_table* table){
	int hash_key = generate_hash(data,table->tsize);
	cout<<hash_key<<endl;
	table_node* hkey_node = &(table->list[hash_key]);  	
	if(hkey_node->bcount == LOAD_FACTOR){
		cout<<"overflow"<<endl;
		return;
	}

	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = data;
	new_node->next = NULL;

	if(hkey_node->bcount == 0){
		hkey_node->next = new_node;
		hkey_node->bcount++;
		table->count++;
		// cout<<"bcount : "<<hkey_node->bcount<<endl;
		cout<<"node added at first position"<<endl;
		return;
	}

	node* itr = hkey_node->next;
	while(itr->next){
		itr = itr->next;
	}
	itr->next = new_node;
	hkey_node->bcount++;
	table->count++;
	// cout<<"bcount : "<<hkey_node->bcount<<endl;
	cout<<"node added"<<endl;
}

void hashDelete(int key,hash_table* table){//here in this implementation data and key means the same
	int hash_key = generate_hash(key,table->tsize);
	table_node* hkey_node = &(table->list[hash_key]);
	if(hkey_node->bcount == 0){
		cout<<"element doesn't exist"<<endl;
	}

	node* itr = hkey_node->next;
	if(itr->data == key){
			hkey_node->next = itr->next;
			hkey_node->bcount--;
			table->count--;
			cout<<"node removed"<<endl;
			return;
		}

	node* prev = itr;
	itr = itr->next;
	while(itr){
		if(itr->data == key){
			prev->next = itr->next;
			hkey_node->bcount--;
			table->count--;
			cout<<"node removed"<<endl;
			return;
		}
		prev = itr;
		itr = itr->next;
	}
}

int main(){
	hash_table* htable1 = createHashTable(5);//maximum number of elements to take in
	htable1?cout<<"created":cout<<"not - created";
	cout<<endl;

	//insertion to hash table
	hashInsert(1,htable1);
	hashInsert(2,htable1);
	hashInsert(3,htable1);
	hashInsert(4,htable1);
	hashInsert(5,htable1);
	hashInsert(6,htable1);

	//deleting
	hashDelete(3,htable1);

	return 0;
}
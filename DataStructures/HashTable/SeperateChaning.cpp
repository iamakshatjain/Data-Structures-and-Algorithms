//not complete
#include<bits/stdc++.h>
#include<iostream>
#define LOAD_FACTOR 3 //maximum number of elements in the list related to each node of the table

using namespace std;

struct node{ //node of the chains
	// int key;
	int data;
	node* next;
};

struct table_node{
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

	cout<<table->tsize<<endl;
	for(int i=0;i<table->tsize;i++){
		table->list[i].hkey = i;
		table->list[i].bcount = 0;
		table->list[i].next = NULL;
	}
	return table;	
}

int hashSearch(int data,hash_table* table){
	int hash_key = generate_hash(data,table->tsize);

	table_node hkey_node = table->list[hash_key];
	if(hkey_node.bcount == 0)
		return 0;

	node* itr = hkey_node.next;
	while(itr->next!=NULL){
		if(itr->data == data)
			return 1;
		itr = itr->next;
	}
	return 0;
}

void hashInsert(int data,hash_table* table){
	int hash_key = generate_hash(data,table->tsize);
	cout<<hash_key<<endl;
	table_node hkey_node = table->list[hash_key];  	
	if(hkey_node.bcount == LOAD_FACTOR){
		cout<<"overflow"<<endl;
		return;
	}

	node* new_node = (node*)malloc(sizeof(node));
	new_node->data = data;
	new_node->next = NULL;

	if(hkey_node.bcount == 0){
		hkey_node.next = new_node;
		hkey_node.bcount++;
		cout<<"added at first position"<<endl;
		return;
	}

	node* itr = hkey_node.next;
	while(itr->next){
		itr = itr->next;
	}
	itr->next = new_node;
	hkey_node.bcount++;
	cout<<"node added"<<endl;
}

int main(){
	hash_table* htable1 = createHashTable(15);
	htable1?cout<<"created":cout<<"not - created";
	cout<<endl;
	hashInsert(5,htable1);
	hashInsert(7,htable1);
	hashInsert(15,htable1);
	hashInsert(12,htable1);
	hashInsert(6,htable1);
	hashSearch(7,htable1)?cout<<"found":cout<<"not-found";

	return 0;
}
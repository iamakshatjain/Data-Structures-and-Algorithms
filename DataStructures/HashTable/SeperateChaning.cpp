//not complete
#include<bits/stdc++.h>
#include<iostream>
#define LOAD_FACTOR 5 //maximum number of elements in the list related to each node of the table

using namespace std;

struct node{
	int key;
	int data;
	node* next;
}

struct table_node{
	int bcount; //number of elements attached or number of elements in the block
	int key; //the hashed index or key related to it
	table_node	*next;
}

struct hash_table{
	int tsize; //size of the table
	int count;
	tableNode **list;
}

hash_table* createHashTable(int size){ //here this size is the total number of elements to accomadate
	hash_table* table = (hash_table	*)malloc(sizeof(hash_table));
	if(!table){
		cout<<'Memory error'<<endl;
		return table;
	}

	h->tsize = size/LOAD_FACTOR; //try keeping size to be multiple of loadfactor
	h->count = 0;
	h->list = (tableNode **)malloc(sizeof(hash_table *)*h->tsize
		);
}


int main(){


	return 0;
}
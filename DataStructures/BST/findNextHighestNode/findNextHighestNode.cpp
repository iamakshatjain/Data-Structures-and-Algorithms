#include<bits/stdc++.h>
#include<iostream>

using namespace std;

struct Node{
	int val;
	Node* parent;
	Node* left;
	Node* right;
};

Node* root = NULL;

Node* create_node(int val){
	Node* node = (Node *)malloc(sizeof(Node));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->val = val;
	return node;
}

Node* create_BST(int val){
	if(root == NULL){
		root = create_node(val);
		return root;
	}
}

Node* add_node(int val){
	if(root == NULL){
		root = create_BST(val);
		return root;
	}

	Node* itr = root;
	Node* prev_itr;
	while(itr != NULL){

		prev_itr = itr;

		if(val <= itr->val ){
			itr = itr->left;
		}
		else{
			itr = itr->right;
		}
	}

	if(val <= prev_itr->val){
		prev_itr->left = create_node(val);
		prev_itr->left->parent = prev_itr;
		return prev_itr;
	}
	else{
		prev_itr->right = create_node(val);
		prev_itr->right->parent = prev_itr;
		return prev_itr;
	}
}

int find_next_highest_node(int val){
	//here the value provided is not the pointer
	int left_parent = -1;
	int next_highest = -1;
	Node* itr = root;
	while(itr->val!=val){
		if(val<=itr->val){
			left_parent = itr->val;
			itr = itr->left;
		}
		else
			itr = itr->right; 
	}

	if(itr->right){
		itr = itr->right;
		while(itr->left!=NULL){
			itr = itr->left;
		}
		next_highest = itr->val;
		return next_highest;
	}

	return left_parent;

	return 0;
}

int main(){
	int n;
	cout<<"enter no. of nodes : ";
	cin>>n;
	for(int i=0;i<n;i++){
		int val;
		cin>>val;
		if(add_node(val))
			cout<<"node added"<<endl;
	}

	int x;
	cout<<"enter x : "<<endl;
	cin>>x;
	int ans = find_next_highest_node(x);
	if(ans == -1)
		cout<<"This is the highest node";
	else
		cout<<"Next highest node is : "<<ans<<endl;

	return 0;
}
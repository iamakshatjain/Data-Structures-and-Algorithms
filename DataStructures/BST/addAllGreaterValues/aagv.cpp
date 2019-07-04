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

int sum = 0;

void add_all_greater(Node *node){
	if(node == NULL)
		return;

	if(node->val > sum)
		sum = node->val;

	add_all_greater(node->right);
	if(node->val < sum){
		sum += node->val;
		node->val = sum;
	}
	add_all_greater(node->left);
}

void inorder_traversal(Node* node){
	if(node == NULL)
		return;

	inorder_traversal(node->left);
	cout<<node->val<<' ';
	inorder_traversal(node->right);
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

	inorder_traversal(root);
	cout<<endl;
	add_all_greater(root);
	//if this to be run again : the add_all_greater must be a util function and passed an address of sum
	//checkout gfg for more info
	inorder_traversal(root);

	return 0;
}
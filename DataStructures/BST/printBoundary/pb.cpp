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

//printing the boundary of a binary tree(no matter BST)
void print_left(Node *node){
	if(node == NULL)
		return;

	//we must not print the node if it is a leaf
	if(node->left!=NULL || node->right!=NULL)
		cout<<node->val<<' ';
	if(node->left)
		print_left(node->left);
	else if(node->right)
		print_left(node->right);
}

void print_leaves(Node* node){
	if(node == NULL)
		return;

	if(node->left == NULL && node->right == NULL)
		cout<<node->val<<' '; 

	print_leaves(node->left);
	print_leaves(node->right);
}

void print_right(Node *node){
	if(node == NULL)
		return;

	if(node->right)
		print_right(node->right);
	else if(node->left)
		print_right(node->left);

	if(node->left!=NULL || node->right!=NULL)
		cout<<node->val<<' ';
}

void print_boundary(Node* root){
	if(root == NULL)
		return;

	cout<<root->val<<' ';
	print_left(root->left);
	print_leaves(root);
	print_right(root->right);
	cout<<endl;
}


int main(){

	//BST
	// int n;
	// cout<<"enter no. of nodes : ";
	// cin>>n;
	// for(int i=0;i<n;i++){
	// 	int val;
	// 	cin>>val;
	// 	if(add_node(val))
	// 		cout<<"node added"<<endl;
	// }

	//Binary Tree
	create_BST(1);
	root->left = create_node(2);
	root->right = create_node(3);
	root->left->left = create_node(4);
	root->left->right = create_node(5);
	root->right->left = create_node(6);
	root->right->right = create_node(7);

	print_boundary(root);

	return 0;
}
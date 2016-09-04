#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

struct node {
	node *left, *right;
	int value;
	int freq, size, priority;
	static node* sentinel;

	node() {
		memset(this, 0, sizeof *this);
	}

	node(int val) {
		value = val;
		freq = size = 1;
		priority = rand();
		left = right = sentinel;
	}

	void update() {
		size = freq + left->size + right->size;
	}
};

node* node::sentinel = new node();

node* rotateRight(node* Q) {
	node* P = Q->left;
	Q->left = P->right;
	P->right = Q;
	Q->update();
	P->update();
	return P;
}

node* rotateLeft(node* P) {
	node* Q = P->right;
	P->right = Q->left;
	Q->left = P;
	P->update();
	Q->update();
	return Q;
}

node* balance(node* root) {
	if (root->left->priority > root->priority)
		root = rotateRight(root);
	else if (root->right->priority > root->priority)
		root = rotateLeft(root);
	return root;
}

node* insert(node* root, int val) {
	if (root == node::sentinel)
		return new node(val);
	if (val == root->value) {
		root->freq++;
		root->size++;
		return root;
	}
	if (val < root->value)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);
	root->update();
	root = balance(root);
	return root;
}

node* remove(node* root, int val) {
	if (root == node::sentinel)
		return root;
	if (val < root->value)
		root->left = remove(root->left, val);
	else if (val > root->value)
		root->right = remove(root->right, val);
	else {
		if (root->freq > 1) {
			root->freq--;
			root->size--;
			return root;
		}
		if (root->left == node::sentinel && root->right == node::sentinel)
			return node::sentinel;
		else if (root->left == node::sentinel)
			root = root->right;
		else if (root->right == node::sentinel)
			root = root->left;
		else {
			if (root->left->priority < root->right->priority)
				root = rotateRight(root);
			else
				root = rotateLeft(root);
			root = remove(root, val);
		}
	}
	root->update();
	return root;
}

int getMn(node* root) {
	if (root->left == node::sentinel)
		return root->value;
	return getMn(root->left);
}

void print(node* root, int val) {
	if (root == node::sentinel)
		return;
	print(root->left, val + 1);
	cout << root->value << " " << val << endl;
	print(root->right, val + 1);
}

//============================================================================
// Name        : tutorialspoint-data-structures.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.tutorialspoint.com/
//============================================================================

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

/*
 * Dequeue or Double Ended Queue is a generalized version of Queue data structure that allows insert and delete at both ends.

Some basic operations of dequeue are −

insert_at_beg(): inserts an item at the front of Dequeue.

insert_at_end(): inserts an item at the rear of Dequeue.

delete_fr_beg(): Deletes an item from front of Dequeue.

delete_fr_rear(): Deletes an item from rear of Dequeue.

Following is a C++ program to implement Dequeue
 */
#define SIZE 10
class dequeue {
	int a[20],f,r;
public:
	dequeue();
	void insert_at_beg(int);
	void insert_at_end(int);
	void delete_fr_front();
	void delete_fr_rear();
	void show();
};
dequeue::dequeue() {
	f=-1;
	r=-1;
}
void dequeue::insert_at_end(int i) {
	if(r>=SIZE-1) {
		cout<<"\n insertion is not possible, overflow!!!!";
	} else {
		if(f==-1) {
			f++;
			r++;
		} else {
			r=r+1;
		}
		a[r]=i;
		cout<<"\nInserted item is"<<a[r];
	}
}
void dequeue::insert_at_beg(int i) {
	if(f==-1) {
		f=0;
		a[++r]=i;
		cout<<"\n inserted element is:"<<i;
	} else if(f!=0) {
		a[--f]=i;
		cout<<"\n inserted element is:"<<i;
	} else {
		cout<<"\n insertion is not possible, overflow!!!";
	}
}
void dequeue::delete_fr_front() {
	if(f==-1) {
		cout<<"deletion is not possible::dequeue is empty";
		return;
	}
	else {
		cout<<"the deleted element is:"<<a[f];
		if(f==r) {
			f=r=-1;
			return;
		} else
			f=f+1;
	}
}
void dequeue::delete_fr_rear() {
	if(f==-1) {
		cout<<"deletion is not possible::dequeue is empty";
		return;
	}
	else {
		cout<<"the deleted element is:"<<a[r];
		if(f==r) {
			f=r=-1;
		} else
			r=r-1;
	}
}
void dequeue::show() {
	if(f==-1) {
		cout<<"Dequeue is empty";
	} else {
		for(int i=f;i<=r;i++) {
			cout<<a[i]<<" ";
		}
	}
}

int int_stack[100];
int stack_size = 100;
int top = -1;
void push(int val) {
	if(top >= stack_size-1)
		cout<<"Stack Overflow"<<endl;
	else {
		top++;
		int_stack[top] = val;
	}
}
void pop() {
	if(top <= -1)
		cout<<"Stack Underflow"<<endl;
	else {
		cout<<"The popped element is "<< int_stack[top] <<endl;
		top--;
	}
}
void display() {
	if(top>= 0) {
		cout<<"Stack elements are:";
		for(int i = top; i>= 0; i--)
			cout<<int_stack[i]<<" ";
		cout<<endl;
	} else
		cout<<"Stack is empty";
}
int testStack() {
	int ch, val;
	cout<<"1) Push in stack"<<endl;
	cout<<"2) Pop from stack"<<endl;
	cout<<"3) Display stack"<<endl;
	cout<<"4) Exit"<<endl;
	do {
		cout<<"Enter choice: "<<endl;
		cin>>ch;
		switch(ch) {
		case 1: {
			cout<<"Enter value to be pushed:"<<endl;
			cin>>val;
			push(val);
			break;
		}
		case 2: {
			pop();
			break;
		}
		case 3: {
			display();
			break;
		}
		case 4: {
			cout<<"Exit"<<endl;
			break;
		}
		default: {
			cout<<"Invalid Choice"<<endl;
		}
		}
	} while(ch != 4);
	return 0;
}

int testDequeue() {
	int c,i;
	dequeue d;
	do {
		cout<<"\n 1.insert at beginning";
		cout<<"\n 2.insert at end";
		cout<<"\n 3.show";
		cout<<"\n 4.deletion from front";
		cout<<"\n 5.deletion from rear";
		cout<<"\n 6.exit";
		cout<<"\n enter your choice:";
		cin>>c;
		switch(c) {
		case 1:
			cout<<"enter the element to be inserted";
			cin>>i;
			d.insert_at_beg(i);
			break;
		case 2:
			cout<<"enter the element to be inserted";
			cin>>i;
			d.insert_at_end(i);
			break;
		case 3:
			d.show();
			break;
		case 4:
			d.delete_fr_front();
			break;
		case 5:
			d.delete_fr_rear();
			break;
		case 6:
			exit(1);
			break;
		default:
			cout<<"invalid choice";
			break;
		}
	} while(c!=7);
	return 0;
}

const int ALPHA_SIZE = 26;

struct Trie {
	struct Trie *child[ALPHA_SIZE];
	bool endofstring; //It is true if node represents end of word.
};
struct Trie *createTrieNode(void) {
	struct Trie *tNode = new Trie;
	tNode->endofstring = false;
	for (int i = 0; i < ALPHA_SIZE; i++)
		tNode->child[i] = NULL;
	return tNode;
}
void insertTrieNode(struct Trie *root, string key) {
	struct Trie *curr = root;
	int slen = key.size();
	for (int i = 0; i < slen; i++) {
		int index = key[i] - 'A';
		if (!curr->child[index])
			curr->child[index] = createTrieNode();
		curr = curr->child[index];
	}
	curr->endofstring= true; //last node as leaf
}
bool searchTrieKey(struct Trie *root, string key) { //check if key is present in trie. If present returns true
	struct Trie *curr = root;
	int slen = key.size();
	for (int i = 0; i < slen; i++) {
		int index = key[i] - 'A';
		if (!curr->child[index])
			return false;
		curr = curr->child[index];
	}
	return (curr != NULL && curr->endofstring);
}
bool isEmptyTrieNode(Trie* root) {  //check if root has children or not
	for (int i = 0; i < ALPHA_SIZE; i++) {
		if (root->child[i]) {
			return false;
		}
	}
	return true;
}
Trie* deletionTrieNode(Trie* root, string key, int depth = 0) {
	//If tree is empty return null.
	int slen = key.size();
	if (!root)
		return NULL;
	if (depth == slen) { //If last character of key is being processed,
		if (root->endofstring) {
			root->endofstring = false; //then that node will be no more end of string after deleting it.
		}
		if (isEmptyTrieNode(root)) { //If given key is not prefix of any other string,
			delete (root);
			root = NULL;
		}
		return root;
	}
	//If key not last character,
	int index = key[depth] - 'A';
	root->child[index] =
			deletionTrieNode(root->child[index], key, depth + 1); //Then recur for the child which will be obtained by using ASCII value.
	if (isEmptyTrieNode(root) && root->endofstring == false) { //If root does not have any child leftand it is not end of another word
		delete (root);
		root = NULL;
	}
	return root;
}

int main() {
	int status = 0;

	status = testDequeue();

	return status;
}

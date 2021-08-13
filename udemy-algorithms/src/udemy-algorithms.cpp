//============================================================================
// Name        : udemy-algorithms.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : https://www.udemy.com/course/datastructurescncpp/learn/lecture
//============================================================================

#include <iostream>

using namespace std;

struct Array
{
	int A[10];
	int size;
	int length;
};

void Display(struct Array arr)
{
	int i;
	cout << "\nElements are:" << endl;
	for(i=0;i<arr.length;i++)
		cout << arr.A[i] << " ";
	cout << endl;
}

void swap(int *x,int *y)
{
	int temp=*x;
	*x=*y;
	*y=temp;
}

int BinarySearch(struct Array arr,int key)
{
	int l,mid,h;
	l=0;
	h=arr.length-1;
	while(l<=h)
	{
		mid=(l+h)/2;
		if(key==arr.A[mid])
			return mid;
		else if(key<arr.A[mid])
			h=mid-1;
		else
			l=mid+1;
	}
	return -1;
}

int RBinSearch(int a[],int l,int h,int key)
{
	int mid=0;
	if(l<=h)
	{
		mid=(l+h)/2;
		if(key==a[mid])
			return mid;
		else if(key<a[mid])
			return RBinSearch(a,l,mid-1,key);
	}
	else
		return RBinSearch(a,mid+1,h,key);
	return -1;
}

/*
 * Linked List Code
 * https://www.udemy.com/course/datastructurescncpp/learn/lecture/13145004#questions
 */
class ListNode
{
public:
	int data;
	ListNode *next;
};
class LinkedList
{
private:
	ListNode *first;
public:
	LinkedList(){first=NULL;}
	LinkedList(int A[],int n);
	~LinkedList();

	void Display();
	void Insert(int index,int x);
	int Delete(int index);
	int Length();
};
LinkedList::LinkedList(int A[],int n)
{
	ListNode *last,*t;
	int i=0;

	first=new ListNode;
	first->data=A[0];
	first->next=NULL;
	last=first;

	for(i=1;i<n;i++)
	{
		t=new ListNode;
		t->data=A[i];
		t->next=NULL;
		last->next=t;
		last=t;
	}
}
LinkedList::~LinkedList()
{
	ListNode *p=first;
	while(first)
	{
		first=first->next;
		delete p;
		p=first;
	}
}
void LinkedList::Display()
{
	ListNode *p=first;

	while(p)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}
int LinkedList::Length()
{
	ListNode *p=first;
	int len=0;

	while(p)
	{
		len++;
		p=p->next;
	}
	return len;
}
void LinkedList::Insert(int index,int x)
{
	ListNode *t,*p=first;

	if(index <0 || index > Length())
		return;
	t=new ListNode;
	t->data=x;
	t->next=NULL;

	if(index==0)
	{
		t->next=first;
		first=t;
	}
	else
	{
		for(int i=0;i<index-1;i++)
			p=p->next;
		t->next=p->next;
		p->next=t;
	}
}
int LinkedList::Delete(int index)
{
	ListNode *p,*q=NULL;
	int x=-1;

	if(index < 1 || index > Length())
		return -1;
	if(index==1)
	{
		p=first;
		first=first->next;
		x=p->data;
		delete p;
	}
	else
	{
		p=first;
		for(int i=0;i<index-1;i++)
		{
			q=p;
			p=p->next;
		}
		q->next=p->next;
		x=p->data;
		delete p;
	}
	return x;
}

// Linear search
struct ListNode * Search(struct ListNode *p,int key)
{
	struct ListNode *q;

	while(p!=NULL)
	{
		if(key==p->data)
		{
			return p;
		}
		p=p->next;
	}
	return NULL;

}

void Merge(struct ListNode *p,struct ListNode *q)
{
	struct ListNode *last;
	struct ListNode *third;

	if(p->data < q->data)
	{
		third=last=p;
		p=p->next;
		third->next=NULL;
	}
	else
	{
		third=last=q;
		q=q->next;
		third->next=NULL;
	}
	while(p && q)
	{
		if(p->data < q->data)
		{
			last->next=p;
			last=p;
			p=p->next;
			last->next=NULL;
		}
		else
		{
			last->next=q;
			last=q;
			q=q->next;
			last->next=NULL;
		}
	}
	if(p)last->next=p;
	if(q)last->next=q;

}
int main() {
	cout << "https://www.udemy.com/course/datastructurescncpp/learn/lecture" << endl; // prints https://www.udemy.com/course/datastructurescncpp/learn/lecture
	struct Array arr1={{2,3,9,16,18,21,28,32,35},10,9};
	cout << "Binary search for value 16 result index = ";
	cout << BinarySearch(arr1,16);
	Display(arr1);

	int A[]={1,2,3,4,5};
	int B[]={11,12,13,14,15};
	LinkedList l1(A,5);
	l1.Insert(3,10);
	cout << "Linked list create & insert:" << endl;
	l1.Display();

	return 0;
}

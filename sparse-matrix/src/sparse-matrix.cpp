//============================================================================
// Name        : sparse-matrix.cpp
// Author      : Carlos Navarrette
// Version     :
// Copyright   : I'll have 2 number 9s
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Element
{
public:
	int row;
	int col;
	int x;
};

class Sparse
{
private:
	int m_rows;
	int n_cols;
	int numElems;
	Element *ele;
public:
	Sparse(int m,int n,int num)
	{
		this->m_rows=m;
		this->n_cols=n;
		this->numElems=num;
		ele=new Element[this->numElems];
	}
	~Sparse()
	{
		delete [] ele;
	}

	Sparse operator+(Sparse &s);

	friend istream & operator>>(istream &is,Sparse &s);
	friend ostream & operator<<(ostream &os,Sparse &s);


};
Sparse Sparse::operator+(Sparse &s)
{
	int i,j,k;
	if(m_rows!=s.m_rows || n_cols!=s.n_cols)
		return Sparse(0,0,0);
	Sparse *sum=new Sparse(m_rows,n_cols,numElems+s.numElems);

	i=j=k=0;
	while(i<numElems && j<s.numElems)
	{
		if(ele[i].row<s.ele[j].row)
			sum->ele[k++]=ele[i++];
		else if(ele[i].row > s.ele[j].row)
			sum->ele[k++]=s.ele[j++];
		else
		{
			if(ele[i].col<s.ele[j].col)
				sum->ele[k++]=ele[i++];
			else if(ele[i].col > s.ele[j].col)
				sum->ele[k++]=s.ele[j++];
			else
			{
				sum->ele[k]=ele[i];
				sum->ele[k++].x=ele[i++].x+s.ele[j++].x;
			}
		}
	}
	for(;i<numElems;i++)sum->ele[k++]=ele[i];
	for(;j<s.numElems;j++)sum->ele[k++]=s.ele[j];
	sum->numElems=k;

	return *sum;

}
istream & operator>>(istream &is,Sparse &s)
{
	for(int i=0;i<s.numElems;i++)
		cin>>s.ele[i].row>>s.ele[i].col>>s.ele[i].x;
	return is;
}
ostream & operator<<(ostream &os,Sparse &s)
{
	int k=0;
	for(int i=0;i<s.m_rows;i++)
	{
		for(int j=0;j<s.n_cols;j++)
		{
			if(s.ele[k].row==i && s.ele[k].col==j)
				cout<<s.ele[k++].x<<" ";
			else
				cout<<"0 ";
		}
		cout<<endl;
	}
	return os;
}

int main()
{
	Sparse s1(5,5,5);
	Sparse s2(5,5,5);

	cout << "https://www.udemy.com/course/datastructurescncpp/learn/lecture" << endl; // prints https://www.udemy.com/course/datastructurescncpp/learn/lecture

	cout<<"Enter first matrix non-zero elements\n";
	cin>>s1;
	cout<<"Enter second matrix non-zero elements\n";
	cin>>s2;

	Sparse sum=s1+s2;

	cout<<"First Matrix"<<endl<<s1;
	cout<<"Second MAtrix"<<endl<<s2;
	cout<<"Sum Matrix"<<endl<<sum;

	return 0;
}


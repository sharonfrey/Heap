#include <iostream>

using namespace std;

class TNode
{
public:
	int val;
	TNode() { val = NULL; left = NULL; right = NULL; parent = NULL; }
	TNode(int v) { this->val = v; left = NULL; right = NULL; parent = NULL; }
	TNode * left;
	TNode * right;
	TNode * parent;
};



class minHeap // binary heap
{
	int size;
	TNode *top;

public:
	minHeap();
	minHeap(const minHeap &h);
	void in(const TNode *t);// you should new a new node and then add into the heap
	void removemin();
	TNode* getmin();
	void Heapify(const int n, const int *p);// p is an array of size n, representing a (full) binray tree of size n-1. (The tree starts at location 1). You should not modify the array p. 



	//Helper functions
	TNode* bubbleup(TNode *x);
	TNode* bubbledown(TNode *x);
	void swapnodes(TNode *n1, TNode *n2);
	TNode* convertpos(int position);
	void print(ostream &out);
};





int * HeapSort(const int n, const int *arr);// arr is an integer array of numbers.
										   //You should output a pointer to a new array which is a sorted version of arr



void Test()
{
	cout << "Binary Heap: " << endl;
	minHeap test;
	test.print(cout);
	cout << endl << "Min Value is:  " << test.getmin()->val << endl << endl << "New Heap: " << endl;
	test.removemin();
	test.print(cout);

	int *p = new int[12];
	p[0] = NULL;
	p[1] = 36;
	p[2] = 4;
	p[3] = 19;
	p[4] = 102; 
	p[5] = 14;
	p[6] = 31;
	p[7] = 59;
	p[8] = 3;
	p[9] = 1;
	p[10] = 99;
	p[11] = 27;

	cout << endl << "Sort Heap Array: " << endl;
	test.Heapify(11, p);
	test.print(cout);
	cout << endl << "Sort Array: " << endl;
	p = HeapSort(12, p);
	for (int i = 1; i < 12; i++)
		cout << p[i] << "   ";
	cout << endl;
}

int main(int argc, const char * argv[]) 
{

	Test();

	return 0;
}

//Task 1
minHeap::minHeap()
{
	size = 14;
	int num = 2;
	top = new TNode(1);
	for (int i = 2; i <= size; i++) 
	{ 
		if (i % 2 == 0)
			convertpos(i / 2)->left = new TNode(num);
		else
			convertpos(i / 2)->right = new TNode(num);
		convertpos(i)->parent = convertpos(i / 2);
		num++; 
	}
}
minHeap::minHeap(const minHeap &h)
{
	size = h.size;
	top = h.top;
}
void minHeap::in(const TNode *t)
{
	if ((size + 1) % 2 == 0)
		convertpos((size + 1) / 2)->left = new TNode(t->val);
	else
		convertpos((size + 1) / 2)->right = new TNode(t->val);
	convertpos(size + 1)->parent = convertpos((size + 1) / 2);
	size++;
	bubbleup(convertpos(size));
}
void minHeap::removemin()
{
	TNode *temp = convertpos(size);
	swapnodes(temp, top);
	
	temp->val = NULL;
	temp->parent = NULL;
	temp = NULL;
	size--;
	bubbledown(top);
}
TNode* minHeap::getmin()
{
	return top;
}

//Task 3
void minHeap::Heapify(const int n, const int *p)
{
	size = n;
	top = new TNode(p[1]);
	for (int i = 2; i <= n; i++)
	{
		if(i % 2 == 0)
			convertpos(i / 2)->left = new TNode(p[i]);
		else
			convertpos(i / 2)->right = new TNode(p[i]);
		convertpos(i)->parent = convertpos(i / 2);
		bubbleup(convertpos(i));
	}

}

//Task 4
int * HeapSort(const int n, const int *arr)
{	
	int *p = new int[n];
	for (int i = 0; i < n; i++)
		p[i] = arr[i];
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n - 1; j++) {
			if (p[j] > p[j + 1]) 
			{
				int t = p[j];
				p[j] = p[j + 1];
				p[j + 1] = t;
			}
		}
		
	}
	return p;
}

//Helper functions implemented	
TNode* minHeap::bubbleup(TNode *x)
{
	while (x->parent != NULL && x->val < x->parent->val)
	{
		swapnodes(x, x->parent);
		x = x->parent;
	}
	return x;
}
TNode* minHeap::bubbledown(TNode *x)
{
	int t = size;
	while ((x->left != NULL && x->right != NULL))
	{
		if (x->left->val < x->val)
		{
			swapnodes(x, x->left);
			x = x->left;
		}
		else if (x->right->val < x->val)
		{
			swapnodes(x, x->right);
			x = x->right;
		}
		else
			break;
	}
	return x;
}
void minHeap::swapnodes(TNode *n1, TNode *n2)
{
	int temp = n1->val;
	n1->val = n2->val;
	n2->val = temp;
}
TNode* minHeap::convertpos(int position)
{
	if (position == 0 || position == 1)
		return top;
	else if (convertpos(position / 2) == NULL)
		return convertpos(position / 2);
	else if (position % 2 == 1)
		return convertpos(position / 2)->right;
	else
		return convertpos(position / 2)->left;
}
void minHeap::print(ostream &out)
{
	TNode *w = top;
	for (int i = 1; i <= size; i++)
	{
		w = convertpos(i);
		if (w == NULL || w->val == NULL || w->val < 0)
			cout << "Position:  " << i << "       Empty Branch";
		else {
			cout << "Position:  " << i << "       Value:  " << w->val << "   ";
			if (w->parent != NULL)
				cout << "       Parent Position:  " << i / 2 << "       Parent Value:  " << w->parent->val;
		}
		cout << endl;
	}
}

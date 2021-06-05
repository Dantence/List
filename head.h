#pragma once
#include<iostream>
using namespace std;
template <typename t> class Node
{
public:
	t data;
	Node* next;
	Node* prev ;
};
template <typename T> class mylist:public Node<T>
{
public:
	void construct();					//构造list
	mylist();							//空list
	mylist(int size_of_list);			//指定大小的list
	mylist(initializer_list<T>ls);		//初始化列表
	mylist(int size_of_list, T val);	//指定大小的list和所有初始元素
	mylist(mylist& A);					//拷贝构造函数
	void push_back(T val);				//尾插
	void push_front(T val);				//头插
	void pop_back();					//尾弹
	void pop_front();					//首弹
	bool empty();						//判断list是否为空
	void resize(int n);					//调用resize(n)将list的长度改为只容纳n个元素，超出的元素将被删除。如果n比list原来的长度长，那么默认超出的部分元素置为0。
	void clear();						//清空所有元素
	void remove(T data);				//删除具有特定值的元素
	void reverse();						//反转list(迭代法）
	void assign(int n, T val);			//将list中的n个元素替换为val
	mylist<T>& assign(Node<T> *A, Node<T> *B);//将一定范围内的元素替换到list
	void merge(mylist<T> &A);			//将另一个list合并于本list中
	Node<T>* erase(Node<T>* it);				//删除某个元素
	Node<T>* erase(Node<T>* lhs, Node<T>* rhs);	//删除某个范围内的元素
	Node<T>* insert(Node<T>* it, T val);		//在某个位置插入一个元素
	Node<T>* insert(Node<T>* it, int n, T val); //某个位置插入n个元素
	T operator[](int n);				//重载[] 用于便捷访问list中的元素
	T operator*();						//重载* 用于解引用list的迭代器
	mylist<T> &operator++();			//前置递增
	mylist<T> &operator++(int);			//后置递增		
	mylist<T> &operator--();			//前置递减
	mylist<T> &operator--(int);			//后置递减
	mylist<T> &operator+=(int step);	//复合赋值运算符
	mylist<T> &operator-=(int step);	//复合赋值运算符
	void operator=(Node<T>* it);		//重载= 用来简化迭代器
	Node<T>* iterator;					//模拟迭代器
	Node<T>* begin();					//首迭代器，list第一个元素的位置
	Node<T>* end();						//尾迭代器，list最后一个元素之后一个位置
	Node<T>* rbegin();					//反向首迭代器
	Node<T>* rend();					//反向尾迭代器
	int size();							//获取list大小的接口
	T& back();							//返回第一个元素的值
	T& front();							//返回最后一个元素的值
	void display();						//用箭头显示该链表所有元素

private:
	int renew_len();					//获取当前list的大小
	int len;							//list的大小
	Node<T>* head;						//list的头结点（头结点数据域为空）
	Node<T>* tail;						//list的尾结点（尾结点是list的最后一个结点）
};
//construct函数用来构造list，在堆区开辟一个空间作为头结点，头结点的前驱和后继均初始化为空，迭代器初始化在头结点
//list长度初始化为0
template <class T>void mylist<T>::construct()
{
	head = new Node<T>;
	head->prev = nullptr;
	head->next = nullptr;
	iterator = head;
	len = 0;
}
//构造函数有4个版本，与STL的用法类似，基本方法是用尾插法插入结点
template <class T>mylist<T>::mylist()
{
	this->construct();
}
template <class T>mylist<T>::mylist(int size_of_list)
{
	this->construct();
	for (int i = 0; i < size_of_list; ++i)
	{
		this->push_back(0);
	}
}
template<class T>mylist<T>::mylist(initializer_list<T>ls)
{
	this->construct();
	for (auto& x : ls)
	{
		this->push_back(x);
	}
}
template<class T>mylist<T>::mylist(int size_of_list, T val)
{
	this->construct();
	for (int i = 0; i < size_of_list; ++i)
	{
		this->push_back(val);
	}
}
//拷贝构造函数，直接用assign函数完成
template<class T>mylist<T>::mylist(mylist& A)
{
	this->construct();
	this->assign(A.begin(), A.tail);
}
//尾插法，重要函数之一，方法是创建一个tmp结点，让tmp的前驱为尾结点，尾结点的后继为tmp，然后更新尾结点
//尾结点后继为空，list长度+1（如果当前list只有头结点，那么尾结点就是头结点）
template <class T> void mylist<T>::push_back(T val)
{
	if (head->next == nullptr)
	{
		tail = head;
	}
	Node<T>* tmp = new Node<T>;
	tmp->data = val;
	tmp->prev = tail;
	tail->next = tmp;
	tail = tmp;
	tail->next = nullptr;
	++len;
}
//头插法，重要函数之一，方法是创建一个tmp结点，让tmp的后继为当前头结点的后继，tmp的前驱为当前头结点
//头结点的后继的前驱为tmp，然后将头结点的后继更新为tmp
template <class T> void mylist<T>::push_front(T val)
{
	if (head->next == nullptr)
	{
		this->push_back(val);
	}
	else
	{
		Node<T>* tmp = new Node<T>;
		tmp->data = val;
		tmp->next = head->next;
		tmp->prev = head;
		head->next->prev = tmp;
		head->next = tmp;
	}
	++len;
}
//判断list是否为空，如果为空，返回1，否则返回0
template <class T> bool mylist<T>::empty()
{
	return size() ? false : true;
}
//模仿STL的resize函数，当resize的参数n小于当前list的长度时，将list的长度变为n，多出的元素被删除
//如果n大于当前list的长度，多出的元素将初始化为0
//这里我的做法是：分三种情况。第一种情况：n等于len，则什么也不做；第二种情况：n小于len，则先找到第n个结点
//然后将n+1~尾结点用erase函数全部删除
template <class T>void mylist<T>::resize(int n)
{
	Node<T>* p = head;
	int size = len;
	if (n == size)
	{
		return;
	}
	else if (n < size)
	{
		for (int i = 0; i < n; ++i)
		{
			p = p->next;
		}
		p = p->next;
		bool flag = true;
		while (flag)
		{
			if (p == tail)
			{
				flag = false;
			}
			p = erase(p);
		}
	}
	else if (n > size)
	{
		for (int i = 0; i < n - size; ++i)
		{
			push_back(0);
		}
	}
	renew_len();
}
//clear函数清空list，思想与erase类似，从头结点开始遍历至尾结点，每次先保存该结点的后继，然后删除该结点，更新后继续迭代
template <class T> void mylist<T>::clear()
{
	Node<T>* p = head;
	Node<T>* tmp;
	for (int i = 0; i < len; ++i)
	{
		tmp = p->next;
		delete p;
		p = tmp;
	}
	head->next = nullptr;
	renew_len();
}
//模仿STL的erase函数，提供2个版本，第一个版本参数为迭代器，删除该迭代器指向的元素，返回该迭代器的下一个迭代器
//第二个版本参数为两个迭代器，删除两个迭代器范围之间的元素，返回右侧迭代器的下一个迭代器
//主要方法：特判尾迭代器；将it的后继临时存储在tmp，然后让it的前驱的后继为it的后继，it后继的前驱为it的前驱
//删除it，返回tmp（即原it的下一个迭代器）
template <class T> Node<T>* mylist<T>::erase(Node<T>* it)
{
	if (it ->next==nullptr)
	{
		tail = tail->prev;
		it->prev->next = nullptr;
		delete it;
		renew_len();
		return tail->next;
	}
	else
	{
		Node<T>* tmp = it->next;
		it->prev->next = it->next;
		it->next->prev = it->prev;
		delete it;
		renew_len();
		return tmp;
	}

}
//有了第一个版本的erase，这个版本的erase无非是多删除几次，只是要注意边界条件
template <class T> Node<T>* mylist<T>::erase(Node<T>* lhs, Node<T>* rhs)
{
	Node<T>* p = lhs;
	bool flag = true;
	while (flag)
	{
		if (p == rhs)
		{
			flag = false;
		}
		else
		{
			p = erase(p);
		}
	}
	if (rhs->next==nullptr)
	{
		tail = lhs->prev;
	}
	renew_len();
	return p;
}
//更新list的长度
template <class T> int mylist<T>::renew_len()
{
	int j = 0;
	if (head->next == nullptr)
	{
		this->len = j;
		return j;
	}
	Node<T>* tmp = head;
	while (tmp ->next!=nullptr)
	{
		tmp = tmp->next;
		++j;
	}
	this->len = j;
	return j;
}
//用于得知list的长度
template <class T> int mylist<T>::size()
{
	try
	{
		if (len < 0)
		{
			throw runtime_error("The size of list cannot less than 0");
		}
		return len;
	}
	catch (runtime_error& err)
	{
		cout << err.what();
	}
}
//返回list的最后一个元素
template <class T>T& mylist<T>::back()
{
	return tail->data;
}
//返回list的第一个元素
template<class T>T& mylist<T>::front()
{
	return head->next->data;
}
//首迭代器，用Node<T>*模拟
template<class T> Node<T>* mylist<T>::begin()
{
	return head->next;
}
//尾后迭代器
template<class T>Node<T>* mylist<T>::end()
{
	return tail->next;
}
//反尾后迭代器
template<class T> Node<T>* mylist<T>::rend()
{
	return head;
}
//反首迭代器
template<class T>Node<T>* mylist<T>::rbegin()
{
	return tail;
}
//重载[]便于访问list中的元素
template<class T>T mylist<T>::operator[](int n)
{
	try
	{
		if (len == 0)
		{
			throw(runtime_error("error:The list is empty! "));
		}
	}
	catch (runtime_error& err)
	{
		cout << err.what();
	}
	Node<T>* p = head->next;
	for (int i = 0; i < n; ++i)
	{
		p = p->next;
	}
	return p->data;
}
//重载*（*list1表示list1当前迭代器所指向的元素）
template<class T>T mylist<T>::operator*()
{
	try
	{
		if (head->next == nullptr)
		{
			throw runtime_error("The list is empty!");
		}
		else
		{
			return iterator->data;
		}
	}
	catch (runtime_error& err)
	{
		cout << err.what() << endl;
	}
}
//重载前置递增运算符，用于递增迭代器
template<class T>mylist<T>& mylist<T>::operator++()
{
	this->iterator = this->iterator->next;
	return *this;
}
//重载前置递减运算符，用于递减迭代器
template<class T>mylist<T>&mylist<T>::operator--()
{
	if (iterator == end())
	{
		iterator = tail;
		return *this;
	}
	iterator = iterator->prev;
	return *this;
}
//重载后置递增运算符，用于递增迭代器，返回值为原迭代器
template<class T>mylist<T>& mylist<T>::operator++(int)
{
	mylist<T>tmp = *this;
	iterator = iterator->next;
	return tmp;
}
//重载后置递增运算符，用于递减迭代器，返回值为原迭代器
template<class T>mylist<T> &mylist<T>::operator--(int)
{
	if (iterator == end())
	{
		iterator = tail;
		return *this;
	}
	mylist<T>tmp = *this;
	iterator = iterator->prev;
	return tmp;
}
//重载复合赋值运算符+=，用于快速递增迭代器
template<class T>mylist<T> &mylist<T>::operator+=(int step)
{
	for (int i = 0; i < step; ++i)
	{
		++* this;
	}
	return *this;
}
//重载复合赋值运算符-=，用于快速递减迭代器
template<class T>mylist<T> &mylist<T>::operator-=(int step)
{
	for (int i = 0; i < step; ++i)
	{
		--* this;
	}
	return *this;
}
template<class T>void mylist<T>::operator=(Node<T>* it)
{
	this->iterator = it;
}
//模仿STL remove函数，这里只实现了一个简易版本，删除特定值的元素
//这里用erase模拟，每次遇到满足条件的元素，调用erase，并退回一个迭代器，防止越界
template<class T>void mylist<T>::remove(T data)
{
	if (len == 0)
	{
		cout << "The list is empty" << endl;
		return;
	}
	Node<T>* p = head;
	while (1)
	{
		p = p->next;
		if (p != tail)
		{
			if (p->data == data)
			{
				p = erase(p);
				--* this;
			}
		}
		if (p == tail)
		{
			break;
		}
	}
}
//用于直观地表现链表的特征，元素之间用箭头-->连接
template<class T>void mylist<T>::display()
{
	if (len == 0)
	{
		cout << "The list is empty" << endl;
		return;
	}
	Node<T>* p = head;
	while (1)
	{
		p = p->next;
		cout << p->data;
		if (p ->next!= nullptr)
		{
			cout << "-->";
		}
		if (p ->next == nullptr)
		{
			break;
		}
	}
	cout << endl;
}
//模仿STL的insert函数，重要函数之一，提供两个版本，第一个版本在it位置之前插入一个元素，返回新结点迭代器
//第二个版本在it位置插入n个元素，返回it迭代器
//第一个版本主要方法是：创建一个tmp结点，把it前驱的后继变为tmp，把tmp的后继变为it
//再把tmp的前驱变为it的前驱，最后把it的前驱变为tmp
//第二个版本用第一个版本多执行几次就行了
template<class T>Node<T>* mylist<T>::insert(Node<T>* it, T val)
{
	Node<T>* tmp = new Node<T>;
	tmp->data = val;
	it->prev->next = tmp;
	tmp->next = it;
	tmp->prev = it->prev;
	it->prev = tmp;
	renew_len();
	return tmp;
}
template<class T>Node<T>* mylist<T>::insert(Node<T>* it, int n, T val)
{
	Node<T>* tmp = it;
	for (int i = 0; i < n; ++i)
	{
		tmp = insert(tmp, val);
	}
	renew_len();
	return tmp;
}
//反转链表，重要函数之一，这里采用的方法是：先保存头结点的后继（作为反转后list的尾结点）
//从头结点的后继开始，用结点p迭代，每次先保存p的后继（p_next)，
//然后将p的后继变为p的前驱，p的前驱变为p的后继(p_next)，将p更新为p的后继(p_next)，
//最后再将头结点的后继，变为尾结点，尾结点的前驱变为头结点，更新尾结点，尾结点指向空
template <class T>void mylist<T>::reverse()
{
	Node<T>* p = head->next;
	Node<T>* newtail = head->next;
	while (p != nullptr)
	{
		Node<T>* p_next = p->next;
		p->next = p->prev;
		p->prev = p_next;
		p = p_next;
	}
	head->next = tail;
	tail->prev = head;
	tail = newtail;
	tail->next = nullptr;
}
//其实就是erase尾结点
template <class T>void mylist<T>::pop_back()
{
	this->erase(tail);
}
//其实就是erase头结点的后继
template <class T>void mylist<T>::pop_front()
{
	this->erase(head->next);
}
//模仿STL assign函数，将n个val元素赋给list，如果n小于list的长度，则将list的长度变为n，前n个元素全部变为val
//多余的元素被删除；如果n大于等于list的长度，则先将list的长度变为n，然后再把n个元素全部变为val
//运用resize函数可以快速模拟这一过程
template <class T>void mylist<T>::assign(int n, T val)
{
	this->resize(n);
	Node<T>* p = head;
	while (1)
	{
		p = p->next;
		p->data = val;
		if (p == tail)
		{
			break;
		}
	}
}
//assign重载版本，重要函数之一，可以将某个容器从A到B迭代器范围内的元素赋给本list
//如果B-A大于len，则先resize(B-A)，再赋值；如果B-A小于len，则直接赋值
//我这里偷懒，依然想用resize函数解决问题，主要是确定resize的参数
template <class T>mylist<T>& mylist<T>::assign(Node<T>* A, Node<T> *B)
{
	bool flag = true;
	Node<T>* p1 = head;
	Node<T>* p2 = A;
	int cnt = 0;
	while (flag)
	{
		if (p2 == B)
		{
			flag = false;
		}
		p2 = p2->next;							
		cnt++;
	}
	int safe_len;
	if (cnt >= len)
	{
		safe_len = cnt;
	}
	else
	{
		safe_len = len;
	}
	this->resize(safe_len);
	flag = true;
	p2 = A;
	while (flag)
	{
		if (p2 == B)
		{
			flag = false;
		}
		p1 = p1->next;
		p1->data = p2->data;
		p2 = p2->next;
	}
	return *this;
}
//merge用于合并两个list，这里只实现了一个简易版本
template <class T>void mylist<T>::merge(mylist &A)
{
	tail->next = A.head->next;	
	tail = A.tail;
	A.head->next = nullptr;
	A.renew_len();
	renew_len();
}

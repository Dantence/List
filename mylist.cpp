#include"mylist.h"
#include<string>
int main()
{
	mylist<int>L1;
	mylist<char>L2{ 'A','B','C'};
	mylist<string>L3{ "you","and","me" };
	mylist<double>L4(5, 3.14);
	
	L2.display();
	L3.display();
	L4.display();

	for (int i = 1; i <= 10; i++)
	{
		L1.push_back(i);
	}

	mylist<int>L5(L1);				//以L1来构造L5

	for (L1.iterator = L1.begin(); L1.iterator != L1.end(); ++L1)
	{
		cout << *L1 << " ";			//遍历并输出L1中的所有元素
	}
	for (int i = 1; i <= 10; i++)
	{
		L1.push_front(i);			//头插法向L1插入元素
	}
	cout << endl;
	L1.display();
	L1.remove(9);					//删除L1中值为9的元素
	L1.push_back(100);				//尾插100
	L1.pop_front();					//首弹
	L1.display();
	cout << L1.size() << endl;		//输出L1的大小
	L1.iterator = L1.begin();		//建立L1的模拟迭代器
	L1 += 5;
	L1.erase(L1.iterator);
	L1.display();
	L1.iterator = L1.end();
	L1 -= 2;
	auto it2 = L1.iterator;
	L1.iterator = L1.begin();
	L1 += 10;
	auto it1 = L1.iterator;
	L1.erase(it1, it2);			//it1指向L1的第11个元素，it2指向L1的倒数第二个元素
	L1.display();
	mylist<int>L6{ 1,2,3 };	
	L1.iterator = L1.begin();
	it1 = L1.iterator;
	L1 += 5;
	it2 = L1.iterator;
	cout << endl;
	L6.assign(it1, it2);		//it1指向L1的第1个元素，it2指向L1的第6个元素，把L1的第1个元素到第6个元素分配给L6
	cout << endl;
	L6.display();
	L1.display();
	L1.reverse();				//反转L1			
	L1.display();
	L1.merge(L5);				//将L1和L5合并于L1
	L1.display();
	cout << L1.back()<< endl;   //输出L1的最后一个元素
	L1.clear();					//清空L1
	cout << L1.empty();			//判断L1是否为空
	cout << endl << endl;

	cout << L2[1] << endl;		//输出L2的第2个元素
	L2.push_front('E');			//L2首插E
	L2.display();
	cout << endl;

	L3.push_back("love");		//L3尾插love
	L3.remove("and");			//L3去除and
	L3.display();
	cout << endl;

	L4.resize(2);				//将L4大小设置为2
	L4.display();
	L4.resize(5);				//将L4大小设置为5
	L4.display();
	L4.pop_back();				//尾弹L4
	L4.display();
	L4.pop_front();				//首弹L4
	L4.display();
	L4.insert(L4.begin(), 999);	//在L4首部插入999
	L4.iterator = L4.begin();	
	L4 += 3;
	L4.insert(L4.iterator, 3, 777);	//在L4的第4个元素位置插入3个777
	L4.display();
	cout << L4.size() << endl;	//输出L4大小
	L4.assign(7, 333);			//将7个333分配给L4
	L4.display();
}

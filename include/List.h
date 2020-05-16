//
// Created by zhichao on 2020/3/30.
//

#ifndef DSA_LEARNING_LIST_H
#define DSA_LEARNING_LIST_H
#include<iostream>


typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template<typename T>
struct ListNode {   //列表节点模板类（双向链表）
	T data;
	ListNodePosi(T)pred;
	ListNodePosi(T)succ; //数值，前驱，后继
	ListNode() {};  //针对header，trailer的构造
	ListNode(T e, ListNodePosi(T)p = NULL, ListNodePosi(T)s = NULL)
			: data(e), pred(p), succ(s) {} //默认构造器
	//操作接口
	ListNodePosi(T)insertAsPred(T const &e);

	ListNodePosi(T)insertAsSucc(T const &e);
};


template<typename T>
class List { //列表模板类

private:
	int _size;
	ListNodePosi(T)header;
	ListNodePosi(T)trailer;//规模，头尾哨兵
protected:
	void init(); //创建时初始化
	int clear();

	void copyNodes(ListNodePosi(T), int); //复制列表中自位置p起的n项
	void merge(ListNodePosi(T)&, int, List<T> &, ListNodePosi(T), int); //归并
	void mergeSort(ListNodePosi(T)&, int); //对从p开始的连续n个节点归并排序
	void selectionSort(ListNodePosi(T), int);

	void insertionSort(ListNodePosi(T), int);

public:
	List() { init(); } //默认
	List(List<T> const &L); //整体复制列表L
	List(List<T> const &L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNodePosi(T)p, int n);//复制列表L自p位置起的n项
	//析构函数
	~List(); //释放包含头、尾哨兵的所有节点
//只读访问接口
	Rank size() { return _size; }

	bool empty() const { return _size <= 0; }

	T &operator[](Rank r) const; //重载，支持循秩访问
	ListNodePosi(T)first() const { return header->succ; }  //首节点位置
	ListNodePosi(T)last() const { return trailer->pred; }  //末节点位置
	bool valid(ListNodePosi(T)p) //判断位置p是否合法
	{
		return p && (trailer != p) && (header != p);
	}

	int disordered() const; //判断列表是否已排序
	ListNodePosi(T)find(T const &e) const      //无序列表查找
	{
		return find(e, _size, trailer);
		//特别注意find是从尾往前找，这种特殊的语义要求，在后面的数据结构构建中我们会发现非常有用
	}

	ListNodePosi(T)find(T const &e, int n, ListNodePosi(T)p) const;     //无序区间查找
	ListNodePosi(T)search(T const &e) const //有序列表查找
	{
		return search(e, _size, trailer);
	}

	ListNodePosi(T)search(T const &e, int n, ListNodePosi(T)p) const; //有序区间查找p的n个前驱中查找(不包括p）
	ListNodePosi(T)selectMax(ListNodePosi(T)p, int n); //在p及其n个后继中选出最大者
	ListNodePosi(T)selectMax() {
		return selectMax(header->succ, _size);
	}
//可写访问接口
	ListNodePosi(T)insertAsFirst(T const &e); //将e当作首节点插入
	ListNodePosi(T)insertAsLast(T const &e); //将e当作尾节点插入
	ListNodePosi(T)insertA(ListNodePosi(T)p, T const &e); //将e当作p的后继插入
	ListNodePosi(T)insertB(ListNodePosi(T)p, T const &e); //将e当作p的前驱插入
	T remove(ListNodePosi(T)p); //删除合法位置p处的节点，返回被删除的节点值
	void merge(List<T> &L) {
		merge(first(), _size, L, L.first(), L._size);
	}

	void sort(ListNodePosi(T)p, int n); //列表区间排序
	void sort() { sort(first(), _size); } //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置
//遍历
	void traverse(void (*)(T &)); //遍历，使用函数指针进行只读或局部性修改
	template<typename VST>
	//操作器
	void traverse(VST &);//遍历，函数对象全局修改
};
#endif //DSA_LEARNING_LIST_H

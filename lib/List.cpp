//
// Created by zhichao on 2020/3/18.
//
#include<iostream>

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T> struct ListNode{   //列表节点模板类（双向链表）
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //数值，前驱，后继
	ListNode(){};  //针对header，trailer的构造
	ListNode(T e,ListNodePosi(T) p = NULL,ListNodePosi(T) s = NULL)
		: data(e),pred(p),succ(s){} //默认构造器
	//操作接口
	ListNodePosi(T) insertAsPred(T const& e);
	ListNodePosi(T) insertAsSucc(T const& e);
};


template <typename T> class List{ //列表模板类

private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;//规模，头尾哨兵
protected:
	void init(); //创建时初始化
	int clear();
	void copyNodes (ListNodePosi(T), int); //复制列表中自位置p起的n项
	void merge(ListNodePosi(T)&, int,List<T>&,ListNodePosi(T), int); //归并
	void mergeSort(ListNodePosi(T)&, int); //对从p开始的连续n个节点归并排序
	void selectionSort(ListNodePosi(T), int);
	void insertionSort(ListNodePosi(T), int);
public:
	List() {init();} //默认
	List(List<T> const& L); //整体复制列表L
	List(List<T> const& L,Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNodePosi(T) p ,int n);//复制列表L自p位置起的n项
	//析构函数
	~List() ; //释放包含头、尾哨兵的所有节点
//只读访问接口
	Rank size() {return _size;}
	bool empty() const {return _size<=0;}
	T& operator[] (Rank r) const; //重载，支持循秩访问
	ListNodePosi(T) first() const {return header->succ;}  //首节点位置
	ListNodePosi(T) last() const {return trailer->pred;}  //末节点位置
	bool valid (ListNodePosi(T) p) //判断位置p是否合法
	{
		return p && (trailer != p) && (header != p);
	}
	int disordered() const; //判断列表是否已排序
	ListNodePosi(T) find(T const& e) const      //无序列表查找
	{
		return find(e,_size,trailer);
		//特别注意find是从尾往前找，这种特殊的语义要求，在后面的数据结构构建中我们会发现非常有用
	}
	ListNodePosi(T) find(T const& e,int n,ListNodePosi(T) p) const;     //无序区间查找
	ListNodePosi(T) search(T const& e) const //有序列表查找
	{
		return search(e,_size,trailer);
	}
	ListNodePosi(T) search(T const& e, int n,ListNodePosi(T) p) const; //有序区间查找p的n个前驱中查找(不包括p）
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) ; //在p及其n个后继中选出最大者
	ListNodePosi(T) selectMax() {
		return selectMax(header->succ,_size);
	}
//可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e); //将e当作首节点插入
	ListNodePosi(T) insertAsLast (T const& e); //将e当作尾节点插入
	ListNodePosi(T) insertA(ListNodePosi(T) p,T const& e); //将e当作p的后继插入
	ListNodePosi(T) insertB(ListNodePosi(T) p,T const& e); //将e当作p的前驱插入
	T remove(ListNodePosi(T) p); //删除合法位置p处的节点，返回被删除的节点值
	void merge(List<T>& L){
		merge(first(),_size,L,L.first(),L._size);
	}
	void sort(ListNodePosi(T)p,int n); //列表区间排序
	void sort() { sort(first(),_size);} //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置
//遍历
	void traverse ( void (*)(T&)); //遍历，使用函数指针进行只读或局部性修改
	template <typename VST>//操作器
	void traverse(VST &);//遍历，函数对象全局修改
};

template <typename T> void List<T>:: init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

template<typename T> T& List<T>::operator[](Rank r) const { //循秩访问
	ListNodePosi(T) p = first();
	while(0 < r--) p = p->succ;
	return p->data;
}

//无序查找
template <typename T>
ListNodePosi(T) List<T>:: find(T const& e,int n,ListNodePosi(T) p) const{
	while(0 < n--)
		if(e == (p = p->pred->data)) return p;
	return NULL;
}

//插入
template<typename T> ListNodePosi(T) List<T>:: insertAsFirst(const T &e) {
	_size++;
	return header->insertAsSucc(e); //e当作首节点插入
}

template<typename T> ListNodePosi(T) List<T>::insertAsLast(const T &e) {
	_size++;
	return trailer->insertAsPred(e);//e当作末节点插入
}

template<typename T> ListNodePosi(T) List<T>:: insertA(ListNodePosi(T) p,T const& e){
	_size++;    return p->insertAssucc(e);  //e当作p的后继插入
}

template<typename T>ListNodePosi(T)List<T>::insertB(ListNodePosi(T) p, T const &e) {
	_size++;    return p->insertAspred(e);  //e当作p的前驱插入
}
//前插入
template <typename T> ListNodePosi(T) ListNode<T>:: insertAsPred(const T &e) {
	ListNodePosi(T) x = new ListNode(e,pred,this);
	pred->succ = x; pred = x;
	return x;
}
//后插入
template<typename T> ListNodePosi(T)  ListNode<T>::insertAsSucc(const T &e) {
	ListNodePosi(T)x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
//copy
template<typename T> void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init();  //创建头尾哨兵及初始化
	while(n--) {
		insertAsLast(p->data);
		p = p->succ;
	}
}
//基于复制的构造方法
template<typename T> List<T>:: List(ListNodePosi(T) p,int n){   //复制p位置起的n项
	//assert：p为合法位置，且至少有n-1个后继节点
	copyNodes(p,n);
}

template<typename T> List<T>:: List(List<T>const& L){   //整体复制列表
	copyNodes(L,L._size);
}

template<typename T> List<T>:: List(List<T>const& L,int r,int n){//复制L自第r项起的n项
	copyNodes(L[r],n);
}

//remove
template<typename T> T List<T>:: remove(ListNodePosi(T) p) {//删除节点，返回数值
	T e = p->data;
	p->pred->succ = p->succ; p->succ->pred = p->pred;
	delete p; _size--;
	return e;
}

//析构
template<typename T> List<T>:: ~List(){
	clear(); delete header; delete trailer;
}

template<typename T> int List<T>:: clear(){
	int oldSize = _size;
	while(0<_size) remove(header->succ); //反复删除节点，直到列表变空
	return oldSize;
}

//无序列表唯一化
template<typename T> int List<T>:: deduplicate() {
	if (_size < 2) return 0;//平凡情况
	int oldSize = _size;//记录原规模
	ListNodePosi(T) p = header; Rank r = 0;
	while (trailer != (p = p->succ)){
		ListNodePosi(T) q = find(p->data,r,p); //在p的r个前驱中找雷同者
		q? remove(q):r++;
	}
	return oldSize - _size;
}
//有序列表唯一化
template<typename T> int List<T>:: uniquify() {
	if (_size < 2 ) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first(); ListNodePosi(T) q;
	while(trailer != (q = p->succ))     //反复考察紧邻的节点对(p,q)
		p->data != q->data ? p=q:remove(q);//若p，q数据不同，则再从q开始
	return oldSize - _size;
}

//遍历，借助函数指针
template<typename T> void List<T>:: traverse(void (*visit)(T&)) {
	for(ListNodePosi(T) p = header->succ; p != trailer; p=p->succ)
		visit(p->data);
}
//遍历，借助函数对象
template<typename T> template<typename VST>
void List<T>:: traverse(VST & visit) {
	for (ListNodePosi(T)p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

//顺序查找——无序
template<typename T> ListNodePosi(T) List<T>:: search(T const& e,int n,ListNodePosi(T) p) const{
	while (0 <= n--){    //从右向左逐个比较
		if((p = p->pred)->data <= e) break;//在p的n个前驱中（不包括p）返回小于等于e的最大位置
	}
	return p;
}

//排序
template<typename T> void List<T>:: sort(ListNodePosi(T) p , int n){
	switch (rand()%3) {
		case 1:insertionSort(p,n); break;
		case 2:selectionSort(p,n); break;
		default:mergeSort(p,n); break;
	}
}
//插入排序，对起始于p的n个元素排序(包括n)  默认语义规定是前闭后开
template<typename T> void List<T>:: insertionSort(ListNodePosi(T) p, int n){
	//valid(p) && rank(p)+n <= _size
	for(int r = 0; r<n; r++){
		insertA(serach(p->data,r,p),p->data);
		p = p->succ; remove(p->pred);
	}
}

//选择排序，对起始于p的n个元素排序(包括n)
template<typename T> void List<T>::selectionSort(ListNodePosi(T) p, int n){
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for(int i=0; i < n; i++) tail = tail->succ; //待排序区间为(head,tail)
	while( 1<n ) {
		ListNodePosi(T) max = selectMax(head->succ,n); //找出最大者(歧义时后者优先)
		insertB(tail,remove(max)); //将最大元素移至无序区间的末尾（作为有序区间的新的首元素）
		//我们可见remove接口返回值的便利
		tail = tail->pred; n--;
	}
}
//从起始于p的n个元素选出最大者
template <typename T> ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; 1<n; n--){
		if (!lt((cur = cur->succ)->data,max->data)) max = cur;
	}return max;
}

//归并排序 :当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
template<typename T>
void List<T>:: merge(ListNodePosi(T) &p,int n,List<T>& L,ListNodePosi(T) q,int m) {
//assert: this.valid(p) && rank(p) + n <= size && this.sorted(p,n)
//        L.valid(q) && rank(q) + m <= L._size && L.sorted(q,m)
// 注意：在归并排序之类的场合，有可能this == L && rank(p) + n = rank(q)
	ListNodePosi(T) pp = p->pred;  //保存新序列的头位置
	while( 0<m ){
		if(( 0 < n ) && (p->data <= q->data)){
			if ( q == ( p = p->succ ))  break; n--;
			//如果相等，说明 this == L && rank(p) + n >= rank(q)，其后不需要再进行排序
		}else {
			insertB(p,L.remove( ( q = q->succ )->pred)); m--;
		}
	} p = pp->succ; //重新让p成为新序列的起点
}
//列表的归并排序：起始于p的n个元素排序
template <typename T>
void List<T>:: mergeSort(ListNodePosi(T) & p,int n){
	if ( n < 2 ) return ;
	int m = n>>1;
	ListNodePosi(T) q = p;
	for( int i = 0; i < m; i++)    q = q->succ; //以m为界，均分列表
	mergeSort(p,m); mergeSort(q,n - m);
	merge(p,m,*this,q,n-m); //归并
}//注意：排序后，p依然指向归并后区间的新起点（正因为此p传入的是引用）
//
// Created by zhichao on 2020/3/14.
//
#include<iostream>
typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class Vector{
	T* _elem; Rank _size; int _capacity;
protected:
	void copyFrom(T const* A,Rank lo,Rank hi);
	void expand();
	void shrink();
	void bubbleSort(Rank lo,Rank hi);
	Rank bubble1(Rank ,Rank);
	Rank bubble2(Rank, Rank);
	void merge(Rank lo,Rank mi,Rank hi);
	void mergeSort(Rank lo,Rank hi);
	Rank partition(Rank lo,Rank hi); //轴点构造算法
	void quickSort(Rank lo,Rank hi);
	void heapSort(Rank lo,Rank hi);

public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY,int s = 0, T v=0)  //容量为c，规模为s，所有元素初始为v
	{
		_elem = new T[_capacity];
		for(_size = 0;_size < s;_elem[_size++] = v);
	}
	Vector(T const*A ,Rank n){          //数组整体复制
		copyFrom(A,0,n);
	}
	Vector(T const*A,Rank lo,Rank hi){      //区间复制
		copyFrom(A,lo,hi);
	}
	Vector(Vector<T> const& V){             //向量整体复制
		copyFrom(V._elem,0,V._size);
	}
	Vector(Vector<T> const&V,Rank lo,Rank hi){
		copyFrom(V._elem,lo,hi);
	}
	// 析构函数
	~Vector(){   delete []_elem;}
	//只读访问接口
	Rank size() const {    return _size; }
	bool empty() const {return !_size;}
	int disordered() const; //判断向量是否已经有序
	Rank find(T const& e) const {
		return find(e,0,_size);
	}
	Rank find(T const& e,Rank lo,Rank hi)const;
	Rank search(T const& e) const{
		return (0>=_size)? -1:search (e,0,_size);
	}
	Rank search(T const& e,Rank lo,Rank hi) const;
	//可写访问接口
	T& operator[](Rank r) const; //重载下标操作符，可以类似于数组形式引用各元素
	Vector<T> & operator= (Vector<T> const&); //重载赋值操作符，以便直接克隆向量
	T remove(Rank r); //删除秩为r的元素
	int remove(Rank lo,Rank hi); //删除秩在区间[lo,hi)的元素
	Rank insert(Rank r,T const&e); //插入元素
	Rank insert(T const& e){            //默认作为末位元素插入
		return insert(_size,e);
	}
	void sort(Rank lo,Rank hi);
	void sort(){sort(0,_size);} //整体排序
	void unsort(Rank lo,Rank hi); //对[lo,hi)置乱
	void unsort(){
		unsort(0,_size);        //整体置乱
	}
	int deduplicate(); //无序去重
	int uniquify();    //有序去重
//遍历  注意两个函数的声明都没有参数名称，这是允许的
    void traverse(void(*)(T&)); //遍历（使用函数指针，只读或者局部性修改） 需要先定义
    template <typename VST> void traverse(VST&); //遍历（使用函数对象，全局修改——使用&）
};

template <typename T>
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi){
	_elem = new T[_capacity = 2*(hi-lo)]; _size = 0;
	while(lo<hi)
		_elem[_size++]  = A[lo++];
}

template <typename T> Vector<T>& Vector<T>:: operator= (Vector<T> const& V){
	if(_elem) delete []_elem;       //释放原有内容
	copyFrom(V._elem,0,V.size());
	return *this;    //返回当前对象的引用，以便链式赋值
}

//扩容   在每次调用insert接口时都先调用expand，检查容量  算法本身O(1)的分摊时间,但是单次扩容时间复杂度高达Ω(n)\
所以对单次操作的执行速度十分敏感的场合并不适用
template <typename T> void Vector<T>::expand(){
	if(_size < _capacity) return ;//尚未满员时,不必扩容
	if( _capacity < DEFAULT_CAPACITY)   _capacity = DEFAULT_CAPACITY; //不低于最小容量
	T *oldElem = _elem; _elem = new T[_capacity<<=1]; //容量加倍
	for(int i = 0; i<_size; i++)
		_elem[i] = oldElem[i]; //复制原向量内容
	delete [] oldElem;
}

//缩容(避免下溢)，一般并不需要,这里选择25%为阙值\
  但实际中为避免出现频繁交替扩容和缩容的情况，可以选择更低的阙值，甚至0
template <typename T> void Vector<T>::shrink(){   //装填因子过小时压缩向量所占的内存空间
	if (_capacity < DEFAULT_CAPACITY << 1) return ;  //不致收缩到DEFAULT_CAPACITY之下
	if (_size<<2 > _capacity) return; //以25%为界
	T *oldElem = _elem; _elem = new T[_capacity >>= 1]; //oldElem记住了elem的地址在结尾时释放，容量减半
	for (int i=0; i < _size; i++) _elem[i] = oldElem[i];
	delete []oldElem;
}

//直接引用元素
template <typename T> T& Vector<T> :: operator[] (Rank r)const
{
	return _elem[r];
}

//置乱器——非成员函数\
理论上permute可以得到同一向量的所有可能的排列，而且能保证生成各种排列的概率均等
template <typename T> void permute(Vector<T>& V){
	for(int i=V.size(); i>0; i++){
		swap(V[i-1],V[rand()%i]);       //iostream 内置了swap,rand
	}
}
//为了便于各种向量算法的测试和比较，这里不妨将permute封装至向量的ADT中
template <typename T> void Vector<T>:: unsort(Rank lo,Rank hi){
	T *V = _elem+lo;
	for(Rank i = hi-lo; i>0; i--){
		swap(V[i-1],V[rand()%i]);
	}
}
//判等器与比较器
template <typename T> static bool lt(T*a,T*b) {return lt(*a,*b);}
template <typename T> static bool lt(T&a,T&b) {return a<b;}
template<typename T>  static bool eq(T *a, T *b) { return eq(*a, *b); }
template<typename T>  static bool eq(T &a, T &b) { return a == b; }

//无序查找  仅支持比对，未必支持比较的向量，称为无序向量\
在无序向量中查找任意指定元素时，因为没有更多信息可以借助，所以采用逐个比对的查找方式
template <typename T>
Rank Vector<T>:: find(T const&e,Rank lo,Rank hi) const {
	while(( lo < hi--)&&(e!=_elem[hi]));  //这里采用了从后向前的查找次序，查找失败统一返回-1，同时也符合了语义要求
	return hi;
}

//插入
template <typename T> Rank Vector<T>:: insert(Rank r,const T& e){
	expand(); //若有必要扩容
	for(int i = _size; i>r; i--)    _elem[i] = _elem[i-1]; //自后向前，后继元素顺次后移一个单元一个单元
	_elem[r] = e; _size++;
	return r; //返回秩
}

//删除
template <typename T> int Vector<T>:: remove(Rank lo,Rank hi){          //删除区间[lo,hi)
	if (lo==hi) return 0;   //出于效率考虑，单独处理退化情况
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();   //若有必要，缩容
	return hi - lo;
}
//利用以上remove接口，通过重载即可实现另一同名函数
template <typename T> T Vector<T>:: remove(Rank r){
	T e = _elem[r]; //备份
	remove (r,r+1); //等效于删除[r,r+1)
	return e;
}

//唯一化,视向量是否有序有两种实现方式
//无序向量
template <typename T> int Vector<T>:: deduplicate() {
	int oldSize = _size;
	Rank i =1;
	while (i < _size)
		(find(_elem[i],0,i) < 0) ? i++: remove(i); //remove后自然不需要增加i
	return oldSize - _size;
}
//有序向量
template <typename T> int Vector<T>:: uniquify(){
	Rank i = 0,j = 0;   //各对互异“相邻”元素
	while (++j < _size)
		if (_elem[i] != _elem[j])       //当发现不同元素时，向前移至前者右侧
			_elem[i++] = _elem[j];
		_size = ++i; shrink();
		return j-i;
}

//遍历，类似于map
template <typename T> void Vector<T> :: traverse( void (*visit) (T&)) {
	for( int i=0; i < _size; i++)   visit(_elem[i]);
}
//函数对象的使用范围更广，比如函数对象的形式支持对向量元素的关联性修改（可以根据某些元素相应的修改另一元素）
//也就是能利用的别的对象的内部成员
// 这样的函数对象可以使用struct来定义
template <typename T> template <typename VST> //元素类型，操作器
void Vector<T>:: traverse(VST & visit) {
	for (int i = 0; i < _size; i++) visit(_elem[i]);
}

//有序向量甄别  向量是无序的，当且仅当存在无序对
template <typename T> int Vector<T> :: disordered() const {
	int n = 0;
	for (int i = 1; i<_size; i++) {
		if (_elem[i-1] > _elem[i])  n++;
	}
	return n;
}

//查找
template <typename T> Rank Vector<T>:: search(T const& e, Rank lo,Rank hi)const {
	switch(rand() % 2){
		case 1: return binSearch(_elem, e, lo, hi);
		case 2: return insertSearch(_elem, e, lo, hi);
	}

}
//p56
template <typename T> static Rank binSearch(T* A,T const& e,Rank lo,Rank hi){
	while (lo < hi) {
		Rank mi = (lo+hi) >> 1;
		(e < A[mi]) ? hi = mi: lo = mi+1; //经比较确定深入[lo,mi)或(mi，hi)
	}   //成功查找不能提前终止，终止时lo = hi
	return --lo;  //考察循环终止时，lo-1是不大于e的区间的最后一个元素，lo是大于e的区间的第一个元素
}

//排序
//冒泡排序*改
template <typename T> void Vector<T>:: bubbleSort(Rank lo,Rank hi){
	while((lo = bubble1(lo,hi)) < (hi = bubble2(lo,hi)));
}

template<typename T> Rank Vector<T>::  bubble1(Rank lo,Rank hi){
	Rank last = hi;
	while(--hi > lo){
		if(_elem[hi-1] > _elem[hi]){
			last = hi;
			swap(_elem[hi-1],_elem[hi]);
		}
	}return last;
}

template<typename T> Rank Vector<T>:: bubble2(Rank lo, Rank hi) {
	Rank last = lo;
	while(++lo < hi){
		if(_elem[lo-1]>_elem[lo]){
			last = lo;
			swap(_elem[lo-1],_elem[lo]);
		}
	}return last;
}
//归并排序  O(nlogn)
template <typename T> void Vector<T> :: mergeSort(Rank lo,Rank hi){
	if (hi-lo < 2) return ;     //自然有序
	int mi = hi+lo >> 1;
	mergeSort(lo,mi); mergeSort(mi,hi);
	merge(lo,mi,hi);
}
template <typename T> void Vector<T> :: merge(Rank lo,Rank mi,Rank hi){
	T* A = _elem + lo;
	int lb = mi-lo; T* B = new T[lb];
	for ( Rank i = 0; i<lb; B[i] = A[i++]);  //临时数组B，复制前子向量
	int lc = hi-mi; T* C = _elem+mi;
	for(Rank i = 0,j = 0,k = 0; j<lb;){
		if (k > lc || B[j]<=C[k]) A[i++] = B[j++];
		if (k > lc && C[k]<B[j] ) A[i++] = C[k++];
	}
}
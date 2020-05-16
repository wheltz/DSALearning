//
// Created by zhichao on 2020/3/30.
//

#ifndef DSA_LEARNING_VECTOR_H
#define DSA_LEARNING_VECTOR_H
typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector {
	T *_elem;
	Rank _size;
	int _capacity;
protected:
	void copyFrom(T const *A, Rank lo, Rank hi);

	void expand();

	void shrink();

	void bubbleSort(Rank lo, Rank hi);

	Rank bubble1(Rank, Rank);

	Rank bubble2(Rank, Rank);

	void merge(Rank lo, Rank mi, Rank hi);

	void mergeSort(Rank lo, Rank hi);

	Rank partition(Rank lo, Rank hi); //轴点构造算法
	void quickSort(Rank lo, Rank hi);

	void heapSort(Rank lo, Rank hi);

public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)  //容量为c，规模为s，所有元素初始为v
	{
		_elem = new T[_capacity];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}

	Vector(T const *A, Rank n) {          //数组整体复制
		copyFrom(A, 0, n);
	}

	Vector(T const *A, Rank lo, Rank hi) {      //区间复制
		copyFrom(A, lo, hi);
	}

	Vector(Vector<T> const &V) {             //向量整体复制
		copyFrom(V._elem, 0, V._size);
	}

	Vector(Vector<T> const &V, Rank lo, Rank hi) {
		copyFrom(V._elem, lo, hi);
	}

	// 析构函数
	~Vector() { delete[]_elem; }

	//只读访问接口
	Rank size() const { return _size; }

	bool empty() const { return !_size; }

	int disordered() const; //判断向量是否已经有序
	Rank find(T const &e) const {
		return find(e, 0, _size);
	}

	Rank find(T const &e, Rank lo, Rank hi) const;

	Rank search(T const &e) const {
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}

	Rank search(T const &e, Rank lo, Rank hi) const;

	//可写访问接口
	T &operator[](Rank r) const; //重载下标操作符，可以类似于数组形式引用各元素
	Vector<T> &operator=(Vector<T> const &); //重载赋值操作符，以便直接克隆向量
	T remove(Rank r); //删除秩为r的元素
	int remove(Rank lo, Rank hi); //删除秩在区间[lo,hi)的元素
	Rank insert(Rank r, T const &e); //插入元素
	Rank insert(T const &e) {            //默认作为末位元素插入
		return insert(_size, e);
	}

	void sort(Rank lo, Rank hi);

	void sort() { sort(0, _size); } //整体排序
	void unsort(Rank lo, Rank hi); //对[lo,hi)置乱
	void unsort() {
		unsort(0, _size);        //整体置乱
	}

	int deduplicate(); //无序去重
	int uniquify();    //有序去重
//遍历  注意两个函数的声明都没有参数名称，这是允许的
	void traverse(void(*)(T &)); //遍历（使用函数指针，只读或者局部性修改） 需要先定义
	template<typename VST>
	void traverse(VST &); //遍历（使用函数对象，全局修改——使用&）
};
#endif //DSA_LEARNING_VECTOR_H

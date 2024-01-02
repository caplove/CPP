
// Callable Object(�Լ���ü) --> std::function
// C++������ ()�� �ٿ��� ȣ���� �� �ִ� ��ü�� Callable Object��� �Ѵ�.
// ���ϰ��� �Լ����ڸ� ������ ����.
// ���� :    std::function<����Ÿ��(����Ÿ��)> �Լ���;
// 
// ���� :    std::function<int(int)> f1 = some_func1 // �Ϲ��Լ��� �Լ���ü��
//           std::function<void(char)> f2 = S() // Ŭ����, ����ü�� �Լ���ü��
//           std::function<void()> f3 = []()  // ����ǥ������ �Լ���ü��




#include <functional>
#include <iostream>
#include <string>

int some_func1(const std::string& a) {
	std::cout << "Func1 ȣ��! " << a << std::endl;
	return 0;
}

struct S {
	void operator()(char c) { std::cout << "Func2 ȣ��! " << c << std::endl; }
};

void main1() {
	std::function<int(const std::string&)> f1 = some_func1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() { std::cout << "Func3 ȣ��! " << std::endl; };

	f1("hello");
	f2('c');
	f3();
}




class A {
	int c;

public:
	A(int c) : c(c) {}
	int some_func() {
		std::cout << "���� �Լ�: " << ++c << std::endl;
		return c;
	}

	int some_const_function() const {
		std::cout << "��� �Լ�: " << c << std::endl;
		return c;
	}

	static void st() {}
};

void main2() {
	A a(5);
	std::function<int(A&)> f1 = &A::some_func; // &�� ���̴� ������ �ɹ��Լ��� ���� ��������� �ּҸ� �����;� �Ѵ�.
	std::function<int(const A&)> f2 = &A::some_const_function;

	f1(a); // ����Ÿ��:int, ����Ÿ��:A&
	f2(a); // ����Ÿ��:int, ����Ÿ��:const A&
};



// transform�� mem_fn�� ����ϸ� �Լ���ü�� ������ �ʰ� ����Լ��� ȣ���� �� �ִ�.
// transform : �����̳��� ��� ���ҿ� ���� �Լ��� �����Ѵ�.
// mem_fn : ����Լ��� �Լ���ü�� ��ȯ�Ѵ�.
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using std::vector;


void main3() {
	vector<int> a(1);
	vector<int> b(2);
	vector<int> c(3);
	vector<int> d(4);

	vector<vector<int>> container;
	container.push_back(a);
	container.push_back(b);
	container.push_back(c);
	container.push_back(d);

	vector<int> size_vec(4);

	//// 1. �Ϲ����� ���
	//std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
	//std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);

	//// 2. mem_fn�� ����� ���
	//transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size));

	// 3. ����ǥ������ ����� ���
	transform(container.begin(), container.end(), size_vec.begin(), [](const vector<int>& v) { return v.size(); });


	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "���� ũ�� :: " << *itr << std::endl;
	}
};


// bind : �Լ��� Ư�����ڸ� �ٿ�, ���ο� �Լ���ü�� �����.
// ���� : std::bind(�Լ���ü, ����1, ����2, ...)

void add(int x, int y) {
	std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
	std::cout << x << " - " << y << " = " << x - y << std::endl;
}
void main4() {
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
	add_with_2(3);

	// �� ��° ���ڴ� ���õȴ�.
	add_with_2(3, 4);

	auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
	auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_from_2(3);  // 3 - 2 �� ����Ѵ�.
	negate(4, 2);        // 2 - 4 �� ����Ѵ�
}


void main() {
	main1();
	main2();
	main3();
	main4();
}	
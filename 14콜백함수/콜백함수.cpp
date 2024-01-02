
// Callable Object(함수객체) --> std::function
// C++에서는 ()를 붙여서 호출할 수 있는 객체를 Callable Object라고 한다.
// 리턴값과 함수인자를 가지고 있음.
// 정의 :    std::function<리턴타입(인자타입)> 함수명;
// 
// 생성 :    std::function<int(int)> f1 = some_func1 // 일반함수를 함수객체로
//           std::function<void(char)> f2 = S() // 클래스, 구조체를 함수객체로
//           std::function<void()> f3 = []()  // 람다표현식을 함수객체로




#include <functional>
#include <iostream>
#include <string>

int some_func1(const std::string& a) {
	std::cout << "Func1 호출! " << a << std::endl;
	return 0;
}

struct S {
	void operator()(char c) { std::cout << "Func2 호출! " << c << std::endl; }
};

void main1() {
	std::function<int(const std::string&)> f1 = some_func1;
	std::function<void(char)> f2 = S();
	std::function<void()> f3 = []() { std::cout << "Func3 호출! " << std::endl; };

	f1("hello");
	f2('c');
	f3();
}




class A {
	int c;

public:
	A(int c) : c(c) {}
	int some_func() {
		std::cout << "비상수 함수: " << ++c << std::endl;
		return c;
	}

	int some_const_function() const {
		std::cout << "상수 함수: " << c << std::endl;
		return c;
	}

	static void st() {}
};

void main2() {
	A a(5);
	std::function<int(A&)> f1 = &A::some_func; // &를 붙이는 이유는 맴버함수의 경우는 명시적으로 주소를 가져와야 한다.
	std::function<int(const A&)> f2 = &A::some_const_function;

	f1(a); // 리턴타입:int, 인자타입:A&
	f2(a); // 리턴타입:int, 인자타입:const A&
};



// transform과 mem_fn을 사용하면 함수객체를 만들지 않고도 멤버함수를 호출할 수 있다.
// transform : 컨테이너의 모든 원소에 대해 함수를 적용한다.
// mem_fn : 멤버함수를 함수객체로 변환한다.
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

	//// 1. 일반적인 방법
	//std::function<size_t(const vector<int>&)> sz_func = &vector<int>::size;
	//std::transform(container.begin(), container.end(), size_vec.begin(), sz_func);

	//// 2. mem_fn을 사용한 방법
	//transform(container.begin(), container.end(), size_vec.begin(), std::mem_fn(&vector<int>::size));

	// 3. 람다표현식을 사용한 방법
	transform(container.begin(), container.end(), size_vec.begin(), [](const vector<int>& v) { return v.size(); });


	for (auto itr = size_vec.begin(); itr != size_vec.end(); ++itr) {
		std::cout << "벡터 크기 :: " << *itr << std::endl;
	}
};


// bind : 함수에 특정인자를 붙여, 새로운 함수객체를 만든다.
// 정의 : std::bind(함수객체, 인자1, 인자2, ...)

void add(int x, int y) {
	std::cout << x << " + " << y << " = " << x + y << std::endl;
}

void subtract(int x, int y) {
	std::cout << x << " - " << y << " = " << x - y << std::endl;
}
void main4() {
	auto add_with_2 = std::bind(add, 2, std::placeholders::_1);
	add_with_2(3);

	// 두 번째 인자는 무시된다.
	add_with_2(3, 4);

	auto subtract_from_2 = std::bind(subtract, std::placeholders::_1, 2);
	auto negate = std::bind(subtract, std::placeholders::_2, std::placeholders::_1);

	subtract_from_2(3);  // 3 - 2 를 계산한다.
	negate(4, 2);        // 2 - 4 를 계산한다
}


void main() {
	main1();
	main2();
	main3();
	main4();
}	
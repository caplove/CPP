
#include <iostream>	

class A {
public:
	A() { std::cout << "A 생성자 호출" << std::endl; }
	};

class B {
	public:
	B() { std::cout << "B 생성자 호출" << std::endl; }
	};

class C : public A, public B {
	public:
	C() : A(), B() { std::cout << "C 생성자 호출" << std::endl; }
	};

int main() {
	C c;
	}

#include <iostream>	

class A {
public:
	A() { std::cout << "A ������ ȣ��" << std::endl; }
	};

class B {
	public:
	B() { std::cout << "B ������ ȣ��" << std::endl; }
	};

class C : public A, public B {
	public:
	C() : A(), B() { std::cout << "C ������ ȣ��" << std::endl; }
	};

int main() {
	C c;
	}
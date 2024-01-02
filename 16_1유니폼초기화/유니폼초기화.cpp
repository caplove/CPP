
// ������ �ʱ�ȭ (Uniform Initialization)
// C++11���� �߰��� �������, �ʱ�ȭ ����� �������ִ� ����̴�.
// ������ ȣ���� () ��� { }�� ǥ��, �ֳ��ϸ� �Լ��� ȣ��� �������� ȣ���� �����ϱ� ���ؼ��̴�.
// �ʱ�ȭ ����� = ��� { }�� ǥ��
// ��, �Ͻ��� ����ȯ�� �Ͼ�� ��쿡�� error�� �߻��Ѵ�.
// Narrow-conversion : �Ͻ��� ����ȯ�� ���� ������ �ս��� �߻��ϴ� ���
// long double -> double -> float -> unsigned long long -> long long -> unsigned long -> long -> unsigned int -> int -> char
// Narrow-conversion�� �߻��ϴ� ���, error�� �߻��Ѵ�.
// 
// ������ �ʱ�ȭ ����� ������ ����.
// int a = 1;
// int b(1);
// int c{ 1 };
// int d = { 1 };
//
// �߰��� ������ �ʱ�ȭ ����� ������ ����.
// int e = { 1, 2, 3 }; // error
// int f{ 1, 2, 3 }; // error
// int g = { 1 }; // ok
// int h{ 1 }; // ok
// int i = {}; // ok
// int j{}; // ok
// int k; // ok
// int l{}; // ok


#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;
class A {
public:
	A(int x) { std::cout << "�Ϲ� ������(int x) ȣ��!" << std::endl; };
	A() { std::cout << "�Ϲ� ������ ȣ��!" << std::endl; };
	A(std::initializer_list<string> list) { std::cout << "�ʱ�ȭ��(initializer_list(string��)) ������ ȣ��!" << std::endl; };
	A(std::initializer_list<int> list) { std::cout << "�ʱ�ȭ��(initializer_list(int��)) ������ ȣ��!" << std::endl; };
};








int main() {
	A a(3.5);  // Narrow-conversion ���� --> �Ͻ��� casting �߻� (3.5 -> 3)
	//A b{ 3.5 };  // Narrow-conversion �Ұ� --> error�߻�
	//A c = { 3.5 };  // Narrow-conversion �Ұ� --> error�߻�
	A d = { 1 }; // ok
	A e{ 1 }; // ok
	A f = {}; // ok
	A g{}; // ok
	A h; // ok
	A i{"abcd", "efgh"}; // ok

	std::cout << "--initializer_list ��ü ����----------------------------------" << std::endl;
	auto j{ 1 }; // initializer_list<int>
	auto k = { 3.5 }; // initializer_list<double>
	auto l = { 1, 2, 3 }; // initializer_list<int>
	//auto m = { 1, 2.5 }; // initializer_list<double>
	auto n = { 1,2 } ; // initializer_list<int>
	auto list = { "a", "b", "cc" }; // initializer_list<const char*>
	auto list2 = { "a"s, "b"s, "cc"s }; // initializer_list<string>









}

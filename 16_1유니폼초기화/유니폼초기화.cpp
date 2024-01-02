
// 균일한 초기화 (Uniform Initialization)
// C++11에서 추가된 기능으로, 초기화 방식을 통일해주는 기능이다.
// 생성자 호출을 () 대신 { }로 표현, 왜냐하면 함수의 호출과 생성자의 호출을 구분하기 위해서이다.
// 초기화 방식을 = 대신 { }로 표현
// 단, 암시적 형변환이 일어나는 경우에는 error가 발생한다.
// Narrow-conversion : 암시적 형변환을 통해 정보의 손실이 발생하는 경우
// long double -> double -> float -> unsigned long long -> long long -> unsigned long -> long -> unsigned int -> int -> char
// Narrow-conversion이 발생하는 경우, error가 발생한다.
// 
// 기존의 초기화 방식은 다음과 같다.
// int a = 1;
// int b(1);
// int c{ 1 };
// int d = { 1 };
//
// 추가된 균일한 초기화 방식은 다음과 같다.
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
	A(int x) { std::cout << "일반 생성자(int x) 호출!" << std::endl; };
	A() { std::cout << "일반 생성자 호출!" << std::endl; };
	A(std::initializer_list<string> list) { std::cout << "초기화자(initializer_list(string형)) 생성자 호출!" << std::endl; };
	A(std::initializer_list<int> list) { std::cout << "초기화자(initializer_list(int형)) 생성자 호출!" << std::endl; };
};








int main() {
	A a(3.5);  // Narrow-conversion 가능 --> 암시적 casting 발생 (3.5 -> 3)
	//A b{ 3.5 };  // Narrow-conversion 불가 --> error발생
	//A c = { 3.5 };  // Narrow-conversion 불가 --> error발생
	A d = { 1 }; // ok
	A e{ 1 }; // ok
	A f = {}; // ok
	A g{}; // ok
	A h; // ok
	A i{"abcd", "efgh"}; // ok

	std::cout << "--initializer_list 객체 생성----------------------------------" << std::endl;
	auto j{ 1 }; // initializer_list<int>
	auto k = { 3.5 }; // initializer_list<double>
	auto l = { 1, 2, 3 }; // initializer_list<int>
	//auto m = { 1, 2.5 }; // initializer_list<double>
	auto n = { 1,2 } ; // initializer_list<int>
	auto list = { "a", "b", "cc" }; // initializer_list<const char*>
	auto list2 = { "a"s, "b"s, "cc"s }; // initializer_list<string>









}

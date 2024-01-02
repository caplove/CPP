
// 타입과 값 카테고리(Value Category)
// decltype 과 declval
// 표현식의 타입을 추론하는데 사용
// decltype(표현식) 변수이름 = 표현식;
// 표현식의 타입을 변수이름에 넣어준다.
// 표현식이 변수일 경우 변수의 타입을 넣어준다.
// 표현식이 함수일 경우 함수의 반환 타입을 넣어준다.
// 만일 식의 값 종류가 xvalue 라면 decltype 는 T&& 가 됩니다.
// 만일 식의 값 종류가 lvalue 라면 decltype 는 T& 가 됩니다.
// 만일 식의 값 종류가 prvalue 라면 decltype 는 T 가 됩니다.
// 
// auto 와 decltype 차이
// int i=4;
// auto a = i; // int a
// decltype(i) b = i; // int b
// 
// int arr[10];
// auto arr2 = arr; // int* arr2
// decltype(arr) arr3 = arr; // int arr3[10]
//
// const int i=4; 
// auto a = i; // int a
// decltype(i) b = i; // const int b



// 값 카테고리
// Lvalue : 이름을 가진 객체 = 메모리에 존재하는 객체  변수 (ex,  a, a[n])
//          함수의 이름, 어떤 타입의 데이터 맴버(ex, std::endl, std::cout)
//          좌측값 레퍼런스를 리턴하는 함수의 호출식. (ex, std::cout << 1, ++i)
//			복합 대입 연산자 식. (ex, a += 1, a = b, a = b = c)
//			전위 증감 연산자 식. (ex, ++i, --i)
//			연산자 식. (ex, a + b, a - b, a * b, a / b, a % b, a << b, a >> b, a & b, a ^ b, a | b, a && b, 
//										a || b, a == b, a != b, a < b, a > b, a <= b, a >= b)
//			맴버 변수 참조 연산자 식. (ex, a.b, a->b) 이때 b는 맴버 변수임. b가 맴버 함수인 경우는 제외
//			문자열 리터럴. (ex, "Hello World")
// 
// Rvalue : 메모리에 존재하지 않는 임시 객체, 리터럴, 함수 등
// 
// glvalue : Lvalue와 Rvalue를 모두 포함하는 표현식, generalized Lvalue
// prvalue : pure Rvalue
//			 정체를 알수 없는 녀석들, 주소값을 취할수 없다. 따라서, &42, &(a+b)는 불가능
//			 문자열을 제외한 리터럴. (ex, 1, 1.1, true, nullptr)
//			 후위 증감 연산자 식. (ex, i++, i--)
// 			 함수 호출식. (ex, f(), std::cout << 1, str1+str2)
//			 주소값 연산자 식. &a
//			 맴버 함수 참조 연산자 식. (ex, a.b(), a->b()) 이때 b는 맴버 함수임. b가 맴버 변수인 경우는 제외
//			 this 포인터. (ex, this)
//			 enum 값 (ex, enum {a, b, c})
//			 람다식. (ex, [](){})
// xvalue : Rvalue Reference만을 포함하는 표현식, expiring value




#include <iostream>

struct A {
	double d;
};

int main() {
	int a = 3; 
	decltype(a) b = 2;  // int

	int& r_a = a; // lvalue reference
	decltype(r_a) r_b = b;  // int&

	int&& x = 3; // rvalue reference
	decltype(x) y = 2;  // int&&

	A* aa;
	A bb;
	decltype(aa) ee = nullptr;  // A*
	decltype(aa->d) dd = 0.1;  // double

	decltype(bb) cc;  // A
	decltype(bb.d) ff = 0.1;  // double

}


// 함수의 리턴값을 인자들 정의 부분 뒤에 써야함. 람다 문법과 유사.
//template <typename T, typename U>
//decltype(t + u) add(T t, U u) {    // ecltype(t + u)는 t와 u의 타입을 결정할 수 없다. t,u의 정의가 decltype나중에 나오기때문에. 컴파일 에러
//	return t + u;
//}

template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
	return t + u;
}

// declval
// 어떤 타입 T의 f 함수의 리턴 타입을 정의하고 싶을떄 사용
// std::declval 함수를 사용해서 원하는 타입의 생성자 호출을 우회해서(하지 않고) 멤버 함수의 타입에 접근할 수 있음.
// C++14부터는 함수의 리턴타입도 auto로 지정할수 있음.
template <typename T>
auto call_f_and_return(T& t) {
	return t.f();
}

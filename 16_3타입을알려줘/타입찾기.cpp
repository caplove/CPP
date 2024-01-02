
// Ÿ�԰� �� ī�װ�(Value Category)
// decltype �� declval
// ǥ������ Ÿ���� �߷��ϴµ� ���
// decltype(ǥ����) �����̸� = ǥ����;
// ǥ������ Ÿ���� �����̸��� �־��ش�.
// ǥ������ ������ ��� ������ Ÿ���� �־��ش�.
// ǥ������ �Լ��� ��� �Լ��� ��ȯ Ÿ���� �־��ش�.
// ���� ���� �� ������ xvalue ��� decltype �� T&& �� �˴ϴ�.
// ���� ���� �� ������ lvalue ��� decltype �� T& �� �˴ϴ�.
// ���� ���� �� ������ prvalue ��� decltype �� T �� �˴ϴ�.
// 
// auto �� decltype ����
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



// �� ī�װ�
// Lvalue : �̸��� ���� ��ü = �޸𸮿� �����ϴ� ��ü  ���� (ex,  a, a[n])
//          �Լ��� �̸�, � Ÿ���� ������ �ɹ�(ex, std::endl, std::cout)
//          ������ ���۷����� �����ϴ� �Լ��� ȣ���. (ex, std::cout << 1, ++i)
//			���� ���� ������ ��. (ex, a += 1, a = b, a = b = c)
//			���� ���� ������ ��. (ex, ++i, --i)
//			������ ��. (ex, a + b, a - b, a * b, a / b, a % b, a << b, a >> b, a & b, a ^ b, a | b, a && b, 
//										a || b, a == b, a != b, a < b, a > b, a <= b, a >= b)
//			�ɹ� ���� ���� ������ ��. (ex, a.b, a->b) �̶� b�� �ɹ� ������. b�� �ɹ� �Լ��� ���� ����
//			���ڿ� ���ͷ�. (ex, "Hello World")
// 
// Rvalue : �޸𸮿� �������� �ʴ� �ӽ� ��ü, ���ͷ�, �Լ� ��
// 
// glvalue : Lvalue�� Rvalue�� ��� �����ϴ� ǥ����, generalized Lvalue
// prvalue : pure Rvalue
//			 ��ü�� �˼� ���� �༮��, �ּҰ��� ���Ҽ� ����. ����, &42, &(a+b)�� �Ұ���
//			 ���ڿ��� ������ ���ͷ�. (ex, 1, 1.1, true, nullptr)
//			 ���� ���� ������ ��. (ex, i++, i--)
// 			 �Լ� ȣ���. (ex, f(), std::cout << 1, str1+str2)
//			 �ּҰ� ������ ��. &a
//			 �ɹ� �Լ� ���� ������ ��. (ex, a.b(), a->b()) �̶� b�� �ɹ� �Լ���. b�� �ɹ� ������ ���� ����
//			 this ������. (ex, this)
//			 enum �� (ex, enum {a, b, c})
//			 ���ٽ�. (ex, [](){})
// xvalue : Rvalue Reference���� �����ϴ� ǥ����, expiring value




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


// �Լ��� ���ϰ��� ���ڵ� ���� �κ� �ڿ� �����. ���� ������ ����.
//template <typename T, typename U>
//decltype(t + u) add(T t, U u) {    // ecltype(t + u)�� t�� u�� Ÿ���� ������ �� ����. t,u�� ���ǰ� decltype���߿� �����⶧����. ������ ����
//	return t + u;
//}

template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
	return t + u;
}

// declval
// � Ÿ�� T�� f �Լ��� ���� Ÿ���� �����ϰ� ������ ���
// std::declval �Լ��� ����ؼ� ���ϴ� Ÿ���� ������ ȣ���� ��ȸ�ؼ�(���� �ʰ�) ��� �Լ��� Ÿ�Կ� ������ �� ����.
// C++14���ʹ� �Լ��� ����Ÿ�Ե� auto�� �����Ҽ� ����.
template <typename T>
auto call_f_and_return(T& t) {
	return t.f();
}

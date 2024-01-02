

// ConstExpr(�����) : ������Ÿ�� ��� ǥ������ �����ϴ� Ű����
// �� ǥ������ �������� �� ����� �ȴ�. ����, ***���� �ð�*** �� �پ���. �� ������ ����ȴ�.
// �������
// 1. �Լ��� ��ȯ���� void�� �ƴϾ�� �Ѵ�.
// 2. �Լ��� �Ű������� ������̾�� �Ѵ�.
// 3. �Լ��� ��ü�� ���� return������ �����Ǿ�� �Ѵ�.
// 4. �Լ��� ��ü���� ���������� ������ �� ����.
// 5. �Լ��� ��ü���� static ������ ������ �� ����.
// 6. �Լ��� ��ü���� �ٸ� �Լ��� ȣ���� �� ����.
// 7. �Լ��� ��ü���� �ݺ����� ����� �� ����.
// 8. �Լ��� ��ü���� goto���� ����� �� ����.
// 9. �Լ��� ��ü���� try ����� ����� �� ����.
// 10. �Լ��� ��ü���� asm ����� ����� �� ����.
// 11. �Լ��� ��ü���� ���� Ŭ������ ������ �� ����.
// 12. �Լ��� ��ü���� ���� ���ø��� ������ �� ����.
// 13. �Լ��� ��ü���� new �����ڸ� ����� �� ����.
// 14. �Լ��� ��ü���� typeid �����ڸ� ����� �� ����.




#include <iostream>

constexpr int ARRAY_SIZE = 10;

constexpr int square(int number) {
    return number * number;
}

// Factorial function
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : (n * factorial(n - 1));
}

// Fibonacci function
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));
}



void main1() {
	int myArray2[ARRAY_SIZE];
	int myArray3[square(ARRAY_SIZE)];

    // Use constexpr functions at compile time
    constexpr int fact = factorial(5);
    constexpr int fib = fibonacci(5);

    std::cout << "Factorial of 5: " << fact << std::endl;
    std::cout << "Fibonacci of 5: " << fib << std::endl;


}




// Vector Ŭ����
// constexpr ������
// constexpr ��� �Լ�
// constexpr �Լ� ȣ��
// constexpr ��ü�� constexpr ��� �Լ� ȣ��, 
// constexpr �Լ��� ���ϰ����� constexpr ��ü�� ����, A<AddVec(v1, v2).x()> b;
// constexpr �Լ��� ���ϰ����� constexpr ��ü�� ���Ϲ޾� constexpr ��ü�� constexpr ��� �Լ� ȣ��, A<AddVec(v1, v2).x()> b;
// constexpr �Լ��� ���ϰ����� constexpr ��ü�� ���Ϲ޾� constexpr ��ü�� constexpr ��� �Լ��� ���ø� ���ڷ� ���,  A<v1.x()> a;

#include <iostream>

class Vector {
public:
    constexpr Vector(int x, int y) : x_(x), y_(y) {}

    constexpr int x() const { return x_; }
    constexpr int y() const { return y_; }

private:
    int x_;
    int y_;
};

constexpr Vector AddVec(const Vector& v1, const Vector& v2) {
    return { v1.x() + v2.x(), v1.y() + v2.y() };
}



template <int N>
struct A {
    int operator()() { return N; } // �Լ� ȣ�� ������ �����ε�
};

void main2() {
    constexpr Vector v1{ 1, 2 };
    constexpr Vector v2{ 2, 3 };

    // v1�� Ȯ��
    std::cout << v1.x() << ", " << v1.y() << std::endl;

    // v2�� Ȯ��
    std::cout << v2.x() << ", " << v2.y() << std::endl;

    // constexpr ��ü�� constexpr ��� �Լ��� ���� constexpr!
    A<v1.x()> a; // v1.x()�� constexpr�̹Ƿ�(��, int��),  A�� ���ø� ���ڷ� ��� �����ϴ�.
    std::cout << a() << std::endl;

    // AddVec ���� constexpr �� �����Ѵ�.
    A<AddVec(v1, v2).x()> b;
    std::cout << b() << std::endl;
}


// if constexpr�� �̿���, Ÿ�����ں��� ������ Ÿ�� ����� �ٸ��� ������ �� �ִ�.
#include <iostream>
#include <type_traits>

template <typename T>
void show_value(T t) {
    if constexpr (std::is_pointer<T>::value) { // constexpr�� ������� ������, ������ ��ü�� �ȵ�.  *t�� ������ Ÿ�ӿ� �����Ǿ�� �ϹǷ�
        std::cout << "������ �̴� : " << *t << std::endl; // is_pointer<T>�� bool�� ����̹Ƿ�, *t �� �ƿ� ����� �ȵǾ�, ������ ���� ����.!
    }
    else {
        std::cout << "�����Ͱ� �ƴϴ� : " << t << std::endl;
    }
}

void main3() {
    int x = 3;
    show_value(x);

    int* p = &x;
    show_value(p);
}







void main() {
	main1();
	main2();
    main3();
}
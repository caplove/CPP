

// ConstExpr(상수식) : 컴파일타임 상수 표현식을 정의하는 키워드
// 이 표현식은 컴파일할 때 상수로 된다. 따라서, ***실행 시간*** 이 줄어든다. 더 빠르게 실행된다.
// 제약사항
// 1. 함수의 반환형이 void가 아니어야 한다.
// 2. 함수의 매개변수는 상수식이어야 한다.
// 3. 함수의 몸체는 단일 return문으로 구성되어야 한다.
// 4. 함수의 몸체에는 지역변수를 선언할 수 없다.
// 5. 함수의 몸체에는 static 변수를 선언할 수 없다.
// 6. 함수의 몸체에는 다른 함수를 호출할 수 없다.
// 7. 함수의 몸체에는 반복문을 사용할 수 없다.
// 8. 함수의 몸체에는 goto문을 사용할 수 없다.
// 9. 함수의 몸체에는 try 블록을 사용할 수 없다.
// 10. 함수의 몸체에는 asm 블록을 사용할 수 없다.
// 11. 함수의 몸체에는 지역 클래스를 선언할 수 없다.
// 12. 함수의 몸체에는 지역 탬플릿을 선언할 수 없다.
// 13. 함수의 몸체에는 new 연산자를 사용할 수 없다.
// 14. 함수의 몸체에는 typeid 연산자를 사용할 수 없다.




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




// Vector 클래스
// constexpr 생성자
// constexpr 멤버 함수
// constexpr 함수 호출
// constexpr 객체의 constexpr 멤버 함수 호출, 
// constexpr 함수의 리턴값으로 constexpr 객체를 리턴, A<AddVec(v1, v2).x()> b;
// constexpr 함수의 리턴값으로 constexpr 객체를 리턴받아 constexpr 객체의 constexpr 멤버 함수 호출, A<AddVec(v1, v2).x()> b;
// constexpr 함수의 리턴값으로 constexpr 객체를 리턴받아 constexpr 객체의 constexpr 멤버 함수를 템플릿 인자로 사용,  A<v1.x()> a;

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
    int operator()() { return N; } // 함수 호출 연산자 오버로딩
};

void main2() {
    constexpr Vector v1{ 1, 2 };
    constexpr Vector v2{ 2, 3 };

    // v1값 확인
    std::cout << v1.x() << ", " << v1.y() << std::endl;

    // v2값 확인
    std::cout << v2.x() << ", " << v2.y() << std::endl;

    // constexpr 객체의 constexpr 멤버 함수는 역시 constexpr!
    A<v1.x()> a; // v1.x()는 constexpr이므로(즉, int형),  A의 템플릿 인자로 사용 가능하다.
    std::cout << a() << std::endl;

    // AddVec 역시 constexpr 을 리턴한다.
    A<AddVec(v1, v2).x()> b;
    std::cout << b() << std::endl;
}


// if constexpr를 이용해, 타입인자별로 컴파일 타임 상수를 다르게 정의할 수 있다.
#include <iostream>
#include <type_traits>

template <typename T>
void show_value(T t) {
    if constexpr (std::is_pointer<T>::value) { // constexpr를 사용하지 않으면, 컴파일 자체가 안됨.  *t는 컴파일 타임에 결정되어야 하므로
        std::cout << "포인터 이다 : " << *t << std::endl; // is_pointer<T>는 bool형 상수이므로, *t 는 아예 고려가 안되어, 에러가 나지 않음.!
    }
    else {
        std::cout << "포인터가 아니다 : " << t << std::endl;
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
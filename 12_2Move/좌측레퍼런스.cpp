
// 좌측레퍼런스 사용
// Case : swap(A,B) -> A,B는 좌측레퍼런스
// temp = A  // 복사생성자
// A = B    // 복사생성자
// B = temp // 복사생성자
// C++11에서는 다음과 같이 구현
// temp = std::move(A)  // 이동생성이므로 복사생성보다 훨씬 빠르다.
// A = std::move(B)     // 이동생성이므로 복사생성보다 훨씬 빠르다.
// B = std::move(temp)  // 이동생성이므로 복사생성보다 훨씬 빠르다.

// 이동 대입연산자를 설계하지않으면, 일반적인 대입연산자가 호출된다. (오버 로딩이 되어있기 때문에)





#include <iostream>
#include <cstring>

template <typename T>
void my_swap(T& a, T& b) {
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

class MyString {
    char* string_content;  // 문자열 데이터를 가리키는 포인터
    int string_length;     // 문자열 길이

    int memory_capacity;  // 현재 할당된 용량

public:
    MyString();

    // 문자열로 부터 생성
    MyString(const char* str);

    // 복사 생성자
    MyString(const MyString& str);

    // 이동 생성자
    MyString(MyString&& str);

    // 일반적인 대입 연산자
    MyString& operator=(const MyString& s);

    // 이동 대입 연산자
    MyString& operator=(MyString&& s);

    ~MyString();

    int length() const;

    void println();
};

MyString::MyString() {
    std::cout << "생성자 호출 ! " << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = NULL;
}

MyString::MyString(const char* str) {
    std::cout << "생성자 호출 ! " << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
    std::cout << "복사 생성자 호출 ! " << std::endl;
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}
MyString::MyString(MyString&& str) {
    std::cout << "이동 생성자 호출 !" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    // 임시 객체 소멸 시에 메모리를 해제하지
    // 못하게 한다.
    str.string_content = nullptr;
    str.string_length = 0;
    str.memory_capacity = 0;
}
MyString::~MyString() {
    if (string_content) delete[] string_content;
}
// 일반적인 대입 연산자
MyString& MyString::operator=(const MyString& s) {
    std::cout << "복사!" << std::endl;
    if (s.string_length > memory_capacity) {
        delete[] string_content;
        string_content = new char[s.string_length];
        memory_capacity = s.string_length;
    }
    string_length = s.string_length;
    for (int i = 0; i != string_length; i++) {
        string_content[i] = s.string_content[i];
    }

    return *this;
}
// 이동 대입 연산자
MyString& MyString::operator=(MyString&& s) {
    std::cout << "이동!" << std::endl;
    this->string_content = s.string_content;
    this->memory_capacity = s.memory_capacity;
    this->string_length = s.string_length;

    s.string_content = nullptr;
    s.memory_capacity = 0;
    s.string_length = 0;
    return *this;
}
int MyString::length() const { return string_length; }
void MyString::println() {
    for (int i = 0; i != string_length; i++) std::cout << string_content[i];

    std::cout << std::endl;
}


void main1() {
    MyString str1("abc");
    MyString str2("def");
    std::cout << "Swap 전 -----" << std::endl;
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();

    std::cout << "Swap 후 -----" << std::endl;
    my_swap(str1, str2);
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();
}


// 이동 생성자를 사용하는 예제
// class A를 맴버로 가지는 class B를 생성할 때, A의 생성자를 복사하지 않고,
// B의 맴버로 A를 생성하고 싶을 때, 이동 생성자를 사용한다.
// B(A&& a) : a_(std::move(a)) {}

class A {
public:
    A() { std::cout << "ctor\n"; }
    A(const A& a) { std::cout << "copy ctor\n"; }
    A(A&& a) { std::cout << "move ctor\n"; }
};

class B {
public:
    B(A&& a) : a_(std::move(a)) {}

    A a_;
};

void main2() {
    A a;
    std::cout << "create B-- \n";
    B b(std::move(a)); // a를 우측값으로 변환하여 이동 생성자 호출 !
}


// wrapper 함수를 잘 정의하려면, 이동 생성자와 이동 대입 연산자를 잘 정의해야한다.
// 원본 - Wrapper의 동작이 정확히 일치하려면, Wrapper의 이동 생성자와 이동 대입 연산자를 정의해야한다.
// 보편적 레퍼런스(Universal Reference)인 forward를 사용하면, 좌측,우측 레퍼런스를 구분하지 않고,
// 하나의 함수로 처리할 수 있다.

template <typename T>
void wrapper(T&& u) {
    g(std::forward<T>(u)); // u가 좌측값이면 좌측값 레퍼런스 호출, u가 우측값이면 우측값 레퍼런스 호출
}

class C {};

void g(C& a) { std::cout << "좌측값 레퍼런스 호출" << std::endl; } 
void g(const C& a) { std::cout << "좌측값 상수 레퍼런스 호출" << std::endl; } 
void g(C&& a) { std::cout << "우측값 레퍼런스 호출" << std::endl; }

void main3() {
    C a;
    const C ca;

    std::cout << "원본 --------" << std::endl;
    g(a); // lvalue
    g(ca); // lvalue
    g(C()); // rvalue

    std::cout << "Wrapper -----" << std::endl;
    wrapper(a); // lvalue
    wrapper(ca); // lvalue
    wrapper(C()); // rvalue
}


void main() {
    main1();
    main2();
    main3();
};


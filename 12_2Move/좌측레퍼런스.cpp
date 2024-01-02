
// �������۷��� ���
// Case : swap(A,B) -> A,B�� �������۷���
// temp = A  // ���������
// A = B    // ���������
// B = temp // ���������
// C++11������ ������ ���� ����
// temp = std::move(A)  // �̵������̹Ƿ� ����������� �ξ� ������.
// A = std::move(B)     // �̵������̹Ƿ� ����������� �ξ� ������.
// B = std::move(temp)  // �̵������̹Ƿ� ����������� �ξ� ������.

// �̵� ���Կ����ڸ� ��������������, �Ϲ����� ���Կ����ڰ� ȣ��ȴ�. (���� �ε��� �Ǿ��ֱ� ������)





#include <iostream>
#include <cstring>

template <typename T>
void my_swap(T& a, T& b) {
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

class MyString {
    char* string_content;  // ���ڿ� �����͸� ����Ű�� ������
    int string_length;     // ���ڿ� ����

    int memory_capacity;  // ���� �Ҵ�� �뷮

public:
    MyString();

    // ���ڿ��� ���� ����
    MyString(const char* str);

    // ���� ������
    MyString(const MyString& str);

    // �̵� ������
    MyString(MyString&& str);

    // �Ϲ����� ���� ������
    MyString& operator=(const MyString& s);

    // �̵� ���� ������
    MyString& operator=(MyString&& s);

    ~MyString();

    int length() const;

    void println();
};

MyString::MyString() {
    std::cout << "������ ȣ�� ! " << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = NULL;
}

MyString::MyString(const char* str) {
    std::cout << "������ ȣ�� ! " << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
    std::cout << "���� ������ ȣ�� ! " << std::endl;
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}
MyString::MyString(MyString&& str) {
    std::cout << "�̵� ������ ȣ�� !" << std::endl;
    string_length = str.string_length;
    string_content = str.string_content;
    memory_capacity = str.memory_capacity;

    // �ӽ� ��ü �Ҹ� �ÿ� �޸𸮸� ��������
    // ���ϰ� �Ѵ�.
    str.string_content = nullptr;
    str.string_length = 0;
    str.memory_capacity = 0;
}
MyString::~MyString() {
    if (string_content) delete[] string_content;
}
// �Ϲ����� ���� ������
MyString& MyString::operator=(const MyString& s) {
    std::cout << "����!" << std::endl;
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
// �̵� ���� ������
MyString& MyString::operator=(MyString&& s) {
    std::cout << "�̵�!" << std::endl;
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
    std::cout << "Swap �� -----" << std::endl;
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();

    std::cout << "Swap �� -----" << std::endl;
    my_swap(str1, str2);
    std::cout << "str1 : ";
    str1.println();
    std::cout << "str2 : ";
    str2.println();
}


// �̵� �����ڸ� ����ϴ� ����
// class A�� �ɹ��� ������ class B�� ������ ��, A�� �����ڸ� �������� �ʰ�,
// B�� �ɹ��� A�� �����ϰ� ���� ��, �̵� �����ڸ� ����Ѵ�.
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
    B b(std::move(a)); // a�� ���������� ��ȯ�Ͽ� �̵� ������ ȣ�� !
}


// wrapper �Լ��� �� �����Ϸ���, �̵� �����ڿ� �̵� ���� �����ڸ� �� �����ؾ��Ѵ�.
// ���� - Wrapper�� ������ ��Ȯ�� ��ġ�Ϸ���, Wrapper�� �̵� �����ڿ� �̵� ���� �����ڸ� �����ؾ��Ѵ�.
// ������ ���۷���(Universal Reference)�� forward�� ����ϸ�, ����,���� ���۷����� �������� �ʰ�,
// �ϳ��� �Լ��� ó���� �� �ִ�.

template <typename T>
void wrapper(T&& u) {
    g(std::forward<T>(u)); // u�� �������̸� ������ ���۷��� ȣ��, u�� �������̸� ������ ���۷��� ȣ��
}

class C {};

void g(C& a) { std::cout << "������ ���۷��� ȣ��" << std::endl; } 
void g(const C& a) { std::cout << "������ ��� ���۷��� ȣ��" << std::endl; } 
void g(C&& a) { std::cout << "������ ���۷��� ȣ��" << std::endl; }

void main3() {
    C a;
    const C ca;

    std::cout << "���� --------" << std::endl;
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


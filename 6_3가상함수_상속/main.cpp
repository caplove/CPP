
// 소멸자를 가상함수로 만들어야 하는 이유
// 1. 소멸자를 가상함수로 만들지 않으면, 부모 클래스의 포인터로 자식 클래스를 가리켰을 때, 자식 클래스의 소멸자가 호출되지 않는다.
// 2. 소멸자를 가상함수로 만들지 않으면, 자식 클래스의 소멸자가 호출되지 않는다.


#include <iostream>

class Parent {
public:
    Parent() { std::cout << "Parent 생성자 호출" << std::endl; }
    virtual ~Parent() { std::cout << "Parent 소멸자 호출" << std::endl; }
    };
class Child : public Parent {
public:
    Child() : Parent() { std::cout << "Child 생성자 호출" << std::endl; }
    ~Child() { std::cout << "Child 소멸자 호출" << std::endl; }
    };







int main() {
    std::cout << "--- 평범한 Child 만들었을 때 ---" << std::endl;
    { Child c; }
    std::cout << "--- Parent 포인터로 Child 가리켰을 때 ---" << std::endl;
    {
    // Parent* p = new Child;
    Parent* p = new Child();   
    delete p;
    }
    }


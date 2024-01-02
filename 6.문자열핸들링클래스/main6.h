
// 나중에 함수의 구현을 업데이트해야할 경우, 그 함수는 virtual로 선언하고, 함수의 구현은 파생클래스에서 하도록 한다. 
// 이렇게 하면, 기존의 코드를 수정하지 않고, 파생클래스에서 함수의 구현을 업데이트 할 수 있다.
// 이러한 기능을 다형성이라고 한다.
// 다형성을 구현하기 위해서는, 부모클래스의 포인터를 사용해야한다.
// 부모클래스의 포인터를 사용하면, 부모클래스의 포인터가 가리키는 객체가 무엇인지에 따라서, 다른 함수가 호출된다.
// 부모클래스의 포인터가 가리키는 객체가 무엇인지에 따라서, 다른 함수가 호출되는 것을 가상함수라고 한다.
// 가상함수를 사용하면, 부모클래스의 포인터를 사용하더라도, 실제로 가리키는 객체에 따라서, 다른 함수가 호출된다.
// 가상함수를 사용하면, 부모클래스의 포인터를 사용하더라도, 실제로 가리키는 객체에 따라서, 다른 함수가 호출되는 것을 다형성이라고 한다.
// 
// 예를들면) 면적 계산한다고 가정했을떄, 도형마다 면적계산하는 방법이 다르다면, 가상함수를 이용하여 다형성을 구현할 수 있다.
//          삼각형의 면적 방식과 사각형, 오각형의 면적계산 방식이 다르기 떄문에 다형성을 통해 면적구하기() 함수를 구현할 수 있다.
// 이런한 가상함수를 순수함수로 만들어서, 자식(파생)클래스에서 반드시 구현하도록 만들 수 있다.
// 순수함수는 자식(파생)클래스에서 반드시 구현해야한다. --> 자식(파생) 클래스에서 구현하지 않으면, 컴파일 에러가 발생한다.
// 형식
// 기반클래스에서 Virtual 함수명(),
// 파생클래스에서 Virtual 함수명() override





// 여러 클래스간의 관계설정은 
//   is a 관계          has a 관계
// 사람은 동물이다.    자동차는 엔진을 가진다.


#include <iostream>
#include <vector>


// Shape 클래스 선언
class Shape {
public:
    // 매소드 - 순수 가상 함수
    virtual double area() const = 0; // 순수 가상 함수: 면적을 계산
    virtual double perimeter() const = 0; // 순수 가상 함수: 둘레를 계산
    };

// Circle 클래스 선언
class Circle : public Shape {

private:
    double m_radius; // 반지름

public:
    // 생성자
    Circle(double radius) : m_radius(radius) {}

    // 소멸자
    virtual ~Circle() {}

    // 매소드 - 면적 계산 가상 함수
    virtual double area() const override {
        return 3.141592 * m_radius * m_radius;
        }
    // 매소드 - 둘레 계산 가상 함수
    virtual double perimeter() const override {
        return 2 * 3.141592 * m_radius;
        }
    };

// Rectangle 클래스 선언
class Rectangle : public Shape {

private:
    double m_width; // 너비
    double m_height; // 높이

public:
    // 생성자
    Rectangle(double width, double height) : m_width(width), m_height(height) {}

    // 면적 계산 가상 함수 구현
    virtual double area() const override {
        return m_width * m_height;
        }

    // 둘레 계산 가상 함수 구현
    virtual double perimeter() const override {
        return 2 * (m_width + m_height);
        }
    };

// Diamond 클래스 선언
class Diamond : public Shape {

private:
    double m_width; // 너비
    double m_height; // 높이

public:
    // 생성자
    Diamond(double width, double height) : m_width(width), m_height(height) {}
    // 면적 계산 가상 함수 구현
    virtual double area() const override {
        return m_width * m_height;
        }
    // 둘레 계산 가상 함수 구현
    virtual double perimeter() const override {
        return 2 * (m_width + m_height);
        }
    };

// 타원 클래스 선언
class Ellipse : public Shape {

private:
    double m_radius1; // 반지름1
    double m_radius2; // 반지름2

public:
    // 생성자
    Ellipse(double radius1, double radius2) : m_radius1(radius1), m_radius2(radius2) {}
    // 면적 계산 가상 함수 구현
    virtual double area() const override {
        return 3.141592 * m_radius1 * m_radius2;
        }
    // 둘레 계산 가상 함수 구현
    virtual double perimeter() const override {
        return 2 * 3.141592 * (m_radius1 + m_radius2);
        }
    };


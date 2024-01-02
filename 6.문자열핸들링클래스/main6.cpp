// File: main6.cpp
/* 
가상 함수(Virtual Function)는 객체 지향 프로그래밍에서 클래스 계층 구조를 사용하여 다형성을 구현하는 메커니즘입니다. 
C++과 같은 언어에서 가상 함수는 기본 클래스에서 선언되며 파생 클래스에서 재정의될 수 있습니다. 
가상 함수를 호출하면 실행 시간에 호출되는 함수가 결정되어, 해당 객체의 실제 타입에 따라 적절한 함수가 호출됩니다.
*/


#include "main6.h"


    int main() {
        // Shape 포인터들을 저장하는 벡터 생성
        std::vector<Shape*> shapes;


        // 새로운 도형 객체를 생성 & 벡터에 추가
        shapes.push_back(new Circle(10));
        shapes.push_back(new Rectangle(10, 20));
        shapes.push_back(new Diamond(10, 20));
        shapes.push_back(new Ellipse(10, 20));

        shapes.push_back(new Circle(30));
        shapes.push_back(new Rectangle(30, 40));


        // 벡터에 저장된 모든 도형 객체의 면적과 둘레를 출력
        for (const auto& shape : shapes) {     // 벡터의 모든 요소에 대해
            std::cout << "area: " << shape->area() << ", perimeter: " << shape->perimeter() << std::endl;
        }

        // 동적 할당된 객체 메모리 해제
        for (const auto& shape : shapes) {
            delete shape;
        }

        return 0;
    }

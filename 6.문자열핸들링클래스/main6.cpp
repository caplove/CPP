// File: main6.cpp
/* 
���� �Լ�(Virtual Function)�� ��ü ���� ���α׷��ֿ��� Ŭ���� ���� ������ ����Ͽ� �������� �����ϴ� ��Ŀ�����Դϴ�. 
C++�� ���� ���� ���� �Լ��� �⺻ Ŭ�������� ����Ǹ� �Ļ� Ŭ�������� �����ǵ� �� �ֽ��ϴ�. 
���� �Լ��� ȣ���ϸ� ���� �ð��� ȣ��Ǵ� �Լ��� �����Ǿ�, �ش� ��ü�� ���� Ÿ�Կ� ���� ������ �Լ��� ȣ��˴ϴ�.
*/


#include "main6.h"


    int main() {
        // Shape �����͵��� �����ϴ� ���� ����
        std::vector<Shape*> shapes;


        // ���ο� ���� ��ü�� ���� & ���Ϳ� �߰�
        shapes.push_back(new Circle(10));
        shapes.push_back(new Rectangle(10, 20));
        shapes.push_back(new Diamond(10, 20));
        shapes.push_back(new Ellipse(10, 20));

        shapes.push_back(new Circle(30));
        shapes.push_back(new Rectangle(30, 40));


        // ���Ϳ� ����� ��� ���� ��ü�� ������ �ѷ��� ���
        for (const auto& shape : shapes) {     // ������ ��� ��ҿ� ����
            std::cout << "area: " << shape->area() << ", perimeter: " << shape->perimeter() << std::endl;
        }

        // ���� �Ҵ�� ��ü �޸� ����
        for (const auto& shape : shapes) {
            delete shape;
        }

        return 0;
    }

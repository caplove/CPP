
// ���߿� �Լ��� ������ ������Ʈ�ؾ��� ���, �� �Լ��� virtual�� �����ϰ�, �Լ��� ������ �Ļ�Ŭ�������� �ϵ��� �Ѵ�. 
// �̷��� �ϸ�, ������ �ڵ带 �������� �ʰ�, �Ļ�Ŭ�������� �Լ��� ������ ������Ʈ �� �� �ִ�.
// �̷��� ����� �������̶�� �Ѵ�.
// �������� �����ϱ� ���ؼ���, �θ�Ŭ������ �����͸� ����ؾ��Ѵ�.
// �θ�Ŭ������ �����͸� ����ϸ�, �θ�Ŭ������ �����Ͱ� ����Ű�� ��ü�� ���������� ����, �ٸ� �Լ��� ȣ��ȴ�.
// �θ�Ŭ������ �����Ͱ� ����Ű�� ��ü�� ���������� ����, �ٸ� �Լ��� ȣ��Ǵ� ���� �����Լ���� �Ѵ�.
// �����Լ��� ����ϸ�, �θ�Ŭ������ �����͸� ����ϴ���, ������ ����Ű�� ��ü�� ����, �ٸ� �Լ��� ȣ��ȴ�.
// �����Լ��� ����ϸ�, �θ�Ŭ������ �����͸� ����ϴ���, ������ ����Ű�� ��ü�� ����, �ٸ� �Լ��� ȣ��Ǵ� ���� �������̶�� �Ѵ�.
// 
// �������) ���� ����Ѵٰ� ����������, �������� ��������ϴ� ����� �ٸ��ٸ�, �����Լ��� �̿��Ͽ� �������� ������ �� �ִ�.
//          �ﰢ���� ���� ��İ� �簢��, �������� ������� ����� �ٸ��� ������ �������� ���� �������ϱ�() �Լ��� ������ �� �ִ�.
// �̷��� �����Լ��� �����Լ��� ����, �ڽ�(�Ļ�)Ŭ�������� �ݵ�� �����ϵ��� ���� �� �ִ�.
// �����Լ��� �ڽ�(�Ļ�)Ŭ�������� �ݵ�� �����ؾ��Ѵ�. --> �ڽ�(�Ļ�) Ŭ�������� �������� ������, ������ ������ �߻��Ѵ�.
// ����
// ���Ŭ�������� Virtual �Լ���(),
// �Ļ�Ŭ�������� Virtual �Լ���() override





// ���� Ŭ�������� ���輳���� 
//   is a ����          has a ����
// ����� �����̴�.    �ڵ����� ������ ������.


#include <iostream>
#include <vector>


// Shape Ŭ���� ����
class Shape {
public:
    // �żҵ� - ���� ���� �Լ�
    virtual double area() const = 0; // ���� ���� �Լ�: ������ ���
    virtual double perimeter() const = 0; // ���� ���� �Լ�: �ѷ��� ���
    };

// Circle Ŭ���� ����
class Circle : public Shape {

private:
    double m_radius; // ������

public:
    // ������
    Circle(double radius) : m_radius(radius) {}

    // �Ҹ���
    virtual ~Circle() {}

    // �żҵ� - ���� ��� ���� �Լ�
    virtual double area() const override {
        return 3.141592 * m_radius * m_radius;
        }
    // �żҵ� - �ѷ� ��� ���� �Լ�
    virtual double perimeter() const override {
        return 2 * 3.141592 * m_radius;
        }
    };

// Rectangle Ŭ���� ����
class Rectangle : public Shape {

private:
    double m_width; // �ʺ�
    double m_height; // ����

public:
    // ������
    Rectangle(double width, double height) : m_width(width), m_height(height) {}

    // ���� ��� ���� �Լ� ����
    virtual double area() const override {
        return m_width * m_height;
        }

    // �ѷ� ��� ���� �Լ� ����
    virtual double perimeter() const override {
        return 2 * (m_width + m_height);
        }
    };

// Diamond Ŭ���� ����
class Diamond : public Shape {

private:
    double m_width; // �ʺ�
    double m_height; // ����

public:
    // ������
    Diamond(double width, double height) : m_width(width), m_height(height) {}
    // ���� ��� ���� �Լ� ����
    virtual double area() const override {
        return m_width * m_height;
        }
    // �ѷ� ��� ���� �Լ� ����
    virtual double perimeter() const override {
        return 2 * (m_width + m_height);
        }
    };

// Ÿ�� Ŭ���� ����
class Ellipse : public Shape {

private:
    double m_radius1; // ������1
    double m_radius2; // ������2

public:
    // ������
    Ellipse(double radius1, double radius2) : m_radius1(radius1), m_radius2(radius2) {}
    // ���� ��� ���� �Լ� ����
    virtual double area() const override {
        return 3.141592 * m_radius1 * m_radius2;
        }
    // �ѷ� ��� ���� �Լ� ����
    virtual double perimeter() const override {
        return 2 * 3.141592 * (m_radius1 + m_radius2);
        }
    };


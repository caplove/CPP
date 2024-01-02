#include <iostream>

/**
 * MyClass is a simple class that contains two integer values.
 * It has a constructor and destructor, and methods to get and set the value of m_value1.
 */
class MyClass
	{
	public:
		MyClass(); // Constructor
		~MyClass(); // Destructor
		int GetValue(); // Method to get the value of m_value1
		void SetValue(int value); // Method to set the value of m_value1

	private:
		int m_value1; // First value
		int n_value2; // Second value

	};

// Constructor implementation
MyClass::MyClass()
	{
	m_value1 = 1;
	n_value2 = 2;
	}

// Destructor implementation
MyClass::~MyClass()
	{
	}

/**
 * void_Cinfunction is a function that takes a MyClass object by value.
 * It multiplies the value of m_value1 by 10 and sets the result back to m_value1.
 */
void void_Cinfunction(MyClass a) {

	std::cout << "void_Cinfunction a�� �ּ� : " << &a << std::endl;

	int temp = a.GetValue() * 10;
	a.SetValue(temp);
	}

/**
 * void_Addinfunction is a function that takes a MyClass object by reference.
 * It multiplies the value of m_value1 by 10 and sets the result back to m_value1.
 */
void void_Addinfunction(MyClass& a) {

	std::cout << "void_Addinfunction a�� �ּ� : " << &a << std::endl;

	int temp = a.GetValue() * 10;
	a.SetValue(temp);
	}

/**
 * AddinAddoutfunction is a function that takes a MyClass object by reference and returns it by reference.
 * It multiplies the value of m_value1 by 10 and sets the result back to m_value1.
 */
MyClass& AddinAddoutfunction(MyClass& a) {

	std::cout << "AddinAddoutfunction a�� �ּ� : " << &a << std::endl;

	int temp = a.GetValue() * 10;
	a.SetValue(temp);
	return a;
	}

int main() {

	MyClass MyObject, ReturnObject;

	std::cout << "����ϱ� �� �� ��� :" << MyObject.GetValue() << std::endl;
	std::cout << "����ϱ� �� Add ��� :" << &MyObject << std::endl;

	void_Addinfunction(MyObject);
	std::cout << "void_Addinfunction ��� :" << MyObject.GetValue() << std::endl;
	std::cout << "void_Addinfunction �ּ���� :" << &MyObject << std::endl;

	void_Cinfunction(MyObject);
	std::cout << "void_Cinfunction ��� :" << MyObject.GetValue() << std::endl;
	std::cout << "void_Cinfunction �ּ���� :" << &MyObject << std::endl;

	ReturnObject = AddinAddoutfunction(MyObject);

	std::cout << "AddinAddoutfunction �Է� ��� :" << MyObject.GetValue() << std::endl;
	std::cout << "AddinAddoutfunction ��� ���  :" << ReturnObject.GetValue() << std::endl;
	std::cout << "����ϱ� �� Addin �ּ���� :" << &MyObject << std::endl;
	std::cout << "����ϱ� �� Addout �ּ���� :" << &ReturnObject << std::endl;
	}

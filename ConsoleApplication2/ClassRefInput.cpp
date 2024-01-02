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

	std::cout << "void_Cinfunction a의 주소 : " << &a << std::endl;

	int temp = a.GetValue() * 10;
	a.SetValue(temp);
	}

/**
 * void_Addinfunction is a function that takes a MyClass object by reference.
 * It multiplies the value of m_value1 by 10 and sets the result back to m_value1.
 */
void void_Addinfunction(MyClass& a) {

	std::cout << "void_Addinfunction a의 주소 : " << &a << std::endl;

	int temp = a.GetValue() * 10;
	a.SetValue(temp);
	}

/**
 * AddinAddoutfunction is a function that takes a MyClass object by reference and returns it by reference.
 * It multiplies the value of m_value1 by 10 and sets the result back to m_value1.
 */
MyClass& AddinAddoutfunction(MyClass& a) {

	std::cout << "AddinAddoutfunction a의 주소 : " << &a << std::endl;

	int temp = a.GetValue() * 10;
	a.SetValue(temp);
	return a;
	}

int main() {

	MyClass MyObject, ReturnObject;

	std::cout << "계산하기 전 값 출력 :" << MyObject.GetValue() << std::endl;
	std::cout << "계산하기 전 Add 출력 :" << &MyObject << std::endl;

	void_Addinfunction(MyObject);
	std::cout << "void_Addinfunction 결과 :" << MyObject.GetValue() << std::endl;
	std::cout << "void_Addinfunction 주소출력 :" << &MyObject << std::endl;

	void_Cinfunction(MyObject);
	std::cout << "void_Cinfunction 결과 :" << MyObject.GetValue() << std::endl;
	std::cout << "void_Cinfunction 주소출력 :" << &MyObject << std::endl;

	ReturnObject = AddinAddoutfunction(MyObject);

	std::cout << "AddinAddoutfunction 입력 결과 :" << MyObject.GetValue() << std::endl;
	std::cout << "AddinAddoutfunction 출력 결과  :" << ReturnObject.GetValue() << std::endl;
	std::cout << "계산하기 후 Addin 주소출력 :" << &MyObject << std::endl;
	std::cout << "계산하기 후 Addout 주소출력 :" << &ReturnObject << std::endl;
	}

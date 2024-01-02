#include <iostream>

// explict / mutable
// 생성자에 explicit 한정이 붙으면,   생성자의 입력 형식(int)을 추론하지 못하도록 명확히, 엄격히 한다. 즉, float형을 입력하면, error가 발생한다.
// mutable is used to modify a member of a class from a const member function
// 주로 Cache를 사용하여, Memory --> Cache --> CPU로 데이터를 전송할 때, Cache 정보는 통상적으로 변경되지 않는다.
// 그러나, Cache 정보를 변경하는 경우가 있을 수 있다. 이럴 때, mutable을 사용한다.
// case : 회원정보를 저장하는 클래스에서, 회원정보를 출력하는 함수를 const로 선언하고, 회원정보를 출력할 때, Cache를 사용하는 경우


class A
	{
	int data_;
	mutable int cache_; // mutable은 const member function에서도 변경할 수 있도록 허용한다.


	public:
		explicit A(int data) : data_(data), cache_(data) {};
		
		// 방법1. mutable을 사용하지 않고, const_cast를 사용한다.
		void Dosomething1(int x) const
			{
			// data_ = x; // error
			const_cast<A*>(this)->data_ = x; // explicit mutable	
			}

		// 방법2. mutable을 사용한다.
		void Dosomething2(int x) const
			{
			cache_ = x; // ok
			};

		void print() const
			{
			// 자신의 변수명인 this와 맴버변수를 한줄에 출력
			std::cout << "this : " << this << ", data : " << data_ << ", cache : " << cache_ << std::endl;
			};

	};

//------------------------------------------------------------------------
void DosomethingwithA(A a)
	{
	a.Dosomething1(20); // ok
	a.print();
	};




int main()
	{
	A a(10); // a.data_ = 10;
	A c(1.9); // a.data_ = 1; a.cache_ = 20;

	a.Dosomething1(3.4); // a.data_ = "a";
	a.print();
	a.Dosomething1(20); // a.data_ = 20;
	a.Dosomething2(30); // a.cache_ = 30;

	c.print();

	//DosomethingwithA(1.5); // error,  explicit 때문에 엄격하게 입력변수를 받는다.
	DosomethingwithA(A(1.5)); // ok



	};









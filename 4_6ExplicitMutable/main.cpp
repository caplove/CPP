#include <iostream>

// explict / mutable
// �����ڿ� explicit ������ ������,   �������� �Է� ����(int)�� �߷����� ���ϵ��� ��Ȯ��, ������ �Ѵ�. ��, float���� �Է��ϸ�, error�� �߻��Ѵ�.
// mutable is used to modify a member of a class from a const member function
// �ַ� Cache�� ����Ͽ�, Memory --> Cache --> CPU�� �����͸� ������ ��, Cache ������ ��������� ������� �ʴ´�.
// �׷���, Cache ������ �����ϴ� ��찡 ���� �� �ִ�. �̷� ��, mutable�� ����Ѵ�.
// case : ȸ�������� �����ϴ� Ŭ��������, ȸ�������� ����ϴ� �Լ��� const�� �����ϰ�, ȸ�������� ����� ��, Cache�� ����ϴ� ���


class A
	{
	int data_;
	mutable int cache_; // mutable�� const member function������ ������ �� �ֵ��� ����Ѵ�.


	public:
		explicit A(int data) : data_(data), cache_(data) {};
		
		// ���1. mutable�� ������� �ʰ�, const_cast�� ����Ѵ�.
		void Dosomething1(int x) const
			{
			// data_ = x; // error
			const_cast<A*>(this)->data_ = x; // explicit mutable	
			}

		// ���2. mutable�� ����Ѵ�.
		void Dosomething2(int x) const
			{
			cache_ = x; // ok
			};

		void print() const
			{
			// �ڽ��� �������� this�� �ɹ������� ���ٿ� ���
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

	//DosomethingwithA(1.5); // error,  explicit ������ �����ϰ� �Էº����� �޴´�.
	DosomethingwithA(A(1.5)); // ok



	};









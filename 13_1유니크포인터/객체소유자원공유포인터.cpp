
// 객체 소유 포인터 - unique_ptr
// 자원 공유 포인터 - shared_ptr, weak_ptr

#include <iostream>
#include <memory>


// 일반 포인터
class A {
    int* data;

public:
    A() {
        data = new int[100];
        std::cout << "자원을 획득함!" << std::endl;
    }

    ~A() {
        std::cout << "소멸자 호출!" << std::endl;
        delete[] data;
    }
};

void do_something() { 
    A* pa = new A(); 
    std::cout << "일반 포인터 사용!" << std::endl;
    delete pa;
}

void main1() {
    std::cout << "" << std::endl << "main1 시작(일반 포인터)" << std::endl;
    do_something();
    // 일반 포인터를 사용하면, delete 연산자를 사용하지 않으면
    // 할당된 객체가 소멸되지 않음!
    // 즉, 400 바이트 (4 * 100) 만큼의 메모리 누수 발생
}









// unique_ptr : 객체 소유 포인터
class B {
    int* data;

public:
    B() {
        std::cout << "자원을 획득함!" << std::endl;
        data = new int[100];
    }

    void some() { std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl; }

    ~B() {
        std::cout << "자원을 해제함!" << std::endl;
        delete[] data;
    }
};

void do_something2() {
    std::unique_ptr<B> pa(new B());  // A 객체를 가리키는 unique_ptr 생성,  A* pa = new A(); 와 동일
    pa->some();					  // 일반 포인터와 동일하게 사용가능
    //delete pa;  // unique_ptr은 delete 연산자를 사용하지 않는다.
}

void main2() { 
    std::cout << ""<< std::endl << "main2 시작(unique_ptr)" << std::endl;
    do_something2(); 
}




// 함수에 unique_ptr 전달하기
void do_something3(std::unique_ptr<B> pa) {
	std::cout << "일반 포인터와 동일하게 사용가능!" << std::endl;
}

void main3() {
	std::cout << "" << std::endl << "main3 시작 (함수에 unique_ptr 전달)" << std::endl;
	std::unique_ptr<B> pa(new B());  // A 객체를 가리키는 unique_ptr 생성,  B* pa = new B(); 와 동일
	do_something3(std::move(pa));					  // 일반 포인터와 동일하게 사용가능
	//delete pa;  // unique_ptr은 delete 연산자를 사용하지 않는다.
}





// unique_ptr을 사용한 컨테이너
// vector에 unique_ptr을 넣을 때는 emplace_back을 사용해야 한다.
// push_back을 사용하면, 복사 생성자가 호출되기 때문에, unique_ptr의 소유권이 이전되지 않는다.

#include <vector>
class D {
    int* data;

    public:
        D(int i) {
			data = new int[100];
			std::cout << "자원을 획득함!" << std::endl;
            data[0] = i;
		}

        void some() { std::cout << "값:" << data[0] << std::endl; }

		~D() {
			std::cout << "자원을 해제함!" << std::endl;
			delete[] data;
		}
        };

void main4() {
    std::cout << "" << std::endl << "main4 시작 (unique_ptr을 사용한 컨테이너)" << std::endl;
    std::vector<std::unique_ptr<D>> vec; // class D를 가리키는 unique_ptr을 원소로 가지는 vector 생성
    vec.emplace_back(new D(2)); // vector의 맨뒤에 D(2)를 가리키는 unique_ptr을 추가
    vec.back()->some();     // vector의 맨뒤에 있는 unique_ptr이 가리키는 D(2)의 some() 호출
}







void main() {
	main1();
	main2();
    main3();
    main4();
}   



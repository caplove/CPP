
//예외발생시키기
// throw 예외객체;
// 예외객체 :out_of_range, overflow_error, underflow_error, runtime_error, bad_alloc, bad_cast, bad_exception, bad_typeid, 
// bad_function_call, bad_weak_ptr, logic_error, domain_error, invalid_argument, length_error, out_of_range, runtime_error, 
// range_error, overflow_error, underflow_error
// 예외처리하고 나면, stack에 생성된 객체를 소멸시켜준다. good

// 예외처리하기
// try - throw - catch

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
public:
    Vector(size_t size) : size_(size) {
        data_ = new T[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = 3;
        }
    }
    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("vector 의 index 가 범위를 초과하였습니다.");
        }
        return data_[index];
    }
    ~Vector() { delete[] data_; }

private:
    T* data_;
    size_t size_;
};
 void main1() {
    printf("main1\n");
    Vector<int> vec(10); // 값이 3인 벡터 생성

    // vector의 내용출력
    for (int i = 0; i < 10; i++) {
		std::cout << vec.at(i) << " ";
	}
    std::cout << std::endl;

    std::cout << "읽을 인덱스 : ";
    int index, data = 0;
    std::cin >> index;

    try {
        data = vec.at(index);
    }
    catch (std::out_of_range& e) {
        std::cout << "예외 발생 ! " << e.what() << std::endl;
    }
    
    // 예외가 발생하지 않았다면 3을 이 출력
    std::cout << "읽은 데이터 : " << data << std::endl;
}




 // throw 예외객체의 따라서 catch가 실행된다.
 int func(int c) {
     if (c == 1) {
         throw 10;
     }
     else if (c == 2) {
         throw std::string("hi!");
     }
     else if (c == 3) {
         throw 'a';
     }
     else if (c == 4) {
         throw "hello!";
     }
     return 0;
 }

void main2() {
     int c;
     printf("main2\n");
     std::cout << "1. int 2. string 3. char 4. string literal : ";
     std::cin >> c;

     try {
         func(c);
     }
     catch (char x) {
         std::cout << "Char : " << x << std::endl;
     }
     catch (int x) {
         std::cout << "Int : " << x << std::endl;
     }
     catch (std::string& s) {
         std::cout << "String : " << s << std::endl;
     }
     catch (const char* s) {
         std::cout << "String Literal : " << s << std::endl;
     }
 }


// 예외가 발생하면, stack에 생성된 객체를 소멸시켜준 후, catch로 넘어간다.
class Resource {
public:
    Resource(int id) : id_(id) {}
    ~Resource() { std::cout << "리소스 해제 : " << id_ << std::endl; }

private:
    int id_;
};

int func3() {
    Resource r(3);
    throw std::runtime_error("Exception from 3!\n");
}
int func2() {
    Resource r(2);
    func3();
    std::cout << "실행 안됨!" << std::endl;
    return 0;
}
int func1() {
    Resource r(1);
    func2();
    std::cout << "실행 안됨!" << std::endl;
    return 0;
}

void main3() {
    printf("main3\n");
    try {
        func1();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}



// 상속 관계에서의 예외처리
class Parent : public std::exception {
public:
    virtual const char* what() const noexcept override { return "Parent!\n"; }
};

class Child : public Parent {
public:
    const char* what() const noexcept override { return "Child!\n"; }
};

int func4(int c) {
    if (c == 1) {
        throw Parent();
    }
    else if (c == 2) {
        throw Child();
    }
    return 0;
}

void main4() {
    int c;
    std::cout << "1. Parent 2. Child : ";
    std::cin >> c;

    try {
        func4(c);
    }
    // Parent& p = Child(); 이므로 반드시 Child가 먼저 와야한다.
    // Child& c = Parent(); 는 불가능하다.
    catch (Child& c) {
        std::cout << "Child Catch!" << std::endl;
        std::cout << c.what();
    }
    catch (Parent& p) {
        std::cout << "Parent Catch!" << std::endl;
        std::cout << p.what();
    }
}



int func5() { throw std::runtime_error("error"); }

void main5() {
    try {
        func5();
    }
    catch (int i) {
        std::cout << "Catch int : " << i;
    }
	//catch (std::exception& e) {
	//	std::cout << "Catch exception : " << e.what();
	//}
	catch (...) {
		std::cout << "Default Catch ...";
	}
};


void main() {
    main1();
    main2();
    main3();
    main4();
    main5();
};
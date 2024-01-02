
//���ܹ߻���Ű��
// throw ���ܰ�ü;
// ���ܰ�ü :out_of_range, overflow_error, underflow_error, runtime_error, bad_alloc, bad_cast, bad_exception, bad_typeid, 
// bad_function_call, bad_weak_ptr, logic_error, domain_error, invalid_argument, length_error, out_of_range, runtime_error, 
// range_error, overflow_error, underflow_error
// ����ó���ϰ� ����, stack�� ������ ��ü�� �Ҹ�����ش�. good

// ����ó���ϱ�
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
            throw std::out_of_range("vector �� index �� ������ �ʰ��Ͽ����ϴ�.");
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
    Vector<int> vec(10); // ���� 3�� ���� ����

    // vector�� �������
    for (int i = 0; i < 10; i++) {
		std::cout << vec.at(i) << " ";
	}
    std::cout << std::endl;

    std::cout << "���� �ε��� : ";
    int index, data = 0;
    std::cin >> index;

    try {
        data = vec.at(index);
    }
    catch (std::out_of_range& e) {
        std::cout << "���� �߻� ! " << e.what() << std::endl;
    }
    
    // ���ܰ� �߻����� �ʾҴٸ� 3�� �� ���
    std::cout << "���� ������ : " << data << std::endl;
}




 // throw ���ܰ�ü�� ���� catch�� ����ȴ�.
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


// ���ܰ� �߻��ϸ�, stack�� ������ ��ü�� �Ҹ������ ��, catch�� �Ѿ��.
class Resource {
public:
    Resource(int id) : id_(id) {}
    ~Resource() { std::cout << "���ҽ� ���� : " << id_ << std::endl; }

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
    std::cout << "���� �ȵ�!" << std::endl;
    return 0;
}
int func1() {
    Resource r(1);
    func2();
    std::cout << "���� �ȵ�!" << std::endl;
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



// ��� ���迡���� ����ó��
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
    // Parent& p = Child(); �̹Ƿ� �ݵ�� Child�� ���� �;��Ѵ�.
    // Child& c = Parent(); �� �Ұ����ϴ�.
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

// ��ü ���� ������ - unique_ptr
// �ڿ� ���� ������ - shared_ptr, weak_ptr

#include <iostream>
#include <memory>


// �Ϲ� ������
class A {
    int* data;

public:
    A() {
        data = new int[100];
        std::cout << "�ڿ��� ȹ����!" << std::endl;
    }

    ~A() {
        std::cout << "�Ҹ��� ȣ��!" << std::endl;
        delete[] data;
    }
};

void do_something() { 
    A* pa = new A(); 
    std::cout << "�Ϲ� ������ ���!" << std::endl;
    delete pa;
}

void main1() {
    std::cout << "" << std::endl << "main1 ����(�Ϲ� ������)" << std::endl;
    do_something();
    // �Ϲ� �����͸� ����ϸ�, delete �����ڸ� ������� ������
    // �Ҵ�� ��ü�� �Ҹ���� ����!
    // ��, 400 ����Ʈ (4 * 100) ��ŭ�� �޸� ���� �߻�
}









// unique_ptr : ��ü ���� ������
class B {
    int* data;

public:
    B() {
        std::cout << "�ڿ��� ȹ����!" << std::endl;
        data = new int[100];
    }

    void some() { std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��밡��!" << std::endl; }

    ~B() {
        std::cout << "�ڿ��� ������!" << std::endl;
        delete[] data;
    }
};

void do_something2() {
    std::unique_ptr<B> pa(new B());  // A ��ü�� ����Ű�� unique_ptr ����,  A* pa = new A(); �� ����
    pa->some();					  // �Ϲ� �����Ϳ� �����ϰ� ��밡��
    //delete pa;  // unique_ptr�� delete �����ڸ� ������� �ʴ´�.
}

void main2() { 
    std::cout << ""<< std::endl << "main2 ����(unique_ptr)" << std::endl;
    do_something2(); 
}




// �Լ��� unique_ptr �����ϱ�
void do_something3(std::unique_ptr<B> pa) {
	std::cout << "�Ϲ� �����Ϳ� �����ϰ� ��밡��!" << std::endl;
}

void main3() {
	std::cout << "" << std::endl << "main3 ���� (�Լ��� unique_ptr ����)" << std::endl;
	std::unique_ptr<B> pa(new B());  // A ��ü�� ����Ű�� unique_ptr ����,  B* pa = new B(); �� ����
	do_something3(std::move(pa));					  // �Ϲ� �����Ϳ� �����ϰ� ��밡��
	//delete pa;  // unique_ptr�� delete �����ڸ� ������� �ʴ´�.
}





// unique_ptr�� ����� �����̳�
// vector�� unique_ptr�� ���� ���� emplace_back�� ����ؾ� �Ѵ�.
// push_back�� ����ϸ�, ���� �����ڰ� ȣ��Ǳ� ������, unique_ptr�� �������� �������� �ʴ´�.

#include <vector>
class D {
    int* data;

    public:
        D(int i) {
			data = new int[100];
			std::cout << "�ڿ��� ȹ����!" << std::endl;
            data[0] = i;
		}

        void some() { std::cout << "��:" << data[0] << std::endl; }

		~D() {
			std::cout << "�ڿ��� ������!" << std::endl;
			delete[] data;
		}
        };

void main4() {
    std::cout << "" << std::endl << "main4 ���� (unique_ptr�� ����� �����̳�)" << std::endl;
    std::vector<std::unique_ptr<D>> vec; // class D�� ����Ű�� unique_ptr�� ���ҷ� ������ vector ����
    vec.emplace_back(new D(2)); // vector�� �ǵڿ� D(2)�� ����Ű�� unique_ptr�� �߰�
    vec.back()->some();     // vector�� �ǵڿ� �ִ� unique_ptr�� ����Ű�� D(2)�� some() ȣ��
}







void main() {
	main1();
	main2();
    main3();
    main4();
}   



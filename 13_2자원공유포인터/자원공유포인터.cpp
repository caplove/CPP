
// �������� ����Ʈ�����Ͱ� �ϳ��� ��ü�� �����ؾ� �ϴ� ��찡 �ִ�.
// �̷� ��쿡�� shared_ptr�� ����Ѵ�.
// shared_ptr�� �������� ����Ʈ�����Ͱ� �ϳ��� ��ü�� ������ �� �ֵ���
// ���� ī������ ����Ѵ�.
// ���� ī������ ��ü�� �����ϴ� ����Ʈ�������� ������ �����ϴ� �����̴�.
// ���� ī������ ��ü�� �����ϴ� ����Ʈ�������� ������ 0�� �Ǹ� ��ü�� �����Ѵ�.
// 
//std::shared_ptr<A> p1(new A());
//std::shared_ptr<A> p2(p1);  // p2 ���� ������ ��ü A �� ����Ų��.
//
//// �ݸ鿡 unique_ptr �� ���
//std::unique_ptr<A> p1(new A());
//std::unique_ptr<A> p2(p1);  // ������ ����!

// ���� : ��	> std::make_shared<A>(����);
// ���� : ��	> std::shared_ptr<A> p2(p1);
// ���� : ��	> p2 = p1;
// �Ҹ� : ��	> p1.reset(); // p1�� ����Ű�� ��ü�� ���� ī������ 1 ���ҽ�Ų��.
// �Ҹ� : ��	> p1 = nullptr; // p1�� ����Ű�� ��ü�� ���� ī������ 1 ���ҽ�Ų��.

// shared_ptr���� ��ȯ������ �ذ��ϱ� ���ؼ��� weak_ptr�� ����Ѵ�.
// weak_ptr�� shared_ptr�� �����ϰ� ��ü�� ���������� ���� ī���ÿ��� ���Ե��� �ʴ´�.
// weak_ptr�� ��ü�� �����ϴ� ����Ʈ�������� ������ 0�� �Ǹ� ��ü�� �����Ѵ�.

// ���� 1
// �Ѱ��� �θ��忡�� �������� �ڽĳ�带 ����Ű�� ���
// �θ���� �ڽĳ�带 ����Ű�� shared_ptr�� ������ �ְ�
// �ڽĳ��� �θ��带 ����Ű�� weak_ptr�� ������ �ִ�.
// �̷��� �ϸ� �θ���� �ڽĳ�尣�� ��ȯ������ �ذ��� �� �ִ�.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class A {
    std::string s;
    std::weak_ptr<A> other;

public:
    A(const std::string& s) : s(s) { std::cout << "�ڿ��� ȹ����!" << std::endl; }

    ~A() { std::cout << "�Ҹ��� ȣ��!" << std::endl; }

    void set_other(std::weak_ptr<A> o) { other = o; }
    void access_other() {
        std::shared_ptr<A> o = other.lock(); // weak_ptr�� shared_ptr�� ��ȯ (���Ҹ� �����ϱ� ���ؼ�, ���� ī������ ������Ų��.)
        if (o) {
            std::cout << "���� : " << o->name() << std::endl;
        }
        else {
            std::cout << "�̹� �Ҹ�� ��" << std::endl;
        }
    }
    std::string name() { return s; }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;
    vec.push_back(std::make_shared<A>("�ڿ� 1")); // vec[0].s = "�ڿ� 1"
    vec.push_back(std::make_shared<A>("�ڿ� 2")); // vec[1].s = "�ڿ� 2"

    vec[0]->set_other(vec[1]); // vec[0].other = vec[1]
    vec[1]->set_other(vec[0]); // vec[1].other = vec[0]

    // pa �� pb �� ref count �� �״�δ�.
    std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

    // weak_ptr �� �ش� ��ü �����ϱ�
    vec[0]->access_other();

    // ���� ������ ���� ���� (vec[1] �Ҹ�)
    vec.pop_back();
    vec[0]->access_other();  // ���� ����!
}


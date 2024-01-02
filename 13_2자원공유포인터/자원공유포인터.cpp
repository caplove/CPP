
// 여러개의 스마트포인터가 하나의 객체를 소유해야 하는 경우가 있다.
// 이런 경우에는 shared_ptr을 사용한다.
// shared_ptr은 여러개의 스마트포인터가 하나의 객체를 소유할 수 있도록
// 참조 카운팅을 사용한다.
// 참조 카운팅은 객체를 참조하는 스마트포인터의 개수를 저장하는 변수이다.
// 참조 카운팅은 객체를 참조하는 스마트포인터의 개수가 0이 되면 객체를 삭제한다.
// 
//std::shared_ptr<A> p1(new A());
//std::shared_ptr<A> p2(p1);  // p2 역시 생성된 객체 A 를 가리킨다.
//
//// 반면에 unique_ptr 의 경우
//std::unique_ptr<A> p1(new A());
//std::unique_ptr<A> p2(p1);  // 컴파일 오류!

// 생성 : ㅡ	> std::make_shared<A>(인자);
// 복사 : ㅡ	> std::shared_ptr<A> p2(p1);
// 대입 : ㅡ	> p2 = p1;
// 소멸 : ㅡ	> p1.reset(); // p1이 가리키는 객체의 참조 카운팅을 1 감소시킨다.
// 소멸 : ㅡ	> p1 = nullptr; // p1이 가리키는 객체의 참조 카운팅을 1 감소시킨다.

// shared_ptr간의 순환참조를 해결하기 위해서는 weak_ptr을 사용한다.
// weak_ptr은 shared_ptr과 동일하게 객체를 참조하지만 참조 카운팅에는 포함되지 않는다.
// weak_ptr은 객체를 참조하는 스마트포인터의 개수가 0이 되면 객체를 삭제한다.

// 예제 1
// 한개의 부모노드에서 여러개의 자식노드를 가리키는 경우
// 부모노드는 자식노드를 가리키는 shared_ptr을 가지고 있고
// 자식노드는 부모노드를 가리키는 weak_ptr을 가지고 있다.
// 이렇게 하면 부모노드와 자식노드간의 순환참조를 해결할 수 있다.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class A {
    std::string s;
    std::weak_ptr<A> other;

public:
    A(const std::string& s) : s(s) { std::cout << "자원을 획득함!" << std::endl; }

    ~A() { std::cout << "소멸자 호출!" << std::endl; }

    void set_other(std::weak_ptr<A> o) { other = o; }
    void access_other() {
        std::shared_ptr<A> o = other.lock(); // weak_ptr을 shared_ptr로 변환 (원소를 참조하기 위해서, 참조 카운팅을 증가시킨다.)
        if (o) {
            std::cout << "접근 : " << o->name() << std::endl;
        }
        else {
            std::cout << "이미 소멸됨 ㅠ" << std::endl;
        }
    }
    std::string name() { return s; }
};

int main() {
    std::vector<std::shared_ptr<A>> vec;
    vec.push_back(std::make_shared<A>("자원 1")); // vec[0].s = "자원 1"
    vec.push_back(std::make_shared<A>("자원 2")); // vec[1].s = "자원 2"

    vec[0]->set_other(vec[1]); // vec[0].other = vec[1]
    vec[1]->set_other(vec[0]); // vec[1].other = vec[0]

    // pa 와 pb 의 ref count 는 그대로다.
    std::cout << "vec[0] ref count : " << vec[0].use_count() << std::endl;
    std::cout << "vec[1] ref count : " << vec[1].use_count() << std::endl;

    // weak_ptr 로 해당 객체 접근하기
    vec[0]->access_other();

    // 벡터 마지막 원소 제거 (vec[1] 소멸)
    vec.pop_back();
    vec[0]->access_other();  // 접근 실패!
}


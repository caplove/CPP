
// list 컨테이너
// list 컨테이너는 연결 리스트를 구현한 컨테이너
// 연결 리스트는 데이터를 노드라는 단위로 관리
// 노드는 데이터와 다음 노드를 가리키는 포인터로 구성
// vector 컨테이너는 임의의 위치에 접근하여 원소를 삽입하거나 삭제할 수 있다.
// list 컨테이너는 임의의 위치에 접근불가하여 원소를 삽입하거나 삭제할 수 없다.
// 즉, ++itr, itr++ 가능, itr + 5 불가능

// deque 컨테이너
// deque 컨테이너는 vector 컨테이너와 비슷한 컨테이너
// vector 컨테이너는 원소를 배열로 관리
// deque 컨테이너는 원소를 블록으로 관리
// vector 컨테이너는 원소를 삽입하거나 삭제할 때 맨 뒤를 제외한 나머지 원소를 이동해야 한다.
// deque 컨테이너는 원소를 삽입하거나 삭제할 때 맨 뒤를 제외한 나머지 원소를 이동하지 않아도 된다.
// deque 컨테이너는 속도는 빠르지만, 메모리를 vector보다 많이 사용한다.
// 속도가 빠른 이유는 vector는 새로운 메모리 영역을 할당하고, 벡터를 전부 복사해야 하지만
// deque는 새로 추가된 메모리 영역만 할당하고, 기존의 메모리 영역은 그대로 둔다.


#include <iostream>
#include <list>
#include <deque>

// iter로 리스트 접근하기
template <typename T>
void print_list(std::list<T>& lst) {
    std::cout << "[ ";
    // 전체 리스트를 출력하기 (이 역시 범위 기반 for 문을 쓸 수 있습니다)
    for (const auto& elem : lst) {
        std::cout << elem << " ";
        }
    std::cout << "]" << std::endl;
    }
void main1() {
    std::list<int> lst;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    lst.push_back(40);

    std::cout << "처음 리스트의 상태 " << std::endl;
    print_list(lst);

    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        // 만일 현재 원소가 20 이라면
        // 그 앞에 50 을 집어넣는다.
        if (*itr == 20) {
            lst.insert(itr, 50);
            }
        }

    std::cout << "값이 20 인 원소 앞에 50 을 추가 " << std::endl;
    print_list(lst);

    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        // 값이 30 인 원소를 삭제한다.
        if (*itr == 30) {
            lst.erase(itr);
            break;
            }
        }

    std::cout << "값이 30 인 원소를 제거한다" << std::endl;
    print_list(lst);
    }

// deque 컨테이너
template <typename T>
void print_deque(std::deque<T>& dq) {
    // 전체 덱을 출력하기
    std::cout << "[ ";
    for (const auto& elem : dq) {
        std::cout << elem << " ";
        }
    std::cout << " ] " << std::endl;
    }
void main2() {
    std::deque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(30);
    dq.push_front(40);

    std::cout << "초기 dq 상태" << std::endl;
    print_deque(dq);

    std::cout << "맨 앞의 원소 제거 by pop_front()" << std::endl;
    dq.pop_front();
    print_deque(dq);

    std::cout << "맨 뒤의 원소 제거 by pop_back()" << std::endl;
    dq.pop_back();
    print_deque(dq);
    }


void main() {
    	main1();
        main2();
	}

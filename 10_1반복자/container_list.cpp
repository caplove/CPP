
// list �����̳�
// list �����̳ʴ� ���� ����Ʈ�� ������ �����̳�
// ���� ����Ʈ�� �����͸� ����� ������ ����
// ���� �����Ϳ� ���� ��带 ����Ű�� �����ͷ� ����
// vector �����̳ʴ� ������ ��ġ�� �����Ͽ� ���Ҹ� �����ϰų� ������ �� �ִ�.
// list �����̳ʴ� ������ ��ġ�� ���ٺҰ��Ͽ� ���Ҹ� �����ϰų� ������ �� ����.
// ��, ++itr, itr++ ����, itr + 5 �Ұ���

// deque �����̳�
// deque �����̳ʴ� vector �����̳ʿ� ����� �����̳�
// vector �����̳ʴ� ���Ҹ� �迭�� ����
// deque �����̳ʴ� ���Ҹ� ������� ����
// vector �����̳ʴ� ���Ҹ� �����ϰų� ������ �� �� �ڸ� ������ ������ ���Ҹ� �̵��ؾ� �Ѵ�.
// deque �����̳ʴ� ���Ҹ� �����ϰų� ������ �� �� �ڸ� ������ ������ ���Ҹ� �̵����� �ʾƵ� �ȴ�.
// deque �����̳ʴ� �ӵ��� ��������, �޸𸮸� vector���� ���� ����Ѵ�.
// �ӵ��� ���� ������ vector�� ���ο� �޸� ������ �Ҵ��ϰ�, ���͸� ���� �����ؾ� ������
// deque�� ���� �߰��� �޸� ������ �Ҵ��ϰ�, ������ �޸� ������ �״�� �д�.


#include <iostream>
#include <list>
#include <deque>

// iter�� ����Ʈ �����ϱ�
template <typename T>
void print_list(std::list<T>& lst) {
    std::cout << "[ ";
    // ��ü ����Ʈ�� ����ϱ� (�� ���� ���� ��� for ���� �� �� �ֽ��ϴ�)
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

    std::cout << "ó�� ����Ʈ�� ���� " << std::endl;
    print_list(lst);

    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        // ���� ���� ���Ұ� 20 �̶��
        // �� �տ� 50 �� ����ִ´�.
        if (*itr == 20) {
            lst.insert(itr, 50);
            }
        }

    std::cout << "���� 20 �� ���� �տ� 50 �� �߰� " << std::endl;
    print_list(lst);

    for (std::list<int>::iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        // ���� 30 �� ���Ҹ� �����Ѵ�.
        if (*itr == 30) {
            lst.erase(itr);
            break;
            }
        }

    std::cout << "���� 30 �� ���Ҹ� �����Ѵ�" << std::endl;
    print_list(lst);
    }

// deque �����̳�
template <typename T>
void print_deque(std::deque<T>& dq) {
    // ��ü ���� ����ϱ�
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

    std::cout << "�ʱ� dq ����" << std::endl;
    print_deque(dq);

    std::cout << "�� ���� ���� ���� by pop_front()" << std::endl;
    dq.pop_front();
    print_deque(dq);

    std::cout << "�� ���� ���� ���� by pop_back()" << std::endl;
    dq.pop_back();
    print_deque(dq);
    }


void main() {
    	main1();
        main2();
	}

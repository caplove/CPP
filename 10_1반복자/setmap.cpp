
//
// set, map은 이진 탐색 트리로 구현되어 있다.
// set은 데이터가 있는지 없는지 확인할 때, map은 데이터를 가져올 때 사용한다.
// set 은 key 만 저장하는 자료구조
// map 은 key 와 value 를 한 쌍으로 저장하는 자료구조
// set 자료에 접근하려면, 역시 iterator를 사용한다. (bidirectional iterator)
// key 와 value 를 한 쌍으로 저장하는 자료구조
// key 는 중복을 허용하지 않는다. (중복을 허용하려면 multimap 을 사용하면 된다.)
// key 는 원소들이 자동으로 정렬된다. (정렬을 원하지 않는다면 unordered_map 을 사용하면 된다.)
// key 는 원소들이 자동으로 정렬되기 때문에 find(), lower_bound(), upper_bound() 등의 함수를 사용할 수 있다.


#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_set(std::set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    std::cout << "[ ";
    for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
        std::cout << *itr << " ";
        }
    std::cout << " ] " << std::endl;
    }
void main1() {
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "순서대로 정렬되서 나온다" << std::endl;
    print_set(s);

    std::cout << "20 이 s 의 원소인가요? :: ";
    auto itr = s.find(20);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
        }
    else {
        std::cout << "No" << std::endl;
        }

    std::cout << "25 가 s 의 원소인가요? :: ";
    itr = s.find(25);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
        }
    else {
        std::cout << "No" << std::endl;
        }
    }


// key-value를 Class로 만들어서 사용하기
// priority 와 job_desc 를 가지고 있는 Todo 클래스를 만들어서 사용한다.
// Todo 클래스는 priority 가 같으면 job_desc 가 사전순으로 정렬되도록 구현한다.
// Todo 클래스는 operator< 를 구현해야 한다. 이유는 set 에서 원소를 정렬하기 위해서는 operator< 가 필요하기 때문이다.
// operator< 를 구현할 때는 priority 를 먼저 비교하고, priority 가 같으면 job_desc 를 비교한다.
// operator< 를 구현할 때는 const,friend 를 잘 사용해야 한다.

template <typename T>
void print_set2(std::set<T>& m) {
	// 맵의 모든 원소들을 출력하기
	std::cout << "[ ";

    for (const auto& elem : m) {
		std::cout << elem << " " << std::endl;
		}
         std::cout << " ] " << std::endl;
	}

class Todo {
    int priority;
    std::string job_desc;

public:
    Todo(int _priority, std::string _job_desc) : priority(_priority), job_desc(_job_desc) {}

    // 정렬하기 위한 비교 연산자 구현
    bool operator<(const Todo& t) const {
		if (priority == t.priority) {
            return job_desc < t.job_desc;
			}
		return priority > t.priority;
		}

    // operator<< 를 friend 로 선언한다. 이유는 operator<< 를 Todo 클래스의 멤버 함수로 구현할 수 없기 때문이다.
    // operator<< 를 Todo 클래스의 멤버 함수로 구현하면, 첫 번째 인자가 ostream& 이어야 한다.
	friend std::ostream& operator<<(std::ostream& o, const Todo& td) {
        o << "[ 중요도 : " << td.priority << "] " << td.job_desc;
        return o;
		}
    };

void main2() {
    std::set<Todo> todos;

    todos.insert(Todo(1, "저녁 먹기"));
    todos.insert(Todo(2, "공부하기"));
    todos.insert(Todo(3, "운동하기"));
    todos.insert(Todo(4, "커피 마시기"));
    todos.insert(Todo(5, "출근하기"));
    print_set2(todos);
    std::cout << "----------------------------------" << std::endl;
    std::cout << "3번째 할 일 찾기" << std::endl;
    auto itr = todos.begin();
    std::advance(itr, 2);
    std::cout << *itr << std::endl;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "3번째 할 일 지우기" << std::endl;
    todos.erase(itr);
    print_set2(todos);
    };


#include <map>

template <typename K, typename V>
void print_map3(std::map<K, V>& m) {
    // 맵의 모든 원소들을 출력하기
    std::cout << "[ ";
    //for (auto itr = m.begin(); itr != m.end(); ++itr) {
    for (const auto& elm : m) { // 위의 for 문과 동일한 코드, 범위기반 for문
        std::cout << elm.first << " : " << elm.second << " " << std::endl; // itr->first 는 key, itr->second 는 value
        }
    };


template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
    auto itr = m.find(key);
    if (itr != m.end()) {
        std::cout << key << " --> " << itr->second << std::endl;
        }
    else {
        std::cout << key << "은(는) 목록에 없습니다" << std::endl;
        }
    }


void main3() {
    std::map<std::string, double> pitcher_list;

    pitcher_list.insert(std::pair<std::string, double>("박세웅", 3.14));
    pitcher_list.insert(std::pair<std::string, double>("해커", 2.7));
    pitcher_list.insert(std::pair<std::string, double>("피어낸드", 1.4));
    pitcher_list.insert(std::pair<std::string, double>("피어낸드", 3.4)); // 중복된 key 는 저장되지 않는다.
    pitcher_list.insert(std::make_pair("박찬호", 0.7)); // 실제로는 이렇게 많이 사용한다.
    pitcher_list.insert(std::make_pair("류현진", 0.4));

    print_map3(pitcher_list);

    std::cout << "----------------------------------" << std::endl;
    search_and_print(pitcher_list, std::string("류현진"));
    search_and_print(pitcher_list, std::string("홍길동")); // find() 함수를 사용해서 key 를 찾는다.
    std::cout << "류현진의 평균 자책점은? :: " << pitcher_list["류현진"] << std::endl;
    std::cout << "홍길동의 평균 자책점은? :: " << pitcher_list["홍길동"] << std::endl; // 홍길동은 없지만, [] 연산자를 사용하면 새로운 원소가 추가된다.(위의방법)
    };



// unordered_set 은 random하게 원소를 저장한다. (정렬을 하지 않는다.)
// unordered_set 은 find() 함수를 사용할 수 없다. (iterator 를 사용할 수 없다.)
// is_exist() 함수를 만들어서 unordered_set 에 원소가 있는지 없는지 확인한다.
#include <unordered_set>

template <typename T>
void print_all_unordered_set(std::unordered_set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    std::cout << "[ ";
    for (const auto& elem : s) {
        std::cout << elem << " " << std::endl;
        std::cout << " ] " << std::endl;
        }
    };

template <typename T>
void is_exist(std::unordered_set<T>& s, T key) {
	auto itr = s.find(key);
	if (itr != s.end()) {
		std::cout << key << " --> " << *itr << std::endl;
		}
	else {
		std::cout << key << "은(는) 목록에 없습니다" << std::endl;
		}
	};


void main4() {

    std::unordered_set<std::string> s;

    s.insert("hello");
    s.insert("world");
    s.insert("bye");
    s.insert("again");
	s.insert("see you");

    print_all_unordered_set(s);
    is_exist(s, std::string("hello"));
    is_exist(s, std::string("junee"));
	};



void main() {
    main1();
    main2();
    main3();
    main4();
	}




// 내가만든 클래스를 unordered_set 에 넣기
// hash 를 구현해야한다.


#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>


template <typename T>
void print_all_unordered_set2(std::unordered_set<T>& s) {
	// 셋의 모든 원소들을 출력하기
	std::cout << "[ ";
	for (const auto& elem : s) {
		std::cout << elem << " " << std::endl;
		std::cout << " ] " << std::endl;
		}
	};

template <typename T>
void is_exist2(std::unordered_set<T>& s, T key) {
	auto itr = s.find(key);
	if (itr != s.end()) {
		std::cout << key << " --> " << *itr << std::endl;
		}
	else {
		std::cout << key << "은(는) 목록에 없습니다" << std::endl;
		}
	};

class Todo2 {
	int priority;
	std::string job_desc;

public:
	Todo2(int _priority, std::string _job_desc) : priority(_priority), job_desc(_job_desc) {}

	// 정렬하기 위한 비교 연산자 구현
	bool operator==(const Todo2& t) const {
		if (priority == t.priority && job_desc == t.job_desc) return true;
		return false;
		}

	friend std::ostream& operator<<(std::ostream& o, const Todo2& td) {
		o << "[ 중요도 : " << td.priority << "] " << td.job_desc;
		return o;
		}

	friend struct std::hash<Todo2>;

	};



// Todo2 클래스를 위한 hash 구현
namespace std {
	template <>
	struct hash<Todo2> {
		size_t operator()(const Todo2& td) const {
			return hash<int>()(td.priority) ^ hash<string>()(td.job_desc);
			}
		};
	}



int main() {
	std::unordered_set<Todo2> todos;

	todos.insert(Todo2(1, "저녁 먹기"));
	todos.insert(Todo2(2, "공부하기"));
	todos.insert(Todo2(3, "운동하기"));
	todos.insert(Todo2(4, "숨쉬기"));

	print_all_unordered_set2(todos);

	is_exist2(todos, Todo2(1, "저녁 먹기"));
	is_exist2(todos, Todo2(2, "공부하기"));
	is_exist2(todos, Todo2(3, "운동하기"));
	is_exist2(todos, Todo2(4, "숨쉬기"));
	is_exist2(todos, Todo2(5, "숨쉬기"));

	return 0;
	}

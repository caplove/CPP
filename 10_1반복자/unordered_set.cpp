

// �������� Ŭ������ unordered_set �� �ֱ�
// hash �� �����ؾ��Ѵ�.


#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>


template <typename T>
void print_all_unordered_set2(std::unordered_set<T>& s) {
	// ���� ��� ���ҵ��� ����ϱ�
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
		std::cout << key << "��(��) ��Ͽ� �����ϴ�" << std::endl;
		}
	};

class Todo2 {
	int priority;
	std::string job_desc;

public:
	Todo2(int _priority, std::string _job_desc) : priority(_priority), job_desc(_job_desc) {}

	// �����ϱ� ���� �� ������ ����
	bool operator==(const Todo2& t) const {
		if (priority == t.priority && job_desc == t.job_desc) return true;
		return false;
		}

	friend std::ostream& operator<<(std::ostream& o, const Todo2& td) {
		o << "[ �߿䵵 : " << td.priority << "] " << td.job_desc;
		return o;
		}

	friend struct std::hash<Todo2>;

	};



// Todo2 Ŭ������ ���� hash ����
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

	todos.insert(Todo2(1, "���� �Ա�"));
	todos.insert(Todo2(2, "�����ϱ�"));
	todos.insert(Todo2(3, "��ϱ�"));
	todos.insert(Todo2(4, "������"));

	print_all_unordered_set2(todos);

	is_exist2(todos, Todo2(1, "���� �Ա�"));
	is_exist2(todos, Todo2(2, "�����ϱ�"));
	is_exist2(todos, Todo2(3, "��ϱ�"));
	is_exist2(todos, Todo2(4, "������"));
	is_exist2(todos, Todo2(5, "������"));

	return 0;
	}

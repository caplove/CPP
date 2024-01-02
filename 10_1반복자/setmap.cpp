
//
// set, map�� ���� Ž�� Ʈ���� �����Ǿ� �ִ�.
// set�� �����Ͱ� �ִ��� ������ Ȯ���� ��, map�� �����͸� ������ �� ����Ѵ�.
// set �� key �� �����ϴ� �ڷᱸ��
// map �� key �� value �� �� ������ �����ϴ� �ڷᱸ��
// set �ڷῡ �����Ϸ���, ���� iterator�� ����Ѵ�. (bidirectional iterator)
// key �� value �� �� ������ �����ϴ� �ڷᱸ��
// key �� �ߺ��� ������� �ʴ´�. (�ߺ��� ����Ϸ��� multimap �� ����ϸ� �ȴ�.)
// key �� ���ҵ��� �ڵ����� ���ĵȴ�. (������ ������ �ʴ´ٸ� unordered_map �� ����ϸ� �ȴ�.)
// key �� ���ҵ��� �ڵ����� ���ĵǱ� ������ find(), lower_bound(), upper_bound() ���� �Լ��� ����� �� �ִ�.


#include <iostream>
#include <set>
#include <string>

template <typename T>
void print_set(std::set<T>& s) {
    // ���� ��� ���ҵ��� ����ϱ�
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

    std::cout << "������� ���ĵǼ� ���´�" << std::endl;
    print_set(s);

    std::cout << "20 �� s �� �����ΰ���? :: ";
    auto itr = s.find(20);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
        }
    else {
        std::cout << "No" << std::endl;
        }

    std::cout << "25 �� s �� �����ΰ���? :: ";
    itr = s.find(25);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
        }
    else {
        std::cout << "No" << std::endl;
        }
    }


// key-value�� Class�� ���� ����ϱ�
// priority �� job_desc �� ������ �ִ� Todo Ŭ������ ���� ����Ѵ�.
// Todo Ŭ������ priority �� ������ job_desc �� ���������� ���ĵǵ��� �����Ѵ�.
// Todo Ŭ������ operator< �� �����ؾ� �Ѵ�. ������ set ���� ���Ҹ� �����ϱ� ���ؼ��� operator< �� �ʿ��ϱ� �����̴�.
// operator< �� ������ ���� priority �� ���� ���ϰ�, priority �� ������ job_desc �� ���Ѵ�.
// operator< �� ������ ���� const,friend �� �� ����ؾ� �Ѵ�.

template <typename T>
void print_set2(std::set<T>& m) {
	// ���� ��� ���ҵ��� ����ϱ�
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

    // �����ϱ� ���� �� ������ ����
    bool operator<(const Todo& t) const {
		if (priority == t.priority) {
            return job_desc < t.job_desc;
			}
		return priority > t.priority;
		}

    // operator<< �� friend �� �����Ѵ�. ������ operator<< �� Todo Ŭ������ ��� �Լ��� ������ �� ���� �����̴�.
    // operator<< �� Todo Ŭ������ ��� �Լ��� �����ϸ�, ù ��° ���ڰ� ostream& �̾�� �Ѵ�.
	friend std::ostream& operator<<(std::ostream& o, const Todo& td) {
        o << "[ �߿䵵 : " << td.priority << "] " << td.job_desc;
        return o;
		}
    };

void main2() {
    std::set<Todo> todos;

    todos.insert(Todo(1, "���� �Ա�"));
    todos.insert(Todo(2, "�����ϱ�"));
    todos.insert(Todo(3, "��ϱ�"));
    todos.insert(Todo(4, "Ŀ�� ���ñ�"));
    todos.insert(Todo(5, "����ϱ�"));
    print_set2(todos);
    std::cout << "----------------------------------" << std::endl;
    std::cout << "3��° �� �� ã��" << std::endl;
    auto itr = todos.begin();
    std::advance(itr, 2);
    std::cout << *itr << std::endl;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "3��° �� �� �����" << std::endl;
    todos.erase(itr);
    print_set2(todos);
    };


#include <map>

template <typename K, typename V>
void print_map3(std::map<K, V>& m) {
    // ���� ��� ���ҵ��� ����ϱ�
    std::cout << "[ ";
    //for (auto itr = m.begin(); itr != m.end(); ++itr) {
    for (const auto& elm : m) { // ���� for ���� ������ �ڵ�, ������� for��
        std::cout << elm.first << " : " << elm.second << " " << std::endl; // itr->first �� key, itr->second �� value
        }
    };


template <typename K, typename V>
void search_and_print(std::map<K, V>& m, K key) {
    auto itr = m.find(key);
    if (itr != m.end()) {
        std::cout << key << " --> " << itr->second << std::endl;
        }
    else {
        std::cout << key << "��(��) ��Ͽ� �����ϴ�" << std::endl;
        }
    }


void main3() {
    std::map<std::string, double> pitcher_list;

    pitcher_list.insert(std::pair<std::string, double>("�ڼ���", 3.14));
    pitcher_list.insert(std::pair<std::string, double>("��Ŀ", 2.7));
    pitcher_list.insert(std::pair<std::string, double>("�Ǿ��", 1.4));
    pitcher_list.insert(std::pair<std::string, double>("�Ǿ��", 3.4)); // �ߺ��� key �� ������� �ʴ´�.
    pitcher_list.insert(std::make_pair("����ȣ", 0.7)); // �����δ� �̷��� ���� ����Ѵ�.
    pitcher_list.insert(std::make_pair("������", 0.4));

    print_map3(pitcher_list);

    std::cout << "----------------------------------" << std::endl;
    search_and_print(pitcher_list, std::string("������"));
    search_and_print(pitcher_list, std::string("ȫ�浿")); // find() �Լ��� ����ؼ� key �� ã�´�.
    std::cout << "�������� ��� ��å����? :: " << pitcher_list["������"] << std::endl;
    std::cout << "ȫ�浿�� ��� ��å����? :: " << pitcher_list["ȫ�浿"] << std::endl; // ȫ�浿�� ������, [] �����ڸ� ����ϸ� ���ο� ���Ұ� �߰��ȴ�.(���ǹ��)
    };



// unordered_set �� random�ϰ� ���Ҹ� �����Ѵ�. (������ ���� �ʴ´�.)
// unordered_set �� find() �Լ��� ����� �� ����. (iterator �� ����� �� ����.)
// is_exist() �Լ��� ���� unordered_set �� ���Ұ� �ִ��� ������ Ȯ���Ѵ�.
#include <unordered_set>

template <typename T>
void print_all_unordered_set(std::unordered_set<T>& s) {
    // ���� ��� ���ҵ��� ����ϱ�
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
		std::cout << key << "��(��) ��Ͽ� �����ϴ�" << std::endl;
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


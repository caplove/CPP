// Virtual 과 override 사용 예제
// has a 관계 및 new / delete 이용한 EmployeeList 클래스 만들기
// EmployeeList 클래스를 만들어서 Employee 클래스와 Manager클래스를 모두 저장할 수 있도록 한다.
// Employee 클래스는 맴버: 이름, 나이, 직책, 순위    매소드 : virtual print_info(),          virtual calculate_pay()
// Manager 클래스는 맴버:Employee파생클래스 + 경력   매소드 :         print_info() override,         calculate_pay() override
// 
// EmployeeList 클래스 ( has a ) Employee 와 Manager
// EmployeeList 클래스는 맴버: 할당한 총 직원 수(alloc_employee), 현재 직원 수(current_employee), 직원 데이터 저장을 위한 배열(Employee** employee_list)
// 매소드 : add_employee(Employee* employee), current_employee_num(), print_employee_info(), ~EmployeeList()
//
// 생성자에서 employee_list = new Employee* [alloc_employee] 를 통해 동적할당을 하고, add_employee()를 통해 직원을 추가한다.(필요시 추가메모리 할당, 여기서는 제외함.)
// 소멸자에서 delete[] employee_list 를 통해 동적할당을 해제한다.



#include <iostream>
#include <string>

class Employee {
protected:
    std::string name;
    int age;

    std::string position;  // 직책 (이름)
    int rank;              // 순위 (값이 클 수록 높은 순위)

public:
    Employee(std::string name, int age, std::string position, int rank)
        : name(name), age(age), position(position), rank(rank) {}

    // 복사 생성자
    Employee(const Employee& employee) {
        name = employee.name;
        age = employee.age;
        position = employee.position;
        rank = employee.rank;
        }

    // 디폴트 생성자
    Employee() {}

    virtual void print_info() {
        std::cout << name << " (" << position << " , " << age << ") ==> "
            << calculate_pay() << "만원" << std::endl;
        }
    virtual int calculate_pay() { return 200 + rank * 50; }
    };

class Manager : public Employee {
    int year_of_service;

public:
    Manager(std::string name, int age, std::string position, int rank,
            int year_of_service)
        : year_of_service(year_of_service), Employee(name, age, position, rank) {}

    int calculate_pay() override { return 200 + rank * 50 + 5 * year_of_service; }
    void print_info() override {
        std::cout << name << " (" << position << " , " << age << ", "
            << year_of_service << "년차) ==> " << calculate_pay() << "만원"
            << std::endl;
        }
    };



class EmployeeList {
    int alloc_employee;        // 할당한 총 직원 수
    int current_employee;      // 현재 직원 수
    Employee** employee_list;  // 직원 데이터 저장을 위한 배열

public:
    EmployeeList(int alloc_employee) : alloc_employee(alloc_employee) {
        employee_list = new Employee* [alloc_employee];
        current_employee = 0;
        }
    void add_employee(Employee* employee) {
        // 사실 current_employee 보다 alloc_employee 가 더
        // 많아지는 경우 반드시 재할당을 해야 하지만, 여기서는
        // 최대한 단순하게 생각해서 alloc_employee 는
        // 언제나 current_employee 보다 크다고 생각한다.
        // (즉 할당된 크기는 현재 총 직원수 보다 많음)
        employee_list[current_employee] = employee;
        current_employee++;
        }
    int current_employee_num() { return current_employee; }

    void print_employee_info() {
        int total_pay = 0;
        for (int i = 0; i < current_employee; i++) {
            employee_list[i]->print_info();
            total_pay += employee_list[i]->calculate_pay();
            }

        std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
        }
    ~EmployeeList() {
        for (int i = 0; i < current_employee; i++) {
            delete employee_list[i];
            }
        delete[] employee_list;
        }
    };





int main() {
    EmployeeList emp_list(10); // 사실 여기서는 10명을 수용할 수 있는employee_list생성, new Employee*[10] 과 같음.
    emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
    emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
    emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
    emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
    emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
    emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
    emp_list.add_employee(new Employee("길", 36, "인턴", -2));
    emp_list.print_employee_info();
    return 0;
    }
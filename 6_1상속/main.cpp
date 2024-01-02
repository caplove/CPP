


#include <iostream>
#include <string>


class Employee
	{
	private:
		std::string name;
		int age;
		std::string position;
		int rank;

	public:
		// 디폴트 생성자
		Employee() : name(""), age(0), position(""), rank(0) {}

		// 생성자
		Employee(std::string name, int age, std::string position, int rank)
			: name(name), age(age), position(position), rank(rank) {}

		// 복사 생성자
		Employee(const Employee& employee)
			: name(employee.name), age(employee.age), position(employee.position), rank(employee.rank) {}
		
		void print_info() {
			std::cout << name << " (" << position << " , " << age << ") ==> "
				<< calculate_pay() << "만원" << std::endl;
			}
		int calculate_pay() { return 200 + rank * 50; }
	};


class EmployeeList 	{
	private:
		int alloc_employee; // 할당한 총 직원 수
		int current_employee; // 현재 직원 수
		Employee** employee_list; // 직원(Class형) 포인터 배열 --> 이중 포인터 !!

	public:
		// 생성자
		EmployeeList(int alloc_employee)
			: alloc_employee(alloc_employee), current_employee(0) {
			employee_list = new Employee*[alloc_employee];
		}

		// 소멸자
		~EmployeeList() {
			for (int i = 0; i < current_employee; i++) {
				delete employee_list[i];
			}
			delete[] employee_list;
		}

		// 새로운 직원 등록
		// Employee* 포인터를 매개변수로 받는다.
		// 이중 포인터 배열인 employee_list에 포인터를 저장하고, current_employee를 1 증가시킨다.
		void add_employee(Employee* employee) {
			employee_list[current_employee++] = employee;
		}

		// 모든 직원 정보 출력
		void print_employee_info() {
			int total_pay = 0;
			for (int i = 0; i < current_employee; i++) {
				employee_list[i]->print_info();
				total_pay += employee_list[i]->calculate_pay();
			}
			std::cout << "총 비용 : " << total_pay << "만원" << std::endl;
		}
	};




// new 연산자는 동적으로 Employee 객체를 생성하고, 객체에 대한 포인터를 반환하는 함수이다.
// new Employee(...)는 Employee 객체를 생성하고, 그 객체에 대한 포인터(Employee*)를 반환한다.

int main() {

	EmployeeList emp_list(10); // 사원 명부 생성
	emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1)); // 사원 등록
	emp_list.add_employee(new Employee("하하", 34, "평사원", 1));
	emp_list.add_employee(new Employee("유재석", 41, "평사원", 7));
	emp_list.add_employee(new Employee("정준하", 43, "평사원", 9));
	emp_list.add_employee(new Employee("박명수", 43, "평사원", 9));

	emp_list.print_employee_info();


	return 0;
}
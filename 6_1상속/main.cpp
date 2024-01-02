


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
		// ����Ʈ ������
		Employee() : name(""), age(0), position(""), rank(0) {}

		// ������
		Employee(std::string name, int age, std::string position, int rank)
			: name(name), age(age), position(position), rank(rank) {}

		// ���� ������
		Employee(const Employee& employee)
			: name(employee.name), age(employee.age), position(employee.position), rank(employee.rank) {}
		
		void print_info() {
			std::cout << name << " (" << position << " , " << age << ") ==> "
				<< calculate_pay() << "����" << std::endl;
			}
		int calculate_pay() { return 200 + rank * 50; }
	};


class EmployeeList 	{
	private:
		int alloc_employee; // �Ҵ��� �� ���� ��
		int current_employee; // ���� ���� ��
		Employee** employee_list; // ����(Class��) ������ �迭 --> ���� ������ !!

	public:
		// ������
		EmployeeList(int alloc_employee)
			: alloc_employee(alloc_employee), current_employee(0) {
			employee_list = new Employee*[alloc_employee];
		}

		// �Ҹ���
		~EmployeeList() {
			for (int i = 0; i < current_employee; i++) {
				delete employee_list[i];
			}
			delete[] employee_list;
		}

		// ���ο� ���� ���
		// Employee* �����͸� �Ű������� �޴´�.
		// ���� ������ �迭�� employee_list�� �����͸� �����ϰ�, current_employee�� 1 ������Ų��.
		void add_employee(Employee* employee) {
			employee_list[current_employee++] = employee;
		}

		// ��� ���� ���� ���
		void print_employee_info() {
			int total_pay = 0;
			for (int i = 0; i < current_employee; i++) {
				employee_list[i]->print_info();
				total_pay += employee_list[i]->calculate_pay();
			}
			std::cout << "�� ��� : " << total_pay << "����" << std::endl;
		}
	};




// new �����ڴ� �������� Employee ��ü�� �����ϰ�, ��ü�� ���� �����͸� ��ȯ�ϴ� �Լ��̴�.
// new Employee(...)�� Employee ��ü�� �����ϰ�, �� ��ü�� ���� ������(Employee*)�� ��ȯ�Ѵ�.

int main() {

	EmployeeList emp_list(10); // ��� ��� ����
	emp_list.add_employee(new Employee("��ȫö", 34, "����", 1)); // ��� ���
	emp_list.add_employee(new Employee("����", 34, "����", 1));
	emp_list.add_employee(new Employee("���缮", 41, "����", 7));
	emp_list.add_employee(new Employee("������", 43, "����", 9));
	emp_list.add_employee(new Employee("�ڸ��", 43, "����", 9));

	emp_list.print_employee_info();


	return 0;
}
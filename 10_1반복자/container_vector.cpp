
//STL(ǥ�����ø�)-Standard Template Library
// iostream(�����), vector(�����迭), algorithm(����,�ִ��ּ�), string(���ڿ�), queue(ť), stack(����), map(��), 
// set(����), list(���Ḯ��Ʈ), deque(��), priority_queue(�켱����ť),chrono(�ð�),bitset(��Ʈ����ũ),tuple(Ʃ��),pair(��)
// regex(����ǥ����),random(����),functional(�Լ���ü),iterator(�ݺ���),numeric(��ġ����),valarray(�迭),thread(������)

// STL 3���� : container(�����̳�), iterator(�ݺ���), algorithm(�˰���)

// �����̳� : �����͸� �����ϴ� ��ü
// 1. ������ �����̳� : �����͸� �������� �����ϴ� �����̳�
// 2. ���� �����̳� : �����͸� key-value ������ �����ϴ� �����̳�
// 3. �����̳� ����� : �ٸ� �����̳ʸ� �������̽��� ����ϴ� �����̳�

// �ݺ��� : �����̳��� ���Ҹ� ��ȸ�ϴ� ��ü
// 1. �Է� �ݺ��� : �б⸸ ����
// 2. ��� �ݺ��� : ���⸸ ����
// 3. ������ �ݺ��� : �б�, ���� ����, ���������� �̵� ����
// 4. ����� �ݺ��� : �б�, ���� ����, ��������� �̵� ����
// 5. ���� ���� �ݺ��� : �б�, ���� ����, ���� ��ġ�� �̵� ����

// �˰��� : �����̳ʿ� ����� �����͸� ó���ϴ� �Լ�
// 1. �� : �� ���� ��Ұ��踦 ���ϴ� �Լ�
// 2. ���� : Ư�� ������ �����ϴ��� �˻��ϴ� �Լ�
// 3. ���� : �����͸� Ư�� ��Ģ�� ���� �����ϴ� �Լ�
// 4. ���� : Ư�� ������ �����ϴ� �����͸� �����ϴ� �Լ�
// 5. ���� : �����͸� �����ϴ� �Լ�
// 6. ���� : �������� ������ �ٲٴ� �Լ�
// 7. ��ġ : ��ġ ������ �����ϴ� �Լ�
// 8. �� �� : �����͸� ó���ϴ� �Լ�



///////////////////////////////////////////////////////////////////////////////////////////////
// �ݺ��� (iterator)
// �ݺ��ڴ� �����̳��� ���Ҹ� ��ȸ�ϴ� ��ü
// �����̳��� ���Ҹ� ��ȸ�ϴ� ����� �����̳ʸ��� �ٸ���
// �ݺ��ڴ� �����̳��� ���Ҹ� ��ȸ�ϴ� ����� ǥ��ȭ�� ��
// �ݺ��ڴ� �����Ϳ� ����� ����
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>




// iter�� ���� �����ϱ�
void main1()
	{
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	// i < v.size() : ������ ũ��
	for (std::vector<int>::size_type i = 0; i < v.size(); i++)
		{
		std::cout << v[i] << std::endl;
		}
	// iter != v.end() : ������ ��
	for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
		{
		std::cout << *iter << std::endl;  // *iter : �ݺ��ڰ� ����Ű�� ��, *������ �����ε����� ��ġ ������ó�� ���
		}

	}



// iter�� ���� �����ϱ�
template <typename T>
void print_vector(std::vector<T>& vec) {
	// ��ü ���͸� ����ϱ�
	for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end();
		 ++itr) {
		std::cout << *itr << std::endl;
		}
	}


void main2() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	std::cout << "ó�� ���� ����" << std::endl;
	print_vector(vec);
	std::cout << "----------------------------" << std::endl;

	// vec[2] �տ� 15 �߰�
	vec.insert(vec.begin() + 2, 15);
	print_vector(vec);

	std::cout << "----------------------------" << std::endl;
	// vec[3] ����
	vec.erase(vec.begin() + 3);
	print_vector(vec);

	std::cout << "----------------------------" << std::endl;
	// vec �ǵڿ� 50 �߰�
	vec.insert(vec.end(),50);
	print_vector(vec);
	}

// �ݺ����� const
void main3() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	std::cout << "�ʱ� vec ����" << std::endl;
	print_vector(vec);

	// itr �� vec[2] �� ����Ų��.
	std::vector<int>::iterator itr = vec.begin() + 2;
	// vec[2] �� ���� 50���� �ٲ۴�.
	*itr = 50;
	std::cout << "---------------" << std::endl;
	print_vector(vec);

	std::vector<int>::const_iterator citr = vec.cbegin() + 2; // begin()�� cbegin()�� ���̴� �����ΰ�?
	// ��� �ݺ��ڰ� ����Ű�� ���� �ٲܼ� ����. �Ұ���!
	//*citr = 30;
	std::cout << "---------------" << std::endl;
	print_vector(vec);

	std::cout << "������ vec ����ϱ�!" << std::endl;
	// r_iter�� vec�� �� �ڸ� ����Ų��. rbegin�� rend�� ����Ѵ�.
	std::vector<int>::reverse_iterator r_iter = vec.rbegin();
	for (; r_iter != vec.rend(); r_iter++) {
		std::cout << *r_iter << std::endl;
		}

	// for������ ������ ���� ����ϱ� (�������� ������ reverse_iterator�� ����Ѵ�.)
	//for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--) {
	//	std::cout << vec[i] << std::endl;
	//	}
	}


void main4() {
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	// range-based for ��
	for (int i : vec) {
		std::cout << "���� : " << i << std::endl;
		}

	}

// ���͸� ����ϴ� �Լ�, range-based for ������
// ���Ͱ��� �ٲ��� �ʱ� ������ const auto& �� �޴´�.
template <typename T> 
void print_vector_range_based(std::vector<T>& vec) {  
	// ��ü ���͸� ����ϱ�
	for (const auto& i : vec) { // auto : �ڵ����� Ÿ���� �߷��Ѵ�. const : ������ ���� �ٲ��� �ʴ´�. & : ������(���۷���)�� �޴´�.
		std::cout << i << std::endl;
		}
	}

void main5() {
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	std::cout << "print_vector" << std::endl;
	print_vector(vec);
	std::cout << "print_vector_range_based" << std::endl;
	print_vector_range_based(vec);

	}

int main() {
	main1();
	main2();
	main3();
	main4();
	main5();

	return 0;
}
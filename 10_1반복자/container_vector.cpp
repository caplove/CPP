
//STL(표준탬플릿)-Standard Template Library
// iostream(입출력), vector(동적배열), algorithm(정렬,최대최소), string(문자열), queue(큐), stack(스택), map(맵), 
// set(집합), list(연결리스트), deque(덱), priority_queue(우선순위큐),chrono(시간),bitset(비트마스크),tuple(튜플),pair(쌍)
// regex(정규표현식),random(난수),functional(함수객체),iterator(반복자),numeric(수치연산),valarray(배열),thread(스레드)

// STL 3대장 : container(컨테이너), iterator(반복자), algorithm(알고리즘)

// 컨테이너 : 데이터를 저장하는 객체
// 1. 시퀀스 컨테이너 : 데이터를 선형으로 저장하는 컨테이너
// 2. 연관 컨테이너 : 데이터를 key-value 쌍으로 저장하는 컨테이너
// 3. 컨테이너 어댑터 : 다른 컨테이너를 인터페이스로 사용하는 컨테이너

// 반복자 : 컨테이너의 원소를 순회하는 객체
// 1. 입력 반복자 : 읽기만 가능
// 2. 출력 반복자 : 쓰기만 가능
// 3. 순방향 반복자 : 읽기, 쓰기 가능, 순방향으로 이동 가능
// 4. 양방향 반복자 : 읽기, 쓰기 가능, 양방향으로 이동 가능
// 5. 임의 접근 반복자 : 읽기, 쓰기 가능, 임의 위치로 이동 가능

// 알고리즘 : 컨테이너에 저장된 데이터를 처리하는 함수
// 1. 비교 : 두 값의 대소관계를 비교하는 함수
// 2. 조건 : 특정 조건을 만족하는지 검사하는 함수
// 3. 변형 : 데이터를 특정 규칙에 따라 변형하는 함수
// 4. 제거 : 특정 조건을 만족하는 데이터를 제거하는 함수
// 5. 정렬 : 데이터를 정렬하는 함수
// 6. 순서 : 데이터의 순서를 바꾸는 함수
// 7. 수치 : 수치 연산을 수행하는 함수
// 8. 그 외 : 데이터를 처리하는 함수



///////////////////////////////////////////////////////////////////////////////////////////////
// 반복자 (iterator)
// 반복자는 컨테이너의 원소를 순회하는 객체
// 컨테이너의 원소를 순회하는 방법은 컨테이너마다 다르다
// 반복자는 컨테이너의 원소를 순회하는 방법을 표준화한 것
// 반복자는 포인터와 비슷한 개념
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>




// iter로 벡터 접근하기
void main1()
	{
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	// i < v.size() : 벡터의 크기
	for (std::vector<int>::size_type i = 0; i < v.size(); i++)
		{
		std::cout << v[i] << std::endl;
		}
	// iter != v.end() : 벡터의 끝
	for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
		{
		std::cout << *iter << std::endl;  // *iter : 반복자가 가리키는 값, *연산자 오버로딩으로 마치 포인터처럼 사용
		}

	}



// iter로 벡터 접근하기
template <typename T>
void print_vector(std::vector<T>& vec) {
	// 전체 벡터를 출력하기
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

	std::cout << "처음 벡터 상태" << std::endl;
	print_vector(vec);
	std::cout << "----------------------------" << std::endl;

	// vec[2] 앞에 15 추가
	vec.insert(vec.begin() + 2, 15);
	print_vector(vec);

	std::cout << "----------------------------" << std::endl;
	// vec[3] 제거
	vec.erase(vec.begin() + 3);
	print_vector(vec);

	std::cout << "----------------------------" << std::endl;
	// vec 맨뒤에 50 추가
	vec.insert(vec.end(),50);
	print_vector(vec);
	}

// 반복자의 const
void main3() {
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	std::cout << "초기 vec 상태" << std::endl;
	print_vector(vec);

	// itr 은 vec[2] 를 가리킨다.
	std::vector<int>::iterator itr = vec.begin() + 2;
	// vec[2] 의 값을 50으로 바꾼다.
	*itr = 50;
	std::cout << "---------------" << std::endl;
	print_vector(vec);

	std::vector<int>::const_iterator citr = vec.cbegin() + 2; // begin()과 cbegin()의 차이는 무엇인가?
	// 상수 반복자가 가리키는 값은 바꿀수 없다. 불가능!
	//*citr = 30;
	std::cout << "---------------" << std::endl;
	print_vector(vec);

	std::cout << "역으로 vec 출력하기!" << std::endl;
	// r_iter은 vec의 맨 뒤를 가리킨다. rbegin과 rend를 사용한다.
	std::vector<int>::reverse_iterator r_iter = vec.rbegin();
	for (; r_iter != vec.rend(); r_iter++) {
		std::cout << *r_iter << std::endl;
		}

	// for문으로 끝에서 부터 출력하기 (에러나기 때문에 reverse_iterator를 사용한다.)
	//for (std::vector<int>::size_type i = vec.size() - 1; i >= 0; i--) {
	//	std::cout << vec[i] << std::endl;
	//	}
	}


void main4() {
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	// range-based for 문
	for (int i : vec) {
		std::cout << "원소 : " << i << std::endl;
		}

	}

// 벡터를 출력하는 함수, range-based for 문으로
// 벡터값을 바꾸지 않기 때문에 const auto& 로 받는다.
template <typename T> 
void print_vector_range_based(std::vector<T>& vec) {  
	// 전체 벡터를 출력하기
	for (const auto& i : vec) { // auto : 자동으로 타입을 추론한다. const : 벡터의 값을 바꾸지 않는다. & : 참조자(레퍼런스)로 받는다.
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

// 정렬, 검색
// template <typename T>
// void do_something(Iter begin, Iter end);
// 조건부 서술
// template <typename T>
// void do_something(Iter begin, Iter end, Pred p);

// 정렬(sort, stable_sort,partial_sort, nth_element)
// 검색(binary_search, lower_bound, upper_bound, equal_range)
// 두 정렬된 범위를 합침(merge, inplace_merge)
// 범위를 정해진 값으로 채움(fill, fill_n)

// 람다 표현식
// 람다 함수는 이름이 없는 함수를 정의하는 데 사용되는 C++의 기능입니다. 람다 함수는 일반 함수와 마찬가지로 매개변수를 받을 수 있으며, 
// 반환 값을 가질 수 있습니다. 람다 함수는 주로 함수를 매개변수로 받는 알고리즘에 사용됩니다.
// 
// [캡처](매개변수) -> 반환형 {함수 본체}
// 캡처: 람다 표현식에서 사용하는 외부 변수를 지정
// 매개변수: 람다 표현식에서 사용하는 매개변수를 지정
// 반환형: 람다 표현식의 반환형을 지정
// 함수 본체: 람다 표현식의 함수 본체를 지정

// 람다 표현식의 반환형을 지정하지 않으면 컴파일러가 반환형을 추론
// 람다 표현식의 반환형을 지정하면 반환형을 추론하지 않음





#include <algorithm>
#include <vector>
#include <iostream>

template <typename Iter>
void print(Iter start, Iter end) {
	while (start != end)
	{
		std::cout << *start << " ";
		start++;
	}
	std::cout << std::endl;
}

template <typename Iter>
void print_pair(Iter start, Iter end) {
	while (start != end)
	{
		std::cout << "(" << start->first << ", " << start->second << ") ";
		start++;
	}
	std::cout << std::endl;
}

void main1() {
	std::vector<int> v = { 1,2,3,4,15,6,7,8,9,10 };
	std::vector<std::pair<int, char>> v2 = { {2, 'b'}, {1, 'a'}, {3, 'c'},{3,'a'},{3, 'e'},{3,'d'} };

	std::vector<int> v3 = { 1,2,3,4,15,6,7,8,9,10 };
	std::vector<int> v4 = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> v5 = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> v6 = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> v7 = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> v8 = { 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> v9 = { 1,2,3,4,5,6,7,8,9,100 };
	std::vector<int> v10 = { 11,12,13,14,15,16,17,18,19,50 };

	std::sort(v.begin(), v.end()); // 오름차순 정렬
	print(v.begin(), v.end());

	//std::sort(v2.begin(), v2.end()); // 오름차순 정렬
	print_pair(v2.begin(), v2.end());

	std::stable_sort(v2.begin(), v2.end()); // 같은 값이 있을 경우, 원래의 순서를 유지
	print_pair(v2.begin(), v2.end());

	std::partial_sort(v3.begin(), v3.begin() + 8, v3.end()); // 8번째 원소를 기준으로 왼쪽은 작은 값, 오른쪽은 큰 값
	print(v3.begin(), v3.end());

	std::nth_element(v4.begin(), v4.begin() + 5, v4.end()); // 5번째 원소를 기준으로 왼쪽은 작은 값, 오른쪽은 큰 값
	print(v4.begin(), v4.end());

	bool found = std::binary_search(v5.begin(), v5.end(), 3); // 이진 탐색
	std::cout << (found ? "Found" : "Not Found") << std::endl;

	auto lower = std::lower_bound(v6.begin(), v6.end(), 3); // 3이상인 첫번째 원소
	print(lower, v6.end());

	auto upper = std::upper_bound(v7.begin(), v7.end(), 3); // 3보다 큰 첫번째 원소
	print(upper, v7.end());

	auto range = std::equal_range(v8.begin(), v8.end(), 3); // 3이상인 첫번째 원소와 3보다 큰 첫번째 원소
	print(range.first, range.second);


	std::vector<int> merged(v9.size() + v10.size());  // 두 정렬된 범위를 합침
	print(merged.begin(), merged.end());


	std::merge(v9.begin(), v9.end(), v10.begin(), v10.end(), merged.begin()); // 두 정렬된 범위를 합침
	print(merged.begin(), merged.end());

	std::inplace_merge(merged.begin(), merged.begin() + v9.size(), merged.end()); // 두 정렬된 범위를 합침
	print(merged.begin(), merged.end());

	std::fill(v9.begin(), v9.end(), 3); // 범위를 3으로 채움
	print(v9.begin(), v9.end());

	std::fill_n(v10.begin(), 5, 3); // 5개의 원소를 3으로 채움
	print(v10.begin(), v10.end());

};

// 람다 표현식
 void main2() {
	std::vector<int> v = { 1, 2, 3, 4, 5 };

	// 람다 함수를 사용하여 벡터의 각 요소를 두 배로 만듭니다.
	std::for_each(v.begin(), v.end(), [](int& n) { n *= 2; }); // inline 함수, 함수 객체

	// 벡터의 요소를 출력합니다.
	for (int n : v) {
		std::cout << n << ' ';
	}
	std::cout << std::endl;
}






void main() {
	main1();
	main2();

};
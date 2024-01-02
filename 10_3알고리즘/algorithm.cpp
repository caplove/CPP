
// ����, �˻�
// template <typename T>
// void do_something(Iter begin, Iter end);
// ���Ǻ� ����
// template <typename T>
// void do_something(Iter begin, Iter end, Pred p);

// ����(sort, stable_sort,partial_sort, nth_element)
// �˻�(binary_search, lower_bound, upper_bound, equal_range)
// �� ���ĵ� ������ ��ħ(merge, inplace_merge)
// ������ ������ ������ ä��(fill, fill_n)

// ���� ǥ����
// ���� �Լ��� �̸��� ���� �Լ��� �����ϴ� �� ���Ǵ� C++�� ����Դϴ�. ���� �Լ��� �Ϲ� �Լ��� ���������� �Ű������� ���� �� ������, 
// ��ȯ ���� ���� �� �ֽ��ϴ�. ���� �Լ��� �ַ� �Լ��� �Ű������� �޴� �˰��� ���˴ϴ�.
// 
// [ĸó](�Ű�����) -> ��ȯ�� {�Լ� ��ü}
// ĸó: ���� ǥ���Ŀ��� ����ϴ� �ܺ� ������ ����
// �Ű�����: ���� ǥ���Ŀ��� ����ϴ� �Ű������� ����
// ��ȯ��: ���� ǥ������ ��ȯ���� ����
// �Լ� ��ü: ���� ǥ������ �Լ� ��ü�� ����

// ���� ǥ������ ��ȯ���� �������� ������ �����Ϸ��� ��ȯ���� �߷�
// ���� ǥ������ ��ȯ���� �����ϸ� ��ȯ���� �߷����� ����





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

	std::sort(v.begin(), v.end()); // �������� ����
	print(v.begin(), v.end());

	//std::sort(v2.begin(), v2.end()); // �������� ����
	print_pair(v2.begin(), v2.end());

	std::stable_sort(v2.begin(), v2.end()); // ���� ���� ���� ���, ������ ������ ����
	print_pair(v2.begin(), v2.end());

	std::partial_sort(v3.begin(), v3.begin() + 8, v3.end()); // 8��° ���Ҹ� �������� ������ ���� ��, �������� ū ��
	print(v3.begin(), v3.end());

	std::nth_element(v4.begin(), v4.begin() + 5, v4.end()); // 5��° ���Ҹ� �������� ������ ���� ��, �������� ū ��
	print(v4.begin(), v4.end());

	bool found = std::binary_search(v5.begin(), v5.end(), 3); // ���� Ž��
	std::cout << (found ? "Found" : "Not Found") << std::endl;

	auto lower = std::lower_bound(v6.begin(), v6.end(), 3); // 3�̻��� ù��° ����
	print(lower, v6.end());

	auto upper = std::upper_bound(v7.begin(), v7.end(), 3); // 3���� ū ù��° ����
	print(upper, v7.end());

	auto range = std::equal_range(v8.begin(), v8.end(), 3); // 3�̻��� ù��° ���ҿ� 3���� ū ù��° ����
	print(range.first, range.second);


	std::vector<int> merged(v9.size() + v10.size());  // �� ���ĵ� ������ ��ħ
	print(merged.begin(), merged.end());


	std::merge(v9.begin(), v9.end(), v10.begin(), v10.end(), merged.begin()); // �� ���ĵ� ������ ��ħ
	print(merged.begin(), merged.end());

	std::inplace_merge(merged.begin(), merged.begin() + v9.size(), merged.end()); // �� ���ĵ� ������ ��ħ
	print(merged.begin(), merged.end());

	std::fill(v9.begin(), v9.end(), 3); // ������ 3���� ä��
	print(v9.begin(), v9.end());

	std::fill_n(v10.begin(), 5, 3); // 5���� ���Ҹ� 3���� ä��
	print(v10.begin(), v10.end());

};

// ���� ǥ����
 void main2() {
	std::vector<int> v = { 1, 2, 3, 4, 5 };

	// ���� �Լ��� ����Ͽ� ������ �� ��Ҹ� �� ��� ����ϴ�.
	std::for_each(v.begin(), v.end(), [](int& n) { n *= 2; }); // inline �Լ�, �Լ� ��ü

	// ������ ��Ҹ� ����մϴ�.
	for (int n : v) {
		std::cout << n << ' ';
	}
	std::cout << std::endl;
}






void main() {
	main1();
	main2();

};
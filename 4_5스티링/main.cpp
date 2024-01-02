
// 연산자 오버로딩
// 비교 연산자 오버로딩
// 형식 
// 리턴형식 operator 매개변수
// ex) bool operator==(const MyString &s) const // 문자열 s와 비교, 문자열 s가 같으면 true, 다르면 false 리턴, 입력과출력은 변경되지 않으므로 const
// 			



#include <iostream>
using namespace std;

class MyString
	{
	public:
		MyString();
		MyString(char c);
		MyString(const char *str);
		MyString(const MyString &s);
		~MyString();

		int length() const; // 문자열 길이 리턴,읽기 전용함수로 const 선언
		void print() const; // 문자열 출력,읽기 전용함수로 const 선언
		MyString& Add(const MyString &s); // 문자열 덧붙이기
		MyString& Assign(const MyString &s); // 문자열 대입하기
		MyString& Assign(const char *str); // 문자열 대입하기
		int capacity() const; // 문자열 용량 리턴,읽기 전용함수로 const 선언
		void reserve(int size); // 문자열 용량 늘리기
		char& at(int i) const; // i번째 문자 리턴,읽기 전용함수로 const 선언
		MyString& insert(int i, const MyString &s); // i번째 위치에 문자열 s 삽입
		MyString& insert(int i, const char *str); // i번째 위치에 문자열 str 삽입
		MyString& insert(int i, char c); // i번째 위치에 문자 c 삽입

		MyString& erase(int i, int j); // i번째 위치부터 j개의 문자열 삭제
		MyString& erase(int i); // i번째 위치의 문자열 삭제
		MyString& replace(int i, int j, const MyString &s); // i번째 위치부터 j개의 문자열을 s로 대체
		MyString& replace(int i, int j, const char *str); // i번째 위치부터 j개의 문자열을 str로 대체
		MyString& replace(int i, int j, char c); // i번째 위치부터 j개의 문자열을 c로 대체
		int find(const MyString &s) const; // 문자열 s가 처음 나타나는 위치 리턴
		int find(const char *str) const; // 문자열 str이 처음 나타나는 위치 리턴
		int find(char c) const; // 문자 c가 처음 나타나는 위치 리턴
		int rfind(const MyString &s) const; // 문자열 s가 마지막으로 나타나는 위치 리턴
		int rfind(const char *str) const; // 문자열 str이 마지막으로 나타나는 위치 리턴
		int rfind(char c) const; // 문자 c가 마지막으로 나타나는 위치 리턴
		int compare(const MyString &s) const; // 문자열 s와 비교
		int compare(const char *str) const; // 문자열 str과 비교

		bool operator==(const MyString &s) const; // 문자열 s와 비교

	private:
		int len;
		char *str;
		int memory_capacity;
	};

MyString::MyString()
	{
		len = 0;
		str = NULL;
		memory_capacity = 0;
	}

MyString::MyString(char c)
	{
		len = 1;
		str = new char[1];
		str[0] = c;
		memory_capacity = 1;
	}
	
MyString::MyString(const char *str)
	{
		len = strlen(str);
		this->str = new char[len+1];
		strcpy_s(this->str, len+1, str);
		memory_capacity = len+1;
	}

MyString::MyString(const MyString &s)
	{
		len = s.len;
		str = new char[len+1];
		strcpy_s(str, len+1, s.str);
		memory_capacity = len+1;
	}

MyString::~MyString()
	{
		if(str != NULL)
			delete []str;
	}

int MyString::length() const
	{
		return len;
	}

void MyString::print() const
	{
	// 문자열, 문자열 길이, 용량을 한출로 출력
	cout << "문자열 : " << str << ", 길이 : " << len << ", 용량 : " << memory_capacity << endl;
	}

MyString& MyString::Add(const MyString &s)
	{
		len += s.len;
		char *temp = new char[len*2];
		strcpy_s(temp, len+1, this->str);
		strcat_s(temp, len+1, s.str);
		if(str != NULL)
			delete []str;
		this->str = temp;
		memory_capacity = len*2;
		return *this;
	}

MyString& MyString::Assign(const MyString &s)
	{
		this->len = s.len;
		if(this->str != NULL)
			delete []str;
		this->str = new char[s.len*2];
		strcpy_s(this->str, s.len+1, s.str);
		memory_capacity = s.len*2;
		return *this;
	}

MyString& MyString::Assign(const char *str)
	{
		this->len = strlen(str);
		if(this->str != NULL)
			delete []str;
		this->str = new char[len*2];
		strcpy_s(this->str, len+1, str);
		memory_capacity = len*2;
		return *this;
	}

int MyString::capacity() const
	{
		return memory_capacity;
	}

void MyString::reserve(int size)
	{
		if(size > memory_capacity)
			{
				char *temp = new char[size];
				strcpy_s(temp, size, str);
				if(str != NULL)
					delete []str;
				str = temp;
				memory_capacity = size;
			}
	}

char& MyString::at(int i) const
	{
	if (i < 0 || i >= len)
		{
			cout << "범위를 벗어났습니다." << endl;
			exit(1);
		}
		return str[i];
	}

MyString& MyString::insert(int i, const MyString &s)
	{
		if(i < 0 || i > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len += s.len;
		// 문자열 길이가 늘어나면 메모리 용량은 2배로 늘린다.
		if(len > memory_capacity)
			{
				char *temp = new char[len*2];
				strcpy_s(temp, len*2, this->str);
				if(this->str != NULL)
					delete []this->str;
				this->str = temp;
				memory_capacity = len*2;
			}
	}

MyString& MyString::insert(int i, const char *str)
	{
		if(i < 0 || i > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len += strlen(str);

		// 문자열 길이가 늘어나면 메모리 용량은 2배로 늘린다.
		if(len > memory_capacity)
			{
				char *temp = new char[len*2];
				strcpy_s(temp, len*2, this->str);
				if(this->str != NULL)
					delete []this->str;
				this->str = temp;
				memory_capacity = len*2;
			}

	}

MyString& MyString::insert(int i, char c)
	{
		if(i < 0 || i > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len += 1;
		// 문자열 길이가 늘어나면 메모리 용량은 2배로 늘린다.
		if(len > memory_capacity)
			{
				char *temp = new char[len*2];
				strcpy_s(temp, len*2, this->str);
				if(this->str != NULL)
					delete []this->str;
				this->str = temp;
				memory_capacity = len*2;
			}
	}

MyString& MyString::erase(int i, int j)  // i번째 위치부터 j개의 문자열 삭제
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len -= j;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i번째 위치까지 복사
		strcat_s(temp, len*2, str+i+j); // i번째 위치부터 j개의 문자열을 제외한 나머지 문자열을 복사
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

MyString& MyString::erase(int i) // i번째 위치의 문자열 삭제
	{
		if(i < 0 || i > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len -= 1;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i번째 위치까지 복사
		strcat_s(temp, len*2, str+i+1); // i번째 위치의 문자를 제외한 나머지 문자열을 복사
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

MyString& MyString::replace(int i, int j, const MyString &s) // i번째 위치부터 j개의 문자열을 s로 대체
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len -= j;
		len += s.len;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i번째 위치까지 복사
		strcat_s(temp, len*2, s.str); // i번째 위치부터 j개의 문자열을 제외한 나머지 문자열을 복사
		strcat_s(temp, len*2, str+i+j); // i번째 위치부터 j개의 문자열을 제외한 나머지 문자열을 복사
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

MyString& MyString::replace(int i, int j, const char *str) // i번째 위치부터 j개의 문자열을 str로 대체
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len -= j;
		len += strlen(str);
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i번째 위치까지 복사
		strcat_s(temp, len*2, str); // i번째 위치부터 j개의 문자열을 제외한 나머지 문자열을 복사
		strcat_s(temp, len*2, str+i+j); // i번째 위치부터 j개의 문자열을 제외한 나머지 문자열을 복사
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}


MyString& MyString::replace(int i, int j, char c) // i번째 위치부터 j개의 문자열을 c로 대체
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "범위를 벗어났습니다." << endl;
				exit(1);
			}
		len -= j;
		len += 1;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i번째 위치까지 복사
		temp[i] = c; // i번째 위치에 문자 c를 복사
		strcat_s(temp, len*2, str+i+j); // i번째 위치부터 j개의 문자열을 제외한 나머지 문자열을 복사
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

int MyString::find(const MyString &s) const // 문자열 s가 처음 나타나는 위치 리턴
	{
		int i, j;
		for(i = 0; i < len; i++)
			{
				for(j = 0; j < s.len; j++)
					{
						if(str[i+j] != s.str[j])
							break;
					}
				if(j == s.len)
					return i;
			}
		return -1;
	}

int MyString::find(const char *str) const // 문자열 str이 처음 나타나는 위치 리턴
	{
		int i, j;
		for(i = 0; i < len; i++)
			{
				for(j = 0; j < strlen(str); j++)
					{
						if(this->str[i+j] != str[j])
							break;
					}
				if(j == strlen(str))
					return i;
			}
		return -1;
	}


int MyString::find(char c) const // 문자 c가 처음 나타나는 위치 리턴
	{
		int i;
		for(i = 0; i < len; i++)
			{
				if(str[i] == c)
					return i;
			}
		return -1;
	}

int MyString::rfind(const MyString &s) const // 문자열 s가 마지막으로 나타나는 위치 리턴
	{
		int i, j;
		for(i = len-1; i >= 0; i--)
			{
				for(j = 0; j < s.len; j++)
					{
						if(str[i-j] != s.str[s.len-j-1])
							break;
					}
				if(j == s.len)
					return i-s.len+1;
			}
		return -1;
	}

int MyString::rfind(const char *str) const // 문자열 str이 마지막으로 나타나는 위치 리턴
	{
		int i, j;
		for(i = len-1; i >= 0; i--)
			{
				for(j = 0; j < strlen(str); j++)
					{
						if(this->str[i-j] != str[strlen(str)-j-1])
							break;
					}
				if(j == strlen(str))
					return i-strlen(str)+1;
			}
		return -1;
	}

int MyString::rfind(char c) const // 문자 c가 마지막으로 나타나는 위치 리턴
	{
		int i;
		for(i = len-1; i >= 0; i--)
			{
				if(str[i] == c)
					return i;
			}
		return -1;
	}


int MyString::compare(const MyString &s) const // 문자열 s와 비교, 문자열 s가 크면 양수, 같으면 0, 작으면 음수 리턴
	{
		int i;
		for(i = 0; i < len; i++)
			{
				if(str[i] != s.str[i])
					return str[i] - s.str[i];
			}
		return 0;
	}

int MyString::compare(const char *str) const // 문자열 str과 비교, 문자열 str이 크면 양수, 같으면 0, 작으면 음수 리턴
	{
		int i;
		for(i = 0; i < len; i++)
			{
				if(this->str[i] != str[i])
					return this->str[i] - str[i];
			}
		return 0;
	}

// 연산자 오버로딩
bool MyString::operator==(const MyString &s) const // 문자열 s와 비교, 문자열 s가 같으면 true, 다르면 false 리턴
	{
	return !compare(s);
	}






int main() {
	MyString s1("Hello ");
	MyString s2("World");
	MyString s3;
	s1.print();
	s2.print();

	// 전체 문자열 길이 출력
	cout << "s1의 길이 : " << s1.length() << endl;
	cout << "s2의 길이 : " << s2.length() << endl;

	// 문자열 덧붙이기
	s1.Add(s2);
	s1.print();

	// 문자열 대입하기
	s3.Assign("New Hello World Assigned");
	s3.print();


	// 모든 변수의 length, capacity 출력
	cout << "s1의 길이 : " << s1.length() << ", 용량 : " << s1.capacity() << endl;
	cout << "s2의 길이 : " << s2.length() << ", 용량 : " << s2.capacity() << endl;
	cout << "s3의 길이 : " << s3.length() << ", 용량 : " << s3.capacity() << endl;

	// 문자열 용량 늘리기
	s1.reserve(100);
	s1.print();

	// 문자위치 접근,출력
	cout << "3번째 위치 문자는 " << s1.at(3) << endl;

	// 문자열 삽입
	s3.insert(4, s1);
	s3.print();

	// 문자열 삭제
	s3.erase(4, 10);
	s3.print();

	// 문자열 대체
	s3.replace(4, 10, s1);
	s3.print();

	// 문자열 찾기
	cout << "s3에서 s1이 처음 나타나는 위치 : " << s3.find(s1) << endl;

	// 문자열 비교
	cout << "s1과 s2를 비교 : " << s1.compare(s2) << endl;

	// 연산자 오버로딩
	if(s1 == s2)
		cout << "s1과 s2는 같다." << endl;
	else
		cout << "s1과 s2는 다르다." << endl;














	return 0;
		}
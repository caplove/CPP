
// ������ �����ε�
// �� ������ �����ε�
// ���� 
// �������� operator �Ű�����
// ex) bool operator==(const MyString &s) const // ���ڿ� s�� ��, ���ڿ� s�� ������ true, �ٸ��� false ����, �Է°������ ������� �����Ƿ� const
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

		int length() const; // ���ڿ� ���� ����,�б� �����Լ��� const ����
		void print() const; // ���ڿ� ���,�б� �����Լ��� const ����
		MyString& Add(const MyString &s); // ���ڿ� �����̱�
		MyString& Assign(const MyString &s); // ���ڿ� �����ϱ�
		MyString& Assign(const char *str); // ���ڿ� �����ϱ�
		int capacity() const; // ���ڿ� �뷮 ����,�б� �����Լ��� const ����
		void reserve(int size); // ���ڿ� �뷮 �ø���
		char& at(int i) const; // i��° ���� ����,�б� �����Լ��� const ����
		MyString& insert(int i, const MyString &s); // i��° ��ġ�� ���ڿ� s ����
		MyString& insert(int i, const char *str); // i��° ��ġ�� ���ڿ� str ����
		MyString& insert(int i, char c); // i��° ��ġ�� ���� c ����

		MyString& erase(int i, int j); // i��° ��ġ���� j���� ���ڿ� ����
		MyString& erase(int i); // i��° ��ġ�� ���ڿ� ����
		MyString& replace(int i, int j, const MyString &s); // i��° ��ġ���� j���� ���ڿ��� s�� ��ü
		MyString& replace(int i, int j, const char *str); // i��° ��ġ���� j���� ���ڿ��� str�� ��ü
		MyString& replace(int i, int j, char c); // i��° ��ġ���� j���� ���ڿ��� c�� ��ü
		int find(const MyString &s) const; // ���ڿ� s�� ó�� ��Ÿ���� ��ġ ����
		int find(const char *str) const; // ���ڿ� str�� ó�� ��Ÿ���� ��ġ ����
		int find(char c) const; // ���� c�� ó�� ��Ÿ���� ��ġ ����
		int rfind(const MyString &s) const; // ���ڿ� s�� ���������� ��Ÿ���� ��ġ ����
		int rfind(const char *str) const; // ���ڿ� str�� ���������� ��Ÿ���� ��ġ ����
		int rfind(char c) const; // ���� c�� ���������� ��Ÿ���� ��ġ ����
		int compare(const MyString &s) const; // ���ڿ� s�� ��
		int compare(const char *str) const; // ���ڿ� str�� ��

		bool operator==(const MyString &s) const; // ���ڿ� s�� ��

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
	// ���ڿ�, ���ڿ� ����, �뷮�� ����� ���
	cout << "���ڿ� : " << str << ", ���� : " << len << ", �뷮 : " << memory_capacity << endl;
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
			cout << "������ ������ϴ�." << endl;
			exit(1);
		}
		return str[i];
	}

MyString& MyString::insert(int i, const MyString &s)
	{
		if(i < 0 || i > len)
			{
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len += s.len;
		// ���ڿ� ���̰� �þ�� �޸� �뷮�� 2��� �ø���.
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
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len += strlen(str);

		// ���ڿ� ���̰� �þ�� �޸� �뷮�� 2��� �ø���.
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
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len += 1;
		// ���ڿ� ���̰� �þ�� �޸� �뷮�� 2��� �ø���.
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

MyString& MyString::erase(int i, int j)  // i��° ��ġ���� j���� ���ڿ� ����
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len -= j;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i��° ��ġ���� ����
		strcat_s(temp, len*2, str+i+j); // i��° ��ġ���� j���� ���ڿ��� ������ ������ ���ڿ��� ����
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

MyString& MyString::erase(int i) // i��° ��ġ�� ���ڿ� ����
	{
		if(i < 0 || i > len)
			{
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len -= 1;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i��° ��ġ���� ����
		strcat_s(temp, len*2, str+i+1); // i��° ��ġ�� ���ڸ� ������ ������ ���ڿ��� ����
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

MyString& MyString::replace(int i, int j, const MyString &s) // i��° ��ġ���� j���� ���ڿ��� s�� ��ü
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len -= j;
		len += s.len;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i��° ��ġ���� ����
		strcat_s(temp, len*2, s.str); // i��° ��ġ���� j���� ���ڿ��� ������ ������ ���ڿ��� ����
		strcat_s(temp, len*2, str+i+j); // i��° ��ġ���� j���� ���ڿ��� ������ ������ ���ڿ��� ����
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

MyString& MyString::replace(int i, int j, const char *str) // i��° ��ġ���� j���� ���ڿ��� str�� ��ü
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len -= j;
		len += strlen(str);
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i��° ��ġ���� ����
		strcat_s(temp, len*2, str); // i��° ��ġ���� j���� ���ڿ��� ������ ������ ���ڿ��� ����
		strcat_s(temp, len*2, str+i+j); // i��° ��ġ���� j���� ���ڿ��� ������ ������ ���ڿ��� ����
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}


MyString& MyString::replace(int i, int j, char c) // i��° ��ġ���� j���� ���ڿ��� c�� ��ü
	{
		if(i < 0 || i > len || j < 0 || j > len)
			{
				cout << "������ ������ϴ�." << endl;
				exit(1);
			}
		len -= j;
		len += 1;
		char *temp = new char[len*2];
		strncpy_s(temp, len*2, str, i); // i��° ��ġ���� ����
		temp[i] = c; // i��° ��ġ�� ���� c�� ����
		strcat_s(temp, len*2, str+i+j); // i��° ��ġ���� j���� ���ڿ��� ������ ������ ���ڿ��� ����
		if(str != NULL)
			delete []str;
		str = temp;
		memory_capacity = len*2;
	}

int MyString::find(const MyString &s) const // ���ڿ� s�� ó�� ��Ÿ���� ��ġ ����
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

int MyString::find(const char *str) const // ���ڿ� str�� ó�� ��Ÿ���� ��ġ ����
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


int MyString::find(char c) const // ���� c�� ó�� ��Ÿ���� ��ġ ����
	{
		int i;
		for(i = 0; i < len; i++)
			{
				if(str[i] == c)
					return i;
			}
		return -1;
	}

int MyString::rfind(const MyString &s) const // ���ڿ� s�� ���������� ��Ÿ���� ��ġ ����
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

int MyString::rfind(const char *str) const // ���ڿ� str�� ���������� ��Ÿ���� ��ġ ����
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

int MyString::rfind(char c) const // ���� c�� ���������� ��Ÿ���� ��ġ ����
	{
		int i;
		for(i = len-1; i >= 0; i--)
			{
				if(str[i] == c)
					return i;
			}
		return -1;
	}


int MyString::compare(const MyString &s) const // ���ڿ� s�� ��, ���ڿ� s�� ũ�� ���, ������ 0, ������ ���� ����
	{
		int i;
		for(i = 0; i < len; i++)
			{
				if(str[i] != s.str[i])
					return str[i] - s.str[i];
			}
		return 0;
	}

int MyString::compare(const char *str) const // ���ڿ� str�� ��, ���ڿ� str�� ũ�� ���, ������ 0, ������ ���� ����
	{
		int i;
		for(i = 0; i < len; i++)
			{
				if(this->str[i] != str[i])
					return this->str[i] - str[i];
			}
		return 0;
	}

// ������ �����ε�
bool MyString::operator==(const MyString &s) const // ���ڿ� s�� ��, ���ڿ� s�� ������ true, �ٸ��� false ����
	{
	return !compare(s);
	}






int main() {
	MyString s1("Hello ");
	MyString s2("World");
	MyString s3;
	s1.print();
	s2.print();

	// ��ü ���ڿ� ���� ���
	cout << "s1�� ���� : " << s1.length() << endl;
	cout << "s2�� ���� : " << s2.length() << endl;

	// ���ڿ� �����̱�
	s1.Add(s2);
	s1.print();

	// ���ڿ� �����ϱ�
	s3.Assign("New Hello World Assigned");
	s3.print();


	// ��� ������ length, capacity ���
	cout << "s1�� ���� : " << s1.length() << ", �뷮 : " << s1.capacity() << endl;
	cout << "s2�� ���� : " << s2.length() << ", �뷮 : " << s2.capacity() << endl;
	cout << "s3�� ���� : " << s3.length() << ", �뷮 : " << s3.capacity() << endl;

	// ���ڿ� �뷮 �ø���
	s1.reserve(100);
	s1.print();

	// ������ġ ����,���
	cout << "3��° ��ġ ���ڴ� " << s1.at(3) << endl;

	// ���ڿ� ����
	s3.insert(4, s1);
	s3.print();

	// ���ڿ� ����
	s3.erase(4, 10);
	s3.print();

	// ���ڿ� ��ü
	s3.replace(4, 10, s1);
	s3.print();

	// ���ڿ� ã��
	cout << "s3���� s1�� ó�� ��Ÿ���� ��ġ : " << s3.find(s1) << endl;

	// ���ڿ� ��
	cout << "s1�� s2�� �� : " << s1.compare(s2) << endl;

	// ������ �����ε�
	if(s1 == s2)
		cout << "s1�� s2�� ����." << endl;
	else
		cout << "s1�� s2�� �ٸ���." << endl;














	return 0;
		}
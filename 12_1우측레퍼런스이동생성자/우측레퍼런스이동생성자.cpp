
// 이동생성자 &&
// str3 = str + str2일때
// str3는 임시생성된 객체이다. (즉, 임시객체가 가리키는 문자열로 바꿔치기를 한다.)
// 임시생성된 객체는 rvalue이다.
// rvalue는 복사생성자가 아닌 이동생성자를 호출한다.
// 이동생성자는 깊은 복사가 아닌 얕은 복사를 수행한다.
// 이동생성자는 임시객체를 소멸시키지 않는다.
// 임시객체를 소멸시키지 않는다는 것은, 임시객체의 소멸자가 호출되지 않는다는 것이다.



#include <iostream>
#include <cstring>
#include <vector>

class MyString {
    char* string_content;  // 문자열 데이터를 가리키는 포인터
    int string_length;     // 문자열 길이

    int memory_capacity;  // 현재 할당된 용량

public:
    MyString();

    // 문자열로 부터 생성
    MyString(const char* str);

    // 복사 생성자
    MyString(const MyString& str);

    // 이동 생성자
    MyString(MyString&& str) noexcept;

    ~MyString();
};

MyString::MyString() {
    std::cout << "생성자 호출 ! " << std::endl;
    string_length = 0;
    memory_capacity = 0;
    string_content = NULL;
}

MyString::MyString(const char* str) {
    std::cout << "생성자 호출 ! " << std::endl;
    string_length = strlen(str);
    memory_capacity = string_length;

    string_content = new char[string_length]; // 깊은 복사
    for (int i = 0; i != string_length; i++) string_content[i] = str[i];
}
MyString::MyString(const MyString& str) {
    std::cout << "복사 생성자 호출 ! " << std::endl;
    string_length = str.string_length;
    memory_capacity = str.string_length;

    string_content = new char[string_length]; // 깊은 복사
    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}
MyString::MyString(MyString&& str) noexcept {
    std::cout << "이동 생성자 호출 !" << std::endl;
    string_length = str.string_length;
    memory_capacity = str.memory_capacity;
    string_content = str.string_content; // 얕은 복사
    // 임시 객체 소멸 시에 메모리를 해제하지 못하게 한다.
    str.string_content = nullptr;
}
MyString::~MyString() {
    // 소멸자가 nullptr이면, delete[]를 호출하지 않는다. 이동생성자에서 nullptr로 만들어줬기 때문에...
    if (string_content) delete[] string_content; 
}

int main() {
    MyString s("abc");
    std::vector<MyString> vec;
    vec.resize(0);

    std::cout << "첫 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "두 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "세 번째 추가 ---" << std::endl;
    vec.push_back(s);
    std::cout << "네 번째 추가 ---" << std::endl;
    vec.push_back(s);
}
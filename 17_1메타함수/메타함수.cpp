
// 17.1 메타함수
// 메타함수란 컴파일 타임에 실행되는 함수를 말한다.
// 종류 : type traits, type transformation, type property, type relationship, type category, type function
// ( ) : 함수 호출 연산자, ()안에 있는 인자를 함수의 인자로 넣어준다.
// < > : 템플릿 인자를 넣어준다.



#include <iostream>

template <typename T>
struct is_void {
    static constexpr bool value = false;
};

template <>
struct is_void<void> {
    static constexpr bool value = true;
};

template <typename T>
void tell_type() {
    if (is_void<T>::value) {
        std::cout << "T 는 void ! \n";
    }
    else {
        std::cout << "T 는 void 가 아니다. \n";
    }
}




int main() {
    tell_type<int>();  // void 아님!

    tell_type<void>();  // void!
}
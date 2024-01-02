
// 17.1 ��Ÿ�Լ�
// ��Ÿ�Լ��� ������ Ÿ�ӿ� ����Ǵ� �Լ��� ���Ѵ�.
// ���� : type traits, type transformation, type property, type relationship, type category, type function
// ( ) : �Լ� ȣ�� ������, ()�ȿ� �ִ� ���ڸ� �Լ��� ���ڷ� �־��ش�.
// < > : ���ø� ���ڸ� �־��ش�.



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
        std::cout << "T �� void ! \n";
    }
    else {
        std::cout << "T �� void �� �ƴϴ�. \n";
    }
}




int main() {
    tell_type<int>();  // void �ƴ�!

    tell_type<void>();  // void!
}
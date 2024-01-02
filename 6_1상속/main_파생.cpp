
// 오버라이딩 : 기반 클래스의 함수를 파생 클래스에서 재정의 하는 것(시간이 지나면서 함수의 기능이 달라질 수 있기 때문에)
// 오버로딩 : 같은 이름의 함수를 여러 개 정의하는 것(매개변수의 개수나 타입이 다를때)
// 파생 클래스가 초기화될 때, 기반 클래스 초기화가 먼저 이루어진다.
//           
#include <iostream>
#include <string>

class Base {
    std::string s;
public:
    Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }

    void what() { std::cout << s << std::endl; }
    };

    
class Derived : public Base {
    std::string s;
public:
    Derived() : Base(), s("파생") {
        std::cout << "파생 클래스" << std::endl;

        // Base 에서 what() 을 물려 받았으므로 호출 가능하다.
        what();
        }
    void what() { std::cout << s << std::endl; }  // 오버라이딩
    };





int main() {
    std::cout << " === 기반 클래스 생성 ===" << std::endl;
    Base p;

    std::cout << " === 파생 클래스 생성 ===" << std::endl;
    Derived c;

    return 0;
    }
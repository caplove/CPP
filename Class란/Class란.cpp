//
// 객체 지향
// 인스턴스와 매소드만 설계해두면, 나중에 대상(객체) 이 엄청나게 늘어나더라도, 유지 보수가 용이하다.
// 
// 아래의 예제에서는...
// 인스턴스 : 년,월,일
// 매소드 : public : 날짜 더하기, 달 더하기, 년 더하기, 날짜 보이기, (날짜 생성하기)
//         private : 년/월을 넣으면 해당되는 년월의 최대 일자 구하기    
// 특히 날짜 생성하기는 생성자로 만듬
// 생성자로 만들경우는 객체 생성시 자동으로 호출된다.


// protected 는 상속을 위한 선언이다.
// 만약 인스턴스 : 년, 월, 일을 가지고
// 나중에 (1년쯤 후에) 다른 일을 하려면 소스를 다시고쳐야 한다.
// 즉, 현재까지의 매소드를 상속받고, 더하기 다른 매소드를 만들기 위해서 필요한 것이다.!!!



// 클래스   인스턴스             매소드
// MyClass  day_,month_,year_   MyClass(d,m,y),AddDay(d),AddMonth(m),AddYear(y),GetMaxDay(y,m),ShowDate()
//                      
// DerivedClass  상속           상속 +  AddTenDays()

#include <iostream>

class MyClass {
protected:
	int year_;
	int month_;
	int day_;

public:
	MyClass(); // 생성자 선언
	MyClass(int year, int month, int day); // 생성자 선언
	~MyClass(); // 소멸자 선언

	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);
	void ShowDate();



	int GetMaxDay(int year, int month);

};

MyClass::MyClass() // 생성자 정의
{
	std::cout << "MyClass 객체가 초기값을 가지고 생성됩니다." << std::endl;
	year_ = 2000;
	month_ = 01;
	day_ = 01;
}


MyClass::MyClass(int year, int month, int day) // 생성자 정의
{
	std::cout << "MyClass 객체가 생성됩니다." << std::endl;
	year_ = year;
	month_ = month;
	day_ = day;
}



void MyClass::AddDay(int inc)
{
	day_ += inc;
	while (day_ > GetMaxDay(year_, month_)) {
		day_ -= GetMaxDay(year_, month_);
		AddMonth(1);
	}
}

void MyClass::AddMonth(int inc)
{
	month_ += inc;
	while (month_ > 12) {
		month_ -= 12;
		AddYear(1);
	}
}

void MyClass::AddYear(int inc)
{
	year_ += inc;
}

void MyClass::ShowDate()
{
	std::cout << year_ << '/' << month_ << '/' << day_ << std::endl;
}

MyClass::~MyClass() // 소멸자 정의
{
	std::cout << "MyClass 객체가 소멸됩니다." << std::endl;
}

int MyClass::GetMaxDay(int year, int month)
{
	if (month == 2) { // 2월은 윤년을 고려해 29일까지 있을 수 있음
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
			return 29;
		}
		else {
			return 28;
		}
	}
	else { // 나머지 달은 30일 또는 31일까지 있을 수 있음
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			return 30;
		}
		else {
			return 31;
		}
	}
}

//--------------------------------------------------------------------------------
class DerivedClass : public MyClass {
public:
	DerivedClass() : MyClass(2000, 1, 1) {} // 파생 클래스 생성자
	DerivedClass(int year, int month, int day) : MyClass(year, month, day) {} // 파생 클래스 생성자
	void AddTenDays(); // 파생 클래스 매소드
	void CountDays(); // 파생 클래스 매소드
};

void DerivedClass::AddTenDays()
{
	AddDay(10);
}

void DerivedClass::CountDays()
{
	// 1월1일부터 현재까지의 날짜 수를 계산하는 매소드

	int total_days = 0;

	//for (int i = 1; i < year_; ++i) {
	//	if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) {
	//		total_days += 366;
	//	}
	//	else {
	//		total_days += 365;
	//	}
	//}

	for (int i = 1; i < month_; ++i) {
		total_days += GetMaxDay(year_, i);
	}

	total_days += day_ - 1;

	std::cout << "1월 1일부터 오늘까지의 날짜 수는 " << total_days << "일 입니다." << std::endl;

}






//--------------------------------------------------------------------------------


int main()
{
	int year, month, day;
	std::cout << "오늘 날짜 입력(YYYY MM DD): ";
	std::cin >> year >> month >> day;

	MyClass obj(year, month, day); // 생성자 호출

	std::cout << "입력된 날짜" << std::endl;
	obj.ShowDate();

	std::cout<< "오리지널 클라스의 매소드를 이용한 결과" << std::endl;
	
	int added_day;
	std::cout<< "증가할 날짜를 입력하시오" << std::endl;

	std::cin >> added_day;
	obj.AddDay(added_day);
	obj.ShowDate();


	std::cout << "파생된 클라스의 AddTenDays 매소드를 이용한 결과" << std::endl;

	DerivedClass derived_obj(year, month, day); // 파생 클래스 객체 생성
	derived_obj.AddTenDays();
	derived_obj.ShowDate();

	//derived_obj.AddDay(added_day);


	derived_obj.CountDays();

	return 0;
}

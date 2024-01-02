// Class예제.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 
// 클래스 뷰를 보면서 매소드와 인스턴스 즉, 맴버변수와 맴버함수 이해하고
// 클래스   인스턴스      매소드
// Point   int x_, int y_        Point(),GetX(),GetY(),CalDistance(Point& point)
//                       좌표값 생성,  값얻기, 두점사이의 거리구하기
// Geometry int num_points_,              Geometry(),Geometry(Point** point_list),AddPoint(Point& point)
//			Point* point_array_[100] 	 ,PrintDistance(),PrintNumMeets()
//         (클래스포인터형)              배열생성하기, 추가하기,배열간의모든 경우의 거리표시하기, 거리10이내 개수 찾기      

#include <iostream>
#include <cmath>

class Point {
private:
	int x_, y_;

public:
	                   
	Point() : x_(0), y_(0) 	{}   // @ note 기본생성자 : 초기값을 0으로 설정
	~Point() {} // @ note 소멸자 : 할당된 메모리를 해제

	Point(int pos_x, int pos_y) : x_(pos_x), y_(pos_y) {} // @ note 생성자 : 좌표값을 받아서 초기화
	Point(const Point& other) : x_(other.x_), y_(other.y_) {} 	// @ note 복사생성자 : 좌표값을 받아서 초기화
	



	// @ note 좌표값을 얻는 함수
	int GetX() const { return x_; }
	int GetY() const { return y_; }

	// @ note 두점사이의 거리를 구하는 함수
	double CalcDistance(const Point& other) const {
		int dx = x_ - other.x_;
		int dy = y_ - other.y_;
		return std::sqrt(dx * dx + dy * dy);
	}
};

/// <summary>
/// 
/// </summary>

class Geometry {
public:
	Point* point_array_[100]; // 포인터
	int num_points_;          

public:
	Geometry() : num_points_(0) {}
																		
	Geometry(Point** point_list) : num_points_(0) { 
		for (int i = 0; i < 100; ++i) {
			if (point_list[i] == nullptr) {
				break;
			}
			AddPoint(*point_list[i]);
		}
	}

	void AddPoint(const Point& point) {  // const표시의 의미 --> 추가만 할 뿐이다. 바꾸지 않는다.
		if (num_points_ < 100) {
			point_array_[num_points_] = new Point(point);
			++num_points_;
		}
	}

	void PrintDistance() {
		for (int i = 0; i < num_points_ - 1; ++i) {
			for (int j = i + 1; j < num_points_; ++j) {
				double dist = point_array_[i]->CalcDistance(*point_array_[j]);
				std::cout << "Point[" << i << "] and Point[" << j << "] distance: " << dist << std::endl;
			}
		}
	}

	void PrintNumMeets() {
		int num_meets = 0;
		for (int i = 0; i < num_points_ - 1; ++i) {
			for (int j = i + 1; j < num_points_; ++j) {
				double dist = point_array_[i]->CalcDistance(*point_array_[j]);
				if (dist <= 10) {
					++num_meets;
				}
			}
		}
		std::cout << "두점간의 거리가 10 이내인 개수는 " << num_meets << std::endl;
	}

	~Geometry() {
		for (int i = 0; i < num_points_; ++i) {
			delete point_array_[i];
		}
	}
};



int main() {
	Point* point_list[10]; // 클래스 정의

	point_list[0] = new Point(1, 1);
	point_list[1] = new Point(2, 2);
	point_list[2] = new Point(3, 5);
	point_list[3] = nullptr;

	Geometry geo(point_list); //클래스 정의
	geo.AddPoint(Point(4, 4));
	geo.AddPoint(Point(5, 11));

	geo.PrintDistance();
	geo.PrintNumMeets();

	return 0;
}

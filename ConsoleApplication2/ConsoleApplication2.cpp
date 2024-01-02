


// 씹어먹는 CPP 공부
// 1. 주소값을 인자로 받아서 바꾸는 함수, 즉 변수값을 바꾸는 것을 함수화 
// 2. 레퍼런스(참조자) 기반 주소값과 거기에 넣을 값을 받아서 구현
// 3. 참조자 입력 --> 참조자 출력
// 4. 참조자 2개 입력 --> 참조자 1개 출력


#include    <iostream> 
 

// 1 : 포인터 기반 주소값과 거기에 넣을 값을 받아서 구현
int change_val_1(int *p, int value)    {   
    *p = value;
    return    0;
}

// 2 : 레퍼런스(참조자) 기반 주소값과 거기에 넣을 값을 받아서 구현
int change_val_2(int& p, int value) {
    p = value;
    return 0;
}

// 3 : 참조자 입력 --> 참조자 출력
// 참조자를 입력받아서 참조자를 내보낸다.
// 여기서 a는 내용, 즉 구조체로 heavy 하기때문에, function(a)하면 xx됨. 
// 따라서 a를 참조하는 주소만을 입력받고
// 함수안에서 a를 처리하고, 다시 그 주소만을 출력하여, 입출력 시간이 간단해진다.
// 즉, 함수의 입출력을 값이 아닌 주소로 한다.!!!!!!!!

int& function(int& a) {

    // a를 처리하는 블록
    a = a*5*5*5;
    return    a;
}

void changeNumber(int& num) {
    num += 10;
}

// 4. 참조자 2개 입력 --> 참조자 1개 출력
int& getLargestNumber(int& num1, int& num2) {
    if (num1 > num2) {
        return num1;
    }
    else {
        return num2;
    }
}

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////



int    main() {
    // 1-2
    int    number1 = 5,number2=10;
    std::cout << number1 << std::endl; 
    change_val_1(&number1,1);
    change_val_2(number2, 2);
    std::cout << number1 << "  " << number2 << std::endl;

    // 3
    int b = 2;
    int c = function(b);
    int z = 10;
    std::cout << "계산하고 난 결과 :"<<c << std::endl;

    // 4.
    int x = 5, y = 10;
    int& largestNum = getLargestNumber(x, y); // largestNum이 x를 참조함
    largestNum = 20; // x의 값이 변경됨
    std::cout << x << " " << y << std::endl; // 출력 결과: 5



}

 



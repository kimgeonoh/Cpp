// INPUT 함수에서 문자 2개를 입력받으세요
// OUTPUT 함수에서 입력 받은 문자 2개를 출력하세요.
// main함수에서는 INPUT 함수와 OUTPUT함수를 호출 하시면 됩니다.

#include <iostream>

void INPUT(char& ch1, char& ch2) {
    std::cin >> ch1 >> ch2;
}

void OUTPUT(char ch1, char ch2) {
    std::cout << ch1 << " " << ch2 << std::endl;
}

int main() {
    char input1, input2;
    INPUT(input1, input2);
    OUTPUT(input1, input2);

    return 0;
}

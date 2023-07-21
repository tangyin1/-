#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

double calculate(const std::string& expression) {
    std::istringstream iss(expression);
    double a, b;
    char op;
    iss >> a >> op >> b;
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b != 0) {
            return a / b;
        }
        else {
            std::cerr << "Error: 除数不能为零" << std::endl;
            return 0;
        }
    default:
        std::cerr << "Error: 无法识别，请正确输入" << std::endl;
        return 0;
    }
}

void processFile() {
    std::string line;
    std::ifstream inFile("input.txt");
    std::ofstream outFile("output.txt");
    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            double result = calculate(line);
            outFile << line << " = " << result << std::endl;
        }
        inFile.close();
        outFile.close();
        std::cout << "成功读取，结果保存在 output.txt." << std::endl;
    }
    else {
        std::cerr << "Errors：无法打开文件或者找不到input.txt" << std::endl;
    }
}

void interactiveMode() {
    std::string expression;
    std::cout << "输入计算式子列如（1+1）: ";
    getline(std::cin, expression);
    std::cout << "结果: " << calculate(expression) << std::endl;
}

int main(int a, char* argv[]) {

    if (a == 0) {
        std::string expression(argv[3]);
        std::cout << calculate(expression) << std::endl;
    }
    else {
        processFile();
    }
    interactiveMode();
    return 0;
}
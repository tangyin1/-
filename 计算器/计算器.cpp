#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

double calculate(const std::string& expression) {
    int length = expression.length();
    double result = 0.0;

    // 用来保存当前子表达式的运算符和操作数
    char operation = '+';
    double operand = 0.0;

    for (int i = 0; i < length; i++) {
        char ch = expression[i];

        // 处理数字
        if (isdigit(ch) || ch == '.') {
            operand = operand * 10.0 + (ch - '0');
        }

        // 处理括号
        if (ch == '(') {
            int j = i + 1;  // 找到与当前左括号匹配的右括号的位置
            int bracketsCount = 1;
            while (bracketsCount > 0 && j < length) {
                if (expression[j] == '(') {
                    bracketsCount++;
                }
                else if (expression[j] == ')') {
                    bracketsCount--;
                }
                j++;
            }

            operand = calculate(expression.substr(i + 1, j - i - 2));  // 递归计算内部的子表达式
            i = j - 1;  // 更新位置到右括号之后
        }

        // 当遇到运算符或表达式结尾时，进行运算
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || i == length - 1) {
            switch (operation) {
            case '+':
                result += operand;
                break;
            case '-':
                result -= operand;
                break;
            case '*':
                result *= operand;
                break;
            case '/':
                if (operand != 0.0) {
                    result /= operand;
                }
                else {
                    std::cerr << "Error: 除数不能为零" << std::endl;
                    return 0.0;
                }
                break;
            default:
                std::cerr << "Error: 无法识别，请正确输入" << std::endl;
                return 0.0;
            }

            operand = 0.0;
            operation = ch;
        }
    }

    return result;
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
    std::cout << "注意！当计算乘除的时候需要在数字两端打上英文括号：" << std::endl;
    std::cout << "输入计算式子（例如 1 + (2 * 3）): ";
    getline(std::cin, expression);
    std::cout << "结果: " << calculate(expression) << std::endl;
}

int main(int a, char* argv[]) {
    if (a == 0) {
        std::string expression(argv[1]);
        std::cout << calculate(expression) << std::endl;
    }
    else {
        processFile();
    }
    interactiveMode();
    return 0;
}

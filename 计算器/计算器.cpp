#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

double calculate(const std::string& expression) {
    std::istringstream iss(expression);
    std::vector<double> operands;
    std::vector<char> operators;
    double operand;
    char op;

    while (iss >> operand) {
        operands.push_back(operand);
        if (iss >> op) {
            operators.push_back(op);
        }
    }

    double result = operands[0];
    for (size_t i = 1; i < operands.size(); i++) {
        switch (operators[i - 1]) {
        case '+':
            result += operands[i];
            break;
        case '-':
            result -= operands[i];
            break;
        case '*':
            result *= operands[i];
            break;
        case '/':
            if (operands[i] != 0) {
                result /= operands[i];
            }
            else {
                std::cerr << "Error: 除数不能为零" << std::endl;
                return 0;
            }
            break;
        default:
            std::cerr << "Error: 无法识别，请正确输入" << std::endl;
            return 0;
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
    std::cout << "输入计算式子（例如 1 + 2 * 3）: ";
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

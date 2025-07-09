#include <iostream>
#include <string>
#include <cctype>

class Parser {
private:
    std::string input;
    size_t pos;

    // Get current character
    char current() {
        if (pos < input.length()) return input[pos];
        return '\0';
    }

    // Move to next character
    void advance() {
        if (pos < input.length()) ++pos;
    }

    // Skip whitespace
    void skipWhitespace() {
        while (isspace(current())) advance();
    }

    // Parse a number (integer or float)
    double parseNumber() {
        skipWhitespace();
        std::string number;
        while (isdigit(current()) || current() == '.') {
            number += current();
            advance();
        }
        return std::stod(number);
    }

    // Parse factor: number or (expression)
    double parseFactor() {
        skipWhitespace();
        if (current() == '(') {
            advance(); // skip '('
            double value = parseExpression();
            if (current() == ')') advance(); // skip ')'
            return value;
        } else {
            return parseNumber();
        }
    }

    // Parse term: factor (* or /) factor
    double parseTerm() {
        double result = parseFactor();
        while (true) {
            skipWhitespace();
            if (current() == '*') {
                advance();
                result *= parseFactor();
            } else if (current() == '/') {
                advance();
                result /= parseFactor();
            } else {
                break;
            }
        }
        return result;
    }

    // Parse expression: term (+ or -) term
    double parseExpression() {
        double result = parseTerm();
        while (true) {
            skipWhitespace();
            if (current() == '+') {
                advance();
                result += parseTerm();
            } else if (current() == '-') {
                advance();
                result -= parseTerm();
            } else {
                break;
            }
        }
        return result;
    }

public:
    Parser(const std::string& expr) : input(expr), pos(0) {}

    double evaluate() {
        return parseExpression();
    }
};

int main() {
    std::string expression;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, expression);

    try {
        Parser parser(expression);
        double result = parser.evaluate();
        std::cout << "Result = " << result << std::endl;
    } catch (...) {
        std::cout << "Error: Invalid expression!" << std::endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Абстрактный класс выражения
class Expression {
public:
    virtual int interpret(unordered_map<string, int>& context) = 0;
    virtual ~Expression() {}
};

// Терминальное выражение - константа
class Constant : public Expression {
    int value;
public:
    Constant(int value) {
        this->value = value;
    }
    int interpret(unordered_map<string, int>& context) {
        return value;
    }
};

// Терминальное выражение - переменная
class Variable : public Expression {
    string name;
public:
    Variable(string name) {
        this->name = name;
    }
    int interpret(unordered_map<string, int>& context) {
        return context[name];
    }
};

// Нетерминальное выражение - операция сложения
class Plus : public Expression {
private:
    Expression* left;
    Expression* right;
public:
    Plus(Expression* left, Expression* right) {
        this->left = left;
        this->right = right;
    }
    int interpret(unordered_map<string, int>& context) {
        return left->interpret(context) + right->interpret(context);
    }
    ~Plus() {
        delete left;
        delete right;
    }
};

// Клиентский код
int main() {
    unordered_map<string, int> context = {
        {"x", 5}, {"y", 10}
    };

    Expression* expression = new Plus(new Variable("x"), new Constant(2));
    cout << expression->interpret(context) << endl;

    delete expression;
}

/*
Паттерн Интерпретатор (Interpreter pattern) позволяет определить
грамматику языка и интерпретировать операции, заданные на этом языке.

В данном примере созданы три класса выражений: Constant (константа),
Variable (переменная) и Plus (операция сложения). Каждый из них реализует
метод interpret, который интерпретирует соответствующее выражение.

Клиентский код создает объект выражения Plus, который состоит из переменной
"x" и константы "2". Затем этот объект передается методу interpret, который
вычисляет значение выражения в контексте переменных "x" и "y". В данном
примере контекст содержит значения переменных "x" и "y", которые используются
при интерпретации выражения.

В данном примере используется структура данных unordered_map для хранения
контекста. Она позволяет быстро и эффективно искать значения переменных
по их именам.

Пример показывает, как можно использовать паттерн Интерпретатор
для создания простого интерпретатора выражений. Однако, в реальных проектах
данная реализация может быть недостаточно мощной.
*/
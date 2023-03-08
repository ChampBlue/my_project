#include <iostream>

using namespace std;

class Strategy
{
    public:
        virtual void operate(double a, double b) = 0;    
};

class AddStrategy : public Strategy
{
    public:
        void operate(double a, double b) override{
            cout << a + b <<endl;
        }
};

class MinusStrategy : public Strategy
{
    public:
        void operate(double a, double b) override{
            cout << a - b <<endl;
        }
};

class MultiplyStrategy : public Strategy
{
    public:
        void operate(double a, double b) override{
            cout << a * b <<endl;
        }
};

class DivideStrategy : public Strategy
{
    public:
        void operate(double a, double b) override{
            cout << a / b <<endl;
        }
};

class Calculator
{
    private:
        Strategy* _strategy;
    public:
        Calculator(Strategy* strategy) : _strategy(strategy) {}
        void setStrategy(Strategy* strategy) {
            _strategy = strategy;
        }
        void calculator(double a, double b) {
            _strategy->operate(a, b);
        }
};

int main()
{
    double num1 = 0, num2 = 0;
    char sign = 0;

    cout << "input number1 : ";
    cin >> num1;
    cout << endl;
    cout << "input number2 : ";
    cin >> num2;
    cout << endl;

    while(1) {
        cout << "input sign : ";
        cin >> sign;
        cout << endl;
        if(sign == '+' || sign == '-' || sign == '*' || sign == '/')
            break;      
        cout << "please input correct sign" << endl; 
    }

    Strategy* strategy = nullptr;
    switch(sign){
        case '+':
            strategy = new AddStrategy();
            break;
        case '-':
            strategy = new MinusStrategy();
            break;
        case '*':
            strategy = new MultiplyStrategy();
            break;
        case '/':
            strategy = new DivideStrategy();
            break;
        default :
            break;
    }
    
    Calculator calc(strategy);
    calc.calculator(num1, num2);

    delete strategy;

    return 0;
}
#include <iostream>
using namespace std;

class number
{
private:
    int a, b;

public:
    /* Constructor */
    number() {}
    void sum() { cout << a + b; }
    void input() { cin >> a >> b; }
};

int main()
{
    number num;
    num.input();
    num.sum();
    return 0;
}
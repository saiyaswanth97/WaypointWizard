#include <iostream>
using namespace std;
int add(int a, int b) {
  int result = a + b;
  if (result > 10)
    cout << "Result is greater than 10" << endl;
  else
    cout << "Result is 10 or less" << endl;
  return result;
}
class MyClass {
public:
  MyClass(int v) : value(v) {}
  void display() { cout << "Value:" << value << endl; }

private:
  int value;
};
int main() {
  int a = 5, b = 7;
  MyClass obj(a);
  obj.display();
  int res = add(a, b);
  return 0;
}
//
// Created by gsanthosh on 5/10/24.
//

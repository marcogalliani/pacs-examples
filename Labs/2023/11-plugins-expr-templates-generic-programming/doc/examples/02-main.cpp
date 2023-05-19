void func() {}
int func(int x) { return x; }
double func(const int x, double y) { return y; }

//in a object file the name of an overloaded function is given by the name of the object plus the 
//name of the types given in input

int main() {
  func();
  return 0;
}
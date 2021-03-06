#include <iostream>
#include <memory>

struct A {
   static const char* static_type;
   const char* dynamic_type;
   A() { dynamic_type = static_type; }
};
struct B: A {
   static const char* static_type;
   B() { dynamic_type = static_type; }
};

const char* A::static_type = "sample text A";
const char* B::static_type = "sample text B";

int main () {
   std::shared_ptr<A> foo;
   std::shared_ptr<B> bar;

   bar = std::make_shared<B>();

   foo = std::dynamic_pointer_cast<A>(bar);

   std::cout << "foo's static type: " << foo->static_type << '\n';
   std::cout << "foo's dynamic type: " << foo->dynamic_type << '\n';
   std::cout << "bar's static type: " << bar->static_type << '\n';
   std::cout << "bar's dynamic type: " << bar->dynamic_type << '\n';

   return 0;
}
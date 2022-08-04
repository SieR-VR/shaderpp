#include <iostream>

#include "parser.h"
#include "codegen/builder.h"

int main() {
  Parser::Function<Parser::Variable, int, int> function("add", [](int a, int b) {
    return Parser::Variable("result", ::Type("int", {}));
  });
}
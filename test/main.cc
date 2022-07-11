#include <iostream>
#include "codegen/builder.h"

int main() {
  Builder builder({
    Declaration(
      Function (
        Type("int", {}),
        "main",
        {
          {"argc", Type("int", {})},
          {"argv", Type("char", {})}
        },
        {
          Statement::If(
            Expression::Literal("true"),
            {
              Statement::Return(Expression::Literal("0"))
            },
            {
              Statement::Return(Expression::Literal("1"))
            }
          )
        }
      )
    )
  });

  std::cout << builder.build() << std::endl;
}
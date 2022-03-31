#include <iostream>

#include "core/parser.h"
#include "core/internal_functions.h"

class MyStruct : public GLSL::Variable 
{
public:
    GLSL::Float fl;
    GLSL::Int in;

    MyStruct() : fl("fl"), in("in") {
        this->tree = new GLSL::Tree(Namer::next(), type_name(), GLSL::ParentType::Declaration);

        GLSL::record(this->tree);

        fl.set_origin(this->tree);
        in.set_origin(this->tree);
    }

    std::string type_name() {
        return "MyStruct";
    }
};

int main(int argc, char *argv[])
{
    using namespace GLSL;
    std::function<MyStruct(Int &, Float &)> to_parse = [](Int &a1, Float &a2)
    {
        MyStruct st;
        st.in = a1;
        st.fl = a2;

        return st;
    };
    auto some_function = Parse(to_parse, "some_function");

    std::cout << some_function.declaration
              << std::endl
              << some_function.definition;
    return 0;
}
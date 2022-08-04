#ifndef _PARSER_H_
#define _PARSER_H_

#include <functional>
#include "codegen/builder.h"

class Parser
{
public:
    template <class ReturnType, class... Args>
    class Function;
    struct Variable;
    class Context;

    struct Variable
    {
        std::string name;
        ::Type type;

        Variable(std::string name, ::Type type)
            : name(name), type(type)
        {
        }

        Expression::Variable toExpression() const;
        std::string toDeclaration() const;

        static Variable None()
        {
            return Variable("", ::Type("void", {}));
        }
    };

    template <class ReturnType, class... Args>
    class Function
    {
    public:
        std::string name;
        std::vector<Variable> arguments;
        ReturnType return_type = Variable::None();

        Function(std::string name, std::function<ReturnType(Args...)> function)
            : name(name)
        {
            std::tuple<Args...> dummy;
            const auto fill_lambda = [&](auto &...arg)
            {
                (arguments.push_back(Variable(arg.name, arg.type)), ...);
            };

            ReturnType r = std::apply(function, dummy);
            return_type = r;
        }
    };

    struct Block
    {
    };

    class Context
    {
    public:
        static std::map<std::string, Variable *> type_table_defaults;

        std::map<std::string, Variable *> type_table;
        std::vector<std::pair<std::string, Variable *>> variables;

        std::vector<Statement> statements;

        Context() {
            type_table = type_table_defaults;
        }
    };

    Context *context = new Context();

    Parser() {}

    template <class ReturnType, class... Args>
    
};

#endif // _PARSER_H_
#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <functional>

namespace GLSL
{
    enum class ParentType
    {
        None = 0,
        Argument = 1,
        Function = 2,
        UnaryOperator = 3,
        BinaryOperator = 4,
        AssignOperator = 5,
        Declaration = 6,
    };

    class Tree;
    class Variable;
    class Context;
    class Parser;

    class Variable
    {
    public:
        Tree *tree;
        Context *context;

        virtual std::string get_declaration() = 0;
    };

    class Tree
    {
    public:
        std::vector<Tree *> parents;
        std::string token;
        std::string glsl_type;
        ParentType parent_type;

        Tree(std::string token, std::string glsl_type, ParentType parent_type = ParentType::None)
            : token(token), glsl_type(glsl_type), parent_type(parent_type)
        {
        }

        std::string get_expression()
        {
            switch (parent_type)
            {
            case ParentType::None:
            case ParentType::Argument:
            case ParentType::AssignOperator:
            case ParentType::Declaration:
                return token;
            case ParentType::Function:
            {
                std::string expression = token + "(";
                for (int i = 0; i < parents.size(); i++)
                {
                    expression += parents[i]->get_expression();
                    if (i != parents.size() - 1)
                        expression += ", ";
                }
                expression += ")";
                return expression;
            }
            case ParentType::UnaryOperator:
                return "(" + token + parents[0]->get_expression() + ")";
            case ParentType::BinaryOperator:
                return "(" + parents[0]->get_expression() + " " + token + " " + parents[1]->get_expression() + ")";
            default:
                return "";
            }
        }
    };

    class Context
    {
    public:
        std::vector<std::string> recorder;

        void record(Tree *lhs, Tree *rhs)
        {
            switch (lhs->parent_type)
            {
            case ParentType::AssignOperator:
                recorder.push_back("\t" + lhs->get_expression() + " = " + rhs->get_expression() + ";\n");
                break;
            case ParentType::Declaration:
                recorder.push_back("\t" + lhs->glsl_type + " " + lhs->token + " = " + rhs->get_expression() + ";\n");
                break;
            default:
                break;
            }
        }
    };

    template <typename T, typename A1, typename A2>
    static std::string Parse(std::function<T(A1 &, A2 &)> func, std::string func_name)
    {
        Context *context = new Context();

        A1 a1("a1", context);
        A2 a2("a2", context);
        T execution_result = func(a1, a2);
        Tree *tree = execution_result.tree;

        std::string header = tree->glsl_type + " " + func_name +
                             "(" + a1.get_declaration() + ", " + a2.get_declaration() + ") {\n";
        std::string footer = "}\n";

        std::string result = header;
        for (std::string line : context->recorder)
            result += line;
        result += "\treturn " + tree->get_expression() + ";\n";
        result += footer;

        return result;
    }
} // namespace GLSL

#endif
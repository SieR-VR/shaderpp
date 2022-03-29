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

    class Variable
    {
    public:
        Tree *tree;
        virtual std::string get_declaration() = 0;
    };

    template <typename T, typename ...Args>
    class Function
    {
    public:
        std::string declaration;
        std::string definition;
        std::string symbol;

        Function(std::string symbol) : symbol(symbol) {}

        std::vector<Tree *> unwrap_others() {
            return std::vector<Tree *>();
        }

        template <typename U, typename ...Args_>
        std::vector<Tree *> unwrap_others(U &u, Args_ &...others) {
            std::vector<Tree *> unwraped = unwrap_others(others...);
            unwraped.insert(unwraped.begin(), u.tree);

            return unwraped;
        }

        T &operator()(Args &...others)
        {
            return *(new T(symbol, ParentType::Function, unwrap_others(others...)));
        }
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

    static std::vector<std::string> recorder;
    static void record(Tree *lhs, Tree *rhs)
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

    static int arg_index = 0;
    static std::string argument_declaration = "";

    template <typename T>
    static auto bind_args(std::function<T()> func) {
        return func;
    }
    
    template <typename T, typename A, typename ...Args>
    static auto bind_args(std::function<T(A&, Args&...)> func) {
        auto result = std::bind(func, A("a" + std::to_string(arg_index)));
        std::function<T(Args&...)> binded = [&](Args&... args) -> T {
            return result(args...);
        };

        return bind_args(binded);
    }

    template <typename T, typename ...F>
    static Function<T, F...> Parse(std::function<T(F &...)> func, std::string func_name)
    {
        recorder.clear();
        arg_index = 0;

        auto binded = bind_args(func);
        T t = binded();

        Function<T, F...> function(func_name);

        // std::string header = t.tree->glsl_type + " " + func_name +
        //                      "(" + a1.get_declaration() + ", " + a2.get_declaration() + ")";
        // std::string footer = "}\n";

        // function.definition = header + " {\n";
        // for (std::string line : recorder)
        //     function.definition += line;
        // function.definition += "\treturn " + tree->get_expression() + ";\n";
        // function.definition += footer;

        // function.declaration = header + ";\n";

        return function;
    }
} // namespace GLSL

#endif
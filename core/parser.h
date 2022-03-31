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
        Argument,
        Member,
        Function,
        UnaryOperator,
        BinaryOperator,
        AssignOperator,
        Declaration,
        Constructor,
    };

    class Tree;
    class Variable;

    template <typename T, typename... Args>
    class Function
    {
    public:
        std::string declaration;
        std::string definition;
        std::string symbol;

        Function(std::string symbol) : symbol(symbol) {}

        std::vector<Tree *> unwrap_others()
        {
            return std::vector<Tree *>();
        }

        template <typename U, typename... Args_>
        std::vector<Tree *> unwrap_others(U &u, Args_ &...others)
        {
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

        Tree *origin;

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
            case ParentType::Member:
            {
                return origin->get_expression() + "." + token;
            }
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
            case ParentType::Constructor:
            {
                std::string expression = glsl_type + "(";
                for (int i = 0; i < parents.size(); i++)
                {
                    expression += parents[i]->get_expression();
                    if (i != parents.size() - 1)
                        expression += ", ";
                }
                expression += ")";
                return expression;
            }
            default:
                return "";
            }
        }
    };

    class Variable
    {
    public:
        Tree *tree;

        void set_origin(Tree *origin) {
            this->tree->origin = origin;
            this->tree->parent_type = ParentType::Member;
        }

        std::string get_symbol() {
            return this->tree->get_expression();
        }
        
        static std::string type_name();
    };

    static std::vector<std::string> recorder;
    static void record(Tree *tree)
    {
        switch (tree->parent_type)
        {
        case ParentType::AssignOperator:
            recorder.push_back("\t" + tree->get_expression() + " = " + tree->parents[0]->get_expression() + ";\n");
            break;
        case ParentType::Declaration:
            recorder.push_back("\t" + tree->glsl_type + " " + tree->token + 
                (tree->parents.size() ? " = " + tree->parents[0]->get_expression() : "") + ";\n");
            break;
        default:
            break;
        }
    }

    static int arg_index = 0;
    static std::string argument_declaration = "";

    template <typename T, typename A>
    static T execute(std::function<T(A&)> func, A &arg)
    {
        argument_declaration += A::type_name() + " " + arg.tree->token;
        return func(arg);
    }

    template <typename T, typename A1, typename A2, typename... Args>
    static T execute(std::function<T(A1 &, A2 &, Args &...)> func, A1 &a1)
    {
        argument_declaration += A1::type_name() + " " + a1.tree->token + ", ";

        std::function<T(A2 &, Args & ...)> bound = [&](A2 &a2, Args &...others) -> T
        {
            return func(a1, a2, others...);
        };

        A2 a2("a" + std::to_string(arg_index++));
        return execute(bound, a2);
    }

    template <typename T, typename A, typename... Args>
    static Function<T, A, Args...> Parse(std::function<T(A &, Args &...)> func, std::string func_name)
    {
        recorder.clear();
        arg_index = 0;
        argument_declaration = "";

        A a("a" + std::to_string(arg_index++));
        T t = execute<T, A, Args...>(func, a);

        Function<T, A, Args...> function(func_name);

        std::string header = t.tree->glsl_type + " " + func_name + "(" + argument_declaration + ")";
        std::string footer = "}\n";

        function.definition = header + " {\n";
        for (std::string line : recorder)
            function.definition += line;
        function.definition += "\treturn " + t.tree->get_expression() + ";\n";
        function.definition += footer;

        function.declaration = header + ";\n";

        return function;
    }
} // namespace GLSL

#endif
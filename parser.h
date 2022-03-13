#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <functional>
#include <map>

enum class ParentType
{
    None = 0,
    Argument = 1,
    Function = 2,
    UnaryOperator = 3,
    BinaryOperator = 4,
    Declaration = 5
};

class Tree;
class Variable;
class Context;
class Parser;

class Variable
{
public:
    Tree *tree;
};

class Tree
{
public:
    std::vector<Tree *> parents;
    std::vector<Tree *> children;
    std::string symbol;
    std::string glsl_type;
    ParentType parent_type;

    int depth = 0;
    bool visited = false;

    Tree(std::string symbol, std::string glsl_type, ParentType parent_type = ParentType::None)
        : symbol(symbol)
        , glsl_type(glsl_type)
        , parent_type(parent_type)
    {
    }

    void update_depth(int parent_depth)
    {
        if (parent_type == ParentType::Declaration)
            depth += parent_depth;
        
        for (Tree *child: this->children)
            child->update_depth(this->depth + 1);
    }

    std::string get_expression(std::map<int, std::string> &decls)
    {
        switch (parent_type)
        {
        case ParentType::None:
            return symbol;
        case ParentType::Argument:
            return symbol;
        case ParentType::Function:
        {
            std::string expression = symbol + "(";
            for (int i = 0; i < parents.size(); i++)
            {
                expression += parents[i]->get_expression(decls);
                if (i != parents.size() - 1)
                    expression += ", ";
            }
            expression += ")";
            return expression;
        }
        case ParentType::UnaryOperator:
        {
            std::string expression = "(" + symbol + parents[0]->get_expression(decls) + ")";
            return expression;
        }
        case ParentType::BinaryOperator:
        {
            std::string expression = "(" + parents[0]->get_expression(decls) + " " + symbol + " " + parents[1]->get_expression(decls) + ")";
            return expression;
        }
        case ParentType::Declaration:
        {
            if (!visited) {
                std::string expression = "\t" + glsl_type + " " + symbol + " = " + parents[0]->get_expression(decls) + ";\n";
                decls[depth] += expression;
                visited = true;
            }

            return symbol;
        }
        default:
            return "";
        }
    }
};

class Context
{
    std::vector<int> stack;

    bool record(Tree *tree) {
        
    }
};

class Parser
{
public:
    template <typename T, typename A1, typename A2>
    static std::string Parse(std::function<T&(A1 &, A2 &)> func, std::string func_name)
    {
        A1 a1("a1");
        A2 a2("a2");

        T& t = func(a1, a2);
        Tree *tree = t.tree;

        a1.tree->update_depth(1);
        a2.tree->update_depth(1);

        std::map<int, std::string> decls_map;
        std::string ret_exp = "\treturn " + tree->get_expression(decls_map) + ";\n";
        std::string decls = "";
        for (auto &decl : decls_map)
            decls += decl.second;

        std::string header = tree->glsl_type + " " + func_name + 
                        "(" + a1.tree->glsl_type + " a1, " + a2.tree->glsl_type + " a2) " + "{\n";
        std::string footer = "}\n";
        std::string result = header + decls + ret_exp + footer;

        return result;
    }
};

#endif
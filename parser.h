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
    enum class ScopeType
    {
        None = 0,
        Block = 1,
        IF = 2,
        ELIF = 3,
        ELSE = 4,
        WHILE = 5, // TODO: Add support for do-while loops
        FOR = 6,   // TODO: Add support for for loops
    };
    struct Record
    {
        int scope;
        ScopeType scope_type;
    };

    std::vector<std::vector<std::pair<Record, std::string>>> recorder;
    std::vector<int> branches;

    int current_scope = 0;
    int current_execution_branch = 0;

    Context()
    {
        recorder.push_back(std::vector<std::pair<Record, std::string>>());
    }

    void record(Tree *lhs, Tree *rhs)
    {
        switch (lhs->parent_type)
        {
        case ParentType::AssignOperator:
            recorder[current_execution_branch]
                .push_back({{current_scope, ScopeType::None}, lhs->get_expression() + " = " + rhs->get_expression() + ";\n"});
            break;
        case ParentType::Declaration:
            recorder[current_execution_branch]
                .push_back({{current_scope, ScopeType::None}, lhs->glsl_type + " " + lhs->token + " = " + rhs->get_expression() + ";\n"});
            break;
        default:
            break;
        }
    }

    bool on_execution_end()
    {
        if (branches.size() == 0)
            return false;

        recorder.push_back(std::vector<std::pair<Record, std::string>>());

        current_scope = 0;
        current_execution_branch++;

        branches.pop_back();
        return true;
    }

    bool enter_if(Tree *tree)
    {
        std::string expression = tree->get_expression();

        if (current_execution_branch == 0)
        {
            recorder[current_execution_branch]
                .push_back({{current_scope, ScopeType::IF}, "if (" + expression + ") {\n"});
            current_scope++;

            branches.push_back(true);
            return true;
        }
        else
        {
            if (branches.size() <= current_scope) {
                recorder[current_execution_branch]
                    .push_back({{current_scope, ScopeType::ELSE}, "else {\n"});
                current_scope++;

                return false;
            }
            else {
                recorder[current_execution_branch]
                    .push_back({{current_scope, ScopeType::IF}, "if (" + expression + ") {\n"});
                current_scope++;

                return true;
            }
        }
    }
};

class Parser
{
public:
    template <typename T, typename A1, typename A2>
    static std::string Parse(std::function<T(A1 &, A2 &)> func, std::string func_name)
    {
        Context *context = new Context();

        A1 sample_a1("a1", context);
        A2 sample_a2("a2", context);
        Tree *last_tree;

        do
        {
            A1 a1("a1", context);
            A2 a2("a2", context);

            T t = func(a1, a2);
            last_tree = t.tree;
            context->recorder[context->current_execution_branch]
                .push_back({{context->current_scope, Context::ScopeType::None}, "return " + last_tree->get_expression() + ";\n"});
        } while (context->on_execution_end());

        std::string header = last_tree->glsl_type + " " + func_name +
                             "(" + sample_a1.get_declaration() + ", " + sample_a2.get_declaration() + ") {\n";
        std::string footer = "}\n";

        std::string sample = "";
        for (int i = 0; i < context->recorder.size(); i++)
        {
            sample += "Candidate " + std::to_string(i) + ":\n";
            sample += header;
            for (auto &record : context->recorder[i])
                sample += std::string((record.first.scope + 1) * 4, ' ') + record.second;
            sample += footer;

            sample += "\n";
        }

        // std::string result = header;
        // for (std::string line : context->recorder)
        //     result += line;
        // result += result_exp;
        // result += footer;

        return sample;
    }
};

#endif
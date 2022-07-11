#ifndef _CODEGEN_BUILDER_H_
#define _CODEGEN_BUILDER_H_

#include <string>
#include <vector>
#include <map>
#include <variant>

struct Builder;
struct Expression;
struct Statement;
struct Type;
struct Function;
struct Operator;

using Declaration = std::variant<Type, Function>;

struct Builder
{
    std::vector<Declaration> expressions;

    Builder(std::initializer_list<Declaration> expressions);
    std::string build();
};

struct Operator
{
    std::string symbol;

    Operator(std::string symbol);
    std::string toString(size_t indent) const;
};

struct Type
{
    std::string name;
    std::map<std::string, Type> fields;

    Type() = default;
    Type(std::string name, std::vector<std::pair<std::string, Type>> fields)
        : name(name)
    {
        for (auto &field : fields)
            this->fields[field.first] = field.second;
    }

    std::string toString(size_t indent) const;
};

struct Expression
{
    struct Literal;
    struct Variable;
    struct FunctionCall;
    struct Binary;
    struct Unary;
    struct Cast;

    struct Literal
    {
        std::string value;
        Literal(std::string value) : value(value) {}

        std::string toString(size_t indent) const;
    };

    struct Variable
    {
        std::string name;

        std::string toString(size_t indent) const;
    };

    struct FunctionCall
    {
        std::string name;
        std::vector<Expression> arguments;

        std::string toString(size_t indent) const;
    };

    struct Binary
    {
        Operator operator_;
        Expression &left;
        Expression &right;

        std::string toString(size_t indent) const;
    };

    struct Unary
    {
        Operator operator_;
        Expression &operand;

        std::string toString(size_t indent) const;
    };

    struct Cast
    {
        ::Type type;
        Expression &operand;

        std::string toString(size_t indent) const;
    };

    using Type = std::variant<Literal, Variable, FunctionCall, Binary, Unary, Cast>;
    Type value;

    Expression(Expression::Type value) : value(value) {}
    std::string toString(size_t indent) const;
};

struct Statement
{
    struct Return;
    struct If;
    struct While;
    struct For;
    struct Block;
    struct Declaration;
    struct Assignment;
    struct VoidCall;

    struct Return
    {
        Expression expr;
        Return(Expression::Type expr) : expr(expr) {}

        std::string toString(size_t indent) const;
    };

    struct If
    {
        Expression condition;
        std::vector<Statement> true_statements;
        std::vector<Statement> false_statements;

        If(Expression::Type condition, std::vector<Statement> then, std::vector<Statement> else_)
            : condition(condition)
        {
            for (auto &statement : then)
                this->true_statements.push_back(statement);
            for (auto &statement : else_)
                this->false_statements.push_back(statement);
        }

        std::string toString(size_t indent) const;
    };

    struct While
    {
        Expression condition;
        std::vector<Statement> statements;

        std::string toString(size_t indent) const;
    };

    struct For
    {
        Expression init;
        Expression condition;
        Expression step;
        std::vector<Statement> statements;

        std::string toString(size_t indent) const;
    };

    struct Block
    {
        std::vector<Statement> statements;

        std::string toString(size_t indent) const;
    };

    struct Declaration
    {
        Type type;
        std::string name;

        std::string toString(size_t indent) const;
    };

    struct Assignment
    {
        std::string name;
        Expression expr;

        std::string toString(size_t indent) const;
    };

    struct VoidCall
    {
        std::string name;
        std::vector<Expression> arguments;

        std::string toString(size_t indent) const;
    };

    using Type = std::variant<Return, If, While, For, Block, Declaration, Assignment, VoidCall>;
    Type data;

    Statement(Return data) : data(data) {}
    Statement(If data) : data(data) {}
    Statement(While data) : data(data) {}
    Statement(For data) : data(data) {}
    Statement(Block data) : data(data) {}
    Statement(Declaration data) : data(data) {}
    Statement(Assignment data) : data(data) {}
    Statement(VoidCall data) : data(data) {}
    std::string toString(size_t indent) const;
};

struct Function
{
    std::string name;
    std::map<std::string, Type> parameters;
    Type returnType;

    std::vector<Statement> statement;

    Function(Type returnType, std::string name, std::vector<std::pair<std::string, Type>> parameters, std::vector<Statement> statement)
        : returnType(returnType), name(name)
    {
        for (auto &parameter : parameters)
            this->parameters[parameter.first] = parameter.second;
        for (auto &statement : statement)
            this->statement.push_back(statement);
    }
    std::string toString(size_t indent) const;
};

#endif
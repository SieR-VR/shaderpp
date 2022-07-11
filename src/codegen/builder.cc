#include "codegen/builder.h"

Builder::Builder(std::initializer_list<Declaration> expressions)
    : expressions(expressions)
{
}

std::string Builder::build()
{
    std::string result;
    for (auto &expression : expressions)
    {
        std::visit(
            [&result](auto &&arg)
            {
                result += arg.toString(0);
            },
            expression);
    }
    return result;
}

std::string Operator::toString(size_t indent) const
{
    std::string result = symbol;
    return result;
}

std::string Type::toString(size_t indent) const
{
    std::string result = "struct " + name + " {\n";
    for (auto &field : fields)
    {
        result += std::string(indent + 2, ' ') + field.first + ";\n";
    }
    result += "};\n";

    return result;
}

std::string Expression::Literal::toString(size_t indent) const
{
    std::string result = value;
    return result;
}

std::string Expression::Variable::toString(size_t indent) const
{
    std::string result = name;
    return result;
}

std::string Expression::FunctionCall::toString(size_t indent) const
{
    std::string result = name + "(";
    for (size_t i = 0; i < arguments.size(); i++)
    {
        result += arguments[i].toString(0);
        if (i < arguments.size() - 1)
            result += ", ";
    }
    result += ")";
    return result;
}

std::string Expression::Binary::toString(size_t indent) const
{
    std::string result = "(" + left.toString(0) + " " + operator_.toString(0) + " " + right.toString(0) + ")";
    return result;
}

std::string Expression::Unary::toString(size_t indent) const
{
    std::string result = "(" + operator_.toString(0) + operand.toString(0) + ")";
    return result;
}

std::string Expression::Cast::toString(size_t indent) const
{
    std::string result = "(" + type.name + ")" + operand.toString(0);
    return result;
}

std::string Statement::Return::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + "return " + expr.toString(0) + ";\n";
    return result;
}

std::string Statement::If::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + "if (" + condition.toString(0) + ") {\n";
    for (auto &statement : true_statements)
    {
        result += statement.toString(indent + 2);
    }
    result += std::string(indent + 1, ' ') + "} else {\n";
    for (auto &statement : false_statements)
    {
        result += statement.toString(indent + 2);
    }
    result += std::string(indent, ' ') + "}\n";
    return result;
}

std::string Statement::While::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + "while (" + condition.toString(0) + ") {\n";
    for (auto &statement : statements)
    {
        result += statement.toString(indent + 2);
    }
    result += std::string(indent, ' ') + "}\n";
    return result;
}

std::string Statement::For::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + "for (" + init.toString(0) + "; " + condition.toString(0) + "; " + step.toString(0) + ") {\n";
    for (auto &statement : statements)
    {
        result += statement.toString(indent + 2);
    }
    result += std::string(indent, ' ') + "}\n";
    return result;
}

std::string Statement::Block::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + "{\n";
    for (auto &statement : statements)
    {
        result += statement.toString(indent + 2);
    }
    result += std::string(indent, ' ') + "}\n";
    return result;
}

std::string Statement::Declaration::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + type.toString(indent) + " " + name + ";\n";
    return result;
}

std::string Statement::Assignment::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + name + " = " + expr.toString(0) + ";\n";
    return result;
}

std::string Statement::VoidCall::toString(size_t indent) const
{
    std::string result = std::string(indent, ' ') + name + "(";
    for (size_t i = 0; i < arguments.size(); i++)
    {
        result += arguments[i].toString(0);
        if (i < arguments.size() - 1)
            result += ", ";
    }
    result += ");\n";
    return result;
}

std::string Expression::toString(size_t indent) const
{
    std::string result;
    std::visit(
        [&result, indent](auto &&arg)
        {
            result += arg.toString(indent);
        },
        this->value);

    return result;
}

std::string Function::toString(size_t indent) const
{
    std::string result = returnType.name + " " + name + "(";
    for (auto &parameter : parameters)
        result += parameter.second.name + " " + parameter.first + ", ";
    result.pop_back();
    result.pop_back();

    result += ") {\n";
    for (auto &statement : statement)
        result += statement.toString(indent + 2);
    result += "}\n";

    return result;
}

std::string Statement::toString(size_t indent) const
{
    std::string result;
    std::visit(
        [&result, indent](auto &&arg)
        {
            result += arg.toString(indent);
        },
        this->data);
    return result;
}

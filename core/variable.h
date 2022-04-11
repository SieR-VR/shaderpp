#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include <vector>

#include "parser.h"

namespace GLSL
{
    /**
     * @brief Default variable class for shaderpp, it can be used as a base class for other variable types.
     */
    class Variable
    {
    public:
        std::string expression;
        std::string glsl_type;

        std::vector<Variable *> branches;
        Variable *origin = nullptr;

        Variable() = delete;

        /**
         * @brief Constructor for auto-generated variable name.
         * @param glsl_type The GLSL type of the variable
         */
        Variable(std::string glsl_type) 
            : glsl_type(glsl_type), 
              expression(Namer::name("va_", Parser::recorder.size(), glsl_type, ""))
        {
            
        }

        /**
         * @brief Constructor for user-defined variable name.
         * @param glsl_type The GLSL type of the variable
         * @param expression The expression of the variable
         */
        Variable(std::string glsl_type, std::string expression)
            : glsl_type(glsl_type), expression(expression)
        {
        }

        /**
         * @brief Constructor for user-defined variable name.
         * @param glsl_type The GLSL type of the variable
         * @param expression The expression of the variable
         * @param origin The origin pointer(usually this of parent) of the variable
         */
        Variable(std::string glsl_type, std::string token, Variable *origin)
            : glsl_type(glsl_type), expression(token), origin(origin)
        {
            if (origin)
                origin->branches.push_back(this);
        }

        /**
         * @brief static function to generate binary operator expression.
         * @param token The operator token
         * @param left The left operand
         * @param right The right operand 
         * @return The expression of the binary operator
         */
        static std::string bin_exp(std::string token, Variable *left, Variable *right)
        {
            return "(" + left->get_expression() + " " + token + " " + right->get_expression() + ")";
        }

        /**
         * @brief static function to generate unary operator expression.
         * @param token The operator token
         * @param right The operand
         * @return The expression of the unary operator
         */
        static std::string un_exp(std::string token, Variable *right)
        {
            return "(" + token + right->get_expression() + ")";
        }

        /**
         * @brief get the declaration of the variable.
         * @return The declaration of the variable.
         */
        std::string get_declaration() const
        {
            return glsl_type + " " + expression;
        }

        /**
         * @brief get the expression of the variable.
         * @return The expression of the variable.
         */
        std::string get_expression() const
        {
            if (origin)
                return origin->get_expression() + "." + expression;
            else
                return expression;
        }
    };
}

#endif
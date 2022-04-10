#ifndef FUNCTION_H_
#define FUNCTION_H_

namespace GLSL
{
    template <typename T, typename... Args>
    class Function
    {
    public:
        std::string declaration;
        std::string definition;
        std::string symbol;

        Function(std::string symbol) : symbol(symbol) {}

    private:
        std::string unwrap_others(std::string &arguments)
        {
            return arguments;
        }

        template <typename U, typename... Args_>
        std::string unwrap_others(std::string &arguments, U &u, Args_ &...others)
        {
            if (arguments.empty())
                arguments += u.get_declaration();
            else
                arguments += ", " + u.get_declaration();

            return unwrap_others(arguments, others...);
        }

    public:
        T &operator()(Args &...others)
        {
            return *(new T(symbol + "(" + unwrap_others(others...) + ")"));
        }
    };
}

#endif
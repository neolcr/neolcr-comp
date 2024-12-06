#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <ostream>
#include <sstream>
#include <unordered_map>
#include <vector>

class Token {
public:
    enum class Type {
        INSTRUCCION,
        EXPRESION,
        VALOR_ENTERO,
        VALOR_STRING,
        TIPO,
        OPERADOR,
        PUNTO_COMA,
        IZ_PAR,
        DER_PAR,
        IZ_COR,
        DER_COR,
        FUNCION,
        VARIABLE,
        IGUAL

    };

private:
    Type type;
    std::vector<std::string> attributes;
    Type next;

public:
    Token(Type t, std::vector<std::string> attrs, Type n)
        : type(t)
        , attributes(std::move(attrs))
        , next(n)
    {
    }

    // Getter for `type`
    Type getType() const
    {
        return type;
    }

    // Getter for `attributes`
    const std::vector<std::string>& getAttributes() const
    {
        return attributes;
    }

    // Getter for `next`
    Type getNext() const
    {
        return next;
    }
};

std::vector<Token> tokens = {
    { Token::Type::TIPO, { "int", "float", "string" }, Token::Type::VARIABLE },
    { Token::Type::VARIABLE, {}, Token::Type::IGUAL },
    { Token::Type::IGUAL, { "=" }, Token::Type::VALOR_ENTERO },
    { Token::Type::VALOR_ENTERO, {}, Token::Type::PUNTO_COMA },
    { Token::Type::PUNTO_COMA, { ";" }, {} }
};

bool exist(std::string& value)
{
    std::vector<Token> filtered;
    std::copy_if(tokens.begin(), tokens.end(), std::back_inserter(filtered),
        [&value](const Token& token) {
            const auto& attrs = token.getAttributes();
            return std::find(attrs.begin(), attrs.end(), value) != attrs.end();
        });
    return !filtered.empty();
}

class Tokenizer {
public:
    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens;
        std::string buffer;

        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buffer.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buffer.push_back(consume());
                }

                if (exist(buffer)) {

                } else {
                    std::cerr << "Error lexico con " << std::endl;
                    exit(EXIT_FAILURE);
                }

            } else if (std::isdigit(peek().value())) {
            }
        }

        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] inline std::optional<char> peek(int offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        } else {
            return m_src.at(m_index + offset);
        }
    }

    inline char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    int m_index = 0;
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Es necesario enviar segundo parametro con fichero a leer" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Numero de parametros recibido: " << argc << std::endl;
    std::cout << "Primer parametro: " << argv[0] << std::endl;
    std::cout << "Segundo parametro: " << argv[1] << std::endl;

    std::string content;
    {
        std::stringstream content_stream;
        std::fstream input(argv[1], std::ios::in);
        content_stream << input.rdbuf();
        content = content_stream.str();
        std::cout << "Contenido: " << content << std::endl;
    }

    std::string value = "flodat";

    std::cout << exist(value) << std::endl;

    return 0;
}

#ifndef REGEX_BUILDER_H_
#define REGEX_BUILDER_H_

#include <regex>
#include <string>

class RegexBuilder {
public:
    std::string pattern_;

    RegexBuilder() : pattern_("") {}
    RegexBuilder(const std::string& pattern) : pattern_(pattern) {}

    std::regex build() const {
        return std::regex(pattern_);
    }

    RegexBuilder &between(char c1, char c2) {
        pattern_ += "[" + std::string(1, c1) + "-" + std::string(1, c2) + "]";
        return *this;
    }

    RegexBuilder &between(std::vector<std::pair<char, char>> ranges) {
        pattern_ += "[";
        for (auto range : ranges) {
            pattern_ += range.first;
            pattern_ += "-";
            pattern_ += range.second;
        }
        pattern_ += "]";
        return *this;
    }

    RegexBuilder &many(std::vector<RegexBuilder> regexes) {
        pattern_ += "(";
        for (auto regex : regexes) {
            pattern_ += regex.pattern_;
            pattern_ += "|";
        }
        pattern_ = pattern_.substr(0, pattern_.size() - 1);
        pattern_ += ")";
        return *this;
    }

    RegexBuilder &count(int n) {
        pattern_ += "{" + std::to_string(n) + "}";
        return *this;
    }

    RegexBuilder &any() {
        pattern_ += ".";
        return *this;
    }

    RegexBuilder &any(int n) {
        pattern_ += std::string(n, '.');
        return *this;
    }

    RegexBuilder &string(const std::string &str) {
        pattern_ += str;
        return *this;
    }

    RegexBuilder &line_break() {
        pattern_ += "(?:\\r\\n|\\r|\\n)";
        return *this;
    }

    RegexBuilder &space() {
        pattern_ += " ";
        return *this;
    }

    RegexBuilder &append(RegexBuilder& builder) {
        pattern_ += builder.pattern_;
        return *this;
    }
};

#endif
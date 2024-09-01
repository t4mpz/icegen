#pragma once
#include <vector>
#include <string>

namespace Iceberg{
    class ItemNotFound : public std::exception {
        private:
            std::string message;
        public:
            ItemNotFound(std::string message) : message(message) {};

            std::string what();
    };

    class DuplicatedItemError : public std::exception{
        private:
            std::string message;
        public:
            DuplicatedItemError(std::string message) : message(message) {};

            std::string what();
    };

    class Layer{
        private:
            std::vector<std::string> content;
            std::string name;
        public:

            Layer(std::vector<std::string> contents, std::string name);

            Layer(std::string* contents, std::string name);

            Layer();

            std::vector<std::string> getContent();

            std::string getName();

            void append(std::string item);

            void remove(std::string item);

            void update(std::string o_item, std::string value);

            bool has(std::string item);

            void setName(std::string name);

            void setContent(std::vector<std::string> cotnent);
    };
}

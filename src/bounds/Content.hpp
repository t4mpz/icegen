#pragma once
#include "PixelArea.hpp"
#include <vector>
#include <string>
#define UNDEFINEDCONTENT "\0"
#define PIXELSPCHAR 5
#define FONTSIZE 12

namespace Bounds{
        class Content{
        private:
            std::string content;
            int x_start;
            int y_start;
            int x_end;
            int y_end;
            PixelArea pixel_area;
            int fontSize;
            int pixelsPChar;

            void calcSize(const int &fontSize, const int &charWidth);
            void calcSize();
        
        public:

            class InvalidCoordinates : std::exception{
                private:
                    std::string msg;
                public:
                    InvalidCoordinates(std::string message) : msg(message){};

                    std::string what();
            };

            Content(const std::string &content, const int &x, const int &y, const int &fontsize, const int &pixelPChar);

            Content(const std::string &content, const int &x, const int &y);

            Content(const int &x, const int &y, const int &fontsize, const int &pixelsPChar);

            Content(const std::string &content, const PixelArea &pa, const int &fontsize = FONTSIZE, const int &pixelsPChar = PIXELSPCHAR);

            Content();

            // Content(const std::string &content, const int &fontsize , const int &pixelsPChar);

            Content(const Content &content);
            Content(Content &content);

            void setX(const int &x);
            void setY(const int &y);
            void setContent(const std::string &value);
            void setFontSize(const int &fontSize = FONTSIZE);
            void setPixelsPCharacter(const int &pixelsPChar = PIXELSPCHAR);

            int getContentArea();
            PixelArea getPixelArea() const;
            int getStartY() const;
            int getStartX() const;
            int getFinalX() const;
            int getFinalY() const;
            std::vector<int> getStartCoords();
            std::vector<int> getFinalCoords();
            std::string getContent() const;
            int getFontSize() const;
            int getPixelsPCharacter() const;

            bool equal(Content content);
            bool operator==(const Content &content);
            bool operator!=(const Content &content);

    };
}
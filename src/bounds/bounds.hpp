#pragma once
#include <vector>
#include <string>
#include <exception>
#include "../iceberg/iceberg.hpp"

#define CONTENTSPACING 2
#define UNDEFINEDCONTENT "\0"
#define PIXELSPCHAR 5
#define FONTSIZE 12
#define AUTOFIND_SPACING 10

namespace Bounds{

    class PixelArea{
        private:
            int x_start;
            int y_start;
            int x_end;
            int y_end;
            int total_area;


        public:

            PixelArea(const int &x_start, const int &y_start, const int &x_stop, const int &y_stop);

            PixelArea();

            int getArea();

            int getDY();
            int getDX();

            bool isContainedIn(PixelArea area, int spacing);
            bool contains(PixelArea area, int spacing);
            bool contains(const int &x, const int &y, int spacing);

            void setXStart(const int &x);
            void setYStart(const int &y);
            void setXFinal(const int &x);
            void setYFinal(const int &y);

            void setX(const int &start, const int &end);
            void setY(const int &start, const int &end);

            int getXStart();
            int getXFinal();
            int getYStart();
            int getYFinal();

            bool equal(PixelArea pa);

            std::string to_string();
    };

    class Content{
        private:
            std::string content;
            int x_start;
            int y_start;
            int x_end;
            int y_end;
            PixelArea pixel_area;

            void calcSize(const int &fontSize, const int &charWidth);
        
        public:

            class InvalidCoordinates : std::exception{
                private:
                    std::string msg;
                public:
                    InvalidCoordinates(std::string message) : msg(message){};

                    std::string what();
            };

            Content(const std::string &content, const int &x, const int &y);

            Content(const int &x, const int &y);

            Content(const std::string &content, PixelArea pa);

            Content();

            void setX(const int &x);
            void setY(const int &y);

            void setContent(const std::string &value);

            int getContentArea();
            PixelArea getPixelArea();

            int getStartX();
            int getStartY();
            int getFinalX();
            int getFinalY();
            std::vector<int> getStartCoords();
            std::vector<int> getFinalCoords();

            std::string getContent();

            bool equal(Content content);

    };

    class ViewPort{
        private:
            std::vector<Content> vp;
            int spacing;
            int x_limit;
            int y_limit;
            int x_start;
            int y_start;
            int space_boards;
            int total_area;
            PixelArea vp_area;

            void checkBounds(const int &x, const int &y);
        
        public:

            class BoundLimitsException : std::exception{
                private:
                    std::string msg;
                public:
                    BoundLimitsException(std::string message) : msg(message) {}

                    std::string what();
            };

            class EmptyPointException : std::exception{
                private:
                    std::string msg;
                
                public:
                    EmptyPointException(std::string message) : msg(message){}
                    std::string what();
            };

            class PointValuesConflict : std::exception{
                private:
                    std::string msg;
                public:
                    PointValuesConflict(std::string message) : msg(message){}
                    std::string what();
            };

            class SegmentError : std::exception{
                private: 
                    std::string msg;
                public:
                    SegmentError(std::string message) : msg(message){}
                    std::string what();
            };

            ViewPort(const std::vector<Content> &vp, 
                    const int &spacing, const int &x_limit, const int &y_limit, const int &x_start, const int &y_start, const int &space_boards = 0);

            ViewPort();

            ViewPort(const int &spacing, const int &x_limit, const int &y_limit, const int &x_start, const int &y_start, const int &space_boards = 0);

            ViewPort(const std::vector<Content> &vp, const PixelArea &pa, const int &spacing, const int &space_boards = 0);

            std::vector<PixelArea> getSegmentsInX(const int &slices);

            std::vector<PixelArea> getSegmentsInY(const int &slices);

            // void iterSegments(const int &height, const int &width);

            PixelArea findSegmentToFit(Content c);

            std::vector<Content> getContentFrom(PixelArea segment);

            Content at(const int &x, const int &y);
            Content at(PixelArea area);

            bool hasSpaceAt(const int &x, const int &y, const bool considerSpacing = true);
            static bool areConflictingSpace(Content a, Content b, const int &spacing = 0);
            bool isInbounds(const int &x, const int &y);
            bool isInbounds(Content content);
            bool hasSpaceFor(Content content);

            int getAreaUsed();
            int getAreaFree();

            std::vector<Content> listConflicting(Content content);
            PixelArea getPixelArea();
            void setPixelArea(const PixelArea &pa);

            std::vector<Content> getContent();

            void append(Content Content);
            void append(const std::string &rawValue);

            void remove(Content Content);
            void remove(const std::string &rawValue);

            void update(Content content, std::string value);
            void update(Content old_content, Content new_content);
    };

    class LayerBounds{

        private:
            Iceberg::Layer layer;
            int width;
            int height;
            ViewPort viewport;

            void generateViewPort();
        
        public:

            class OutOfBoundsException : std::exception{
                private:
                    std::string msg;
                
                public:
                    OutOfBoundsException(std::string message) : msg(message){};

                    std::string what();
            };

            class InvalidLimitException : std::exception{
                private:
                    std::string msg;
                
                public:
                    InvalidLimitException(std::string message) : msg(message){};

                    std::string what();
            };

            class ContentTooBigException : std::exception{
                private:
                    std::string msg;
                
                public:
                    ContentTooBigException(std::string message) : msg(message){};

                    std::string what();
            };

            LayerBounds(const Iceberg::Layer &l, const int &width, const int &height);

            LayerBounds(std::vector<std::string> contents, std::string name, const int &width, const int &height);

            Iceberg::Layer getLayer();

            int getHeight();

            int getWidth();

            void sortContents(const int &spacing = CONTENTSPACING);

            ViewPort getViewPort();
    };
}
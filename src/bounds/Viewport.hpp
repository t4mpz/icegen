#pragma once
#include "PixelArea.hpp"
#include "Content.hpp"
#include <vector>
#include <string>

namespace Bounds{
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

            ViewPort(const PixelArea &pa, const int &spacing, const int &space_boards);

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
            PixelArea getPixelArea() const;
            void setPixelArea(const PixelArea &pa);

            std::vector<Content> getContent() const;

            void append(Content Content);
            void append(const std::string &rawValue);

            void remove(Content Content);
            void remove(const std::string &rawValue);

            void update(Content content, std::string value);
            void update(Content old_content, Content new_content);

            bool equals(ViewPort vp);
            bool operator==(const ViewPort &vp);
            bool operator!=(const ViewPort &vp);
    };
}
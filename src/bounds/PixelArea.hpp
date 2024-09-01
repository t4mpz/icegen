#pragma once
#include <string>

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

            PixelArea(const PixelArea &pa);

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

            int getXStart() const;
            int getXFinal() const;
            int getYStart() const;
            int getYFinal() const;

            bool equal(PixelArea pa);

            std::string to_string();

            bool operator==(const PixelArea &pa);

            bool operator!=(const PixelArea &pa);
    };
}
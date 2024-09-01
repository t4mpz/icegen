#include "PixelArea.hpp"
#include <string>
using namespace Bounds;


int PixelArea::getDX(){ return (this->x_end - this->x_start); }
int PixelArea::getDY(){ return (this->y_end - this->y_start); }

void PixelArea::setX(const int &start, const int &end){
    this->x_start = start;
    this->x_end   = end;
    this->total_area = this->getDX() * this->getDY();
    return;
}
int PixelArea::getXStart() const{ return this->x_start; }

int PixelArea::getXFinal() const{ return this->x_end; }

int PixelArea::getYStart() const{ return this->y_start; }

int PixelArea::getYFinal() const{return this->y_end;}

void PixelArea::setXStart(const int &start){
    this->x_start = start;
    this->total_area = this->getDX() * this->getDY();
}

void PixelArea::setXFinal(const int &end){
    this->x_end = end;
    this->total_area = this->getDX() * this->getDY();
}

void PixelArea::setYStart(const int &start){
    this->y_start = start;
    this->total_area = this->getDX() * this->getDY();
}

void PixelArea::setYFinal(const int &end){
    this->y_end = end;
    this->total_area = this->getDX() * this->getDY();
}


void PixelArea::setY(const int &start, const int &end){
    this->y_start = start;
    this->y_end   = end;
    this->total_area = this->getDX() * this->getDY();
    return;
};

bool PixelArea::equal(PixelArea pa){
    return ((this->x_start == pa.getXStart()) && (this->y_start == pa.getYStart())) && 
            ((this->x_end == pa.getXFinal()) && (this->y_end == pa.getYFinal())) && this->total_area == pa.getArea();
}

bool PixelArea::contains(PixelArea area, int spacing){
    return (
    ((
        ((area.getXStart() + spacing) >= this->getXStart()) && ((area.getYStart() + spacing) >= this->getYStart())) || 
        ((area.getXFinal() + spacing) >= this->getXStart()) && ((area.getYFinal() + spacing) >= this->getYStart())
    ) && (
        (((area.getXFinal() + spacing) <= this->getXFinal()) && ((area.getYFinal() + spacing) <= this->getYFinal())) ||
        (((area.getXStart() + spacing) <= this->getXFinal()) && ((area.getYStart() + spacing) <= this->getYFinal()))
    ));
}

bool PixelArea::contains(const int &x, const int &y, int spacing){
    return (
        ((x + spacing) >= this->getXStart() || (y + spacing) >= this->getYStart()) &&
        ((x + spacing) <= this->getXFinal() || (y + spacing) <= this->getYFinal())
    );
}

bool PixelArea::isContainedIn(PixelArea area, int spacing){
    return (
    (   
        (((this->getXStart() + spacing) >= area.getXStart()) && ((this->getYStart() + spacing) >= area.getYStart())) || 
        ((this->getXFinal() + spacing) >= area.getXStart()) && ((this->getYFinal() + spacing) >= area.getYStart())
    ) && (
        (((this->getXFinal() + spacing) <= area.getXFinal()) && ((this->getYFinal() + spacing) <= area.getYFinal())) ||
        (((this->getXStart() + spacing) <= area.getXFinal()) && ((this->getYStart() + spacing) <= area.getYFinal()))
    ));
}

std::string PixelArea::to_string(){
    return "(" + std::to_string(this->x_start) + "x" + std::to_string(this->y_start) + 
            ")X(" + std::to_string(this->x_end) + "x" + std::to_string(this->y_end) + "): " 
            + std::to_string(this->total_area); 
};

PixelArea::PixelArea(){};

PixelArea::PixelArea(const int &x_start, const int &y_start, const int &x_end, const int &y_end){
    this->x_start = x_start;
    this->y_start = y_start;
    this->x_end   = x_end;
    this->y_end   = y_end;  
    this->total_area = this->getDX() * this->getDY();

}

PixelArea::PixelArea(const PixelArea &pa){
    this->x_start = pa.getXStart();
    this->y_start = pa.getYStart();
    this->x_end   = pa.getXFinal();
    this->y_end   = pa.getYFinal();
    this->total_area = this->getDX() * this->getDY();
}

int PixelArea::getArea(){ return this->total_area; }

bool PixelArea::operator==(const PixelArea &pa){ return this->equal(pa); }
bool PixelArea::operator!=(const PixelArea &pa){ return !this->equal(pa); }
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include "bounds.hpp"
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
using namespace Bounds;

// defining exceptions usage

std::string Content::InvalidCoordinates::what(){ return this->msg; }

int PixelArea::getDX(){ return (this->x_end - this->x_start); }
int PixelArea::getDY(){ return (this->y_end - this->y_start); }

void PixelArea::setX(const int &start, const int &end){
    this->x_start = start;
    this->x_end   = end;
    this->total_area = this->getDX() * this->getDY();
    return;
}
int PixelArea::getXStart(){ return this->x_start; }

int PixelArea::getXFinal(){ return this->x_end; }

int PixelArea::getYStart(){ return this->y_start; }

int PixelArea::getYFinal(){return this->y_end;}

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

int PixelArea::getArea(){ return this->total_area; }
// defining classes actions

void Content::setContent(const std::string &content){ this->content = content;}


void Content::calcSize(const int &fontSize, const int &charWidth){
    if((this->x_start * this->y_start) >= 0){
        this->y_end = this->y_start + fontSize;
        this->x_end = this->x_start + this->content.size() * charWidth;
        this->pixel_area = * new PixelArea(this->x_start, this->y_start, this->x_end, this->y_end);
    }
}


std::string Content::getContent(){ return this->content; }


Content::Content(const std::string &content, const int &x, const int &y){
    this->content = content;
    this->x_start = x;
    this->y_start = y;
    this->calcSize(FONTSIZE, PIXELSPCHAR);
}


Content::Content(const int &x, const int &y){
    this->x_start = x;
    this->y_start = y;
    this->content = UNDEFINEDCONTENT;
    this->calcSize(FONTSIZE, PIXELSPCHAR);
}

Content::Content(){}

void Content::setX(const int &x){ 
    this->x_start = x; 
    this->calcSize(FONTSIZE, PIXELSPCHAR);
}


void Content::setY(const int &y){ 
    this->y_start = y; 
    this->calcSize(FONTSIZE, PIXELSPCHAR);
}


int Content::getStartX(){ return this->x_start; }
int Content::getFinalX(){ return this->x_end; }

int Content::getStartY(){ return this->y_start; }
int Content::getFinalY(){ return this->y_end; }

bool Content::equal(Content content){
    return this->content == content.getContent() && this->pixel_area.equal(content.getPixelArea());
}


std::vector<int> Content::getStartCoords(){ 
    const std::vector<int> coords{this->x_start, this->y_start};
    return coords; 
}

std::vector<int> Content::getFinalCoords(){
    const std::vector<int> coords{this->x_end, this->y_end};
    return coords;    
}

int Content::getContentArea(){ return this->pixel_area.getArea();}

PixelArea Content::getPixelArea(){ return this->pixel_area;}

// viewport declarations
std::string ViewPort::BoundLimitsException::what(){ return this->msg; }
std::string ViewPort::EmptyPointException::what(){ return this->msg; }
std::string ViewPort::PointValuesConflict::what(){ return this->msg; }
std::string ViewPort::SegmentError::what(){ return this->msg; }

ViewPort::ViewPort(const std::vector<Content> &vp, const int &spacing, 
                    const int &x_limit, const int &y_limit, const int &x_start, const int &y_start, const int &space_boards){
    this->vp = vp;
    this->spacing = spacing;
    this->x_limit = x_limit;
    this->y_limit = y_limit;
    this->x_start = x_start;
    this->y_start = y_start;
    this->total_area = (x_limit - x_start) * (y_limit - y_start);
    this->space_boards = space_boards;
}

ViewPort::ViewPort(const int &spacing, const int &x_limit, const int &y_limit, const int &x_start, const int &y_start, const int &space_boards){
    this->spacing = spacing;
    this->x_limit = x_limit;
    this->y_limit = y_limit;
    this->x_start = x_start;
    this->y_start = y_start;
    this->vp_area = *new PixelArea(x_start, x_limit, y_start, y_limit);
    this->total_area = (x_limit - x_start) * (y_limit - y_start);
    this->space_boards = space_boards;
    this->vp.clear();
}

ViewPort::ViewPort(const std::vector<Content> &vp, const PixelArea &pa, const int &spacing, const int &space_boards){
    this->vp = vp;
    this->vp_area = pa;
    this->total_area = this->vp_area.getArea();
    if(vp.size() > 0){ this->total_area = this->getAreaFree(); }
    this->space_boards = space_boards;
    this->spacing = spacing;
}

int ViewPort::getAreaUsed(){
    std::vector<int> areas;
    std::transform(this->vp.begin(), this->vp.end(), std::back_inserter(areas), [&](Content c){ return c.getContentArea(); });
    int sum_areas = std::accumulate(areas.begin(), areas.end(), 0);
    return sum_areas;
}

int ViewPort::getAreaFree(){ return this->total_area - this->getAreaUsed(); }

PixelArea ViewPort::getPixelArea(){ return this->vp_area;}

void ViewPort::checkBounds(const int &x, const int &y){
    if(!this->isInbounds(x, y))
        throw BoundLimitsException("ViewPorts limits broken x: " + std::to_string(x) + " y: " + std::to_string(y));
}

Content ViewPort::at(const int &x, const int &y){
    this->checkBounds(x, y);
    for(std::vector<Content>::iterator it = this->vp.begin(); it != this->vp.end();){
        if(((it->getStartX() <= x) && (x <= it->getFinalX())) || ((it->getStartY() <= y) && (y <= it->getFinalY())))
            return *it;
        ++it;
    }
    return *new Content(-1, -1);
}

Content ViewPort::at(PixelArea area){
    this->checkBounds(area.getXStart(), area.getYStart());
    this->checkBounds(area.getXFinal(), area.getYFinal());
    for(std::vector<Content>::iterator it = this->vp.begin(); it != this->vp.end(); ){
        if(area.contains(it->getPixelArea(), this->spacing)){ return *it; }
        ++it;
    }
    return *new Content();
}

bool ViewPort::hasSpaceAt(const int &x, const int &y, const bool considerSpacing){
    Content at = considerSpacing ? this->at( x + this->spacing, y + this->spacing) : this->at(x, y);
    return at.getContent() != UNDEFINEDCONTENT;
}

bool ViewPort::isInbounds(const int &x, const int &y){ return this->vp_area.contains(x, y, this->space_boards); }
bool ViewPort::isInbounds(Content content){ 
    return this->vp_area.contains(content.getPixelArea(), this->spacing);
}

bool ViewPort::areConflictingSpace(Content a, Content b, const int &spacing){
    bool conflictOnX = ((((a.getStartX() + spacing) <= b.getStartX()) && (b.getStartX() <= (a.getFinalX() + spacing))) ||
                        (((a.getStartX() - spacing) <= b.getFinalX()) && (b.getFinalX() <= (a.getFinalX() - spacing))));
    bool conflictOnY = ((((a.getStartY() + spacing) <= b.getStartY()) && (b.getStartY() <= (a.getFinalY() + spacing))) ||
                        (((a.getStartY() - spacing) <= b.getFinalY()) && (b.getFinalY() <= (a.getFinalY() - spacing))));
    return conflictOnX && conflictOnY;
}

PixelArea ViewPort::findSegmentToFit(Content content){
    int width  = content.getPixelArea().getDX(); 
    int height = content.getPixelArea().getDY();
    if(!this->isInbounds(content))
        throw SegmentError("Content must be inside the x and y limits");
    for(int i = (this->x_start + space_boards); i <= (this->x_limit - this->space_boards); i += width){
        int end_seg_x = this->x_start + (i + width) > x_limit ? x_limit : this->x_start + (i + width);
        for(int j = (this->y_start + space_boards); j <= (this->y_limit - this->space_boards); j += height){
            int end_seg_y = this->y_start + (j + height) > y_limit ? y_limit : this->y_start + (j + height);
            PixelArea pa(i, j, end_seg_x, end_seg_y);
            if(pa.getArea() < content.getContentArea()) break;  // at this point the area of the viewport will be small to the content meaning that there's no more available space
            Content inArea = this->at(pa);
            if(inArea.getContent() == UNDEFINEDCONTENT){ 
                // free area for the Content
                return pa;
             }
            if(end_seg_y == y_limit) break;
        }
        if(end_seg_x == x_limit) break;
    }
    return PixelArea(0, 0, 0, 0);
}

std::vector<Content> ViewPort::listConflicting(Content content){
    std::vector<Content> conflicting;
    for(std::vector<Content>::iterator it = this->vp.begin(); it != this->vp.end(); ++it){
        if(areConflictingSpace(*it, content, this->spacing))
            conflicting.push_back(*it);
    }
    return conflicting;
}

void ViewPort::append(Content content){
    if(!this->isInbounds(content) || !this->hasSpaceFor(content)){ return; }
    Content areaOfContent = this->at(content.getPixelArea());
    if(areaOfContent.getContent() != UNDEFINEDCONTENT){
        // there is something where the content would like to be
        PixelArea newAreaForContent = this->findSegmentToFit(content);
        if(newAreaForContent.getArea() >= 0){
            Content newContent(content.getContent(), newAreaForContent.getXStart(), newAreaForContent.getYStart());
            this->vp.push_back(newContent);
        }
    }
    else this->vp.push_back(content);
}

void ViewPort::remove(Content content){
    if(this->at(content.getPixelArea()).getContent() == UNDEFINEDCONTENT) 
        throw EmptyPointException("No points at the provided area " + content.getPixelArea().to_string() + " for " + content.getContent());
    for(std::vector<Content>::iterator it = this->vp.begin(); it != this->vp.end(); ++it){
        if(it->equal(content)){
            this->vp.erase(it);
            return; // only one content at the time
        }
    }
}

void ViewPort::update(Content old_content, Content new_content){
    this->remove(old_content);
    this->append(new_content);
}

void ViewPort::update(Content old_content, std::string new_value){
    Content new_content(new_value, old_content.getStartX(), old_content.getStartY());
    this->update(old_content, new_content);
}

void ViewPort::append(const std::string &raw_value){
    Content content_from_value(raw_value, 0, 0);
    this->append(content_from_value);
}

std::vector<Content> ViewPort::getContent(){ return this->vp; }

bool ViewPort::hasSpaceFor(Content content){ return content.getContentArea() <= this->getAreaFree(); }

ViewPort LayerBounds::getViewPort(){ return this->viewport;}
ViewPort::ViewPort(){}

LayerBounds::LayerBounds(const Iceberg::Layer &l, const int &width, const int &height){
    this->layer = l;
    this->width = width;
    this->height = height;
}


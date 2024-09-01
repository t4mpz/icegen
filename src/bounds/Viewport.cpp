#include "Viewport.hpp"
#include "Content.hpp"
#include "PixelArea.hpp"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <iostream>
#define CONTENTSPACING 2
#define UNDEFINEDCONTENT "\0"
#define PIXELSPCHAR 5
#define FONTSIZE 12
#define AUTOFIND_SPACING 10

using namespace Bounds;

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

ViewPort::ViewPort(const Bounds::PixelArea &pa, const int &spacing, const int &space_boards){
    this->vp_area = pa;
    this->spacing = spacing;
    this->space_boards = space_boards;
    this->vp = {};
    this->total_area = this->vp_area.getArea();
}

int ViewPort::getAreaUsed(){
    if (this->vp.size() == 0) return 0;
    std::vector<int> areas;
    std::transform(this->vp.begin(), this->vp.end(), std::back_inserter(areas), [&](Content c){ return c.getContentArea(); });
    int sum_areas = std::accumulate(areas.begin(), areas.end(), 0);
    return sum_areas;
}

int ViewPort::getAreaFree(){ return this->total_area - this->getAreaUsed(); }

PixelArea ViewPort::getPixelArea() const{ return this->vp_area;}

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
    return *new Content();
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
    std::cout << "Content " << content.getContentArea() << " VP " << this->getAreaFree() << std::endl;
    if(!this->isInbounds(content) || !this->hasSpaceFor(content)){ return; }
    Content areaOfContent = this->at(content.getPixelArea());
    std::cout << "Checking area for " << content.getContent() << content.getPixelArea().to_string() << std::endl;
    if(areaOfContent.getContent() != UNDEFINEDCONTENT){
        // there is something where the content would like to be
        PixelArea newAreaForContent = this->findSegmentToFit(content);
        if(newAreaForContent.getArea() >= 0){
            Content newContent(content.getContent(), newAreaForContent);
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
            return;
        }
    }
}

void ViewPort::update(Content old_content, Content new_content){
    this->remove(old_content);
    this->append(new_content);
}

void ViewPort::update(Content old_content, std::string new_value){
    Content new_content(new_value, old_content.getPixelArea(), old_content.getFontSize(), old_content.getPixelsPCharacter());
    this->update(old_content, new_content);
}

void ViewPort::append(const std::string &raw_value){
    Content content_from_value(raw_value, 0, 0);
    this->append(content_from_value);
}

std::vector<Content> ViewPort::getContent() const{ return this->vp; }

bool ViewPort::hasSpaceFor(Content content){ return content.getContentArea() <= this->getAreaFree(); }
ViewPort::ViewPort(){}

bool ViewPort::equals(ViewPort vp){
    std::pair<std::vector<Content>::iterator, std::vector<Content>::iterator> pair;
    pair = std::mismatch(this->vp.begin(), this->vp.end(), vp.getContent().begin());
    return this->vp_area == vp.getPixelArea() && (pair.first == this->vp.end());
}

bool ViewPort::operator==(const ViewPort &vp){ return this->equals(vp); }
bool ViewPort::operator!=(const ViewPort &vp){ return !this->equals(vp); }

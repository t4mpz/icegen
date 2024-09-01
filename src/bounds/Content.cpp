#include "PixelArea.hpp"
#include "Content.hpp"
#define UNDEFINEDCONTENT "\0"
#define PIXELSPCHAR 5
#define FONTSIZE 12
using namespace Bounds;

std::string Content::InvalidCoordinates::what(){ return this->msg; }

void Content::setContent(const std::string &content){ this->content = content;}


void Content::calcSize(const int &fontSize, const int &charWidth){
    if((this->x_start * this->y_start) >= 0){
        this->y_end = this->y_start + fontSize;
        this->x_end = this->x_start + this->content.size() * charWidth;
        this->pixel_area = * new PixelArea(this->x_start, this->y_start, this->x_end, this->y_end);
    }
}

void Content::calcSize(){
    if((this->x_start * this->y_start) >= 0){
        this->y_end = this->y_start + this->fontSize;
        this->x_end = this->x_start + this->content.size() * this->pixelsPChar;
        this->pixel_area = * new PixelArea(this->x_start, this->y_start, this->x_end, this->y_end);
    }
}


std::string Content::getContent() const{ return this->content; }


Content::Content(const std::string &content, const int &x, const int &y, const int &fontsize, const int &pixelsPChar){
    this->content = content;
    this->x_start = x;
    this->y_start = y;
    this->fontSize = fontSize;
    this->pixelsPChar = pixelsPChar;
    this->calcSize();
}

Content::Content(const std::string &content, const PixelArea &pa, const int &fontsize, const int &pixelspchar){
    this->content = content;
    this->x_start, this->y_start = 0, 0;
    this->pixel_area = pa;
    this->fontSize = fontSize;
    this->pixelsPChar = pixelsPChar;
    this->calcSize();
}

Content::Content(const Content &content){
    this->content = content.getContent();
    this->x_start, this->y_start = content.getStartX(), content.getStartY();
    this->pixel_area = content.getPixelArea();
    this->fontSize = content.getFontSize();
    this->pixelsPChar = content.getPixelsPCharacter();
    this->calcSize();
}

Content::Content(Content &content){
    this->content = content.getContent();
    this->x_start, this->y_start = content.getStartX(), content.getStartY();
    this->pixel_area = content.getPixelArea();
    this->fontSize = content.getFontSize();
    this->pixelsPChar = content.getPixelsPCharacter();
    this->calcSize();
}


Content::Content(const int &x, const int &y, const int &fontsize, const int &pixelsPChar){
    this->x_start = x;
    this->y_start = y;
    this->content = UNDEFINEDCONTENT;
    this->fontSize = fontSize;
    this->pixelsPChar = pixelsPChar;
    this->calcSize();
}

Content::Content(const std::string &content, const int &x, const int &y){
    this->content = content;
    this->x_start, this->y_start = 0, 0;
    this->fontSize = FONTSIZE;
    this->pixelsPChar = PIXELSPCHAR;
    this->calcSize();
}

Content::Content(){
    this->content = UNDEFINEDCONTENT;
    this->fontSize = FONTSIZE;
    this->pixelsPChar = PIXELSPCHAR;
    this->pixel_area = PixelArea(0, 0, 0, 0);
}

void Content::setX(const int &x){ 
    this->x_start = x; 
    this->calcSize(FONTSIZE, PIXELSPCHAR);
}


void Content::setY(const int &y){ 
    this->y_start = y; 
    this->calcSize(FONTSIZE, PIXELSPCHAR);
}


int Content::getStartX() const{ return this->x_start; }
int Content::getFinalX() const{ return this->x_end; }

int Content::getStartY() const{ return this->y_start; }
int Content::getFinalY() const{ return this->y_end; }

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

PixelArea Content::getPixelArea() const{ return this->pixel_area;}

int Content::getFontSize() const{ return this->fontSize; }
int Content::getPixelsPCharacter() const{ return this->pixelsPChar; }

void Content::setFontSize(const int &fontsize){ this->fontSize = fontsize; }
void Content::setPixelsPCharacter(const int &pixelspchar){ this->pixelsPChar = pixelspchar; }

bool Content::operator==(const Content &content){ return this->equal(content); }
bool Content::operator!=(const Content &content){ return !this->equal(content); }
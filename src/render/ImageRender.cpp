#include "ImageRender.hpp"
#include "../bounds/Viewport.hpp"
#include "../bounds/Content.hpp"
#include <string>
#include <vector>
#include <CImg.h>
#include <algorithm>
#include <list>
#include <iostream>
using namespace Render;

std::string ImageRender::InvalidViewport::what(){ return this->msg; }

bool ImageRender::checkViewports(std::vector<Bounds::ViewPort> viewports){
    for(std::vector<Bounds::ViewPort>::iterator it = viewports.begin(); it != viewports.end(); ++it){
        if(it->getPixelArea().getXFinal() > this->image.width() || it->getPixelArea().getYFinal() > this->image.height())
            return false;
    }
    return true;
}

ImageRender::ImageRender() {};
ImageRender::ImageRender(std::string path, std::vector<Bounds::ViewPort> viewports){
    this->path = path;
    cimg_library::CImg<unsigned char> img(path.c_str());
    this->image = img;
    if(!checkViewports(viewports)) throw ImageRender::InvalidViewport("Invalid viewports received to image " + path);
    this->viewports = viewports;
}

cimg_library::CImg<unsigned char> ImageRender::getImage(){ return this->image; }

std::vector<Bounds::ViewPort> ImageRender::getViewPorts(){ return this->viewports; }

std::string ImageRender::getOriginPath(){ return this->path; }

void ImageRender::writeText(const Bounds::Content &content){
    this->image.draw_text(content.getStartX(), content.getStartY(), content.getContent().c_str(), 0, "white");
}

void ImageRender::save_with_contents(std::string path_to_save){
    for(const Bounds::ViewPort &vp : this->viewports){
        for(const Bounds::Content &content : vp.getContent()){
            std::cout << "Writing " << content.getContent() << " from " << vp.getPixelArea().to_string() << std::endl;
            this->writeText(content);
        }
    }
    this->image.save_png(path_to_save.c_str());
}


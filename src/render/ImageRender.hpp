#pragma once

#include <CImg.h>
#include <string>
#include "../bounds/Viewport.hpp"
#include "../bounds/Content.hpp"
#include <vector>
#include <exception>

namespace Render{
    class ImageRender{
        private:
            std::string path;
            cimg_library::CImg<unsigned char> image;
            std::vector<Bounds::ViewPort> viewports;

            bool checkViewports(std::vector<Bounds::ViewPort> viewports);
            void writeText(const Bounds::Content &content);
        public:
            class InvalidViewport : std::exception{
                private:
                    std::string msg;
                public:
                    InvalidViewport(std::string message) : msg(message){}
                    std::string what();
            };
            ImageRender();

            ImageRender(std::string path, std::vector<Bounds::ViewPort> viewports);

            cimg_library::CImg<unsigned char> getImage();

            void save_with_contents(std::string path_to_save);

            std::string getOriginPath();

            std::vector<Bounds::ViewPort> getViewPorts();

            void setViewports(std::vector<Bounds::ViewPort> viewports);

            void setImagePath(std::string new_path);

            void appendViewport(Bounds::ViewPort vp);
    };
}
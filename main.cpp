#include <iostream>
#include <CImg.h>
#include <string>
#include <list>
using namespace cimg_library;

int main(int argc, char **argv){
    std::string scrdir("./images/");
    CImg<unsigned char> baseImageTest("icebergmodel.png");
    std::cout << baseImageTest.width() << "X" << baseImageTest.height() << std::endl;
    baseImageTest.draw_text(100, 100, "testing cimage", 0, "white");
    baseImageTest.save_jpeg("test-model.jpeg");
    return 0;
}
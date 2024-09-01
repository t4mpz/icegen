#include "../src/render/ImageRender.hpp"
#include "../src/bounds/Viewport.hpp"
#include "../src/bounds/Content.hpp"
#include "../src/bounds/PixelArea.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

void testRender(){
    std::cout << "Enter test render" << std::endl;
    Bounds::Content c1("teste_c1", 100, 100), c2("teste_c2", 120, 100);
    Bounds::Content c3("teste_c3", 100, 400), c4("teste_c4", 140, 440);
    Bounds::ViewPort vp1(Bounds::PixelArea(0, 0, 1300, 290), 0, 0);
    Bounds::ViewPort vp2(Bounds::PixelArea(0, 290, 1300, 580), 0, 0);
    vp1.append(c1);
    vp1.append(c2);
    vp2.append(c3);
    vp2.append(c4);
    Render::ImageRender img("icebergmodel.png", {vp1, vp2});
    std::cout << "Started image img" << std::endl;
    img.save_with_contents("tests/rendered.test.png");
}


int main(){
    testRender();
    std::cout << "testing render" << std::endl;
    return 0;
}
#include "../src/bounds/Content.hpp"
#include "../src/bounds/PixelArea.hpp"
#include "../src/bounds/Viewport.hpp"
#include "../src/iceberg/iceberg.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

using namespace Bounds;

const std::vector<std::string> contents{"test_layer", "testLayer"};
// const Iceberg::Layer l(contents, "testLayer");


bool isIn(Content item, std::vector<Content> pool){
    for(std::vector<Content>::iterator it = pool.begin(); it < pool.end();){
        if(it->equal(item)) { return true;} 
        ++it;
    }
    return false;
}

void testPixelArea(){
    PixelArea pa(0, 0, 100, 100);
    PixelArea pa2(0, 0, 100, 100);
    assertm(pa.equal(pa2), "PA should be equal to its clone");
    PixelArea pl(50, 50, 200, 200);
    PixelArea pb(150, 150, 250, 250);
    assertm(pl.contains(pa, 0), "Should contain some instance of pa inside of pl");
    assertm(pa.isContainedIn(pl, 0), "Should see pa contained inside pl at some point");
    assertm(pl.isContainedIn(pb, 1), "PB should contain PL");
    assertm(!pb.contains(pa, 10), "PB should not contain pa");
    int px = 10, py = 20;
    assertm(pa.contains(px, py, 0), "Should contain point inside of the area");
    assertm(!pl.contains(px, py, 0), "Should see point not contained inside of pl");
    std::cout << "Pixel area created!" << std::endl;
    assertm(pa.getArea() == 10000, "Should have calculated the area correctly");

}

void testContent(){
    Content c("teste_content", 100, 100);
    Content c2("teste_content", 100, 100);
    assertm(c.equal(c2), "C should be equal to its clone");
    std::cout << "Created content test" << std::endl;
}

void testViewPort(){
    Content stablished("test1", 50, 50);
    ViewPort vp({stablished}, PixelArea(0, 0, 100, 100), 0, 0);
    ViewPort vp2({stablished}, PixelArea(0, 0, 100, 100), 0, 0);
    assertm(vp == vp2, "The viewports should be equal at first dum code");
    Content c("teste", 10, 10);
    Content found = vp.at(PixelArea(0, 0, 50, 50));
    assertm(found.getContent() == stablished.getContent(), "Should have found test1 inside area");
    vp.append(c);
    assertm(isIn(c, vp.getContent()), "C content should have been inserted in the viewport");
    vp.remove(stablished);
    assertm(!isIn(stablished, vp.getContent()), "Stablished should have been remove from the viewport");
}

int main(){
    testViewPort();
    std::cout << "ViewPort tested" << std::endl;
    testPixelArea();
    std::cout << "Pixel Area tested" << std::endl;
    testContent();
    std::cout << "Content tested" << std::endl;
    
    return 0;
}
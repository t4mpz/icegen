#include "../src/iceberg/iceberg.hpp"
#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#define assertm(exp, msg) assert(((void)msg, exp))

const std::vector<std::string> BASEVECTOR{"base_test", "base_test2", "base_test3"};

void test_object(){
    Iceberg::Layer l(BASEVECTOR, "test_layer");
    assertm(l.getName() == "test_layer", "should have created the layer name properly");

    return;
}

void test_has(){
    Iceberg::Layer l(BASEVECTOR, "test_layer");
    assertm(l.has("base_test"), "Expected function has to find existing item base_test");
}

void test_append(){
    Iceberg::Layer l(BASEVECTOR, "test_layer");
    l.append("test_append");
    assertm(l.has("test_append"), "Expected function append to insert new item in layer content");  
}

void test_remove(){
    Iceberg::Layer l(BASEVECTOR, "test_layer");
    l.remove("base_test2");
    assertm(!l.has("base_test2"), "Expected function remove to remove item in layer content");
}

void test_update(){
    Iceberg::Layer l(BASEVECTOR, "test_layer");
    l.update("base_test2", "base_test4");
    assertm(!l.has("base_test2") && l.has("base_test4"), "Expected function update to update item in layer content");
}


int main(int argc, char** argv){
    std::cout << "Starting Iceberg test" << std::endl;
    test_object();
    std::cout << "Passed test_object" << std::endl;
    test_has();
    std::cout << "Passed test_has" << std::endl;
    test_append();  
    std::cout << "Passed test_apppend" << std::endl;
    test_remove();
    std::cout << "Passed test_remove" << std::endl;
    test_update();
    std::cout << "Passed test_update" << std::endl;
    return 0;
}
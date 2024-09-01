#include <vector>
#include <string>
#include "iceberg.hpp"
using namespace Iceberg;

std::string ItemNotFound::what(){
    return this->message;
}

std::string DuplicatedItemError::what(){
    return this->message;
}


Layer::Layer(std::vector<std::string> contents, std::string name){
    this->name = name;
    this->content = contents;
}

Layer::Layer(std::string* contents, std::string name){
    this->name = name;
    int szcontents = size_t(contents);
    for(int counter = 0; counter < szcontents; ++counter){ 
        this->content.push_back(contents[counter]);
    }
}

Layer::Layer(){}

bool Layer::has(std::string item){
    for(std::string from_content : this->content){
        if(item == from_content) return true;
    }
    return false;
}

std::vector<std::string> Layer::getContent(){ return this->content;}

std::string Layer::getName(){ return this->name; }

void Layer::setName(std::string name){ this->name = name; }

void Layer::setContent(std::vector<std::string> content){ this->content = content;}

void Layer::append(std::string item){
    if(this->has(item)) throw DuplicatedItemError("Duplicated entrance " + item + " at layer " + this->name);
    else this->content.push_back(item);
}

void Layer::remove(std::string item){
    for(std::vector<std::string>::iterator from_content = this->content.begin(); from_content != this->content.end();){
        if(*from_content == item){
            this->content.erase(from_content);
            return;
        }
        from_content++;
    }
    throw ItemNotFound("No item " + item + " found in layer " + this->name);
}

void Layer::update(std::string o_item, std::string value){
    this->remove(o_item);
    this->content.push_back(value);
    return;
}


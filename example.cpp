#include <iostream>
#include "tinyxml/tinyxml.h"
#include "CD.h"
#include <vector>

std::string Information(TiXmlElement* root, std::string Attribute){
    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
        elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();
        if (elemName == Attribute) {
            TiXmlElement *attr = elem->ToElement();
            return attr->GetText();
        }
    }
    return "";
}

int main() {
    TiXmlDocument doc;
    if (!doc.LoadFile("../cdCatalog.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }
    if ((std::string)root->Value() == "CD") {
        CD *cd = new CD(root);
        std::cout << cd->getTitle() << std::endl;
    }
    std::cout<<root->Value()<<std::endl;
    if ((std::string)root->Value() == "CATALOG") {

        for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL;
        elem = elem->NextSiblingElement()) {
            std::cout << root->FirstChildElement()->Value() << std::endl;
            for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {
                std::cout << elem << std::endl;
            }
        }
    }
}


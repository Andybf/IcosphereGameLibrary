//
//  Text.cpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#include <Apolo/World/Entities/Text.hpp>

Text::Text(uint fontMapTextureId, uint textShaderId) {
    this->fontmapWidth = 256;
    this->characterScale = this->fontmapWidth/16;
    this->setPosition(glm::vec3(0,characterScale,1));
    this->setScale(glm::vec3(characterScale));
    this->relatedTextureId = fontMapTextureId;
    this->relatedShaderId = textShaderId;
    this->string32bit = (int*) calloc(sizeof(int), 1);
    this->content = (char*) calloc(sizeof(char), 256);
}

void Text::calcCharPositionOnScreen(uchar* string) {
    short x = 0;
    short y = 0;
    this->stringPositionList.clear();
    for (ushort c=0; c<this->stringSize; c++) {
        this->stringPositionList.push_back(glm::vec2(x,y));
        if (string[c] == '\n') {
            y++;
            x=0;
            this->string32bit[c] = 0xFF;
        } else {
            this->string32bit[c] = string[c];
            x++;
        }
    }
}

void Text::processContents(uchar* string) {
    this->stringSize = (uint) strlen((const char*)string);
    this->string32bit = (int*) realloc(this->string32bit, sizeof(int)*this->stringSize);
    this->calcCharPositionOnScreen(string);
}

int* Text::get32bitString() {
    return this->string32bit;
}

uint Text::getStringSize() {
    return this->stringSize;
}

std::vector<glm::vec2> Text::getStringPositionList() {
    return this->stringPositionList;
}

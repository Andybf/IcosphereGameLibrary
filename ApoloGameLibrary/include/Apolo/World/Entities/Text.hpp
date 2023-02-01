//
//  Text.hpp
//  ApoloGameLibrary
//
//  Created by Anderson Bucchianico on 30/01/23.
//

#ifndef Text_hpp
#define Text_hpp

#include "../../Core.hpp"
#include "../Entity.hpp"

class Text : public Entity {
    
private:
    short elementsCountX;
    short elementsCountY;
    float characterScale;
    
    float fontmapWidth;
    int* string32bit;
    std::vector<glm::vec2> stringPositionList;
    int stringSize;
    
    void countStringSize(uchar* string);
    void calcCharPositionOnScreen(uchar* string);
    
public:
    Text(uint fontMapTextureId, uint textShaderId);
    void setText(uchar* string);
    int* get32bitString();
    int getStringSize();
    std::vector<glm::vec2> getStringPositionList();
};

#endif /* Text_hpp */

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
    float characterScale;
    
    ushort fontmapWidth;
    int* string32bit;
    std::vector<glm::vec2> stringPositionList;
    uint stringSize;
    
    void calcCharPositionOnScreen(uchar* string);
    
public:
    char * content;
    
    Text(uint fontMapTextureId, uint textShaderId);
    void processContents(uchar* string);
    int* get32bitString();
    uint getStringSize();
    std::vector<glm::vec2> getStringPositionList();
};

#endif /* Text_hpp */

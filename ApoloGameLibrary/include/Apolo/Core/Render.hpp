//
//  render.h
//  Apolo Game Library
//
//  Created by Anderson Bucchianico on 27/01/23.
//

#ifndef render_h
#define render_h

#include "../Core.hpp"
#include "Window.hpp"
#include "../World/Entity.hpp"

namespace Render {
    void initialize(Window::WindowData* window);
    void renderLoop();

    void drawArrays(struct Entity* model);
    void drawElements(struct Entity* model);
    void drawElementsInstanced(struct Entity* model, uint count);

    void printContextInformation();
}

#endif /* render_h */

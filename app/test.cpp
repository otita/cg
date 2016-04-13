//
//  test.cpp
//
//  Created by otita on 2016/04/13.
//
/*
The MIT License (MIT)

Copyright (c) 2016 otita.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <iostream>

#include "Window.h"
#include "Object.h"

int main(int argc, const char *argv[]) {
  using namespace std;
  using namespace otita::cg;

  WindowFactory *wFactory = WindowFactory::getInstance();
  Window *window = wFactory->createWindowOrDie(640, 480, "Test");
  delete wFactory;

  World *world = new World();
  ObjectFactory *oFactory = ObjectFactory::getInstance();
  world->addObject(
      oFactory->createTriangle(
        {
        -0.6, -0.4, 0.,
        0.6,  -0.4, 0.,
        0.,    0.6, 0.,
        }
        )
      );

  window->setWorld(world);

  while (!window->shouldClose()) {
    window->clear();
    window->draw();
    window->swapBuffers();
  }

  delete world;
  delete window;

  return 0;
}

//
//  Window.cpp
//
//  Created by otita on 2016/04/12.
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
#include <cstdlib>

#include <GLFW/glfw3.h>

#include "Window.h"
#include "Object.h"
#include "Camera.h"
#include "KeyboardDelegate.h"

namespace otita {

namespace cg {

class GLWindow : public Window {
  using base = Window;
public:
  GLWindow(uint32_t width,
           uint32_t height,
           const char title[]);
  virtual ~GLWindow();
  virtual bool shouldClose() const;
  virtual void clear();
  virtual void swapBuffers();
  virtual void setKeyboardDelegate(
      KeyboardDelegate *keyboardDelegate
      );
private:
  GLFWwindow *_window;
  static void _keyCallback(
      GLFWwindow *window,
      int key,
      int scancode,
      int action,
      int mods
      );
  static void _resizeCallback(
      GLFWwindow *window,
      int width,
      int height
      );
};

class GLWindowFactory : public WindowFactory {
public:
  virtual Window *createWindowOrDie(
      uint32_t width,
      uint32_t height,
      const char title[]
      );
};

Window::Window() : _world(nullptr), _keyboardDelegate(nullptr) {
  CameraFactory *factory = CameraFactory::getInstance();
  _camera = factory->createCamera();
  CameraFactory::deleteInstance();
}

World *Window::world() {
  return _world;
}

void Window::setWorld(World *world) {
  _world = world;
}

Camera *Window::camera() {
  return _camera;
}

void Window::setKeyboardDelegate(
    KeyboardDelegate *keyboardDelegate
    ) {
  if (_keyboardDelegate != keyboardDelegate) {
    if (_keyboardDelegate) delete _keyboardDelegate;
    _keyboardDelegate = keyboardDelegate;
  }
}

void Window::draw() const {
  if (_world) _world->render();
}

WindowFactory *WindowFactory::_instance = nullptr;

WindowFactory *WindowFactory::getInstance() {
  if (!_instance) {
    _instance = new GLWindowFactory();
  }
  return _instance;
}

void WindowFactory::deleteInstance() {
  if (_instance) {
    delete _instance;
    _instance = nullptr;
  }
}

GLWindow::GLWindow(
    uint32_t width,
    uint32_t height,
    const char title[]
    ) {
  using namespace std;

  if (!glfwInit()) exit(EXIT_FAILURE);

  _window = glfwCreateWindow(width, height, title, NULL, NULL);
  glfwSetFramebufferSizeCallback(_window, _resizeCallback);

  if (!_window) {
    cerr << "cannot create window" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetWindowUserPointer(_window, this);
  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  _resizeCallback(
      _window,
      width, height
      );
}

GLWindow::~GLWindow() {
  glfwDestroyWindow(_window);
  glfwTerminate();
}

bool GLWindow::shouldClose() const {
  return glfwWindowShouldClose(_window);
}

void GLWindow::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::swapBuffers() {
  glfwSwapBuffers(_window);
  glfwPollEvents();
}

void GLWindow::setKeyboardDelegate(
    KeyboardDelegate *keyboardDelegate
    ) {
  using namespace std;
  base::setKeyboardDelegate(keyboardDelegate);

  glfwSetKeyCallback(_window, _keyCallback);
}

void GLWindow::_keyCallback(
    GLFWwindow *window,
    int key,
    int scancode,
    int action,
    int mods
    ) {
  GLWindow *glWindow = reinterpret_cast<GLWindow *>(
      glfwGetWindowUserPointer(window)
      );
  if (glWindow) {
    KeyboardDelegate *delegate = glWindow->_keyboardDelegate;
    if (delegate) {
      delegate->keyCallback(
          glWindow,
          key,
          action,
          mods
          );
    }
  }
}
void GLWindow::_resizeCallback(
    GLFWwindow *window,
    int width,
    int height
    ) {
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  GLWindow *glWindow = reinterpret_cast<GLWindow *>(
      glfwGetWindowUserPointer(window)
      );
  if (glWindow) {
    Camera *camera = glWindow->_camera;
    if (camera) camera->look();
  }
//  glOrtho(
//      -width / 50., width / 50.,
//      -height / 50., height / 50.,
//      -0., 1.
//      );
  glOrtho(
      -10., 10.,
      -10., 10.,
      -0., 1.
      );
}
 
Window *GLWindowFactory::createWindowOrDie(
    uint32_t width,
    uint32_t height,
    const char title[]
    ) {
  return new GLWindow(width, height, title);
}

} // cg

} // otita

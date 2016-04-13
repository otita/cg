//
//  Object.h
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

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <list>

namespace otita {

namespace cg {

class Object {
public:
  virtual ~Object() {}
  virtual void render() const = 0;
};

class World : Object {
public:
  virtual ~World();
  virtual void render() const;
  void addObject(Object *obj);
private:
  std::list<Object *> _objects;
};

class Vertex : public Object {
};

class Line : public Object {
};

class Triangle : public Object {
};

class ObjectFactory {
public:
  ObjectFactory(const ObjectFactory &) = delete;
  ObjectFactory &operator =(const ObjectFactory &) = delete;
  ObjectFactory(ObjectFactory &&) = delete;
  ObjectFactory &operator =(ObjectFactory &&) = delete;

  static ObjectFactory *getInstance();
  static void deleteInstance();

  virtual Triangle *createTriangle(const double (&vertexes)[9]) = 0;

protected:
  ObjectFactory() = default;
  virtual ~ObjectFactory() = default;
  static ObjectFactory *_instance;
};

} // cg

} // otita


#endif  // _OBJECT_H_

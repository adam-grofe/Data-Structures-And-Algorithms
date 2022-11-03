[![CMake](https://github.com/adam-grofe/Data-Structures-And-Algorithms/actions/workflows/singleton_factory.yml/badge.svg?branch=main)](https://github.com/adam-grofe/Data-Structures-And-Algorithms/actions/workflows/singleton_factory.yml)

# Description
There are often times that you need to ensure programmatically 
that there is one and only one instantiation of a class. This 
is traditionally where the Singleton design pattern from the 
Gang of Four is used. However, this design pattern uses static 
variables that, once initialized, are difficult to destroy 
(usually you have to wait until the program finishes). This
design pattern addresses this concern by using the Singleton
design for a factory object that can create the object.
Furthermore, the object's lifetime can be controlled through
the use of shared_ptr's. When all of the external shared_ptr's
have been reset or gone out of scope, then the object is
destroyed. Thus, this allows us to both create and destroy
an object with a guarentee that there will only ever be one
instantiated.

# Usage
```cpp
class Object {
   private:
   // Make friends with the SingletonFactory so that it can create your object
   friend class SingletonFactory<Object>;

   // Private Constructor prevents creation except through the SingletonFactory.
   Object(){
       std::cout << "Object::Object()" << std::endl;
   }
   Object(Object&) = delete;

   public:

   /* Public destructor is necessary so that shared_ptr/weak_ptr can destroy the
    * object when it goes out of scope.
    */
   ~Object(){
       std::cout << "Object::~Object()" << std::endl;
   }
};
```

# Compilation
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCOMPILE_TESTS=On <path/to/source>
cmake --build .
ctest
```

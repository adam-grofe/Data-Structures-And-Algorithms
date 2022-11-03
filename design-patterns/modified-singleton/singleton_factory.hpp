
#pragma once

#ifdef SINGLETON_DEBUG
#include <iostream>
#endif

#include <memory>

template<class T>
class SingletonFactory {

   static SingletonFactory *instance;
   std::weak_ptr<T> object;

   // Private constructor so that no objects can be created.
   SingletonFactory() {
#ifdef SINGLETON_DEBUG
       std::cout << "SingletonFactory::SingletonFactory()" << std::endl;
#endif
   };
   ~SingletonFactory(){
#ifdef SINGLETON_DEBUG
       std::cout << "SingletonFactory::~SingletonFactory()" << std::endl;
#endif
   };

   std::shared_ptr<T> getPtr(){
      if( object.use_count() == 0 ){
           T* rawPtr = new T;
           std::shared_ptr<T> ptr(rawPtr);
           object = ptr;
           return ptr;
      }

      return object.lock();
   }


   public:
   static std::shared_ptr<T> getInstance() {
      if (!instance)
        instance = new SingletonFactory<T>;
      return instance->getPtr();
   }
};

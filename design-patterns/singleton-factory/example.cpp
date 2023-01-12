#include <iostream>
#include <memory>

#define SINGLETON_DEBUG
#include "singleton_factory.hpp"

class Object
{
  private:
    // Make friends with Singleton so that it can create
    // this class
    friend class SingletonFactory<Object>;

    // Private Constructor prevents creation except through
    // the singleton class.
    Object()
    {
        std::cout << "Object::Object()" << std::endl;
    }
    Object(Object&) = delete;

  public:
    // Public destructor is necessary so that shared_ptr/weak_ptr
    ~Object()
    {
        std::cout << "Object::~Object()" << std::endl;
    }
};

// Initialize pointer to zero so that it can be initialized in first call to getInstance
template <> SingletonFactory<Object>* SingletonFactory<Object>::instance = nullptr;

int main()
{
    std::cout << "Entering Main\n";
    // First lifetime
    std::cout << "First Lifetime: " << std::endl;
    std::shared_ptr<Object> ptr1 = SingletonFactory<Object>::getInstance();
    std::shared_ptr<Object> ptr2 = SingletonFactory<Object>::getInstance();
    ptr1.reset();
    ptr2.reset();
    std::cout << "\n\n";

    // Second lifetime
    std::cout << "Second Lifetime: " << std::endl;
    ptr1 = SingletonFactory<Object>::getInstance();
    ptr2 = SingletonFactory<Object>::getInstance();
    ptr1.reset();
    ptr2.reset();
    std::cout << "\n\n";

    // Third lifetime
    {
        std::cout << "Third Lifetime: " << std::endl;
        std::shared_ptr<Object> ptr3 = SingletonFactory<Object>::getInstance();
    }
    std::cout << "\n\n";
    std::cout << "Exiting Main\n";
    return 0;
}

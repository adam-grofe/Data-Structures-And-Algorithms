#include <iostream>
#include <memory>

#include "singleton_factory.hpp"
#include <gtest/gtest.h>


class Object {
   private:
   // Make friends with Singleton so that it can create
   // this class
   friend class SingletonFactory<Object>;

   // Private Constructor prevents creation except through
   // the singleton class.
   Object(){
       cnt++;
   }
   Object(Object&) = delete;

   public:

   size_t cnt = 0;

   // Public destructor is necessary so that shared_ptr/weak_ptr
   ~Object(){};
};



//Initialize pointer to zero so that it can be initialized in first call to getInstance
template<>
SingletonFactory<Object>* SingletonFactory<Object>::instance = nullptr;

TEST( ModifiedSingleton, TwoPointersResetTest ){

    std::shared_ptr<Object> ptr1 = SingletonFactory<Object>::getInstance();
    EXPECT_EQ(ptr1->cnt, 1);
    std::shared_ptr<Object> ptr2 = SingletonFactory<Object>::getInstance();
    EXPECT_EQ(ptr1->cnt, 1);
    EXPECT_EQ(ptr2->cnt, 1);
    EXPECT_EQ(&(*ptr1),&(*ptr2));
    ptr1.reset();
    EXPECT_EQ(ptr2->cnt, 1);
    ptr2.reset();
}

TEST( ModifiedSingleton, TwoPointersScopeTest){

    {
        std::shared_ptr<Object> ptr1;
        std::shared_ptr<Object> ptrScoped = SingletonFactory<Object>::getInstance();
        EXPECT_EQ(ptrScoped->cnt, 1);
        ptr1 = SingletonFactory<Object>::getInstance();
        EXPECT_EQ(ptrScoped->cnt, 1);
        EXPECT_EQ(ptr1->cnt, 1);
        EXPECT_EQ(&(*ptr1),&(*ptrScoped));
    }
}

TEST( ModifiedSingleton, TwoPointersResetAndScopeTest){

    std::shared_ptr<Object> ptr1;
    {
        std::shared_ptr<Object> ptrScoped = SingletonFactory<Object>::getInstance();
        EXPECT_EQ(ptrScoped->cnt, 1);
        ptr1 = SingletonFactory<Object>::getInstance();
        EXPECT_EQ(ptrScoped->cnt, 1);
        EXPECT_EQ(ptr1->cnt, 1);
        EXPECT_EQ(&(*ptr1),&(*ptrScoped));
    }
    EXPECT_EQ(ptr1->cnt, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

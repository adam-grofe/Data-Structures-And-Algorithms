
#include <gtest/gtest.h>
#include <iostream>

#include "cyclic-queue.hpp"

TEST(CyclicQueueTest, InsertEqualAmountTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);
    cq.insert(4);

    int sum = 0;
    auto func = [&sum](int& i) { sum += i; };
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 10) << "Sum of the values in the queue should be 10\nSum = " << sum;
}

TEST(CyclicQueueTest, InsertLessThanTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    int sum = 0;
    auto func = [&sum](int& i) { sum += i; };
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 6) << "Sum of the values in the queue should be 6\nSum = " << sum;
}

TEST(CyclicQueueTest, InsertMoreThanTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);
    cq.insert(4);
    cq.insert(5);

    int sum = 0;
    auto func = [&sum](int& i) { sum += i; };
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 14) << "Sum of the values in the queue should be 14\nSum = " << sum;

    cq.insert(6);
    cq.insert(7);
    cq.insert(8);
    cq.insert(9);
    cq.insert(10);
    sum = 0;
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 34) << "Sum of the values in the queue should be 34\nSum = " << sum;
}

TEST(CyclicQueueTest, InsertOnTopTest)
{
    CyclicQueue<int> cq(4);
    cq.insert_on_top(1);
    cq.insert_on_top(2);
    cq.insert_on_top(3);
    cq.insert_on_top(4);
    cq.insert_on_top(5);

    int sum = 0;
    auto func = [&sum](int& i) { sum += i; };
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 14) << "Sum of the values in the queue should be 14\nSum = " << sum;

    cq.insert(6);
    cq.insert(7);
    cq.insert(8);
    cq.insert(9);
    cq.insert_on_top(10); // CyclcQueue should be (10,6,7,8)
    sum = 0;
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 31) << "Sum of the values in the queue should be 31\nSum = " << sum;
    ASSERT_EQ(cq[0], 10) << "First element of the CyclicQueue should be 10";
    ASSERT_EQ(cq[1], 6) << "Second element of the CyclicQueue should be 6";
    ASSERT_EQ(cq[2], 7) << "Third element of the CyclicQueue should be 7";
    ASSERT_EQ(cq[3], 8) << "Fourth element of the CyclicQueue should be 8";
}

TEST(CyclicQueueTest, DequeueLessThanTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    int dq = cq.dequeue();
    ASSERT_EQ(dq, 1) << "Dequeue result should return the last value";

    int sum = 0;
    auto func = [&sum](int& i) { sum += i; };
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 5) << "Sum of the values in the queue should be 5\nSum = " << sum;
}

TEST(CyclicQueueTest, DequeueEqualTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    int dq1 = cq.dequeue();
    EXPECT_EQ(dq1, 1) << "Dequeue result should return the last value";
    int dq2 = cq.dequeue();
    EXPECT_EQ(dq2, 2) << "Dequeue result should return the last value";
    int dq3 = cq.dequeue();
    ASSERT_EQ(dq3, 3) << "Dequeue result should return the last value";

    size_t nIn = cq.nInserted();
    ASSERT_EQ(nIn, 0) << "Cyclic Queue empty after removing all elements";
}

TEST(CyclicQueueTest, DequeueMoreThanTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    int dq1 = cq.dequeue();
    EXPECT_EQ(dq1, 1) << "Dequeue result should return the last value";
    int dq2 = cq.dequeue();
    EXPECT_EQ(dq2, 2) << "Dequeue result should return the last value";
    int dq3 = cq.dequeue();
    ASSERT_EQ(dq3, 3) << "Dequeue result should return the last value";

    bool except = false;
    try
    {
        dq1 = cq.dequeue();
    }
    catch (...)
    {
        except = true;
    }
    ASSERT_EQ(except, true) << "Dequeue-ing an empty queue did not throw an exception";
}

TEST(CyclicQueueTest, FrontBackTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    int front = cq.front();
    ASSERT_EQ(front, 1);
    int back = cq.back();
    ASSERT_EQ(back, 3);

    cq.insert(4);
    cq.insert(5);
    cq.insert(6);

    front = cq.front();
    ASSERT_EQ(front, 3);
    back = cq.back();
    ASSERT_EQ(back, 6);

    cq.dequeue();
    front = cq.front();
    ASSERT_EQ(front, 4);
    back = cq.back();
    ASSERT_EQ(back, 6);
}

TEST(CyclicQueueTest, ResizeTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    cq.resize(3);

    int sum = 0;
    auto func = [&sum](int& i) { sum += i; };
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 6) << "Sum of the values in the queue should be 6\nSum = " << sum;

    size_t ref = cq.size();
    ASSERT_EQ(ref, 3) << "Cyclic Queue should be size 3 after being resized";

    cq.resize(7);
    sum = 0;
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 6) << "Sum of the values in the queue should be 6\nSum = " << sum;
    ref = cq.size();
    ASSERT_EQ(ref, 7) << "Cyclic Queue should be size 7 after beingn resized";

    cq.resize(2);
    sum = 0;
    cq.traverseQueue(func);
    ASSERT_EQ(sum, 5) << "Sum of the values in the queue is wrong";
    ref = cq.size();
    ASSERT_EQ(ref, 2) << "Total size of queue is wrong after resize";
}

TEST(CyclicQueueTest, CopyTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    CyclicQueue<int> cq2(cq);
    ASSERT_EQ(cq2.size(), 4) << "Size of the copied cyclic queue is wrong";
    int sum = 0;
    auto func = [&sum](const int& i) { sum += i; };
    cq2.traverseQueue(func);
    ASSERT_EQ(sum, 6) << "Sum of the values in the queue are wrong";
    ASSERT_EQ(cq2.frontIndex(), cq.frontIndex()) << "Front indices should be equal after copy";

    cq.insert(4);
    cq.insert(5);
    cq.insert(6);
    CyclicQueue<int> cq3 = cq;
    sum = 0;
    cq3.traverseQueue(func);
    ASSERT_EQ(sum, 18) << "Sum of the values in the queue are wrong";
    ASSERT_EQ(cq3.frontIndex(), cq.frontIndex()) << "Front indices should be equal after copy";

    cq2 = cq;
    sum = 0;
    cq3.traverseQueue(func);
    ASSERT_EQ(sum, 18) << "Sum of the values in the queue are wrong";
    ASSERT_EQ(cq2.frontIndex(), cq.frontIndex()) << "Front indices should be equal after copy";
}

TEST(CyclicQueueTest, MoveTest)
{
    CyclicQueue<int> cq(4);
    cq.insert(1);
    cq.insert(2);
    cq.insert(3);

    size_t cqFront = cq.frontIndex();
    CyclicQueue<int> cq2(std::move(cq));
    ASSERT_EQ(cq2.size(), 4) << "Size of the copied cyclic queue is wrong";
    int sum = 0;
    auto func = [&sum](const int& i) { sum += i; };
    cq2.traverseQueue(func);
    ASSERT_EQ(sum, 6) << "Sum of the values in the queue are wrong";
    ASSERT_EQ(cq2.frontIndex(), cqFront) << "Front indices should be equal after copy";

    cq2.insert(4);
    cq2.insert(5);
    cq2.insert(6);
    cqFront = cq2.frontIndex();
    CyclicQueue<int> cq3 = std::move(cq2);
    sum = 0;
    cq3.traverseQueue(func);
    ASSERT_EQ(sum, 18) << "Sum of the values in the queue are wrong";
    ASSERT_EQ(cq3.frontIndex(), cqFront) << "Front indices should be equal after copy";
}

TEST(CyclicQueueTest, OStreamTest)
{
    std::ostringstream out;
    CyclicQueue<std::string> cq(4);
    cq.insert("hello");
    cq.insert("world");
    cq.insert("!");

    out << cq;
    ASSERT_TRUE(out.good());
    std::string outStr = out.str();
    std::cout << outStr;
    size_t hello = outStr.find("hello");
    ASSERT_NE(hello, std::string::npos);
    size_t world = outStr.find("world");
    ASSERT_NE(world, std::string::npos);
    size_t front = outStr.find("Front");
    ASSERT_NE(front, std::string::npos);
    size_t size = outStr.find("Total Size");
    ASSERT_NE(size, std::string::npos);
}

// TODO:
//   1. Test copy/move constructors
//   3. Test resize function
//   4. Ostream output
//   5.

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
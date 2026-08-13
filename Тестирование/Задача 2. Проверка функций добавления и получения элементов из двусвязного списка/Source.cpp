#include <catch2/catch_test_macros.hpp>

#include <cstdint>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};


// ==================== ТЕСТЫ ====================

TEST_CASE("PushBack on empty list", "[pushback]") {
    List list;

    SECTION("PushBack one element") {
        list.PushBack(10);

        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 1);

        int value = list.PopFront();
        REQUIRE(value == 10);
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("PushBack multiple elements") {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);

        REQUIRE(list.Size() == 3);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopFront() == 1);
        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.PopFront() == 3);
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }
}

TEST_CASE("PushFront on empty list", "[pushfront]") {
    List list;

    SECTION("PushFront one element") {
        list.PushFront(20);

        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 1);

        int value = list.PopFront();
        REQUIRE(value == 20);
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("PushFront multiple elements") {
        list.PushFront(1);
        list.PushFront(2);
        list.PushFront(3);

        REQUIRE(list.Size() == 3);
        REQUIRE(list.Empty() == false);

        // PushFront добавляет в начало, поэтому порядок обратный
        REQUIRE(list.PopFront() == 3);
        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.PopFront() == 1);
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }
}

TEST_CASE("PopBack on empty list", "[popback]") {
    List list;

    SECTION("PopBack throws exception on empty list") {
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);

        // Проверяем, что список остался пустым
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("PopBack exception message") {
        try {
            list.PopBack();
            FAIL("Expected exception was not thrown");
        }
        catch (const std::runtime_error& e) {
            REQUIRE(std::string(e.what()) == "list is empty");
        }
    }
}

TEST_CASE("PopFront on empty list", "[popfront]") {
    List list;

    SECTION("PopFront throws exception on empty list") {
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);

        // Проверяем, что список остался пустым
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }

    SECTION("PopFront exception message") {
        try {
            list.PopFront();
            FAIL("Expected exception was not thrown");
        }
        catch (const std::runtime_error& e) {
            REQUIRE(std::string(e.what()) == "list is empty");
        }
    }
}

TEST_CASE("PushBack and PopBack combination", "[pushback][popback]") {
    List list;

    SECTION("PushBack then PopBack - LIFO order") {
        list.PushBack(10);
        list.PushBack(20);
        list.PushBack(30);

        REQUIRE(list.Size() == 3);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopBack() == 30);
        REQUIRE(list.Size() == 2);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopBack() == 20);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopBack() == 10);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("PushBack then PopBack interleaved") {
        list.PushBack(1);
        list.PushBack(2);
        REQUIRE(list.PopBack() == 2);
        REQUIRE(list.Size() == 1);

        list.PushBack(3);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopBack() == 3);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopBack() == 1);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("PushFront and PopFront combination", "[pushfront][popfront]") {
    List list;

    SECTION("PushFront then PopFront - LIFO order") {
        list.PushFront(10);
        list.PushFront(20);
        list.PushFront(30);

        REQUIRE(list.Size() == 3);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopFront() == 30);
        REQUIRE(list.Size() == 2);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopFront() == 20);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopFront() == 10);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("PushFront then PopFront interleaved") {
        list.PushFront(1);
        list.PushFront(2);
        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.Size() == 1);

        list.PushFront(3);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopFront() == 3);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopFront() == 1);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("Mixed PushBack and PopFront (FIFO)", "[pushback][popfront]") {
    List list;

    SECTION("PushBack then PopFront - FIFO order") {
        list.PushBack(10);
        list.PushBack(20);
        list.PushBack(30);

        REQUIRE(list.Size() == 3);

        REQUIRE(list.PopFront() == 10);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopFront() == 20);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopFront() == 30);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("Mixed PushFront and PopBack (FIFO)", "[pushfront][popback]") {
    List list;

    SECTION("PushFront then PopBack - FIFO order") {
        list.PushFront(10);
        list.PushFront(20);
        list.PushFront(30);

        REQUIRE(list.Size() == 3);

        REQUIRE(list.PopBack() == 10);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopBack() == 20);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopBack() == 30);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("Edge cases - single element", "[edge]") {
    List list;

    SECTION("Single element - PushFront then PopFront") {
        list.PushFront(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.PopFront() == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Single element - PushFront then PopBack") {
        list.PushFront(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.PopBack() == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Single element - PushBack then PopFront") {
        list.PushBack(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.PopFront() == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Single element - PushBack then PopBack") {
        list.PushBack(42);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.PopBack() == 42);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("Complex scenario - alternating operations", "[complex]") {
    List list;

    SECTION("Alternating PushFront and PushBack with pops") {
        list.PushBack(1);     // [1]
        list.PushFront(2);    // [2,1]
        list.PushBack(3);     // [2,1,3]
        list.PushFront(4);    // [4,2,1,3]

        REQUIRE(list.Size() == 4);
        REQUIRE(list.Empty() == false);

        REQUIRE(list.PopFront() == 4);
        REQUIRE(list.Size() == 3);

        REQUIRE(list.PopBack() == 3);
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.Size() == 1);

        REQUIRE(list.PopBack() == 1);
        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
    }

    SECTION("Complex interleaved operations") {
        list.PushBack(1);
        list.PushBack(2);
        list.PushFront(3);
        REQUIRE(list.PopFront() == 3);  // [1,2]
        list.PushBack(4);
        list.PushFront(5);
        REQUIRE(list.PopBack() == 4);   // [5,1,2]
        REQUIRE(list.PopFront() == 5);
        REQUIRE(list.PopFront() == 1);
        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.Empty() == true);
    }
}

TEST_CASE("Stress test - many operations", "[stress]") {
    List list;

    SECTION("Push 100 elements and pop all") {
        const int N = 100;

        for (int i = 0; i < N; ++i) {
            list.PushBack(i);
            REQUIRE(list.Size() == i + 1);
        }

        for (int i = N - 1; i >= 0; --i) {
            REQUIRE(list.PopBack() == i);
            REQUIRE(list.Size() == i);
        }

        REQUIRE(list.Empty() == true);
    }

    SECTION("Alternating front and back operations") {
        for (int i = 0; i < 50; ++i) {
            list.PushFront(i);
            list.PushBack(i * 2);
            REQUIRE(list.Size() == (i + 1) * 2);
        }

        // Проверяем, что элементы на месте
        REQUIRE(list.Size() == 100);
        REQUIRE(list.Empty() == false);

        // Очищаем список пополам
        for (int i = 0; i < 50; ++i) {
            list.PopFront();
            list.PopBack();
        }

        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }
}
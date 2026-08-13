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
    ListNode* prev; // указатель на предыдущий элемент списка
    ListNode* next; // указатель на следующий элемент списка
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


    TEST_CASE("List operations test", "[List]") {
        List list;

        // Тест Empty и Size для пустого списка
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        // Добавляем элементы
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);

        // Тест Empty и Size после добавления
        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 3);

        // Тест Clear
        list.Clear();
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);

        // Тест Clear на пустом списке (не должно падать)
        REQUIRE_NOTHROW(list.Clear());

        // Добавляем через PushFront
        list.PushFront(10);
        list.PushFront(20);
        REQUIRE(list.Empty() == false);
        REQUIRE(list.Size() == 2);

        // Очищаем через Pop
        list.PopFront();
        list.PopFront();
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
    }


#include <iostream>
#include <cassert>
#include "_Heap.h" 

void test_basic_operations() {
    std::cout << "Teste básico de inserção e extração\n";
    Heap heap(2);

    heap.insert(50, 1);
    heap.insert(40, 2);
    heap.insert(60, 3);

    assert(heap.extract_max().vertex == 3);
    assert(heap.extract_max().vertex == 1);
    assert(heap.extract_max().vertex == 2);
    assert(heap.is_empty());
}

void test_equal_capacities() {
    std::cout << "Teste com capacidades iguais\n";
    Heap heap(3);

    heap.insert(100, 1);
    heap.insert(100, 2);
    heap.insert(100, 3);

    int v1 = heap.extract_max().capacity;
    int v2 = heap.extract_max().capacity;
    int v3 = heap.extract_max().capacity;

    assert(v1 == 100 && v2 == 100 && v3 == 100);
    assert(heap.is_empty());
}

void test_updates() {
    std::cout << "Teste de updates\n";
    Heap heap(2);

    heap.insert(30, 1);
    heap.insert(20, 2);

    // increase key: 1 de 30 → 50
    heap.insert(50, 1);
    assert(heap.extract_max().vertex == 1);

    // update de valor menor: 2 de 20 → 10 (não afeta max-heap pois só aceita valor maior)
    heap.insert(10, 2); // já existe com 20, não atualiza pois 10 < 20 (se mantivermos a lógica atual que só atualiza se capacity > atual)

    // Por isso testamos com um novo increase válido:
    heap.insert(35, 2);
    assert(heap.extract_max().vertex == 2);
    assert(heap.is_empty());
}

void test_insert_extract_intercalated() {
    std::cout << "Teste de inserção e extração intercalada\n";
    Heap heap(2);

    heap.insert(30, 1);
    assert(heap.extract_max().vertex == 1);

    heap.insert(40, 2);
    heap.insert(50, 3);
    assert(heap.extract_max().vertex == 3);

    heap.insert(20, 4);
    assert(heap.extract_max().vertex == 2);
    assert(heap.extract_max().vertex == 4);
    assert(heap.is_empty());
}

void test_single_element() {
    std::cout << "Teste com heap de um elemento\n";
    Heap heap(2);
    heap.insert(99, 1);
    assert(!heap.is_empty());
    auto n = heap.extract_max();
    assert(n.vertex == 1 && n.capacity == 99);
    assert(heap.is_empty());
}

void test_different_k_values() {
    std::cout << "Teste com heaps de k-ário variado\n";

    for (int k = 2; k <= 5; ++k) {
        Heap heap(k);
        for (int i = 1; i <= 10; ++i)
            heap.insert(i * 10, i);

        int expected_capacity = 100;
        while (!heap.is_empty()) {
            auto n = heap.extract_max();
            assert(n.capacity == expected_capacity);
            expected_capacity -= 10;
        }
    }
}

void test_large_number_of_inserts() {
    std::cout << "Teste com grande número de inserções\n";
    Heap heap(3);
    const int N = 10000;

    for (int i = 1; i <= N; ++i)
        heap.insert(i, i);

    int expected_capacity = N;
    while (!heap.is_empty()) {
        auto n = heap.extract_max();
        assert(n.capacity == expected_capacity);
        --expected_capacity;
    }
    assert(expected_capacity == 0);
}

void run_all_tests() {
    test_basic_operations();
    test_equal_capacities();
    test_updates();
    test_insert_extract_intercalated();
    test_single_element();
    test_different_k_values();
    test_large_number_of_inserts();

    std::cout << "\n Todos os testes passaram!\n";
}

int main() {
    run_all_tests();
    return 0;
}

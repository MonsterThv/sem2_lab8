#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;


template <class It, class Out, class Compare = less<>>
Out merge(It a1, It b1, It a2, It b2, Out out, Compare cmp = Compare{}) {
    // Пока оба диапазона не пусты
    while (a1 != b1 && a2 != b2) {
        // Выбираем меньший элемент из двух диапазонов
        if (cmp(*a1, *a2)) {
            *out++ = *a1++;  // Берем из первого диапазона
        }
        else {
            *out++ = *a2++;  // Берем из второго диапазона
        }
    }

    // Дописываем оставшиеся элементы из первого диапазона
    out = copy(a1, b1, out);
    // Дописываем оставшиеся элементы из второго диапазона
    out = copy(a2, b2, out);

    return out;
}


template <class It, class Out, class Compare = less<>>
Out merge_sort(It a, It b, Out out, Compare cmp = Compare{}) {
    auto n = distance(a, b);

    // Базовый случай: диапазон из 0 или 1 элемента уже отсортирован
    if (n <= 1) {
        return copy(a, b, out);
    }

    // Находим середину диапазона
    auto m = a + n / 2;

    // Временные вектора для левой и правой частей
    vector<typename iterator_traits<It>::value_type> v1, v2;

    // Рекурсивно сортируем левую и правую части
    merge_sort(a, m, back_inserter(v1), cmp);
    merge_sort(m, b, back_inserter(v2), cmp);

    // Сливаем отсортированные части в выходной итератор
    return merge(v1.begin(), v1.end(), v2.begin(), v2.end(), out, cmp);
}


template <class It, class Compare = less<>>
void inplace_merge_sort(It a, It b, Compare cmp = Compare{}) {
    auto n = distance(a, b);

    // Базовый случай: диапазон из 0 или 1 элемента
    if (n <= 1) return;

    // Находим середину диапазона
    auto m = a + n / 2;

    // Рекурсивно сортируем левую и правую части
    inplace_merge_sort(a, m, cmp);
    inplace_merge_sort(m, b, cmp);

    // Сливаем отсортированные части на месте
    inplace_merge(a, m, b, cmp);
}


template <class It, class Compare = less<>>
void heap_sort(It a, It b, Compare cmp = Compare{}) {
    // Превращаем диапазон в кучу
    make_heap(a, b, cmp);

    // Извлекаем элементы из кучи в отсортированном порядке
    sort_heap(a, b, cmp);
}


template <class It, class Compare = less<>>
void quick_sort(It a, It b, Compare cmp = Compare{}) {
    // Базовый случай: диапазон из 0 или 1 элемента
    if (distance(a, b) <= 1) return;

    // Выбираем опорный элемент (середина диапазона)
    auto p = *next(a, distance(a, b) / 2);

    // Разделяем элементы на меньшие и большие опорного
    auto m1 = partition(a, b, [&](auto& x) { return cmp(x, p); });

    // Разделяем элементы на равные и большие опорного
    auto m2 = partition(m1, b, [&](auto& x) { return !cmp(p, x); });

    // Рекурсивно сортируем левую и правую части
    quick_sort(a, m1, cmp);
    quick_sort(m2, b, cmp);
}


template <class It, class Compare = less<>>
void insertion_sort(It a, It b, Compare cmp = Compare{}) {
    // Проходим по всем элементам начиная со второго
    for (auto i = a; i != b; ++i) {
        // Находим позицию для вставки текущего элемента
        // и сдвигаем элементы чтобы освободить место
        rotate(upper_bound(a, i, *i, cmp), i, next(i));
    }
}
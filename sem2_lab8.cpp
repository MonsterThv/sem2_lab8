#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;


template <class It, class Out, class Compare = less<>>
Out merge(It a1, It b1, It a2, It b2, Out out, Compare cmp = Compare{}) {
    // ���� ��� ��������� �� �����
    while (a1 != b1 && a2 != b2) {
        // �������� ������� ������� �� ���� ����������
        if (cmp(*a1, *a2)) {
            *out++ = *a1++;  // ����� �� ������� ���������
        }
        else {
            *out++ = *a2++;  // ����� �� ������� ���������
        }
    }

    // ���������� ���������� �������� �� ������� ���������
    out = copy(a1, b1, out);
    // ���������� ���������� �������� �� ������� ���������
    out = copy(a2, b2, out);

    return out;
}


template <class It, class Out, class Compare = less<>>
Out merge_sort(It a, It b, Out out, Compare cmp = Compare{}) {
    auto n = distance(a, b);

    // ������� ������: �������� �� 0 ��� 1 �������� ��� ������������
    if (n <= 1) {
        return copy(a, b, out);
    }

    // ������� �������� ���������
    auto m = a + n / 2;

    // ��������� ������� ��� ����� � ������ ������
    vector<typename iterator_traits<It>::value_type> v1, v2;

    // ���������� ��������� ����� � ������ �����
    merge_sort(a, m, back_inserter(v1), cmp);
    merge_sort(m, b, back_inserter(v2), cmp);

    // ������� ��������������� ����� � �������� ��������
    return merge(v1.begin(), v1.end(), v2.begin(), v2.end(), out, cmp);
}


template <class It, class Compare = less<>>
void inplace_merge_sort(It a, It b, Compare cmp = Compare{}) {
    auto n = distance(a, b);

    // ������� ������: �������� �� 0 ��� 1 ��������
    if (n <= 1) return;

    // ������� �������� ���������
    auto m = a + n / 2;

    // ���������� ��������� ����� � ������ �����
    inplace_merge_sort(a, m, cmp);
    inplace_merge_sort(m, b, cmp);

    // ������� ��������������� ����� �� �����
    inplace_merge(a, m, b, cmp);
}


template <class It, class Compare = less<>>
void heap_sort(It a, It b, Compare cmp = Compare{}) {
    // ���������� �������� � ����
    make_heap(a, b, cmp);

    // ��������� �������� �� ���� � ��������������� �������
    sort_heap(a, b, cmp);
}


template <class It, class Compare = less<>>
void quick_sort(It a, It b, Compare cmp = Compare{}) {
    // ������� ������: �������� �� 0 ��� 1 ��������
    if (distance(a, b) <= 1) return;

    // �������� ������� ������� (�������� ���������)
    auto p = *next(a, distance(a, b) / 2);

    // ��������� �������� �� ������� � ������� ��������
    auto m1 = partition(a, b, [&](auto& x) { return cmp(x, p); });

    // ��������� �������� �� ������ � ������� ��������
    auto m2 = partition(m1, b, [&](auto& x) { return !cmp(p, x); });

    // ���������� ��������� ����� � ������ �����
    quick_sort(a, m1, cmp);
    quick_sort(m2, b, cmp);
}


template <class It, class Compare = less<>>
void insertion_sort(It a, It b, Compare cmp = Compare{}) {
    // �������� �� ���� ��������� ������� �� �������
    for (auto i = a; i != b; ++i) {
        // ������� ������� ��� ������� �������� ��������
        // � �������� �������� ����� ���������� �����
        rotate(upper_bound(a, i, *i, cmp), i, next(i));
    }
}
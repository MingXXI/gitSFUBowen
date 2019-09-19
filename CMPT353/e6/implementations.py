# -*- coding: utf-8 -*-

import numpy as np


def builtin(arr):
    """
    Just in case you're interested, sompare the built-in NumPy sort.
    """
    return np.sort(arr, kind='quicksort')


def qs1(arr):
    """
    Quicksort the array by partitioning using NumPy mask indexing: requires three passes through array.
    """
    if arr.shape[0] < 30:
        return insertion(arr)

    pivot = np.random.choice(arr)

    sm = arr[arr < pivot]
    sm = qs1(sm)
    
    eq = arr[arr == pivot]
    
    lg = arr[arr > pivot]
    lg = qs1(lg)
    
    return np.concatenate((sm, eq, lg))


def qs2(arr):
    """
    Quicksort by building dynamically-sized Python lists of values, in one pass.
    """
    if arr.shape[0] < 30:
        return insertion(arr)

    pivot = np.random.choice(arr)

    sm = []
    eq = []
    lg = []
    for x in arr:
        if x < pivot:
            sm.append(x)
        elif x > pivot:
            lg.append(x)
        else:
            eq.append(x)
    
    sm = qs2(np.array(sm, dtype=arr.dtype))
    lg = qs2(np.array(lg, dtype=arr.dtype))
    return np.concatenate((sm, np.array(eq, dtype=arr.dtype), lg))


def qs3(arr):
    """
    Quicksort by building statically-sized NumPy arrays, to avoid allocation+conversion overhead.
    """
    if arr.shape[0] < 30:
        return insertion(arr)

    pivot = np.random.choice(arr)

    sm = np.empty(arr.shape, dtype=arr.dtype)
    eq = np.empty(arr.shape, dtype=arr.dtype)
    lg = np.empty(arr.shape, dtype=arr.dtype)
    n_sm = n_eq = n_lg = 0
    for x in arr:
        if x < pivot:
            sm[n_sm] = x
            n_sm += 1
        elif x > pivot:
            lg[n_lg] = x
            n_lg += 1
        else:
            eq[n_eq] = x
            n_eq += 1
    
    sm = sm[:n_sm]
    eq = eq[:n_eq]
    lg = lg[:n_lg]
    
    sm = qs2(sm)
    lg = qs2(lg)
    return np.concatenate((sm, eq, lg))


def qs4(arr):
    """
    Quicksort in-place with Lomuto partitioning (after initially copying the input array).
    """
    def qs_inplace(arr, st, en):
        # Sort arr[st:en] in-place.
        if en - st <= 20:
            insertion_inplace(arr[st:en])
            return

        piv = np.random.randint(st, en-1)
        pivot = arr[piv]
        # stash the pivot at the end, so Lomuto partitioning works
        arr[piv], arr[en-1] = arr[en-1], arr[piv]
        
        i = st - 1
        for j in range(st, en):
            if arr[j] <= pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]

        qs_inplace(arr, st, i)
        qs_inplace(arr, i, en)
        
    
    arr = np.copy(arr)
    qs_inplace(arr, 0, arr.shape[0])
    return arr



def qs5(arr):
    """
    Quicksort in-place with Hoare paritioning (after initially copying the input array).
    """
    def qs_inplace(arr, st, en):
        if en - st <= 25:
            insertion_inplace(arr[st:en])
            return

        piv = np.random.randint(st, en-1)
        pivot = arr[piv]

        # move pivot to list[st]
        arr[piv], arr[st] = arr[st], arr[piv]

        # Hoare partition arr[(st+1):en] around the pivot
        left = st + 1
        right = en - 1
        while True:
            while left < en and arr[left] <= pivot:
                left += 1
            while right >= st and arr[right] >= pivot:
                right -= 1

            if left >= right:
                break

            arr[left], arr[right] = arr[right], arr[left]

        pivloc = left - 1
        arr[st], arr[pivloc] = arr[pivloc], arr[st]

        qs_inplace(arr, st, pivloc)
        qs_inplace(arr, pivloc+1, en)

    arr = np.copy(arr)
    qs_inplace(arr, 0, arr.shape[0])
    return arr


def merge1(arr):
    """
    Mergesort the array
    """
    if arr.shape[0] < 10:
        return insertion(arr)
    
    n = len(arr)
    half = n // 2
    otherhalf = n - half
    left = merge1(arr[:half])
    right = merge1(arr[half:])
    
    res = np.empty(arr.shape, dtype=arr.dtype)
    l = r = i = 0
    while True:
        if l < half and ((r < len(right) and left[l] < right[r]) \
                or (r >= otherhalf)):
            # i.e. (check both and left smaller) or (still left but done right)
            res[i] = left[l]
            l += 1
            i += 1
        elif r < otherhalf:
            # i.e. still things in right (but left is empty or larger)
            res[i] = right[r]
            r += 1
            i += 1
        else:
            # both are done
            break
        
    return res


def partition_sort(arr):
    """
    An idyllic variant of quicksort, powered by numpy.partition.
    """
    if arr.shape[0] < 2:
        return arr
    
    mid = arr.shape[0] // 2
    partitioned = np.partition(arr, mid)
    
    sm = partition_sort(partitioned[:mid])
    lg = partition_sort(partitioned[(mid+1):])
    
    return np.concatenate((sm, partitioned[mid:(mid+1)], lg))


def insertion(arr):
    arr = np.copy(arr)
    insertion_inplace(arr)
    return arr


def insertion_inplace(arr):
    n = len(arr)
    for i in range(n):
        j = i
        while j > 0 and arr[j-1] > arr[j]:
            arr[j-1], arr[j] = arr[j],  arr[j-1]
            j -= 1


all_implementations = [qs1, qs2, qs3, qs4, qs5, merge1, partition_sort]


# Tests that run if you call this .py as a script.
from collections import Counter
import unittest
class TestSorts(unittest.TestCase):
    def _is_sorted(self, l):
        # from http://stackoverflow.com/a/3755251/6871666
        return all(l[i] <= l[i + 1] for i in range(len(l) - 1))

    def _test_impl(self, sort, arr, orig_arr):
        input_counts = Counter(arr)
        result = sort(arr)
        self.assertTrue(np.array_equal(arr, orig_arr), '%s modified input' % (sort))
        self.assertTrue(self._is_sorted(result), "%s didn't correctly sort\n%s\n%s" % (sort, arr, result))
        self.assertEqual(input_counts, Counter(result), "%s didn't preserve the elements" % (sort))
        self.assertIsInstance(result, np.ndarray)
        self.assertEqual(result.shape, orig_arr.shape)
        self.assertEqual(result.dtype, orig_arr.dtype, "%s changed types" % (sort))

    def _test_arr(self, arr):
        orig_arr = np.copy(arr)
        for sort in all_implementations + [insertion]:
            self._test_impl(sort, arr, orig_arr)

    def test_helpers(self):
        n = 40
        for i in range(5):
            arr = np.random.randint(10000, 100 * n + 10000, size=(n,))
            a2 = insertion(arr)
            self.assertTrue(self._is_sorted(a2))

            insertion_inplace(arr)
            self.assertTrue(self._is_sorted(arr))

    def test_implementations(self):
        n = 100
        for i in range(5):
            self._test_arr(np.random.randint(10000, 100 * n + 10000, size=(n,)))
            self._test_arr(np.random.randint(10000, n + 10000, size=(10 * n,)))
        self._test_arr(np.arange(10, dtype=np.int32))
        self._test_arr(np.ones(shape=(10,), dtype=np.int32))
        self._test_arr(np.ones(shape=(1,), dtype=np.int32))
        self._test_arr(np.ones(shape=(0,), dtype=np.int32))


if __name__ == '__main__':
    unittest.main()
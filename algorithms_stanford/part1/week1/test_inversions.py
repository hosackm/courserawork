from inversions import ninv


def test_mergesort():
    t = [1, 3, 5, 7, 2, 4, 6]
    merged, n = ninv(t)
    assert merged == list(range(1, 8))


def test_inversions():
    # inversions (3, 2) (5, 2) (5, 4)
    t = [1, 3, 5, 2, 4, 6]
    merged, n = ninv(t)
    assert n == 3

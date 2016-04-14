from inversions import ninv


def test_mergesort():
    t = [1, 3, 5, 7, 2, 4, 6]
    merged, n = ninv(t)
    assert merged == list(range(1, 8))


def test_inversions():
    # inversions (3, 2) (5, 2) (5, 4)
    t = [1, 3, 5, 2, 4, 6]
    _, n = ninv(t)
    assert n == 3


def test_inversions_odd():
    t = [1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 11]
    _, n = ninv(t)
    assert n == 10

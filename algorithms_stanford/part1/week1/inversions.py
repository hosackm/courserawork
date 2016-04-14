def ninv(arr):
    if len(arr) < 2:
        return arr, 0

    def merge(l, r):
        tmp = []
        n = 0

        while l and r:
            if l[0] < r[0]:
                tmp.append(l.pop(0))
            else:
                n += len(l)
                tmp.append(r.pop(0))

        tmp.extend(l + r)

        return tmp, n

    mid = len(arr) // 2

    left, nl = ninv(arr[:mid])
    right, nr = ninv(arr[mid:])
    merged, nm = merge(left, right)

    return merged, nm+nl+nr

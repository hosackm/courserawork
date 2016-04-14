def ninv(arr):
    def mergesort(arr):
        def merge(l, r):
            tmp = []
            n = 0

            while l and r:
                if l[0] < r[0]:
                    tmp.append(l.pop(0))
                else:
                    tmp.append(r.pop(0))
                    n += len(l)

            tmp.extend(l + r)

            print("Adding", n)
            return tmp, n
            # end of merge()
        if len(arr) < 2:
            return arr, 0

        mid = len(arr) // 2

        left, nl = mergesort(arr[:mid])
        right, nr = mergesort(arr[mid:])
        merged, nm = merge(left, right)

        return merged, nm+nl+nr
        # end of mergesort()
    return mergesort(arr)

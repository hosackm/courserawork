import sys
from inversions import ninv


def main(fn):
    lines = []
    with open(fn, "r") as f:
        for line in f:
            lines.append(int(line))
    merged, n = ninv(lines)
    print(n, "inversions")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please pass a filename")
        sys.exit()
    main(sys.argv[1])

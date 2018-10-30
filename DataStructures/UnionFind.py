class UnionFind:
    def __init__(self, size):
        self.data = [-1]*size

    def get_root(self, x):
        if self.data[x] < 0: return x
        else: self.data[x] = self.get_root(self.data[x])
        return self.data[x]

    def unite_set(self, x, y):
        x = self.get_root(x)
        y = self.get_root(y)
        if x != y:
            if self.data[y] < self.data[x]:
                self.data[x], self.data[y] = self.data[x], self.data[y]
            self.data[x] += self.data[y]
            self.data[y] = x

    def is_same(self, x, y):
        return self.get_root(x) == self.get_root(y)

    def get_size(self, x):
        return -self.data[self.get_root(x)]

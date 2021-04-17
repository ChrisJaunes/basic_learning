a = 1
print(a, type(a), abs(a))
b = -1.0
print(b, type(b), abs(b))
c = 2+0j
print(c, type(c), abs(c))
class X:
    def __init__(self, _x):
        self._x = _x

    def __abs__(self) :
        if self._x < 0 : return -self._x
        return self._x


d = X(-2)
print(d, type(d), abs(d))

#include "Five.h"


bool Five::isFivSys (unsigned char c) const {
    return (c >= '0' and c < BASE);
}

Five::Five(): _size(0), _array{nullptr} {}

Five::Five(const std::size_t &n, unsigned char t) {
    _array = new unsigned char[n];
    _size = n;
    for (int i = n - 1; i >= 0; --i) {
        if (isFivSys(t)) _array[i] = t;
        else throw std::invalid_argument("Fill constructor: symbol is not in correct place");
    }
}

Five::Five(const std::initializer_list<unsigned char> &t) {
    _array = new unsigned char[t.size()];
    _size = t.size();
    std::size_t i {t.size() - 1};
    for (unsigned char c : t) {
        if (isFivSys(c)) _array[i--] = c;
        else throw std::invalid_argument("Init list constuctor: symbol is not in correct place");
    }
}

Five::Five(const std::string &str) {
    int ind = 0;
    while (str[ind] == '0' and str.size() - 1 > ind) ind++;

    _size = str.size() - ind;
    _array = new unsigned char [_size];

    for (int i = _size - 1; i >= 0; i--) {
        if (isFivSys(str[ind])) {
            _array[i] = str[ind];
            ind++;
        }
        else throw std::invalid_argument("Copy String constructor: symbol is not in correct place");
    }
}


Five::Five(const Five &other) {
    _size = other._size;
    _array = new unsigned char[_size];

    for(std::size_t i{0}; i < _size; ++i) _array[i] = other._array[i];
}

Five::Five(Five &&other) noexcept {
    _size = other._size;
    _array = other._array;

    other._size = 0;
    other._array = nullptr;
}

Five::~Five() noexcept {
    if (_size > 0) {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}

bool Five::operator> (const Five &other) const {
    if (_size > other._size) return true;
    else if (_size ==other._size) {
        for (int i = _size - 1; i >= 0; i--) {
            if (_array[i] > other._array[i]) return true;
        }
    }
    return false;
}

bool Five::operator== (const Five &other) const {
    if (_size == other._size) {
        for (int i = 0; i < _size; i++) {
            if (_array[i] != other._array[i]) return false;
        }
        return true;
    } else {
        return false;
    }
}

bool Five::operator!= (const Five &other) const {
    return (!(*this == other));
}

bool Five::operator>= (const Five &other) const {
    return (*this > other or *this == other);
}

bool Five::operator< (const Five &other) const {
    return (!(*this >= other));
}

bool Five::operator<= (const Five &other) const {
    return(!(*this > other));
}


Five Five::operator+ (const Five &other) const {
    Five res;
    res._size = (this -> _size < other._size) ? other._size : this -> _size;
    res._array = new unsigned char[res._size];

    int val = 0, mod = 0, i = 0;
    for (i = 0; i < res._size; i++) {
        if (i < _size) val += this -> _array[i] - '0';
        if (i < other._size) val += other._array[i] - '0';
        val += mod;
        mod = val % (BASE - '0');
        res._array[i] = mod + '0';
        mod = val / (BASE - '0');
        val = 0;
    }
    if (mod != 0) {
        unsigned char* arrtemp = new unsigned char[res._size + 1];

        for (i = 0; i < res._size; i++) {
            arrtemp[i] = res._array[i];
        }
        arrtemp[i] = mod + '0';
        delete [] res._array;
        res._array = arrtemp;
        res._size++;
    }
    return res;
}

Five Five::operator- (const Five &other) const {
    Five res;
    int val, mod = 0;
    if (*this == other) {
        res._size = 1;
        res._array = new unsigned char[res._size];
        res._array[0] = '0';
        return res;
    }
    if (*this > other) {
        res._size = _size;
        res._array = new unsigned char[res._size];
        for (int i = 0; i < _size; i++) {
            if (i < other._size) {
                if (_array[i] >= other._array[i]) {
                    val = _array[i] - other._array[i] + mod + '0';
                    mod = 0;
                } else {
                    val = _array[i] - other._array[i] + mod + BASE + '0';
                    mod = -1;
                }
                res._array[i] = val;
            } else {
                res._array[i] = _array[i] + mod;
            }
        }

        if (res._array[res._size - 1] == '0') {
            int ind = res._size - 1;
            while (res._array[ind] == '0' and ind > 0) {
                ind--;
            }
            ind = res._size - ind - 1;
            unsigned char* arrtemp = new unsigned char[res._size - ind];
            for (int i = 0; i < res._size - ind; i++) {
                arrtemp[i] = res._array[i];
            }
            res._size -= ind;
            delete [] res._array;
            res._array = arrtemp;
        }

        return res;
    } else throw std::invalid_argument("First numb is less than second");
}

Five Five::operator= (const Five &other) {
    delete [] _array;
    _size = other._size;
    _array = new unsigned char [_size];
    for (int i = 0; i < _size; i++) {
        _array[i] = other._array[i];
    }

    return *this;
}

Five Five::operator+= (const Five &other) {
    *this = *this + other;
    return *this;
}

Five Five::operator-= (const Five &other) {
    *this = *this - other;
    return *this;
}

std::size_t Five::getsize() const noexcept {
    return _size;
}

unsigned char* Five::getarray() const noexcept {
    return _array;
}

std::ostream& operator<< (std::ostream& os, const Five &obj) {
    for (int i = obj.getsize() - 1; i >= 0; i--) {
        os << obj.getarray()[i];
    }
    return os;
}

#pragma once

#include <iostream>
#include <string>

class Five {
    public:

        Five();
        Five(const std::size_t &n, unsigned char t = 0);
        Five(const std::initializer_list<unsigned char> &t);
        Five(const std::string &t);
        Five(const Five& other);
        Five(Five&& other) noexcept;
        virtual ~Five() noexcept;

        bool operator> (const Five &other) const;
        bool operator< (const Five &other) const;
        bool operator== (const Five &other) const;
        bool operator!= (const Five &other) const;
        bool operator>= (const Five &other) const;
        bool operator<= (const Five &other) const;
        bool operator+= (const Five &other) const;
        bool operator-= (const Five &other) const;

        Five operator+ (const Five &other) const;
        Five operator- (const Five &other) const;
        Five operator= (const Five &other);
        Five operator+= (const Five &other);
        Five operator-= (const Five &other);

        friend std::ostream& operator<< (std::ostream &os, const Five &obj);

        std::size_t getsize() const noexcept;
        unsigned char* getarray() const noexcept;

        private:

        const unsigned char BASE {'5'};
        std::size_t _size;
        unsigned char* _array;
        bool isFivSys (unsigned char c) const;

};


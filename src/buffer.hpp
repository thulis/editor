#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>

// FIXME: Rule of 3/5
class GapBuffer
{
private:
    char* data;
    uint32_t size;
    uint32_t gap_size;
    mutable char* gap_start;
    mutable char* gap_end;
public:
    explicit GapBuffer(uint32_t);
    ~GapBuffer();
public:
    void resize(uint32_t);
    void move(uint32_t) const;
    void left(uint32_t) const;
    void right(uint32_t) const;
    void insert(char) noexcept;
    void del() noexcept;
    void print() const noexcept;

    const char* get_ptr() const noexcept;

    inline int32_t gap_start_pos();
    inline int32_t gap_end_pos();
};

#endif

#include <iostream>
#include <cstring>

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
    explicit GapBuffer(uint32_t _size)
        : size(_size), gap_size(_size)
    {
        char* _data = new char[_size];
        // TODO: use exceptions
        if (_data == nullptr) {
            std::cerr << "Error creating gap buffer!\n";
            exit(1);
        }
        this->data = _data;
        this->gap_start = _data;
        this->gap_end = _data + _size * sizeof(char);
    }

    ~GapBuffer()
    {
        delete[] this->data;
    }
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

const char* GapBuffer::get_ptr() const noexcept
{
    return static_cast<const char*>(this->data);
}

// TODO: error handling (gap should stay inside bounds, e.g. gap_start should 
// never be ==size, expect for it's 0 of course)
void GapBuffer::left(uint32_t amount) const
{
    size_t n = amount * sizeof(char);
    std::memcpy(this->gap_end - n, this->gap_start - n, amount);
    this->gap_end -= n;
    this->gap_start -= n;
}

// TODO: error handling
void GapBuffer::right(uint32_t amount) const
{
    size_t n = amount * sizeof(char);
    std::memcpy(this->gap_start + n, this->gap_end + n, amount);
    this->gap_end += n;
    this->gap_start += n;
}

void GapBuffer::insert(char character) noexcept
{
    *(this->gap_start) = character;
    this->gap_start++;
    this->gap_size--;
}

void GapBuffer::del() noexcept
{
    // gap simply swallows the character so it doesn't get rendered anymore
    // there's no point in overriding it...
    this->gap_start--;
    this->gap_size++;
}

void GapBuffer::print() const noexcept
{
    // part before gap
    ptrdiff_t end = (char*)(this->gap_start) - (char*)(this->data);
    printf("%.*s", (int)end, this->data);
    // part after gap
    ptrdiff_t end2 = (char*)(this->data + this->size * sizeof(char)) - (char*)(this->gap_end);
    printf("%.*s\n", (int)end2, this->gap_end);
}

// TODO: proper error handling
//       - update gap size
//       - expand gap to fit
void GapBuffer::resize(uint32_t factor)
{
    uint
    void* new_buff = std::realloc(this->data, (size_t)(this->size * factor));
    if (new_buff == nullptr) {
        std::cerr << "Error reallocating gap buffer!\n";
        exit(1);
    }
    this->data = static_cast<char*>(new_buff);
}

// TODO: error handling
void GapBuffer::move(uint32_t position) const
{
    ptrdiff_t diff = (char*)(this->gap_start) - (char*)(this->data);
    uint32_t gap_pos = diff;
    gap_pos < position ? this->right(position-gap_pos) : this->left(gap_pos-position);
}

int main(void)
{
    GapBuffer buff{20};
    buff.insert('a');
    buff.insert('b');
    buff.insert('c');
    buff.insert('d');
    buff.insert('e');
    buff.insert('f');
    buff.insert('g');
    buff.insert('h');
    buff.insert('i');
    buff.insert('\0');
    buff.print();
    buff.move(1);
    buff.del();
    buff.print();
    return 0;
}

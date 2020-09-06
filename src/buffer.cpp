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
        void* _data = std::malloc(_size * sizeof(char));
        // TODO: use exceptions
        if (_data == nullptr) {
            std::cerr << "Error creating gap buffer!\n";
            exit(1);
        }
        this->data = static_cast<char*>(_data);
        this->gap_start = this->data;
        this->gap_end = this->data + _size * sizeof(char);
    }

    ~GapBuffer()
    {
        std::free(this->data);
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
    if (this->gap_size <= 2) this->resize(20);
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
void GapBuffer::resize(uint32_t increase)
{
    ptrdiff_t _gap_start = this->gap_start - this->data;
    ptrdiff_t _gap_end = this->gap_end - this->data;
    void* new_buff = std::realloc(this->data, this->size + increase);
    if (new_buff == nullptr) {
        std::cerr << "Error reallocating gap buffer!\n";
        exit(1);
    }
    this->data = static_cast<char*>(new_buff);
    // update gap start and end position 
    this->gap_start = this->data + _gap_start;
    this->gap_end = this->data + _gap_end;

    // amount of elements that need to be copied over
    ptrdiff_t amount = (this->data + this->size * sizeof(char)) - this->gap_end;
    //std::cout << "amount is: " << amount << "\n";
    // update size of buffer
    this->size += increase;
    // where to copy the characters
    char* dst = (this->data + this->size * sizeof(char)) - amount;
    // do the copy
    std::memmove(dst, this->gap_end+1, (int)amount);
    // update members
    // update only gap end, since we don't know anything about gap_start, gap size might not even be 0
    this->gap_end = dst - 1;
    this->gap_size += increase;
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
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    buff.move(1);
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    buff.move(2);
    for (int i = 'a'; i < 'z'; i++) buff.insert((char)i);
    buff.insert('\0');
    buff.print();
    return 0;
}

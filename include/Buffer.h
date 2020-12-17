#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>

#include "Mode.h"

namespace buffer {
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
        virtual ~GapBuffer();
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

    template<class BMode>
    struct BufferSettings
    {
        BufferSettings(uint32_t size, BMode& bmode)
            : textsize(size), mode(bmode)
        {}
        //  size of the gap buffer
        uint32_t textsize;
        // mode the buffer should be initialized with
        BMode& mode;
    };

    template<class mode>
    class Buffer : public GapBuffer
    {
    private:
        mode _mode;
    public:
        Buffer(buffer::BufferSettings<mode>& settings)
            : buffer::GapBuffer { settings.textsize },
            _mode(settings.mode)
        {
            this->_mode.init();
        }

        virtual ~Buffer()
        {
            this->_mode.exit();
        }
    };
}
#endif

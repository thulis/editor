#ifndef __MODE_H_
#define __MODE_H_

namespace mode {
    // TODO: as interface
    class Mode
    {
    public:
        virtual void init() const = 0;
        virtual void exit() const = 0;
    };

    class Normal : public Mode
    {
    public:
        explicit Normal();
        ~Normal();

        void init() const override;
        void exit() const override;
    };
}
#endif // __MODE_H_

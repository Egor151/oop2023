#ifndef OOP2_SIGNALER_H
#define OOP2_SIGNALER_H

#include <string>
#include <stdexcept>

namespace Prog2 {
    class Signaler {
    private:
        bool signal;
        int duration;

    public:
        explicit Signaler(bool level, int dur);
        explicit Signaler(const std::string &signal);
        explicit Signaler();

        // Setters
        void setSignal(const std::string &signal);
        void setDuration(int duration);
        void setLevel(bool level);

        // Getters
        bool getSignal() const;
        int getDuration() const;

        void operator~();
        void extendSignal(int units);
        void shortenSignal(int units);
        std::string formatSignal() const;
    };
}
#endif // OOP2_SIGNALER_H
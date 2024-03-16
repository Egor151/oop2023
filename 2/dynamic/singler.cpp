#include "singler.h"
#include <stdexcept>
#include <string>

namespace Prog2 {
    /**
         * @brief Constructor with parameters. Creates a signal with a specified level and duration.
         * @param level Signal level (0 or 1).
         * @pura dur Signal duration.
         */
    Signaler::Signaler(bool level, int dur) : signal(level), duration(dur) {
    }
    /**
         * @brief Default constructor. Creates a signal with level 0 and duration 0.
         */
    Signaler::Signaler() : signal(false), duration(0) {}

    /**
        * @brief Constructor that takes a string as a parameter and interprets it as a signal.
        * @param sig String representing the signal (sequence 0 and 1).
        */
    Signaler::Signaler(const std::string &sig) {
        if (sig.empty()) {
            throw std::invalid_argument(
                    "Invalid signal format. Expected a sequence of 0 or 1.");
        }
        signal = (sig[0] != '0');
        duration = 1;
        for (int i = 1; i < static_cast<int>(sig.length()); i++) {
            if ((sig[i] == '1') == signal) {
                duration++;
            } else {
                break;
            }
        }
    }

    /**
         * @brief Signal inversion operator.
         */
    void Signaler::operator~() {
        signal = !signal;
    }

    /**
         * @brief Increases the duration of the signal by a specified number of units.
         * @param units The number of units by which the duration increases.
         */
    void Signaler::extendSignal(int units) {
        if (units > 0) {
            duration += units;
        } else {
            throw std::invalid_argument("Invalid units. Expected a positive value.");
        }
    }

    /**
         * @brief Reduces the duration of the signal by a specified number of units.
         * @param units The number of units by which the duration is reduced.
         */
    void Signaler::shortenSignal(int units) {
        if (units < duration) {
            duration -= units;
        } else {
            throw std::invalid_argument(
                    "Invalid units. Cannot shorten signal beyond its duration.");
        }
    }

    /**
         * @brief Returns a formatted representation of the signal as a string.
         * '-' represents level 1, and '_' represents level 0.
         * @return Formatted representation of the signal.
         */
    std::string Signaler::formatSignal() const {
        std::string formattedSignal;
        for (int i = 0; i < duration; i++) {
            if (signal) {
                formattedSignal += "-";
            } else {
                formattedSignal += "_";
            }
        }
        return formattedSignal;
    }

    /**
         * @brief Sets a new signal value based on the passed string.
         * @param signal String representing the new signal value.
         */
    void Signaler::setSignal(const std::string &signal) {// присвоение
        Signaler newSignal(signal);
        *this = newSignal;
    }

    /**
         * @brief Sets a new signal value based on the passed string.
         * @param signal String representing the new signal value.
         */
    void Signaler::setDuration(int dur) {
        if (dur >= 0) {
            duration = dur;
        } else {
            throw std::invalid_argument(
                    "Invalid duration. Expected a non-negative value.");
        }
    }

    /**
         * @brief Sets a new signal level.
         * @param level New signal level (0 or 1).
         */
    void Signaler::setLevel(bool level) {
        if (level == 0 || level == 1) {
            signal = level;
            duration = 1;
        } else {
            throw std::invalid_argument("Invalid signal level. Expected 0 or 1.");
        }
    }

    /**
         * @brief Returns the current duration of the signal.
         * @return The current duration of the signal.
         */
    int Signaler::getDuration() const { return duration; }

    /**
         * @brief Returns the current signal strength.
         * @return The current signal strength (0 or 1).
         */
    bool Signaler::getSignal() const { return signal; }

    /**
         * @brief Overload of the input operator to read the signal from the input stream.
         * @param is the input stream.
         * @param signal The Signaler object for reading the signal.
         * @return The input stream after reading the signal.
         */
    std::istream& operator>>(std::istream& is, Signaler& signal) {
        std::string input;
        is >> input;
        signal.setSignal(input);
        return is;
    }

} // namespace Prog2
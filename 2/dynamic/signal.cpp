#include "signal.h"
#include <stdexcept>
#include <string>

namespace Prog3 {
    /**
        *  @brief Default constructor for the Signal class.
        */
    Signal::Signal() = default;

    /**
         * @brief Constructor for creating a signal with a given duration.
         * @param level Signal level (0 or 1).
         * @param duration Signal duration.
         */
    Signal::Signal(bool level, int duration) : Signal() {
        for (int i = 0; i < duration; i++) {
            signalArray.push_back(Prog2::Signaler(level,1)); // Создаем объекты Signaler
        }
    }

    /**
         * @brief Constructor for creating a signal based on a string of characters.
         * @param signalString String of characters representing the signal (e.g., "101010").
         */
    Signal::Signal(const std::string &signalString) : Signal() {
        for (char i: signalString) {
            if (i == '1') {
                signalArray.push_back(Prog2::Signaler(true, 1));
            } else {
                signalArray.push_back(Prog2::Signaler(false, 1));
            }
        }
    }

    /**
         * @brief Destructor for the Signal class.
         */
    Signal::~Signal() {
        signalArray.clear();
    }

    /**
            * @brief Prints the signal as a string (e.g., "101010").
            */
    void Signal::printSignal() {
        for (int i = 0; i < signalArray.size(); i++) {
            std::cout << signalArray[i].getSignal(); // Используем оператор разыменования для доступа к объекту Signaler
        }
    }

    /**
         * @brief Inverts the signal level at all time points.
         */
    void Signal::invertSignal() {
        for (int i = 0; i < signalArray.size(); i++) {
            ~signalArray[i]; // Используем оператор разыменования для доступа к объекту Signaler
        }
    }

    /**
         * @brief Adds another signal to the current signal (+= operator).
         * @param otherSignal The other signal to add.
         */
    void Signal::operator+=( Signal &otherSignal) {
        for (int i = 0; i < otherSignal.getLength(); i++) {
            signalArray.push_back(otherSignal.signalArray[i]);
        }
    }

    /**
         * @brief Inserts another signal at a specified time point.
         * @param otherSignal The other signal to insert.
         * @param position The position at which to insert the signal.
         */
    void Signal::insertSignal( Signal &otherSignal, int position) {
        if (position < 0 || position >= (signalArray.size())) {
            throw std::invalid_argument("Invalid position!");
        }
        for (auto i = 0; i < otherSignal.getLength(); ++i) {
            signalArray.insert(signalArray.begin() + 1 + position++, otherSignal.signalArray[i]);
        }
    }

    /**
         * @brief Duplicates the signal a specified number of times (*= operator).
         * @param times The number of times to duplicate the signal.
         */
    void Signal::operator*=(int times) {
        std::size_t size = signalArray.size();
        for (int i = 0; i < (times - 1); i++) {
            for (std::size_t j = 0; j < size; j++) {
                signalArray.push_back(signalArray[j]);
            }
        }
    }

    /**
         * @brief Deletes a segment of the signal at a specified time point and duration.
         * @param start The starting position for deletion.
         * @param duration The duration of the segment to delete.
         */
    void Signal::deleteSignal(int start, int duration) {
        if (start < 0 || start >= static_cast<int>(signalArray.size()) || duration < 0 ||
            duration >= static_cast<int>(signalArray.size())) {
            throw std::invalid_argument("Invalid start position or duration!");
        }
        for (auto i = 0; i < duration; ++i) {
            signalArray.erase(signalArray.begin() + start);
        }
    }

    /**
        * @brief Formatting the signal as a string using the characters \ and /.
        * @return Formatted signal string.
        */
    std::string Signal::formatSignal()  {
        std::string formattedSignal;
        int size = signalArray.size();
        for (int i = 0; i < size - 1; i++) {
            formattedSignal += signalArray[i].formatSignal();
            if ((*this)[i] == "1" && (*this)[i + 1] == "0") formattedSignal += R"(\)";
            else if ((*this)[i] == "0" && (*this)[i + 1] == "1") formattedSignal += "/";
        }
        formattedSignal += signalArray[size - 1].formatSignal();
        return formattedSignal;
    }

    /**
         * @brief Setting a signal based on a string of characters.
         * @param signalString A string of characters representing the signal.
         */
    void Signal::setSignal(const std::string &signalString) {
        signalArray.clear();
        for (char i: signalString) {
            if (i == '1') {
                signalArray.push_back(Prog2::Signaler(true,1));
            } else {
                signalArray.push_back(Prog2::Signaler(false,1));
            }
        }
    }

    /**
        * @brief Getting the signal length.
        * @return Signal length.
        */
    int Signal::getLength() const {
        return static_cast<int>(signalArray.size());
    }

    /**
         * @brief Getting the signal level at a given time ([] operator).
         * @param i Position in the signal.
         * @return Signal strength (line "0" or "1").
         */
    std::string Signal::operator[](int i) {
        if (i < 0 || i >= static_cast<int>(signalArray.size())) {
            throw std::invalid_argument("Invalid index!");
        }
        return signalArray[i].getSignal() ? "1" : "0";
    }

    /**
        * @brief Assignment operator for the Signal class.
        * @param other Another Signal object.
        * @return A reference to the current Signal object after assignment.
        */
    Signal& Signal::operator=(const Signal& other) {
        if (this == &other) {
            return *this;
        }
        signalArray = other.signalArray;
        return *this;
    }

    /**
         * @brief Insert operator (>>) to read the signal from the stream.
         * @param is the input stream.
         * @param signal Reference to the Signal object.
         * @return A reference to the input stream after reading the signal.
         */
    std::istream& operator>>(std::istream& is, Signal& signal) {
        std::string input;
        is >> input;
        Signal tempSignal(input);
        signal += tempSignal;
        return is;
    }

    /**
        * @brief Extraction operator (<<) to output the signal to the stream.
        * @palm os Output stream.
        * @param signal Reference to the Signal object.
        * @return A reference to the output stream after the signal output.
        */
    std::ostream& operator<<(std::ostream& os,  Signal& signal) {
        os << signal.formatSignal();
        return os;
    }

} // namespace Prog3

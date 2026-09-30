class FizzBuzz {
private:
    int n;
    int current = 1;
    mutex mtx;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    void fizz(function<void()> printFizz) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return current > n ||
                       (current % 3 == 0 && current % 5 != 0);
            });

            if (current > n)
                return;

            printFizz();
            current++;
            cv.notify_all();
        }
    }

    void buzz(function<void()> printBuzz) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return current > n ||
                       (current % 5 == 0 && current % 3 != 0);
            });

            if (current > n)
                return;

            printBuzz();
            current++;
            cv.notify_all();
        }
    }

    void fizzbuzz(function<void()> printFizzBuzz) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return current > n ||
                       (current % 3 == 0 && current % 5 == 0);
            });

            if (current > n)
                return;

            printFizzBuzz();
            current++;
            cv.notify_all();
        }
    }

    void number(function<void(int)> printNumber) {
        while (true) {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [&]() {
                return current > n ||
                       (current % 3 != 0 && current % 5 != 0);
            });

            if (current > n)
                return;

            printNumber(current);
            current++;
            cv.notify_all();
        }
    }
};
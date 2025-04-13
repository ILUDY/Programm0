#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<int> buyers(n + 1, 0);
    buyers[0] = 0;

    for (int i = 1; i <= n; ++i) {
        // Вариант 1: текущий человек покупает 1 билет
        buyers[i] = buyers[i - 1] + a[i];

        // Вариант 2: предыдущий покупает билеты для себя и текущего
        if (i >= 2) {
            buyers[i] = min(buyers[i], buyers[i - 2] + b[i - 1]);
        }

        // Вариант 3: человек за два до текущего покупает билеты для троих
        if (i >= 3) {
            buyers[i] = min(buyers[i], buyers[i - 3] + c[i - 2]);
        }
    }

    cout << buyers[n] << endl;

}
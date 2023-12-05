#include <iostream>
#include <string>

using namespace std;

class PalindromeChecker {
private:
    string str;

public:
    PalindromeChecker(const string& s) : str(s) {}

    // Kiểm tra tính chất Palindrome
    bool isPalindrome() const {
        int n = str.length();
        for (int i = 0; i < n / 2; ++i) {
            if (str[i] != str[n - 1 - i]) {
                return false;
            }
        }
        return true;
    }

    // Chuyển đổi chuỗi thành chuỗi Palindrome
    string makePalindrome() {
        string reversed = str;
        reverse(reversed.begin(), reversed.end());
        return str + reversed;
    }
};

int main() {
    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;

        PalindromeChecker checker(s);

        if (checker.isPalindrome()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
            string palindrome = checker.makePalindrome();
            cout << palindrome << "\n";
        }
    }

    return 0;
}

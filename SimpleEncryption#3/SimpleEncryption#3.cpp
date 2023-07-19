#include <iostream>
#include <bitset>
#include <unordered_map>
#include <vector>

using namespace std;

//https://www.codewars.com/kata/57d0329442e44e65e8000bb5/train/cpp

/*
1. Измените пятый бит символа и первый бит следующего символа. (C1.1 <==> C2.5, только если есть следующий символ!)
2. Инвертируйте второй и четвертый биты символа. (2,4 => 0->1 или 1->0)
3. Измените первые 3 бита на последние 3 бита символа. (1,2,3 <==> 4,5,6)
4. Измените каждый нечетный бит на следующий бит символа. (1 <==> 2, 3 <==> 4, 5 <==> 6)
5. Переверните все биты символа.
6. Замените первый бит символа на третий. (3 <==> 5)

123456
543210
*/

class Encryptor {
public:
    string encrypt(string text) {
        if (text.empty()) {
            return text;
        }
        Test(text);

        std::vector<bitset<6>> textRegion = PushVect(text);
        Step1(textRegion);
        Step2(textRegion);
        Step3(textRegion);
        Step4(textRegion);
        Step5(textRegion);
        Step6(textRegion);
        text.clear();
        text = PushString(textRegion);

        return text;
    }
    string decrypt(string encryptedText) {
        if (encryptedText.empty()) {
            return encryptedText;
        }
        Test(encryptedText);

        std::vector<bitset<6>> textRegion = PushVect(encryptedText);
        Step6(textRegion);
        Step5(textRegion);
        Step4(textRegion);
        Step3(textRegion);
        Step2(textRegion);
        Step1(textRegion);
        encryptedText.clear();
        encryptedText = PushString(textRegion);
        return encryptedText;
    }

private:
    const unordered_map <char, int> Region = {
     { 'A', 0 },
     { 'B', 1 },
     { 'C', 2 },
     { 'D', 3 },
     { 'E', 4 },
     { 'F', 5 },
     { 'G', 6 },
     { 'H', 7 },
     { 'I', 8 },
     { 'J', 9 },
     { 'K', 10 },
     { 'L', 11 },
     { 'M', 12 },
     { 'N', 13 },
     { 'O', 14 },
     { 'P', 15 },
     { 'Q', 16 },
     { 'R', 17 },
     { 'S', 18 },
     { 'T', 19 },
     { 'U', 20 },
     { 'V', 21 },
     { 'W', 22 },
     { 'X', 23 },
     { 'Y', 24 },
     { 'Z', 25 },
     { 'a', 26 },
     { 'b', 27 },
     { 'c', 28 },
     { 'd', 29 },
     { 'e', 30 },
     { 'f', 31 },
     { 'g', 32 },
     { 'h', 33 },
     { 'i', 34 },
     { 'j', 35 },
     { 'k', 36 },
     { 'l', 37 },
     { 'm', 38 },
     { 'n', 39 },
     { 'o', 40 },
     { 'p', 41 },
     { 'q', 42 },
     { 'r', 43 },
     { 's', 44 },
     { 't', 45 },
     { 'u', 46 },
     { 'v', 47 },
     { 'w', 48 },
     { 'x', 49 },
     { 'y', 50 },
     { 'z', 51 },
     { '0', 52 },
     { '1', 53 },
     { '2', 54 },
     { '3', 55 },
     { '4', 56 },
     { '5', 57 },
     { '6', 58 },
     { '7', 59 },
     { '8', 60 },
     { '9', 61 },
     { ' ', 62 },
     { '.', 63 } };
    const std::vector <char> inversRegion = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                              'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                              '0','1','2','3','4','5','6','7','8','9',' ','.' };

    std::vector<bitset<6>> PushVect(const std::string& s) {
        std::vector<bitset<6>> result = {};
        for (auto c : s) {
            result.push_back(0b111111 & Region.at(c));
        }
        return result;
    }

    std::string PushString(const std::vector<bitset<6>>& v) {
        std::string s = {};
        for (auto x : v) {
            s.push_back(inversRegion[x.to_ullong()]);
        }
        return s;
    }

    void Step1(vector<bitset<6>>& v) {
        //1. Измените пятый бит символа и первый бит следующего символа. (C1.1 <==> C2.5, только если есть следующий символ!)
        size_t size = v.size();
        for (size_t i = 1; i < size; i += 1) {
            if (v[i - 1][1] != v[i][5]) {
                v[i - 1].flip(1);
                v[i].flip(5);
            }
        }
    }

    void Step2(vector<bitset<6>>& v) {
        //2. Поменяйте местами второй и четвертый биты символа. (2, 4 = > 0->1 или 1->0)
        for (auto& x : v) {
            x.flip(2);
            x.flip(4);
        }
    }

    void Step3(vector<bitset<6>>& v) {
        //3. Измените первые 3 бита на последние 3 бита символа. (1, 2, 3 <= = > 4, 5, 6)
        for (auto& x : v) {
            SwapBit(x, 0, 3);
            SwapBit(x, 1, 4);
            SwapBit(x, 2, 5);
        }
    }

    void Step4(vector<bitset<6>>& v) {
        //4. Измените каждый нечетный бит на следующий бит символа. (1 <==> 2, 3 <==> 4, 5 <==> 6)
        for (auto& x : v) {
            SwapBit(x, 0, 1);
            SwapBit(x, 2, 3);
            SwapBit(x, 4, 5);
        }
    }

    void Step5(vector<bitset<6>>& v) {
        //5. Переверните все биты символа.
        for (auto& x : v) {
            ReverseBit(x);
        }
    }

    void Step6(vector<bitset<6>>& v) {
        //6. Замените первый бит символа на третий. (3 <==> 5)
        for (auto& x : v) {
            SwapBit(x, 3, 5);
        }
    }

    bool AllowedChar(const int& c) {
        std::string s = " .";
        for (int el : s) {
            if (c == el) {
                return 1;
            }
        }
        return 0;
    }

    void Test(const std::string& s) {
        for (int c : s) {
            if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || AllowedChar(c))) {
                throw std::exception();
            }
        }
    }

    void SwapBit(bitset<6>& symbol, unsigned int b1, unsigned int b2) {
        if (symbol[b1] != symbol[b2]) {
            symbol.flip(b1);
            symbol.flip(b2);
        }
    }

    void ReverseBit(bitset<6>& symbol) {
        SwapBit(symbol, 0, 5);
        SwapBit(symbol, 1, 4);
        SwapBit(symbol, 2, 3);
    }

};

int main()
{
    Encryptor k;

    std::string s1 = "Abc";
    std::string s2 = "B9";
    std::string s3 = "A";
    std::string s4 = "This is a test.";
    std::string s5 = "jvLdRPdQXV8Rd5x";
    std::string s6 = "Do the kata Kobayashi Maru Test. Endless fun and excitement when finding a solution.";
    std::string s7 = "rfR9qRVMT8TUfeyXGXdrLUcT.dUmVd5xUNo1oRdZQ1dtUXs1QVmRL8RMVt9RHqRtU1Ps1LtPQXVdbpZ9Lfp1";

    std::cout << k.encrypt(s1) << std::endl;
    std::cout << k.encrypt(s2) << std::endl;
    std::cout << k.encrypt(s3) << std::endl;
    std::cout << k.encrypt(s4) << std::endl;
    std::cout << k.decrypt(s5) << std::endl;
    std::cout << k.encrypt(s6) << std::endl;
    std::cout << k.decrypt(s7) << std::endl;

    return 0;
}
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

//https://www.codewars.com/kata/57d0329442e44e65e8000bb5/train/cpp

/*
1. Измените пятый бит символа и первый бит следующего символа. (C1.5 <==> C2.1, только если есть следующий символ!)
2. Поменяйте местами второй и четвертый биты символа. (2,4 => 0->1 или 1->0)
3. Измените первые 3 бита на последние 3 бита символа. (1,2,3 <==> 4,5,6)
4. Измените каждый нечетный бит на следующий бит символа. (1 <==> 2, 3 <==> 4, 5 <==> 6)
5. Переверните все биты символа.
6. Замените первый бит символа на третий. (1 <==> 3)

123456
543210
*/

class Kata
{
public:
    std::string encrypt(std::string text)
    {
        if (text.empty()) {
            return text;
        }
        Test(text);
        std::vector<int> textRegion = PushVect(text);
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

    std::string decrypt(std::string encryptedText)
    {
        if (encryptedText.empty()) {
            return encryptedText;
        }
        Test(encryptedText);
        std::vector<int> textRegion = PushVect(encryptedText);
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

    const std::unordered_map <char, int> Region = {
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
    { '.', 63 }
    }; 
    const std::vector <char> inversRegion = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                              'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                              '0','1','2','3','4','5','6','7','8','9',' ','.'};

    std::vector<int> PushVect(const std::string& s) {
        std::vector<int> result = {};
        for (auto c : s) {
            result.push_back(Region.at(c));
        }
        return result;
    }

    std::string PushString(const std::vector<int> &v) {
        std::string s = {};
        for (auto x : v) {
            s.push_back(inversRegion[x]);
        }
        return s;
    }
   
    void Step1(std::vector<int> &v) {
        //Change 5 bit C1 and 1 bit C2
        size_t size = v.size();
        if (size % 2 == 0) {
            for (size_t i = 1; i < size; i+=2) {
                v[i - 1] = ChangeBit(v[i - 1], 1);
                v[i] = ChangeBit(v[i], 5);
            }
        }else {
            for (size_t i = 2; i < size; i+=2) {
                v[i - 1] = ChangeBit(v[i - 1], 1);
                v[i] = ChangeBit(v[i], 5);
            }
        }        
    }

    void Step2(std::vector<int> &v) {
        //Change 2,4 bit char
        size_t size = v.size();
        for (size_t i = 0; i < size; ++i) {
            v[i] = ChangeBit(v[i], 2);
            v[i] = ChangeBit(v[i], 4);
        }
    }

    void Step3(std::vector<int> &v) {
        size_t size = v.size();
        for (size_t i = 0; i < size; ++i) {
            v[i] = SwapBit(v[i], 0, 3);
            v[i] = SwapBit(v[i], 1, 4);
            v[i] = SwapBit(v[i], 2, 5);
        }
    }

    void Step4(std::vector<int> &v) {
        size_t size = v.size();
        for (size_t i = 0; i < size; ++i) {
            v[i] = SwapBit(v[i], 0, 1);
            v[i] = SwapBit(v[i], 2, 3);
            v[i] = SwapBit(v[i], 4, 5);
        }
    }

    void Step5(std::vector<int> &v) {
        size_t size = v.size();
        for (size_t i = 0; i < size; ++i) {
            v[i] = ReverseBit(v[i]);
        }
    }

    void Step6(std::vector<int> &v) {
        size_t size = v.size();
        for (size_t i = 0; i < size; ++i) {
            v[i] = SwapBit(v[i], 3, 5);
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

    bool StateBit(const int &c, int index) {
        return c & (1 << index);
    }
    
    int ChangeBit(const int& c, int index) {
        return c ^ (1 << index);
    }
    
    int SwapBit(const int& c, int i1, int i2) {
        bool flag = StateBit(c, i1) != StateBit(c, i2);
        if (!flag) {
            return c;
        }
        else {
            int result = ChangeBit(c, i1);
            result = ChangeBit(result, i2);            
            return result;
        }
    }

    int ReverseBit(int a) {
        size_t size = 5;
        int result = 0;
        for (size_t i = size, j = 0; i != -1; --i, ++j) {
            result += StateBit(a, i) ? (1 << j) : 0;
        }
        return result;
    }
};



int main()
{
    Kata k;
    
    std::string s1 = "Abc";
    std::string s2 = "B9";
    std::string s3 = "A";
    std::string s4 = "This is";
    std::string s5 = "jvLdRPd";

    std::cout << k.encrypt(s1) << std::endl;
    std::cout << k.encrypt(s2) << std::endl;
    std::cout << k.encrypt(s3) << std::endl;
    std::cout << k.encrypt(s4) << std::endl;
    std::cout << k.decrypt(s5) << std::endl;
    
    return 0;
}

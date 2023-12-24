#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>


std::string addInBase(const std::string& I1, const std::string& I2, int B) {
    
    // Convert strings to vector of integers for easier manipulation
    std::vector<int> L1, L2, R1, R2; // initializing four vectors: L1, L2, R1, R2. L1 and L2 will store the digits of s1 and s2 respectively

    for (size_t i = 0; i < I1.size(); ++i) {
        L1.push_back(I1[i] - '0'); // The digits from the strings are converted into integers using the expression (s1[i] - '0').
    }

    for (size_t i = 0; i < I2.size(); ++i) {
        L2.push_back(I2[i] - '0'); //The digits from the strings are converted into integers using the expression (s1[i] - '0').
    }

    if (L1.size() >= L2.size()) {
        R1.push_back(0);  // ensure that R1 and R2 vectors have the same length by padding them with zeros.
        R1.insert(R1.end(), L1.begin(), L1.end()); // insert the digits of L1 into R1
        R2.resize(L1.size() - L2.size() + 1, 0); // resize R2 to the same length as R1 and pad it with zeros
        R2.insert(R2.end(), L2.begin(), L2.end()); // insert the digits of L2 into R2
    } else {
        R1.resize(L2.size() - L1.size() + 1, 0);
        R1.insert(R1.end(), L1.begin(), L1.end());
        R2.push_back(0);
        R2.insert(R2.end(), L2.begin(), L2.end());
    }

    std::string out = "";
    int carry = 0;

    for (int i = R1.size() - 1; i >= 0; i--) { //  the core logic for the base addition
        int digit_sum = R1[i] + R2[i] + carry; // digit_sum is the sum of the digits in the same position in R1 and R2
        carry = digit_sum / B; // carry is the quotient of digit_sum divided by B
        out = std::to_string(digit_sum % B) + out; // the remainder of digit_sum divided by B is appended to the output string
    }

    // Remove any leading zeros from the output
    size_t pos = out.find_first_not_of("0");
    if (pos != std::string::npos) {
        out = out.substr(pos);
    } else {
        out = "0";
    }

    return out;
}


bool comparision(std::string I1, std::string I2){
    
    if (I1.size() > I2.size()) {
        return true;
    } 
    else if (I1.size() < I2.size()) {
        return false;
    }
    else{
        for (int i =0; i < I1.size(); i++) {
            if (I1[i] > I2[i]) {
                return true;
            }
            else if (I1[i] < I2[i]) {
                return false;
            }
        }
    }
    return true;
}


std::string subtraction(const std::string& I1, const std::string& I2, int B) {
   
    // Convert strings to vector of integers for easier manipulation
    std::vector<int> L1, L2, R1, R2; // initializing four vectors: L1, L2, R1, R2. L1 and L2 will store the digits of s1 and s2 respectively

    for (size_t i = 0; i < I1.size(); ++i) {
        L1.push_back(I1[i] - '0'); // The digits from the strings are converted into integers using the expression (s1[i] - '0').
    }

    for (size_t i = 0; i < I2.size(); ++i) {
        L2.push_back(I2[i] - '0'); //The digits from the strings are converted into integers using the expression (s1[i] - '0').
    }

    if (L1.size() >= L2.size()) {        
        R1.insert(R1.end(), L1.begin(), L1.end()); // insert the digits of L1 into R1
        R2.resize(L1.size() - L2.size(), 0); // resize R2 to the same length as R1 and pad it with zeros
        R2.insert(R2.end(), L2.begin(), L2.end()); // insert the digits of L2 into R2
    } else {
        R1.resize(L2.size() - L1.size(), 0);
        R1.insert(R1.end(), L1.begin(), L1.end());
        R2.insert(R2.end(), L2.begin(), L2.end());
    }

    std::string out = "";
    int carry = 0;

    for (int i = R1.size() - 1; i >= 0; i--) { //  the core logic for the base addition
        if (R1[i] >= R2[i] + carry) {
            int digit_sub = R1[i] - R2[i] - carry;
            out = std::to_string(digit_sub) + out;
            carry = 0;
        }else{
            int digit_sub = (R1[i] + B) - R2[i] - carry;
            out = std::to_string(digit_sub) + out;
            carry = 1;
        }
    }

    if (comparision(I1, I2) == false) {
        out = "0";
    }

    // Remove any leading zeros from the output
    size_t pos = out.find_first_not_of("0");
    if (pos != std::string::npos) {
        out = out.substr(pos);
    } else {
        out = "0";
    }

    return out;
}



std::string karasubaProgram(std::string I1, std::string I2, int B) {


    if (I1.size() < 4 || I2.size() < 4) { // base case

        if (I1.size() > I2.size()) {
            int n = I1.size();
            I2 = std::string(n - I2.size(), '0') + I2;
        } 
        else {
            int n = I2.size();
            I1 = std::string(n - I1.size(), '0') + I1;
        }

        std::string out = "0";  // Initialize the result to "0"
        
        for (int j = I2.size() - 1; j >= 0; j--) { 
            std::string temp = "";
            int carry = 0;
        
            for (size_t k = 0; k < I2.size() - 1 - j; k++) {  // Append zeros based on the position
                temp += '0';
            }
        
            for (int i = I1.size() - 1; i >= 0; i--) { 
                int digit_multi = (I1[i] - '0') * (I2[j] - '0') + carry; 
                carry = digit_multi / B; 
                temp = std::to_string(digit_multi % B) + temp; 
            }
        
            if (carry > 0) {  // If there's a remaining carry
                temp = std::to_string(carry) + temp;
            }
        
            out = addInBase(out, temp, B);  // Summation of intermediate products
        }
        return out;
    } 
    else {

        if (I1.size() > I2.size()) {
            int n = I1.size();
            I2 = std::string(n - I2.size(), '0') + I2;
        } 
        else {
            int n = I2.size();
            I1 = std::string(n - I1.size(), '0') + I1;
        }

        int n = std::max(I1.length(), I2.length()); // max lenghth of two numbers
        int half = n / 2; // half is the number of digits 

        std::string a_str = I1.substr(0, I1.length() - half); // high level substr of I1
        std::string b_str = I1.substr(I1.length() - half); //low level substr of I1

        std::string c_str = I2.substr(0, I2.length() - half); // high level substr of I2
        std::string d_str = I2.substr(I2.length() - half); // low level substr of I2

        std::string ac = karasubaProgram(a_str, c_str, B); // recursive substr untill base case
        std::string bd = karasubaProgram(b_str, d_str, B); 

        //calculate a + b and c + d, then convert them to strings
        std::string a_plus_b = addInBase(a_str, b_str, B); // stoi converts a string to an integer
        std::string c_plus_d = addInBase(c_str, d_str, B);

        //recursive a+b and c+d until digit is base case, and calculate (a + b) * (c + d) - ac - bd, then convert it to a string
        std::string ad_bc = subtraction(karasubaProgram(a_plus_b, c_plus_d, B), addInBase(ac, bd, B), B); 

        //the equation for the karasuba algorithm: ac * B^2(n/2) + (ad + bc) * B^(2/n) + bd 
        std::string ac_val = ac + std::string(2 * half, '0'); 
        std::string ad_bc_val = ad_bc + std::string(half, '0');
        std::string temp_out = addInBase(ac_val, ad_bc_val, B);

        return addInBase(temp_out, bd, B); 
    }
}



std::string division(std::string I1, std::string I2, int B){    

    if (I2 == "0") {
        // Dividing by zero is not allowed.
        throw std::runtime_error("Division by zero is not allowed.");
    }

    if (comparision(I1, I2) == false) {
        // Dividend is less than divisor.
        return "0";
    }

    int n = I1.size() - I2.size();
    I2 = I2 + std::string(n, '0');
    std::string out = "";
    std::string temp = "1";

    while (I1 != "0" && n>=0){
        if (comparision(I1,I2)== false){
            I2.pop_back();
            n--;
            std::string temp = "1";
        }
        else{
            I1 = subtraction(I1, I2, B);
            std::string temp = "1";
            temp = temp + std::string(n, '0');
            out = addInBase(out, temp, 10);
        }
    }
    
    return out;
 }
 

std::string binaryToDecimal(const std::string& binary, int B) {
    std::string result = "0";
    std::string base = "1"; // Start with the least significant bit

    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            result = addInBase(result, base, B);
        }
        base = addInBase(base, base, B); // Double the base for the next iteration
    }

    return result;
}



std::string division2(const std::string& I1_original, const std::string& I2, int B) {
    if (I2 == "0") {
        return "divisor cannot be zero";
    }
    if (I1_original == "0") {
        return "0";
    }

    std::string I1 = I1_original; // This is a non-const copy of I1_original

    std::vector<std::string> listL5 = { I2 };

    while (true) {
        std::string nextVal = addInBase(listL5.back(), listL5.back(), B);
        if(comparision(nextVal, I1) > 0) {
            break;
        }
        listL5.push_back(nextVal);
    }

    std::string ans = "0";
    
    for (int i = listL5.size() - 1; i >= 0; i--) {
        if (comparision(listL5[i], I1) <= 0) {
            std::string powerOfTwo = "1";
            for (int j = 0; j < i; j++) {
                powerOfTwo += "0";
            }
            ans = addInBase(ans, powerOfTwo, B);
            I1 = subtraction(I1, listL5[i], B);
        }
    }

    return binaryToDecimal(ans, B);

}

int main() {
    std::string I1, I2;
    int B;

    std::cin >> I1 >> I2 >> B; 

    std::cout << addInBase(I1, I2, B) << " " << karasubaProgram(I1, I2, B) << " " << division(I1, I2, B) << " " << division2(I1, I2, B) << std::endl;
    return 0;
}



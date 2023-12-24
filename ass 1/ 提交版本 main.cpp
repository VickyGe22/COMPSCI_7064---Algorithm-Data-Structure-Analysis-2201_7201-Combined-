#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>


std::string ADD(const std::string& I1, const std::string& I2, int B) {
    
    std::vector<int> L1, L2, R1, R2; 

    for (size_t i = 0; i < I1.size(); ++i) {
        L1.push_back(I1[i] - '0'); 
    }

    for (size_t i = 0; i < I2.size(); ++i) {
        L2.push_back(I2[i] - '0'); 
    }

    if (L1.size() >= L2.size()) {
        R1.push_back(0);  
        R1.insert(R1.end(), L1.begin(), L1.end()); 
        R2.resize(L1.size() - L2.size() + 1, 0); 
        R2.insert(R2.end(), L2.begin(), L2.end()); 
    } else {
        R1.resize(L2.size() - L1.size() + 1, 0);
        R1.insert(R1.end(), L1.begin(), L1.end());
        R2.push_back(0);
        R2.insert(R2.end(), L2.begin(), L2.end());
    }

    std::string out = "";
    int carry = 0;

    for (int i = R1.size() - 1; i >= 0; i--) { 
        int digit_sum = R1[i] + R2[i] + carry; 
        carry = digit_sum / B; 
        out = std::to_string(digit_sum % B) + out; 
    }

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
    
    std::vector<int> L1, L2, R1, R2; 

    for (size_t i = 0; i < I1.size(); ++i) {
        L1.push_back(I1[i] - '0'); 
    }

    for (size_t i = 0; i < I2.size(); ++i) {
        L2.push_back(I2[i] - '0'); 
    }

    if (L1.size() >= L2.size()) {        
        R1.insert(R1.end(), L1.begin(), L1.end()); 
        R2.resize(L1.size() - L2.size(), 0); 
        R2.insert(R2.end(), L2.begin(), L2.end()); 
    } else {
        R1.resize(L2.size() - L1.size(), 0);
        R1.insert(R1.end(), L1.begin(), L1.end());
        R2.insert(R2.end(), L2.begin(), L2.end());
    }

    std::string out = "";
    int carry = 0;

    for (int i = R1.size() - 1; i >= 0; i--) { 
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

        std::string out = "0"; 
        
        for (int j = I2.size() - 1; j >= 0; j--) { 
            std::string temp = "";
            int carry = 0;
        
            for (size_t k = 0; k < I2.size() - 1 - j; k++) { 
                temp += '0';
            }
        
            for (int i = I1.size() - 1; i >= 0; i--) { 
                int digit_multi = (I1[i] - '0') * (I2[j] - '0') + carry; 
                carry = digit_multi / B; 
                temp = std::to_string(digit_multi % B) + temp; 
            }
        
            if (carry > 0) {  
                temp = std::to_string(carry) + temp;
            }
        
            out = ADD(out, temp, B); 
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

        int n = std::max(I1.length(), I2.length()); 
        int half = n / 2; 

        std::string a_str = I1.substr(0, I1.length() - half);
        std::string b_str = I1.substr(I1.length() - half);

        std::string c_str = I2.substr(0, I2.length() - half);
        std::string d_str = I2.substr(I2.length() - half);

        std::string ac = karasubaProgram(a_str, c_str, B); 
        std::string bd = karasubaProgram(b_str, d_str, B); 

        //calculate a + b and c + d, then convert them to strings
        std::string a_plus_b = ADD(a_str, b_str, B); 
        std::string c_plus_d = ADD(c_str, d_str, B);

        //recursive a+b and c+d until digit is base case, and calculate (a + b) * (c + d) - ac - bd, then convert it to a string
        std::string ad_bc = subtraction(karasubaProgram(a_plus_b, c_plus_d, B), ADD(ac, bd, B), B); 

        //the equation for the karasuba algorithm: ac * B^2(n/2) + (ad + bc) * B^(2/n) + bd 
        std::string ac_val = ac + std::string(2 * half, '0'); 
        std::string ad_bc_val = ad_bc + std::string(half, '0');
        std::string temp_out = ADD(ac_val, ad_bc_val, B);

        return ADD(temp_out, bd, B); 
    }
}



std::string division(std::string I1, std::string I2, int B){    

    if (I2 == "0") {
        return "error";
    }

    if (comparision(I1, I2) == false) {
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
            out = ADD(out, temp, 10);
        }
    }
    
    return out;
 }
 


int main() {
    std::string I1, I2;
    int B;

    std::cin >> I1 >> I2 >> B; 

    std::cout << ADD(I1, I2, B) << " " << karasubaProgram(I1, I2, B) << " " << division(I1, I2, B) << std::endl;
    return 0;
}



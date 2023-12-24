#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <gmp.h>

// // int main() {
// // std::string I1 = "3141592653589793238462643383279502884197169399375105820974944592";
// // std::string I2 = "2718281828459045235360287471352662497757247093699959574966967627";
// // int half = std::max(I1.length(), I2.length()) / 2; // half is the number of digits

// // std::string a_str = I1.substr(0, I1.length() - half); // high level substr of I1
// // std::string b_str = I1.substr(I1.length() - half); //low level substr of I1

// // std::string c_str = I2.substr(0, I2.length() - half); // high level substr of I2
// // std::string d_str = I2.substr(I2.length() - half); // low level substr of I2

// // std::string a_plus_b = std::to_string(std::stoi(a_str) + std::stoi(b_str)); // stoi converts a string to an integer
// // std::string c_plus_d = std::to_string(std::stoi(c_str) + std::stoi(d_str));

// // std::cout << a_str << " " << b_str << " " << c_str << " " << d_str << " " << a_plus_b << " " << c_plus_d << std::endl;
// // }

// // std::string karasubaProgram(std::string I1, std::string I2, int B) {

// //     if (I1.size() < 10 || I2.size() < 10) { // base case
// //         int x = std::stoi(I1); // stoi converts a string to an integer
// //         int y = std::stoi(I2);
// //         return std::to_string(x * y); // to_string converts an integer to a string
// //     } else {
// //         int n = std::max(I1.length(), I2.length()); // max lenghth of two numbers
// //         int half = n / 2; // half is the number of digits 

// //         std::string a_str = I1.substr(0, I1.length() - half); // high level substr of I1
// //         std::string b_str = I1.substr(I1.length() - half); //low level substr of I1

// //         std::string c_str = I2.substr(0, I2.length() - half); // high level substr of I2
// //         std::string d_str = I2.substr(I2.length() - half); // low level substr of I2

// //         std::string ac = karasubaProgram(a_str, c_str, B); // recursive substr untill base case
// //         std::string bd = karasubaProgram(b_str, d_str, B); 

// //         //calculate a + b and c + d, then convert them to strings
// //         std::string a_plus_b = std::to_string(std::stoi(a_str) + std::stoi(b_str)); // stoi converts a string to an integer
// //         std::string c_plus_d = std::to_string(std::stoi(c_str) + std::stoi(d_str));

// //         //recursive a+b and c+d until digit is base case, and calculate (a + b) * (c + d) - ac - bd, then convert it to a string
// //         std::string ad_bc = std::to_string(std::stoi(karasubaProgram(a_plus_b, c_plus_d, B)) - std::stoi(ac) - std::stoi(bd));

// //         //the equation for the karasuba algorithm: ac * B^2(n/2) + (ad + bc) * B^(2/n) + bd
// //         int ac_val = std::stoi(ac) * (pow(B, 2 * half)); 
// //         int ad_bc_val = std::stoi(ad_bc) * (pow(B, half)); 

// //         return std::to_string(ac_val + ad_bc_val + std::stoi(bd)); // stoi converts a string to an integer
// //     }
// // }

// // mpz_class karasuba(const mpz_class &x, const mpz_class &y, int B) {
// //     if (x < 10 || y < 10) {
// //         return x * y;
// //     }

// //     size_t n = std::max(x.get_str().size(), y.get_str().size());
// //     size_t half = n / 2;

// //     mpz_class basePowerHalf;
// //     mpz_pow_ui(basePowerHalf.get_mpz_t(), B, half);

// //     mpz_class a = x / basePowerHalf;
// //     mpz_class b = x % basePowerHalf;
// //     mpz_class c = y / basePowerHalf;
// //     mpz_class d = y % basePowerHalf;

// //     mpz_class ac = karasuba(a, c, B);
// //     mpz_class bd = karasuba(b, d, B);
// //     mpz_class ad_bc = karasuba(a + b, c + d, B) - ac - bd;

// //     mpz_class basePowerDoubleHalf;
// //     mpz_pow_ui(basePowerDoubleHalf.get_mpz_t(), B, 2*half);

// //     return ac * basePowerDoubleHalf + ad_bc * basePowerHalf + bd;
// // }

// std::string addInBase(const std::string& I1, const std::string& I2, int B) {
//     // Convert strings to vector of integers for easier manipulation
//     std::vector<int> L1, L2, R1, R2; // initializing four vectors: L1, L2, R1, R2. L1 and L2 will store the digits of s1 and s2 respectively

//     for (size_t i = 0; i < I1.size(); ++i) {
//         L1.push_back(I1[i] - '0'); // The digits from the strings are converted into integers using the expression (s1[i] - '0').
//     }

//     for (size_t i = 0; i < I2.size(); ++i) {
//         L2.push_back(I2[i] - '0'); //The digits from the strings are converted into integers using the expression (s1[i] - '0').
//     }

//     if (L1.size() >= L2.size()) {
//         R1.push_back(0);  // ensure that R1 and R2 vectors have the same length by padding them with zeros.
//         R1.insert(R1.end(), L1.begin(), L1.end()); // insert the digits of L1 into R1
//         R2.resize(L1.size() - L2.size() + 1, 0); // resize R2 to the same length as R1 and pad it with zeros
//         R2.insert(R2.end(), L2.begin(), L2.end()); // insert the digits of L2 into R2
//     } else {
//         R1.resize(L2.size() - L1.size() + 1, 0);
//         R1.insert(R1.end(), L1.begin(), L1.end());
//         R2.push_back(0);
//         R2.insert(R2.end(), L2.begin(), L2.end());
//     }

//     std::string out = "";
//     int carry = 0;

//     for (int i = R1.size() - 1; i >= 0; i--) { //  the core logic for the base addition
//         int digit_sum = R1[i] + R2[i] + carry; // digit_sum is the sum of the digits in the same position in R1 and R2
//         carry = digit_sum / B; // carry is the quotient of digit_sum divided by B
//         out = std::to_string(digit_sum % B) + out; // the remainder of digit_sum divided by B is appended to the output string
//     }

//     // Remove any leading zeros from the output
//     size_t pos = out.find_first_not_of("0");
//     if (pos != std::string::npos) {
//         out = out.substr(pos);
//     } else {
//         out = "0";
//     }

//     return out;
// }

// std::string Multi_Recursive(std::string I1, std::string I2, int B) {
//     if (I1.size() > I2.size()) {
//         int n = I1.size();
//         I2 = std::string(n - I2.size(), '0') + I2;
//     } else {
//         int n = I2.size();
//         I1 = std::string(n - I1.size(), '0') + I1;
//     }

//     std::string out = "0";  // Initialize the result to "0"
    
//     for (int j = I2.size() - 1; j >= 0; j--) { 
//         std::string temp = "";
//         int carry = 0;
        
//         for (int k = 0; k < I2.size() - 1 - j; k++) {  // Append zeros based on the position
//             temp += '0';
//         }
        
//         for (int i = I1.size() - 1; i >= 0; i--) { 
//             int digit_multi = (I1[i] - '0') * (I2[j] - '0') + carry; 
//             carry = digit_multi / B; 
//             temp = std::to_string(digit_multi % B) + temp; 
//         }
        
//         if (carry > 0) {  // If there's a remaining carry
//             temp = std::to_string(carry) + temp;
//         }
        
//         out = addInBase(out, temp, B);  // Summation of intermediate products
//     }

//     return out;
// }

// // int x = std::stoi(I1); // stoi converts a string to an integer
//         // int y = std::stoi(I2);
//         // return std::to_string(x * y); // to_string converts an integer to a string
//         // if (I1.size() > I2.size()) {
//         //     int n = I1.size();
//         //     I2 = std::string(n - I2.size(), '0') + I2;
//         // }else{
//         //     int n = I2.size();
//         //     I1 = std::string(n - I1.size(), '0') + I1;
//         // }
        
//         // std::string out = "";
//         // std::string temp = "";
//         // int carry = 0;
//         // int count=0;

//         // for (int j = I1.size()-1; j >= 0; j--) { 
//         //     for (int i = I1.size() - 1; i >= 0; i--) { 
//         //         int digit_multi = I1[i] * I2[j] + carry; 
//         //         carry = digit_multi / B; 
//         //         temp = std::to_string(digit_multi - carry*B) + temp; 
//         //     }
//         // temp = temp + std::string(count, '0');
//         // count++;
//         // out = addInBase(out, temp, B);
//         // }
//         // return out;


int main() {
    // std::string I1, I2;
    // int B;

    // std::cin >> I1 >> I2 >> B;

    // // Add validation if needed for lengths of I1 and I2 and ranges of B
    // if (B < 2 || B > 10 || I1.size() > 100 || I2.size() > 100) {
    //     std::cout << "Invalid input!";
    //     return 1;
    // }

    // std::cout << Multi_Recursive(I1, I2, B) << std::endl;
    // return 0;

    // std:string c=["1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"];



}


//TASK description
// You are asked to use C++ to implement
// • School Method for Integer Addition and Karatsuba Algorithm for Integer Multiplication
// • Integer Division (postgraduate only)
// If you are an undergraduate student, the maximum mark (on Websubmission) is 100. If you are a
// postgraduate student, your maximum mark is 200.

// Your submission should contain exactly one file: main.cpp. You do not need to submit a design.
// Your program takes one line as input. 
// The input line contains three integers separated by spaces. 
// Let the three integers be I1, I2, and B. 
//I1 and I2 are both nonnegative integers up to 100 digits long (there are no leading 0s, except when the value itself is 0). 
// B is I1 and I2’s base (B is from 2 to 10)
// Your program should output the sum of I1 and I2, using the school method
// then the product of I1 and I2, using the Karatsuba algorithm, and finally the ratio between I1 and I2 (rounded down). 
// You are asked to come up with a way to perform this division. It’s not covered in lectures. 
// I2 will not be 0.

// The results should still use base B. Please separate the results using one space.
// Sample input 1: 101 5 10
// Sample output 1: 106 505 20
// Sample input 2: 10 111 2
// Sample output 2: 1001 1110 0
// Sample input 3: 111 10 2
// Sample output 2: 1001 1110 11

// bool comparision(std::string I1, std::string I2){
    
//     if (I1.size() > I2.size()) {
//         return true;
//     } 
//     else if (I1.size() < I2.size()) {
//         return false;
//     }
//     else{
//         for (int i =0; i < I1.size(); i--) {
//             if (I1[i] > I2[i]) {
//                 return true;
//             }
//             else if (I1[i] < I2[i]) {
//                 return false;
//             }
//         }
//     }
//     return false;
// }


// std::string division(std::string I1, std::string I2, int B){    

//     if (I2 == "0") {
//         // Dividing by zero is not allowed.
//         throw std::runtime_error("Division by zero is not allowed.");
//     }

//     if (comparision(I1, I2) == false) {
//         // Dividend is less than divisor.
//         return "0";
//     }

//     int n = I1.size() - I2.size();
//     I2 = I2 + std::string(n, '0');
//     std::string out = "";
//     std::string I1_original = I1;
//     std::string I2_original = I2;
//     std::string temp = "1";

//     while (comparision(subtraction(I1, I2, B), I2)==false){
//         if (comparision(I1,I2)== false){
//             I2.pop_back();
//             n--;
//         }
//         else{
//             I1 = subtraction(I1, I2, B);
//             temp = temp + std::string(n, '0');
//             out = addInBase(out, temp, 10);
//         }
//     }
    
//     return out;
//  }


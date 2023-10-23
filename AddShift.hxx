#ifndef __ADD_SHIFT_H__
#define  __ADD_SHIFT_H__ 1

#include <iostream>
#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <cmath>

using namespace std;

class AddShift {
    public:
        size_t BitCount;
        int *B;
        int *Q;
        int *A;
        int SC;
        int E;
        int Q0;

        // Convert bits to array
        constexpr void BitToArray(int* arr, const char *bits, size_t __l) noexcept;
        
        // Compute carry value
        constexpr int ComputeC(const int num) noexcept;

        // Compute remainder value
        constexpr int ComputeR(const int num) noexcept;

    public:
        // Constructor
        AddShift(const char *, const char *, size_t) noexcept;

        // Add two bit arrays
        constexpr int* BitSum(int* x, int* y) noexcept;

        // Shift right and update EAQ
        constexpr void ShiftToRightEAQ() noexcept;

        void Print() noexcept;

        string BitString() noexcept;
        int ResInDec() noexcept;
        int BitToDec(const char *bits, size_t __l) noexcept;
};

inline AddShift::AddShift(const char *bit_q, const char *bit_b, size_t bit_count) noexcept {
    // Initialize bit count
    this->SC = bit_count;
    this->BitCount = bit_count;

    // Allocate memory for A, B, and Q arrays
    this->A = (int*)malloc(bit_count*sizeof(int));
    this->B = (int*)malloc(bit_count*sizeof(int));
    this->Q = (int*)malloc(bit_count*sizeof(int));

    // Convert bit strings to integer arrays
    BitToArray(this->B, bit_b, this->BitCount);
    BitToArray(this->Q, bit_q, this->BitCount);

    // Initialize E and Q0
    this->E = 0;
    this->Q0 = this->Q[this->SC - 1];
}

inline constexpr void AddShift::BitToArray(int* arr, const char *bits, size_t __l) noexcept {
    // Iterate through each bit
    for (size_t i = 0; i < __l; i++) {
        // Convert bit to integer and store in array
        arr[i] = int(bits[i]) - 48;
    }
}

inline constexpr int* AddShift::BitSum(int* x, int *y) noexcept {
    // Allocate memory for the result
    int* result = (int*)malloc(this->SC*sizeof(int));
    size_t sum = 0, c = 0, r = 0;

    // Iterate through the bits in reverse order
    for (int i = this->BitCount - 1; i >= 0; i--) {
        // Calculate the sum of the bits at the current position
        sum = x[i] + y[i] + c;

        // Compute the carry value
        c = ComputeC(sum);

        // Compute the result value
        r = ComputeR(sum);

        // Store the result value in the result array
        result[i] = r;
        // cout<<'-'<<c<<endl;
    }
    this->E = c;


    return result;
}

inline constexpr int AddShift::ComputeR(const int num) noexcept {
    // Return remainder of num divided by 2
    return num % 2;
}

inline constexpr int AddShift::ComputeC(const int num) noexcept {
    // Subtract remainder and divide by 2
    return (num - (num % 2)) / 2;
}

inline constexpr void AddShift::ShiftToRightEAQ() noexcept {
    // Store carry out values
    int c1 = this->E, c2 = this->A[this->BitCount - 1];

    this->E = 0;

    for (int i = this->BitCount - 1; i >= 0; i--) {
        this->A[i] = this->A[i - 1];
    }
    this->A[0] = c1;

    for (int i = this->BitCount - 1; i >= 0; i--) {
        this->Q[i] = this->Q[i - 1];
    }
    this->Q[0] = c2;

    // Decrement shift count
    this->SC--;
    
    // Store Q0 value
    this->Q0 = this->Q[this->BitCount - 1];
}


inline void AddShift::Print() noexcept {
    stringstream ss;

    // Print Q0, E, A, Q, SC
    ss << "Q0 : " << this->Q0;
    ss << " | E : " << this->E;

    ss << " | A : ";
    for (size_t i = 0; i < this->BitCount; i++) {
        ss << this->A[i];
    }

    ss << " | Q : ";
    for (size_t i = 0; i < this->BitCount; i++) {
        ss << this->Q[i];
    }

    ss << " | SC : " << this->SC;

    // Print the result
    cout<<ss.str()<<endl;
}

inline string AddShift::BitString() noexcept {
    // Allocate memory for result string
    int *res = (int*)malloc(this->BitCount*2*sizeof(int));
    stringstream ss;

    // Convert E to string and append to result string
    ss << this->E;

    // Convert A array to string and append to result string
    for (size_t i = 0; i < this->BitCount; i++) {
        ss << this->A[i];
    }

    // Convert Q array to string and append to result string
    for (size_t i = 0; i < this->BitCount; i++) {
        ss << this->Q[i];
    }

    // Return the final result string
    return ss.str();
}


inline int AddShift::ResInDec() noexcept {
    // Convert bit string to array
    string str = this->BitString();
    const char *bits = str.c_str();
    int *arr = (int*)malloc((this->BitCount*2+1)*sizeof(int));
    int __l = this->BitCount*2+1, tp, ans = 0;
    this->BitToArray(arr, bits, __l);

    // Calculate decimal result
    for (int i = __l - 1; i >= 0; i--) {
        tp = int(arr[i]);
        ans += tp*pow(2, __l - i - 1);
    }
    return ans;
}


inline int AddShift::BitToDec(const char *bits, size_t __l) noexcept {
    int *arr = (int*)malloc(__l*sizeof(int));
    int ans = 0, tp;
    this->BitToArray(arr, bits, __l);

    for (int i = __l - 1; i >= 0; i--) {
        tp = int(arr[i]);
        ans += tp*pow(2, __l - i - 1);
    }

    return ans;
}






#endif // !__ADD_SHIFT_H__
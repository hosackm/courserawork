// C++ conversion of HW1.c
// Changes made:
//   printf is now std::cout
//   /* */ comments are now //
//   #defines are now const variables
//   int[] is now std::vector<int>
//   sum is now an inline function

#include <iostream>
#include <vector>

// Since we are using std::vector<int> we no longer need to pass the length
// as an argument.
inline void sum(int *result, std::vector<int> vec){
    // Avoid derefencing null pointers
    if(!result){
        return;
    }

    *result = 0; // initialize result to 0
    for(int i = 0; i < vec.size(); ++i){
        *result = *result + vec[i];
    }
}

int main(int argc, char **argv){
    int accum = 0;
    const int size = 40; // #define is now const
    std::vector<int> data(size, 0); // int[] is now std::vector<int>

    for(int i = 0; i < size; ++i){
        data.push_back(i); // data[] is now data.push_back vector method
    }

    sum(&accum, data);
    std::cout << "sum is " << accum << std::endl; // printf now std::cout

    return 0;
}

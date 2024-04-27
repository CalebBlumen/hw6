#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };

    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

      unsigned long long sequence[5] = {0,0,0,0,0};
      
      int i = k.size()-1;
      int idx = 0;
      while (i >= 0) {
        unsigned long long curr = 0;
        for (int j = 0; j < 6; ++j) {
          std::cout << "i-j: " << i-j << std::endl;
          if (i-j < 0) {
            break;
          }
          curr += pow(36,j)*letterDigitToNumber(k[i-j]);
        }
        std::cout << "stop" << std::endl;
        sequence[4-idx] = curr;
       
        idx++;
        i -= 6;
      }
       //to clear the ++ at the end of the last loop

      for (int j = 0; j < 5; ++j) {
        std::cout << "w[" << j << "] = " << sequence[j] << std::endl;
      }
      
      unsigned long long hash = 0;

      for (int i = 0; i < 5; ++i) {
        hash += sequence[i] * rValues[i];
      }
      return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (isalpha(letter)) {
            return tolower(letter) - 'a';
        }
        else {
            return letter - '0' + 26;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif

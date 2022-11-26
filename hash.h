#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct TheirStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    TheirStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    HASH_INDEX_T operator()(const std::string& k) const 
    {
        // Calculate the w values for use in the hash function.
        HASH_INDEX_T w[5]{ 0, 0, 0, 0, 0 };
        calculateWValues(k, w);

        // Calculate the hash value using the r values that were generated, then return
        // the final hash value.
        HASH_INDEX_T hashValue{ 0 };
        for(int i{ 0 }; i < 5; ++i)
        {
            hashValue += rValues[i] * w[i];
        }
        return hashValue;
    }
    void calculateWValues(const std::string& k, HASH_INDEX_T w[5]) const
    {
        // Insert leading characters to the string until it reaches exactly
        // 30 characters. This gets rid of unnecessary checks for the size
        // of the string when trying to get the substring.
        std::string word{ k };
        while(word.size() < 30)
        {
            word = "a" + word;
        }

        // Calculate the w values to be used when calculating the hash value.
        for(int i{ 0 }; i < 5; ++i)
        {
            unsigned long startIndex{ word.size() - 6 * (i + 1) };
            std::string sixLetters{ word.substr(startIndex, 6) };
            for(unsigned int j{ 0 }; j < sixLetters.size(); ++j)
            {
                HASH_INDEX_T intermediary{ static_cast<HASH_INDEX_T>(std::pow(26, sixLetters.size() - 1 - j)) };
                intermediary *= letterToNumber(sixLetters[j]);
                w[4 - i] += intermediary;
            }
        }
    }
    HASH_INDEX_T letterToNumber(char letter) const
    {
        static unsigned int a = 97;
        char lower{ static_cast<char>(std::tolower(letter)) };
        return static_cast<HASH_INDEX_T>(lower - a);
    }

    void generateRValues()
    {
        srand(time(0));
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = rand();
        }
    }

};

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
        // Calculate the w values for use in the hash function.
        HASH_INDEX_T w[5]{ 0, 0, 0, 0, 0 };
        calculateWValues(k, w);

        // Calculate the hash value using the r values that were generated, then return
        // the final hash value.
        HASH_INDEX_T hashValue{ 0 };
        for(int i{ 0 }; i < 5; ++i)
        {
#ifdef DEBUG
            std::cout << "w[" << i << "] = " << w[i] << std::endl;
#endif
            hashValue += rValues[i] * w[i];
        }
        return hashValue;
    }
    void calculateWValues(const std::string& k, HASH_INDEX_T w[5]) const
    {
        size_t processed = 0;
        while(processed != k.size()){
            if(k.size() - processed < 6 ){
                HASH_INDEX_T currW = 0;
                for(size_t j = 0; j < k.size()-processed; j++){
                    currW = currW*36 + letterDigitToNumber(k[j]);   
                }
#ifdef DEBUG
//                std::cout << "Setting w idx=" << 4-processed/6 << " to " << currW << std::endl;
#endif
                w[4 - processed/6]  = currW;
                processed = k.size();
            }
            else {
                // a full 6 exists
                HASH_INDEX_T currW = 0;
                for(size_t j = k.size()-processed-6; j < k.size()-processed; j++){
                    currW = currW*36 + letterDigitToNumber(k[j]);   
                }
#ifdef DEBUG
//                std::cout << "Setting w idx=" << 4-processed/6 << " to " << currW << std::endl;
#endif
                w[4 - processed/6]  = currW;
                processed += 6;
            }
#ifdef DEBUG
//            std::cout << "Processed now = " << processed << std::endl;
#endif
        }
    }
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if('0' <= letter && letter <= '9') {
            return static_cast<HASH_INDEX_T>(letter - '0' + 26);
        }
        else {
            return static_cast<HASH_INDEX_T>(std::tolower(letter) - 'a');
        }
    }

    // Add code to generate the random R values
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

struct SumHash {
   
    SumHash()
    {
    }
    HASH_INDEX_T operator()(const std::string& k) const
    {
        HASH_INDEX_T sum = 0;
        for(HASH_INDEX_T i=0; i < k.size(); i++){
            sum += k[i];
        }
        return sum;
    }

};
#endif

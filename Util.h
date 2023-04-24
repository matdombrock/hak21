#pragma once
#include <iostream>

class Util{
public:
    // Output some text to the console
    template<typename T = std::string>
    static void echo(T input){
        std::cout << input << std::endl;
    }

    // Output some special (alert) text to the console
    // Bold red
    // https://stackoverflow.com/a/2616912
    static void alert(std::string str){
        echo("\033[1;31m"+str+"\033[0m");
    }

    // Read a line of CLI input
    template<typename T = std::string>
    static T readLine(std::string prompt = "> "){
        T input;
        std::cout << "\033[1;32m" << prompt << "\033[0m";
        std::cin >> input;
        return input;
    }

    // Returns the greater of 2 values
    template<typename T = int>
    static T greater(T a, T b){
        return a > b ? a : b;
    }

    // Returns the lesser of 2 values
    template<typename T = int>
    static T lesser(T a, T b){
        return a > b ? b : a;
    }

    // Returns a value bound between min and max
    template<typename T = int>
    static T bound(T val, T min, T max){
        val = Util::lesser(val, max);
        val = Util::greater(val, min);
        return val;
    }

    // Prints 1024 empty lines to the console
    static void clearScreen(){
        for(int i = 0; i < 1024; i++){
            echo("");
        }
    }

};
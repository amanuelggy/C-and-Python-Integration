import re
import string


def printsomething():
    print("Hello from python!");

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v;

def DoubleValue(v):
    return v * 2;

def printMenu():
    print("1: Display a Multiplication Table");
    print("2: Double a value");
    print("3: Exit");
    print("Enter your selection as a number 1, 2 or 3. Use 99 to stop the program.");

def error():
    print("Error: please enter number 1, 2, or 3.")

def MultiplicationTable(v):
    for i in range(1,11):
        print("{0} * {1} = {2}".format(v, i, (v * i)));
    return 0;



    

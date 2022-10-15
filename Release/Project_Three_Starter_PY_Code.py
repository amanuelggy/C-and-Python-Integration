import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def printMenu():
    print("\n");
    print("1: Display the number of times each individual item appears");
    print("2: Determine the frequency of a specific item");
    print("3. Display the data file as a text-based histogram");
    print("4: Exit");

def DisplayItems(item):
    print(item);
    return 0;

def DisplaySearchResult(item):
    print("Search Result: " + item);
    return 0;
    

def Error():
    print("Error: please enter number 1, 2, 3, or 4.")

    

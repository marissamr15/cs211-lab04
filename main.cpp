/*main.cpp*/

/**
  * @brief Silly animal program that stores animals in a map
  *
  * Silly animal program with animals, and how many we own,
  * in a map. The program starts by using the built-in std::map,
  * then we switch over to our implementation of map using a 
  * linked-list.
  * 
  * @note Prof. Joe Hummel
  * @note Northwestern University
 */

#include <iostream>
#include <map>
#include <string>
#include <cctype>

// #include <map>
#include "mapll.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;


/**
  * @brief returns true if s is an integer string, false if not
  *
  * @param s is a string of characters
  * @return true if all the characters are integer digits, false if not
  */
bool is_int(string s)
{
  for (char c : s) {
    if (!std::isdigit(c))
      return false;
  }
  
  //
  // if get here, then all the chars were digits:
  //
  return true;
}


/**
  * @brief prints all the animals in the map.
  *
  * @param animals is the map to print
  * @return nothing
  */
void printall(map<string, int>& animals)
{
  //
  // NOTE: we are using foreach to loop through map. Requires
  // a begin() method in the map class, and 3 methods in the 
  // iterator class: operator!=, operator++, and operator*.
  // These have been implemented for you in "mapll.h" if 
  // you're curious.
  //
  for (auto kv_pair : animals)
    cout << "(" << kv_pair.first << "," << kv_pair.second << ") ";

  cout << endl;
}


/**
  * @brief main
  *
  * @return 0 denoting successful execution
  */
int main()
{
  int count = 0;
  map<string, int> animals;

  //
  // insert some animals to get started:
  //
  animals["elephant"] = 1;
  animals["cat"] = 3;
  animals["owl"] = 1;
  animals["dog"] = 2;
  animals["bear"] = 1;
  animals["moth"] = 9;
  animals["pig"] = 4;
  animals["ferret"] = 6;
  animals["zebra"] = 1;

  //
  // input commands and animals from the user:
  //
  while (true) {
    count = count + 1;

    string type;

    cout << ">> Enter a type of animal: ";
    cin >> type;

    if (type == "$") {
      break;
    }
    else if (type == "#") {  // # of animals:

      cout << "# of animals: " << animals.size() << endl;

    }
    else if (type == "*") {  // list all animals:

      printall(animals);

    }
    else if (is_int(type)) { // list all the animals where value >= min:
   
      int min = std::stoi(type);
      
      //
      // We could just foreach through and output ourselves, but the
      // challenge is to create an iterator and pass it the min value,
      // and then as we iterate through the map with ++, the iterator
      // object skips over the animals where value < min.
      //
      
     // cout << "TODO" << endl;
      
      auto iter = animals.begin(min);
      while (iter != animals.end()) {
      //  
         cout << "(" << iter->first << "," << iter->second << ") ";
      //   
         ++iter;
      }
      cout << endl;
      
    }
    else if (type == "-") {  // delete:

      cin >> type;

      int result = animals.erase(type);

      if (result == 1)
        cout << "deleted" << endl;
      else
        cout << "not deleted" << endl;
    }
    else if (type == "+") {  // insert or increment:

      cin >> type;

      animals[type] = (animals[type] + 1);

      cout << "I now own " << animals[type] << " " << type << endl;
    }
    else { // search for animal, output how many I own (if any):

      //std::cout << "I own " << animals[type] << " " << type << std::endl;
      auto iter = animals.find(type);

      if (iter == animals.end()) {
        cout << "I don't own any " << type << endl;
      }
      else {
        cout << "I own " << iter->second << " " << type << endl;
      }
       
    
    } 

    cout << endl;

  }//while
  cout << "Count: " << count << endl;
  return 0;
}

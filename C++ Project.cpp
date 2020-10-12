//
//  main.cpp
//  Midterm_Alan
//
//  Created by Alan on 2020/1/20.
//  Copyright © 2020 Alan. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct people{
    string name;
    int age;
    char gender;
};


class Resident : public people {
    // attributes
private:
    int aptNumber;
    
public:
    // constructor
    Resident(int aptNumber){
        this->aptNumber = aptNumber;
        name = "";
        age = 0;
        gender = ' ';
    }
    Resident(string name, int age, char gender){
        this->name = name;
        this->age = age;
        this->gender = gender;
    }
    
    // functions
    // modifiers
    int getAptNumber(){
        return aptNumber;
    }
    void changeAptNumber(int aptNum){
        aptNumber = aptNum;
    }
    string getName(){
        return name;
    }
    void changeName(string newName){
        name = newName;
    }
    int getAge(){
        return age;
    }
    void changeAge(int newAge){
        age = newAge;
    }
    char getGender(){
        return gender;
    }
    void changeGender(char newGender){
        gender = newGender;
    }
    void erase(){
        name = "";
        age = 0;
        gender = ' ';
    }
    
};


class Building{
    int levels;
    int suitsPerLevel;
    vector<Resident> residentList;
    
public:
    
    // constructor
    Building(){
        levels = 3;
        suitsPerLevel = 4;
        for (int i=1; i<=levels; i++){
            for (int j=1; j<=suitsPerLevel; j++){
                Resident temp(i*100 + j);
                residentList.push_back(temp);
            }
        }
    }
    
    // functions
    // add resident
    int findAvaliableApt(){
        for (int i=0; i<residentList.size(); i++){
            if (residentList[i].getName() == ""){
                return i;
            }
        }
        return -1;
    }
    bool addResident(Resident *res){
        int index = findAvaliableApt();
        if (index != -1){
            Resident *pointer = &residentList[index];
            pointer->changeAge(res->getAge());
            pointer->changeName(res->getName());
            pointer->changeGender(res->getGender());
            res->changeAptNumber(pointer->getAptNumber());
            return true;
        }
        else {
            return false;
        }
        
    }
    
    // find resident by apartment number
    // return index
    int indexOfAptNum(int aptNum){
        for (int i=0; i<residentList.size(); i++){
            if (residentList[i].getAptNumber() == aptNum){
                return i;
            }
        }
        return -1;
    }
    
    // delete resident
    bool deleteResidentByAptNum(int aptNum){
        int index = indexOfAptNum(aptNum);
        if (index == -1){
            return false;
        }
        else{
            residentList[index].erase();
            return true;
        }
    }
    
    // output resident information
    void searchAndPrint(int aptNum){
        int index = indexOfAptNum(aptNum);
        if (index != -1){
            cout << "Apartment number: " << aptNum << endl <<
            "Name: " << residentList[index].getName() << endl <<
            "Age: " << residentList[index].getAge() << endl <<
            "Gender: " << residentList[index].getGender() <<endl;
        }
        else {
            cout << "Wrong apartment number." << endl;
        }
    }
    
    // output all residents' information
    void outputAll(){
        for(int i = 0; i<residentList.size(); i++){
            cout << "Resident " << i+1 << endl <<
            "Apartment number: " << residentList[i].getAptNumber() << endl <<
            "Name: " << residentList[i].getName() << endl <<
            "Age: " << residentList[i].getAge() << endl <<
            "Gender: " << residentList[i].getGender() << endl;
        }
    }
    
    
};



int main(int argc, const char * argv[]) {
    
    // initialize building
    Building b;
    cout << "Welcome to Condo System" << endl;
    while (true){
        
        cout << "Please enter a number for choice:" << endl <<
        "1. Add a resident" << endl <<
        "2. Output resident information" << endl <<
        "3. delete resident by apartment number" << endl <<
        "4. Exit" << endl <<
        "____________________" << endl;
        
        int choice;
        cout << "Please enter your number: ";
        cin >> choice;
        cout << "____________________" << endl;
        // add resident, input name, age, gender
        if (choice == 1){
            string name;
            cout << "Please enter resident name: ";
            cin >> name;
            int age;
            cout << "Please enter resident age: ";
            cin >> age;
            char gender;
            cout << "Please enter resident gender(M/F): ";
            cin >> gender;
            
            Resident *res = new Resident(name, age, gender);
            bool ifAdded = b.addResident(res);
            
            if (ifAdded){
                cout << "Thanks, " << name << " is registered to apartment " << res->getAptNumber() << endl;
            }
            else {
                cout << "Sorry, register fail, building is full." << endl;
            }
            
            cout << "____________________" << endl;
        }
    
        // output information
        else if(choice == 2){
            cout << "1. Search your information" << endl <<
            "2. output all resident information" << endl;
            
            int searchChoice;
            cout << "Please enter your number: ";
            cin >> searchChoice;
            cout << "____________________" << endl;
            // search resident by apartment number, output the information
            if (searchChoice == 1){
                int aptNum;
                cout << "Please enter your apartment number: ";
                cin >> aptNum;
                b.searchAndPrint(aptNum);
            }
            // output all residents' information
            else if (searchChoice == 2){
                b.outputAll();
            }
            else {
                cout << "Wrong input." << endl;
            }
            cout << "____________________" << endl;
        }
    
    
        // delete on resident by apartment number
        else if(choice == 3){
            int aptNum;
            cout << "Please enter your apartment number: ";
            cin >> aptNum;
            bool ifDeleted = b.deleteResidentByAptNum(aptNum);
            if(ifDeleted){
                cout << "Deleted." << endl;
            }
            else {
                cout << "Sorry, fail to delet." << endl;
            }
        }
    
        // exit
        else if(choice == 4){
            cout << "Quit the system." << endl;
            return 0;
        }
        
    }
    
    return 0;
}

//Rae Decastro
//CS 320 01
//Assignment - METAL HEAD

#include <iostream>
#include <utility> 
#include <vector> 
#include <cmath> 
using namespace std;

class g1{
    vector<double> stringNotes;
    int numFrets;  
    public:  
    g1(){ //Initializing notes EADBGE using vector class/library
        stringNotes.push_back(82.4); //low E - string 1
        stringNotes.push_back(110);  //A - string 2
        stringNotes.push_back(146.8);//D - string 3
        stringNotes.push_back(196);  //B - string 4
        stringNotes.push_back(246.9);//G - string 5
        stringNotes.push_back(329.6);//high E - string 6
        numFrets = 21;
    }
    
    g1(const g1 &guitar) { //contructor
    stringNotes = guitar.stringNotes;
    numFrets = guitar.numFrets;

    }
    //method makes sure that the number of frets are within the acceptable range
    bool setFretBoardLength(const unsigned int numberOfFrets) { 
        if (numberOfFrets>=1 && numberOfFrets <= 24) {
        numFrets = numberOfFrets;
        return true;
        }
        else
        return false;
    }
    //method calculate the pitch of a given string number and fret number
    //considers fret = 0 (open)
    double pitchAt(const unsigned int &stringNumber, const unsigned int &fretNum) {
       switch(stringNumber) {
            case '1': return stringNotes[0] * pow(2, fretNum / 12.0); break;
            case '2': return stringNotes[1] * pow(2, fretNum / 12.0); break;
            case '3': return stringNotes[2] * pow(2, fretNum / 12.0); break;
            case '4': return stringNotes[3] * pow(2, fretNum / 12.0); break;
            case '5': return stringNotes[4] * pow(2, fretNum / 12.0); break;
            case '6': return stringNotes[5] * pow(2, fretNum / 12.0); break;
        }
      return 0;
    }
    //method changes the tune of a single string into a specified frequency
    void tuneString(unsigned char& stringNote, const double& pitchChange) {
        switch(stringNote) {
            case '1': stringNotes[0] = pitchChange; break;
            case '2': stringNotes[1] = pitchChange; break;
            case '3': stringNotes[2] = pitchChange; break;
            case '4': stringNotes[3] = pitchChange; break;
            case '5': stringNotes[4] = pitchChange; break;
            case '6': stringNotes[5] = pitchChange; break;
        }
    }
    // method to find the combination of string and fret (as a pair) that can produce a given pitch
    //goes through all the possible combination of String 1-6 and fret 0-24 to find the closest value of the given pitch
    std::pair<unsigned char, unsigned int> getStringAndFret(double pitch) {
    vector<double> allPossiblePitch;
    vector<pair<unsigned char, unsigned int>>combinations;//
       for (int i = '1'; i <= '6'; i++) {
           for (int j = 0; j <= numFrets; j++) {
           combinations.push_back(make_pair(i, j));//
           allPossiblePitch.push_back(stringNotes[i - '0' - 1] * pow(2, j / 12.0));
           }
       }

       double absDiff = abs(allPossiblePitch[0] - pitch);
       int index = 0; 
        for (int i = 1; i < allPossiblePitch.size(); i++ ) {
           if ( abs(allPossiblePitch[i] - pitch) < absDiff ) {
           index = i;
           absDiff = abs(allPossiblePitch[i] - pitch);
           }
        }

    return combinations[index];

    }
  
};  //end g1 class

int main(){
    //tests the public methods of the class g1
    g1 guitar;
    pair<unsigned char, unsigned int> g = guitar.getStringAndFret(220.0); 
    unsigned char stringNum = '3';

    // prints the pitch produce by strumming string 3 while pushing on fret 5 w/o tuning
    cout<<"The pitch of string 3 and fret 5 is "<< guitar.pitchAt('3',5)<<" Hz"<<std::endl;
    guitar.tuneString(stringNum, 196.0);//tunes string 3 to 196.0 Hz  
    //prints the new pitch value of string 3 and fret 5 after string 3 is tuned to 196.0 Hz
    cout<<"The pitch of string 3 and fret 5 after string 3 was tuned to 196.0 Hz is now "<< guitar.pitchAt('3',5)<<" Hz"<<std::endl;
    //prints one possible combination of the string number and fret number that can produce a pitch of 220 Hz
    cout<< "220.0 Hz pitch is from the combination of string number:"<< g.first << " and fret number:"<< g.second << endl;
    
    return 0;

}




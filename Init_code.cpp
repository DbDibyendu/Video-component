/** @file Init_code.cpp
 *  @brief Initialisation API's
 *  
 *  @author Dibyendu 
 *  @bug I didn't find any  
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* --- Standard Includes --- */

#include <iostream> 


/* --- Project Includes --- */
using namespace std; 

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */


class Init{

    public:
    string c_id, v_id;                              // creating variables for storing the device ids

// Creating a constructor for creating object in main

    Init(){
    
    }

    void Initialise_camera(){

    cout<<ListActivecamera();                   // lists all the camera ids available

    cin>>c_id;                                      // gets the camera id from user
    
    cout<<ReadCameraSettings(c_id);

    InitCamera(c_id);


    }

    void Initialise_Vsource(){

        string new;

        cin>>new;                               // getting new virtual source name from the user;
        
        CreateVirtualSource(new);                   // creating a new virtual source using the API

        cout<<ListVirtualSource();                  // List all the existing Virual source

        cin>>v_id;                                  // gets the virtual source Id from the user

        cout<<ReadVirtualSourceSettings(v_id)<<endl;

        InitVirtualSource(v_id);
        

    }

};



/** 
 *  @brief Description on main
 *  
 * 
 *  @return List all Function returns 
 */

int main(){

    Init device;

    char a;
    cout<<"Choose camera or virtual source  c or v" <<endl;
    cin>>a;
    if(a =='c')
    device.Initialise_camera();

    else if(a == 'v')
    device.Initialise_Vsource();

    else cout<<"Error"<<endl;
    

            
    return 0;
}
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
#include <bits/stdc++.h> 

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
// Creating  a function for Initialising Camera

    int Initialise_camera(){

    if(ListActiveCamera.empty()){
        cout<<"No camera found"<<endl;
        return -1;
    }

    else
    cout<<"List of cameras"<<ListActiveCamera()<<endl;                   // lists all the camera ids available


    cin>>c_id;                                      // gets the camera id from user
    
    if(ReadCameraSettings(c_id).empty()){
        cout<<"Error in opening file"<<endl;
        return -1;
    }
    else
    cout<<"Camera settings of:"<<c_id<<ReadCameraSettings(c_id);


    if(InitCamera(c_id)){
        cout<<"Camera initialised successfully"<<endl;
        return 1;
    }
    else
    {
        cout<<"Error in initialisation"<<endl;
        return -1;
    }
    


    }
// Creating a function to Initialise VirtualSource

    int Initialise_Vsource(){

        string new;

        cin>>new;                               // getting new virtual source name from the user;
        
        if(CreateVirtualSource(new)){               // creating a new virtual source using the API

            cout<<"Successfully created new VirtualSource with name "<<new<<endl;
        }                                        
        else 
        cout<<"Failed to create VirtualSource"<<endl;       
                           


        if(ListActiveCamera.empty()){
        cout<<"No VirtualSource found"<<endl;
        return -1;

        }

        else
        cout<<"List of VirtualSource:"<<ListVirtualSource()<<endl;                // List all the existing Virual source
     

        cin>>v_id;                                  // gets the virtual source Id from the user

        if(ReadVirtualSourceSettings(v_id).empty()){
            cout<<"Error in opening the settings"<<endl;
            return -1;
        }
        else
        cout<<ReadVirtualSourceSettings(v_id)<<endl;


        if(InitVirtualSource(v_id)){

            cout<<"Camera initialised successfully"<<endl;
            return 1;
        
        }
        else
        {
            cout<<"Error in initialisation"<<endl;
            return -1;
        }
        

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
    if(a == 'c')
    device.Initialise_camera();

    else if(a == 'v')
    device.Initialise_Vsource();

    else cout<<"Error"<<endl;
    

            
    return 0;
}
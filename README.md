## Video Component


### Psuedo codes and flowcharts for the functions and code

##### 1. `loadJsonConfig()`

This function Parse and store JSON document into global variable

###### Flowchart
![](https://github.com/DbDibyendu/Video-component/blob/master/Images/mermaid-diagram-20200912132203.png)

###### Psuedo code

        initialise a var ret = -1 for returning
        Open the config.json file in read mode
        
        if file is not empty{
            
            Declare readbuffer
            Declare stream for reading the config file
            Parse config.json and store it in config global var
            Store the result in ok
            
            if it is empty{
                Print the JSON parse error
                
            end
            }
            
            set ret = 0;
            
         end
        }
        
        else if file is empty{
            
            Print Error in reading JSON file
        end
        }
        
        
        close the file
        return -1 
        
        end
        

##### 2. `ListActiveCamera()`

This Function Prints out all the available device

It Uses `<glob.h>` and `<unistd.h>` libraries to do so

###### Flowchart

![](https://github.com/DbDibyendu/Video-component/blob/master/Images/mermaid-diagram-20200912132212.png)


##### 3. `initCamera()`

It Initialises the camera by opening it's location and `returns` the following integer variable i.e.**fd**


###### Flowchart

![](https://github.com/DbDibyendu/Video-component/blob/master/Images/mermaid-diagram-20200912132221.png)

##### 4. `ReadCameraSettings()`

This function Prints out the Settings of the device entered by user which is stored in the respective Object in the main function

###### Flowchart

![](https://github.com/DbDibyendu/Video-component/blob/master/Images/mermaid-diagram-20200912132235.png)

##### 5. `CaptureFrametoMem()`

This function Starts the following device and captures a frame and store it into Memory

###### Flowchart

![](https://github.com/DbDibyendu/Video-component/blob/master/Images/mermaid-diagram-20200912132251.png)



##### 6. `CaptureStreamtoMem()`

This function Parse and store JSON document into global variable

###### Flowchart

![](https://github.com/DbDibyendu/Video-component/blob/master/Images/mermaid-diagram-20200912132304.png)

### Info about the config.json file

It contains The `Device Number`


## Video Component

**Code Links:**

1.OpenCV      
2.webcam_capture.cpp - https://gist.github.com/mike168m/6dd4eb42b2ec906e064d

Run commands:

               1. g++ code1.cpp -L/path/to/my/openCV/lib   -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_objdetect -lopencv_imgcodecs -lopencv_calib3d -lopencv_videoio -ltsanalyser

               2. g++ code2.cpp -ltsanalyser
      

### Table

| Code | Time Taken | Peak RAM Consumed | CPU Usage | Storage size of a dependency/library | Lines of code|
| ------ | ------ | -------------- | ---------- | --------- | ---------- |
| Code1 | 0.076168 secs  | 46 MB  |   0.093 CPUs utilized  | Size of OpenCV lib | 58 |  
| Code2 | 0.003325 secs  | 3 MB |  0.006 CPUs utilized  | NIL(no additional lib) | 179 |
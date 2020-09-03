#include <fstream>
#include <cstdlib>
#include <string>
#include <errno.h>

/* --- include/rapidjson Includes --- */

#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/error/en.h"


/* --- Project Includes --- */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/v4l2-common.h>
#include <linux/v4l2-controls.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include <fstream>
#include <string>
#include <tsanalyser/tsanalyser.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <linux/videodev2.h>

#include <linux/videodev.h>
#include <glob.h>
#include <unistd.h>

void list_videos() {
  int i;
  glob_t globbuf;
  if (glob("/dev/v4l/by-path/*", 0, NULL, &globbuf) != 0) {
    perror("glob");
    return;
  }
  for (i=0; i < globbuf.gl_pathc; i++) {
    char buf[256] = {};
    if (readlink(globbuf.gl_pathv[i], buf, sizeof(buf)-1) > 0) {
      puts(buf);
    }
  }
}

int main(){
    list_videos();
    int fd;
    struct video_capability video_cap;
    struct video_window     video_win;
    struct video_picture   video_pic;

    if((fd = open("/dev/video0", O_RDONLY)) == -1){
        perror("cam_info: Can't open device");
        return 1;
    }

    if(ioctl(fd, VIDIOCGCAP, &video_cap) == -1)
        perror("cam_info: Can't get capabilities");
    else {
        printf("Name:\t\t '%s'\n", video_cap.name);
        printf("Minimum size:\t%d x %d\n", video_cap.minwidth, video_cap.minheight);
        printf("Maximum size:\t%d x %d\n", video_cap.maxwidth, video_cap.maxheight);
    }

    if(ioctl(fd, VIDIOCGWIN, &video_win) == -1)
        perror("cam_info: Can't get window information");
    else
        printf("Current size:\t%d x %d\n", video_win.width, video_win.height);

    if(ioctl(fd, VIDIOCGPICT, &video_pic) == -1)
        perror("cam_info: Can't get picture information");
    else
        printf("Current depth:\t%d\n", video_pic.depth);

    close(fd);
    return 0;
}
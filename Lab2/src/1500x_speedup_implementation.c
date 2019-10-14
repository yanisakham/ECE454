#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"  // DO NOT REMOVE this line
#include "implementation_reference.h"   // DO NOT REMOVE this line

struct color{
    unsigned char R,G,B;
};

struct non_white_data{
    int row, col;
    struct color c;
};
void transform(unsigned char*frame, int up, int right,int clockwise,bool mx,bool my, int height,int width,struct non_white_data* data,int id);

#define white 0xffffff
#define times3(x) ((x<<1)+x)
#define div2(x) (x>>1)
#define CW1(col, row, width, newcol, newrow) newrow =col; newcol=width-1-row
#define CW2(col, row, width, height, newcol, newrow) newrow =height-1-row; newcol = width-1-col
#define CW3(col, row, width, height, newcol, newrow) newrow =height-1-col; newcol = row
#define MX(col, row, height, newcol, newrow) newrow = height-1-row; newcol = col
#define MY(col, row, width, newcol, newrow) newrow = row; newcol = width-1-col

void transform(unsigned char*frame, int up, int right,int clockwise,bool mx,bool my, int height,int width, struct non_white_data* data_array, int id){
    struct color * r_frame = (struct color *) frame;
    int x1, x2, y1, y2;
    for (int i = 0; i< id; i++){
        struct non_white_data data = data_array[i];
        y1 = data.row - up;
        x1 = data.col + right;
        x2 = x1;
        y2 = y1;
        // printf("old %d %d \n", y2, x2);
        if (clockwise){
            // printf("CLOCK %d", clockwise);
            switch(clockwise){
                case 1:
                    CW1(x1, y1, width, x2, y2); break;
                case 2:
                    CW2(x1, y1, width, height, x2, y2); break;
                case 3:
                    CW3(x1, y1, width, height, x2, y2); break;
            }
            x1 = x2;
            y1 = y2;
        }
        // printf("newxy %d %d \n", y2, x2);
        if (mx){
            MX(x1, y1, height, x2, y2);
            x1 = x2;
            y1 = y2;
        }
        // printf("newxy %d %d \n", y2, x2);
        if (my){
            MY(x1, y1, width, x2, y2);
            x1 = x2;
            y1 = y2;
        }
        int pos = (y2*width + x2);
        data_array[i].row = y2;
        data_array[i].col = x2;
        // printf("x y %d %d \n", y2, x2);
        // printf("place %d %d %d \n", data.c.R,data.c.G,data.c.B);
        r_frame[pos] = data.c;
        
    }
    // frame = (unsigned char *) r_frame; 
    return;
}

/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          Do not forget to modify the team_name and team member information !!!
 **********************************************************************************************************************/
void print_team_info(){
    // Please modify this field with something interesting
    char team_name[] = "team-koala";

    // Please fill in your information
    char student_first_name[] = "yanisa";
    char student_last_name[] = "khambanonda";
    char student_student_number[] = "1003883005";

    // Printing out team information
    printf("*******************************************************************************************************\n");
    printf("Team Information:\n");
    printf("\tteam_name: %s\n", team_name);
    printf("\tstudent_first_name: %s\n", student_first_name);
    printf("\tstudent_last_name: %s\n", student_last_name);
    printf("\tstudent_student_number: %s\n", student_student_number);
}

/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          You can modify anything else in this file
 ***********************************************************************************************************************
*/
void implementation_driver(struct kv *sensor_values, int sensor_values_count, unsigned char *frame_buffer,
                           unsigned int width, unsigned int height, bool grading_mode) {
  // printf("1"); 
    // printf("SIZE OF COLOR %d, DATA %d", (sizeof(struct color)),sizeof(struct non_white_data));

    struct non_white_data * data= (struct non_white_data *) malloc(width*height*sizeof(struct non_white_data));
    struct color* frame = (struct color*) frame_buffer;
    // for (int j = 0; j < 20; j++){
    //     printf("%s %s %s \n", frame[j].R, frame[j].B, frame[j].G);
    // }
    int data_id = 0;
    int row_width = times3(width);
    int rw = 0;
    int c3;
    struct color pixel;
    struct color white_pixel = {0xff,0xff,0xff};
    int w3 = times3(width);
    char * white_row = (char*) malloc(row_width);
    memset(white_row, white, row_width);
    for (int row = 0; row < height; row ++){
        if(memcmp(&frame[rw],white_row, row_width)){
            for (int column = 0; column < width; column +=1){
                pixel = frame[rw];
                if(memcmp(&frame[rw], &white_pixel, sizeof(struct color))){
                    data[data_id].c =pixel;
                    data[data_id].row = row;
                    data[data_id].col = column;
                    data_id += 1;
                } 
                rw += 1;
            }
        }
        else{
            rw += width;    
        }
    }
    free(white_row);
   // printf(" old data %d",width*height*sizeof(struct non_white_data));
    data = realloc(data, data_id*sizeof(struct non_white_data));
   // printf(" new data %d index %d",sizeof(data),id);
    // printf("DATA ARRAY \n");
    // for (int i=0; i< data_id; i ++){
    //     printf(" x %d, y %d \n",data[i].row, data[i].col);
    //     printf(" %d %d %d",data[i].c.R,data[i].c.G,data[i].c.B);
    // }
    // printf("DATA ARRAY \n");

    int processed_frames = 0, up = 0, right = 0, clockwise = 0;
    bool mx = false, my = false;
    int val;
    char * key;
    for (int sensorValueIdx = 0; sensorValueIdx < sensor_values_count; sensorValueIdx++) {
        val = sensor_values[sensorValueIdx].value;
        key = sensor_values[sensorValueIdx].key;

        // IF UP:
        if (!strcmp(key, "W")) {
            if (clockwise&&mx){
                switch(clockwise){
                    case 1: // 90 deg clockwise
                        right += val; break;
                    case 2: // 180 deg
                        up += val; break;
                    case 3: // 270 deg clockwise
                        right -= val; break;
                }
            }
            else if (clockwise){
                switch(clockwise){
                    case 1: // 90 deg clockwise
                        right -= val; break;
                    case 2: // 180 deg
                        up -= val; break;
                    case 3: // 270 deg clockwise
                        right += val; break;
                }
            }
            else if (mx){
                up -= val;
            }
            else{
                up += val;
            }
        }else if (!strcmp(key, "S")) {
            if (clockwise && mx){
                switch(clockwise){
                    case 1: // 90 deg clockwise
                        right -= val; break;
                    case 2: // 180 deg
                        up -= val; break;
                    case 3: //270 deg clockwise
                        right += val; break;
                }
            }else if (clockwise){
                switch(clockwise){
                    case 1: // 90 deg clockwise
                        right += val; break;
                    case 2: // 180 deg
                        up += val; break;
                    case 3: //270 deg clockwise
                        right -= val; break;
                }
            }
            else if (mx){
                up += val;
            }
            else{
                up -= val; 
            }
        }else if (!strcmp(key, "A")) {
            if (clockwise&& my){
                switch(clockwise){
                    case 1:
                        up += val; break;
                    case 2:
                        right -= val; break;
                    case 3:
                        up -= val; break;
                }
            }
            else if (clockwise){
                switch(clockwise){
                    case 1:
                        up -= val; break;
                    case 2:
                        right += val; break;
                    case 3:
                        up += val; break;
                }
            }else if (my){
                right += val;
            }else{
                right -= val;
            }
        }else if (!strcmp(key, "D")) {
            if (clockwise&&my){
                switch(clockwise){
                    case 1:
                        up -= val; break;
                    case 2:
                        right += val; break;
                    case 3:
                        up += val; break;
                }
            }
            else if (clockwise){
                switch(clockwise){
                    case 1:
                        up += val; break;
                    case 2:
                        right -= val; break;
                    case 3:
                        up -= val; break;
                }
            }else if (my){
                right -= val;
            }else{
                right += val;
            }
        }else if (!strcmp(key, "CW")) {
            val = val%4;
            if (mx){
                switch(val){
                    case 0:
                        break;
                    case 1:
                        clockwise += 3; break;
                    case 2:
                        mx = !mx;
                        my = !my; break;
                    case 3:
                        clockwise += 1; break;
                }
            }else if (my){
                switch(val){
                    case 0:
                        break;
                    case 1:
                        clockwise += 3; break;
                    case 2:
                        mx = !mx;
                        my = !my; break;
                    case 3:
                        clockwise += 1; break;
                }
            }
            else{
                clockwise += val;
            }
        }else if (!strcmp(key, "CCW")) {
            val = 4-(val%4);
            if (mx){
                switch(val){
                    case 0:
                        break;
                    case 1:
                        clockwise += 3; break;
                    case 2:
                        mx = !mx;
                        my = !my; break;
                    case 3:
                        clockwise += 1; break;
                }
            }else if (my){
                switch(val){
                    case 0:
                        break;
                    case 1:
                        clockwise += 3; break;
                    case 2:
                        mx = !mx;
                        my = !my; break;
                    case 3:
                        clockwise += 1; break;
                }
            }
            else{
                clockwise += val;
            }
        }else if (!strcmp(key, "MX")) {
            mx=!mx;
            if(mx&&my){
                mx = !mx;
                my = !my;
                clockwise += 2;
            }   
        }else if (!strcmp(key, "MY")) {
            my=!my;
            if(mx&&my){
                mx = !mx;
                my = !my;
                clockwise += 2;
            }
        }
        clockwise = clockwise % 4;
        processed_frames +=1;
        if (processed_frames % 25 == 0) {
            // printf("U %d R %d C %d mx %d my %d", up, right, clockwise, mx, my);
            memset(frame, white, height*width*3);
            transform(frame_buffer, up, right, clockwise, mx, my, height, width, data, data_id);
            // printBMP(width, height, frame_buffer);
	        verifyFrame(frame_buffer, width, height, grading_mode);
            up = 0;right=0;clockwise=0;mx=false;my=false;
        }
    }
    free(data);
    return;
}

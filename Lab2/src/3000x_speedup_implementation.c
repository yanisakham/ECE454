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

void transform(unsigned char*frame, int up, int right,int clockwise,bool mx,bool my, int height,int width, struct non_white_data* data_array, int id){
    struct color * r_frame = (struct color *) frame;
    int i, x1, x2, y1, a1, b1, b2, c1, d1, d2, e1, f1, f2, g1, h1, h2, i1, j1, j2, k1, l1, l2, m1, n1, n2;
    int lim = id - 7;
    int w1 = width -1;
    int hh = height-1;
    struct non_white_data data, data2, data3, data4, data5, data6, data7, data8;
    for (i = 0; i< lim; i+=8){                          // LOOP UNROLL OF 8
        data = data_array[i];
        data2 = data_array[i+1];
        data3 = data_array[i+2];
        data4 = data_array[i+3];
        data5 = data_array[i+4];
        data6 = data_array[i+5];
        data7 = data_array[i+6];
        data8 = data_array[i+7];
        y1 = data.row - up;
        x1 = data.col + right;
        x2 = x1; //y2 = y1;        
        a1 = data2.row - up;
        b1 = data2.col + right;
        b2 = b1; //a2 = a1;
        c1 = data3.row - up;
        d1 = data3.col + right;
        d2 = d1; //c2 = c1; 
        e1 = data4.row - up;
        f1 = data4.col + right;
        f2 = f1; //e1 = e1; 
        g1 = data5.row - up;
        h1 = data5.col + right;
        h2 = h1; //g1 = g1; 
        i1 = data6.row - up;
        j1 = data6.col + right;
        j2 = j1; //i1 = i1; 
        k1 = data7.row - up;
        l1 = data7.col + right;
        l2 = l1; //k1 = k1; 
        m1 = data8.row - up;
        n1 = data8.col + right;
        n2 = n1; //m1 = m1; 
        if (clockwise){
            switch(clockwise){
                case 1:
                    if (mx){
                        x2 = w1-y1; y1 = hh-x1;
                        b2 = w1-a1; a1 = hh-b1;
                        d2 = w1-c1; c1 = hh-d1;
                        f2 = w1-e1; e1 = hh-f1; 
                        h2 = w1-g1; g1 = hh-h1;
                        j2 = w1-i1; i1 = hh-j1;
                        l2 = w1-k1; k1 = hh-l1;
                        n2 = w1-m1; m1 = hh-n1;break;
                    }
                    else if (my){
                        x2 = y1; y1 = x1;
                        b2 = a1; a1 = b1;
                        d2 = c1; c1 = d1;
                        f2 = e1; e1 = f1; 
                        h2 = g1; g1 = h1;
                        j2 = i1; i1 = j1;
                        l2 = k1; k1 = l1;
                        n2 = m1; m1 = n1; break;
                    }
                    else{
                        x2 = w1-y1; y1 = x1;
                        b2 = w1-a1; a1 = b1;
                        d2 = w1-c1; c1 = d1;
                        f2 = w1-e1; e1 = f1;
                        h2 = w1-g1; g1 = h1;
                        j2 = w1-i1; i1 = j1;
                        l2 = w1-k1; k1 = l1;
                        n2 = w1-m1; m1 = n1; break;
                    }
                case 2:
                    if (mx){
                        x2 = w1-x1 ; //y1 = y1;
                        b2 = w1-b1 ; //a1 = a1;
                        d2 = w1-d1 ; //c1 = c1;
                        f2 = w1-f1 ; //e1 = e1; 
                        h2 = w1-h1 ; //g1 = g1;
                        j2 = w1-j1 ; //i1 = i1;
                        l2 = w1-l1 ; //k1 = k1;
                        n2 = w1-n1 ; break; //m1 = m1; break; 
                    }
                    else if (my){
                        x2 = x1 ; y1 = hh-y1;
                        b2 = b1 ; a1 = hh-a1;
                        d2 = d1 ; c1 = hh-c1;
                        f2 = f1 ; e1 = hh-e1; //break;
                        h2 = h1 ; g1 = hh-g1;
                        j2 = j1 ; i1 = hh-i1;
                        l2 = l1 ; k1 = hh-k1;
                        n2 = n1 ; m1 = hh-m1; break;  
                    }
                    else{
                        x2 = w1-x1 ; y1 = hh-y1;
                        b2 = w1-b1 ; a1 = hh-a1;
                        d2 = w1-d1 ; c1 = hh-c1;
                        f2 = w1-f1 ; e1 = hh-e1; 
                        h2 = w1-h1 ; g1 = hh-g1;
                        j2 = w1-j1 ; i1 = hh-i1;
                        l2 = w1-l1 ; k1 = hh-k1;
                        n2 = w1-n1 ; m1 = hh-m1; break;    
                    }     
                case 3:
                    if (mx){
                        x2 = y1; y1 = x1; 
                        b2 = a1; a1 = b1;
                        d2 = c1; c1 = d1;
                        f2 = e1; e1 = f1;
                        h2 = g1; g1 = h1;
                        j2 = i1; i1 = j1;
                        l2 = k1; k1 = l1;
                        n2 = m1; m1 = n1; break;

                    }
                    else if (my){
                        x2 = w1-y1; y1 = hh-x1;
                        b2 = w1-a1; a1 = hh-b1;
                        d2 = w1-c1; c1 = hh-d1;
                        f2 = w1-e1; e1 = hh-f1; 
                        h2 = w1-g1; g1 = hh-h1;
                        j2 = w1-i1; i1 = hh-j1;
                        l2 = w1-k1; k1 = hh-l1;
                        n2 = w1-m1; m1 = hh-n1; break;
                    }
                    else{
                        x2 = y1; y1 = hh-x1; 
                        b2 = a1; a1 = hh-b1;
                        d2 = c1; c1 = hh-d1;
                        f2 = e1; e1 = hh-f1;
                        h2 = g1; g1 = hh-h1;
                        j2 = i1; i1 = hh-j1;
                        l2 = k1; k1 = hh-l1;
                        n2 = m1; m1 = hh-n1; break;
                    }
            }
        }
        else if (mx){
            y1 = hh-y1;   a1 = hh-a1;   c1 = hh-c1; e1 = hh-e1;
            g1 = hh-g1;   i1 = hh-i1;   k1 = hh-k1; m1 = hh-m1; break;
        }
        else if (my){
            x2 = w1-x1;    b2 = w1-b1;    d2 = w1-d1;    f2 = w1-f1;
            h2 = w1-h1;    j2 = w1-j1;    l2 = w1-l1;    n2 = w1-n1;
        }
        data_array[i].row = y1;
        data_array[i].col = x2;
        data_array[i+1].row = a1;
        data_array[i+1].col = b2;
        data_array[i+2].row = c1;
        data_array[i+2].col = d2;
        data_array[i+3].row = e1;
        data_array[i+3].col = f2;
        data_array[i+4].row = g1;
        data_array[i+4].col = h2;
        data_array[i+5].row = i1;
        data_array[i+5].col = j2;
        data_array[i+6].row = k1;
        data_array[i+6].col = l2;
        data_array[i+7].row = m1;
        data_array[i+7].col = n2;
        r_frame[y1*width + x2] = data.c;
        r_frame[a1*width + b2] = data2.c;   
        r_frame[c1*width + d2] = data3.c;  
        r_frame[e1*width + f2] = data4.c;       
        r_frame[g1*width + h2] = data5.c;       
        r_frame[i1*width + j2] = data6.c;       
        r_frame[k1*width + l2] = data7.c;       
        r_frame[m1*width + n2] = data8.c;       

    }
    // printf("%d",i);
    for (; i< id; i++){
        struct non_white_data data = data_array[i];
        y1 = data.row - up;
        x1 = data.col + right;
        x2 = x1;
        // y2 = y1;
        if (clockwise){
            switch(clockwise){
                case 1:
                    if (mx){
                        x2 = w1-y1; y1 = hh-x1; break;
                    }
                    else if (my){
                        x2 = y1; y1 = x1; break;
                    }
                    else{
                        x2 = w1-y1; y1 = x1; break;
                    }
                case 2:
                    if (mx){
                        x2 = w1-x1 ;break;
                    }
                    else if (my){
                        x2 = x1 ; y1 = hh-y1; break;
                    }
                    else{
                        x2 = w1-x1 ; y1 = hh-y1; break; 
                    }
                case 3:
                    if (mx){
                        x2 = y1; y1 = x1;    
                    }
                    else if (my){
                        x2 = w1-y1; y1 = hh-x1;
                    }
                    else{
                        x2 = y1; y1 = hh-x1; break;
                    }
            }
            // x1 = x2;
            // y1 = y2;
        }
        else if (mx){
            y1 = hh-y1;
            // y1 = y2;
        }
        else if (my){
            x2 = w1-x1;
            // x1 = x2;
        }
        data_array[i].row = y1;
        data_array[i].col = x2;
        r_frame[y1*width + x2] = data.c;
        
    }
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
    struct non_white_data * data= (struct non_white_data *) malloc(width*height*sizeof(struct non_white_data));
    struct color* frame = (struct color*) frame_buffer;
    int processed_frames = 0, up = 0, right = 0, clockwise = 0, data_id = 0, rw = 0, val;
    bool mx = false, my = false;
    char * key;
    int row_width = times3(width);
    struct color pixel;
    struct color white_pixel = {0xff,0xff,0xff};
    char * white_row = (char*) malloc(row_width);
    memset(white_row, white, row_width);
    
    int ratio = 15;
    int smallrow = width/ratio;
    int offsetrow = width%ratio;
    int offsetrow3 = times3(offsetrow);
    int smallrow3 = times3(smallrow);
    int i;
    int col;
    for (int row = 0; row < height; row ++){
        if(memcmp(&frame[rw],white_row, row_width)){
            int i;
            col = 0;
            for (i=0;i<ratio; i++){
                if(memcmp(&frame[rw],white_row,smallrow3)){
                    for (int column = 0; column < smallrow; column ++){
                        pixel = frame[rw];
                        if(memcmp(&pixel, &white_pixel, sizeof(struct color))){
                            data[data_id].c =pixel;
                            data[data_id].row = row;
                            data[data_id].col = col;
                            data_id += 1;
                        }
                        rw += 1;
                        col += 1;
                    }
                }
                else{
                    rw += smallrow;
                    col += smallrow;
                }
            }
            if(memcmp(&frame[rw],white_row,offsetrow3)){
                for(int column=0;column<offsetrow; column ++){
                    pixel = frame[rw];
                    if(memcmp(&pixel, &white_pixel, sizeof(struct color))){
                        data[data_id].c =pixel;
                        data[data_id].row = row;
                        data[data_id].col = col;
                        data_id += 1;
                    }
                    rw += 1;
                    col += 1;
                }
            }
            else{
                rw += offsetrow;
            }
        }
        else{
            rw += width;    
        }
    }

    for (int sensorValueIdx = 0; sensorValueIdx < sensor_values_count; sensorValueIdx++) {
        val = sensor_values[sensorValueIdx].value;
        key = sensor_values[sensorValueIdx].key;

        if (!strcmp(key, "W")) {
            if (clockwise){
                if (mx){
                    val = 0-val;
                }
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
            if (clockwise){
                if (mx){
                    val = 0-val;
                }
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
            if (clockwise){ //&& my){
                if (my){
                    val = 0-val;
                }
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
            if (clockwise){
                if (my){
                    val = 0-val;
                }
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
            if (mx||my){
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
            if (mx||my){
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
            struct color * r_frame = (struct color *) frame_buffer;
            for (int i = 0; i < data_id; i ++){
                r_frame[data[i].row*width+data[i].col] = white_pixel;
            }
            transform(frame_buffer, up, right, clockwise, mx, my, height, width, data, data_id);
	        verifyFrame(frame_buffer, width, height, grading_mode);
            up = 0;right=0;clockwise=0;mx=false;my=false;
        }
    }
    // free(data);
    return;
}

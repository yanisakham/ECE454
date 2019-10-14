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
// #define div2(x) (x>>1)
// #define CW1(col, row, width, newcol, newrow) newrow =col; newcol=width-1-row
// #define CW2(col, row, width, height, newcol, newrow) newrow =height-1-row; newcol = width-1-col
// #define CW3(col, row, width, height, newcol, newrow) newrow =height-1-col; newcol = row
// #define MX(col, row, height, newcol, newrow) newrow = height-1-row; newcol = col
// #define MY(col, row, width, newcol, newrow) newrow = row; newcol = width-1-col

void transform(unsigned char*frame, int up, int right,int clockwise,bool mx,bool my, int height,int width, struct non_white_data* data_array, int id){
    struct color * r_frame = (struct color *) frame;
    int i, x1, x2, y1, y2, a1, a2, b1, b2, c1, c2, d1, d2, e1, e2, f1, f2, g1, g2, h1, h2, i1, i2, j1, j2, k1, k2, l1, l2, m1, m2, n1, n2;
    int lim = id -7;
    for (i = 0; i< lim; i+=8){                          // LOOP UNROLL OF 8
        struct non_white_data data = data_array[i];
        struct non_white_data data2 = data_array[i+1];
        struct non_white_data data3 = data_array[i+2];
        struct non_white_data data4 = data_array[i+3];
        struct non_white_data data5 = data_array[i+4];
        struct non_white_data data6 = data_array[i+5];
        struct non_white_data data7 = data_array[i+6];
        struct non_white_data data8 = data_array[i+7];
        y1 = data.row - up;
        x1 = data.col + right;
        x2 = x1; y2 = y1;        
        a1 = data2.row - up;
        b1 = data2.col + right;
        a2 = a1; b2 = b1;
        c1 = data3.row - up;
        d1 = data3.col + right;
        c2 = c1; d2 = d1;
        e1 = data4.row - up;
        f1 = data4.col + right;
        e2 = e1; f2 = f1;
        g1 = data5.row - up;
        h1 = data5.col + right;
        g2 = g1; h2 = h1;
        i1 = data6.row - up;
        j1 = data6.col + right;
        i2 = i1; j2 = j1;
        k1 = data7.row - up;
        l1 = data7.col + right;
        k2 = k1; l2 = l1;
        m1 = data8.row - up;
        n1 = data8.col + right;
        m2 = m1; n2 = n1;
        if (clockwise){
            switch(clockwise){
                case 1:
                    if (mx){
                        x2 = width-1-y1; y2 = height-1-x1;
                        b2 = width-1-a1; a2 = height-1-b1;
                        d2 = width-1-c1; c2 = height-1-d1;
                        f2 = width-1-e1; e2 = height-1-f1;
                        h2 = width-1-g1; g2 = height-1-h1;
                        j2 = width-1-i1; i2 = height-1-j1;
                        l2 = width-1-k1; k2 = height-1-l1;
                        n2 = width-1-m1; m2 = height-1-n1;
                    }
                    else if (my){
                        x2 = y1; y2 = x1;
                        b2 = a1; a2 = b1;
                        d2 = c1; c2 = d1;
                        f2 = e1; e2 = f1;
                        h2 = g1; g2 = h1;
                        j2 = i1; i2 = j1;
                        l2 = k1; k2 = l1;
                        n2 = m1; m2 = n1; break;
                    }
                    else{
                        x2 = width-1-y1; y2 = x1;
                        b2 = width-1-a1; a2 = b1;
                        d2 = width-1-c1; c2 = d1;
                        f2 = width-1-e1; e2 = f1;
                        h2 = width-1-g1; g2 = h1;
                        j2 = width-1-i1; i2 = j1;
                        l2 = width-1-k1; k2 = l1;
                        n2 = width-1-m1; m2 = n1; break;
                    }
                case 2:
                    if (mx){
                        x2 = width-1-x1 ; y2 = y1;
                        b2 = width-1-b1 ; a2 = a1;
                        d2 = width-1-d1 ; c2 = c1;
                        f2 = width-1-f1 ; e2 = e1;
                        h2 = width-1-h1 ; g2 = g1;
                        j2 = width-1-j1 ; i2 = i1;
                        l2 = width-1-l1 ; k2 = k1;
                        n2 = width-1-n1 ; m2 = m1; break; 
                    }
                    else if (my){
                        x2 = x1 ; y2 = height-1-y1;
                        b2 = b1 ; a2 = height-1-a1;
                        d2 = d1 ; c2 = height-1-c1;
                        f2 = f1 ; e2 = height-1-e1;
                        h2 = h1 ; g2 = height-1-g1;
                        j2 = j1 ; i2 = height-1-i1;
                        l2 = l1 ; k2 = height-1-k1;
                        n2 = n1 ; m2 = height-1-m1; break;  
                    }
                    else{
                        x2 = width-1-x1 ; y2 = height-1-y1;
                        b2 = width-1-b1 ; a2 = height-1-a1;
                        d2 = width-1-d1 ; c2 = height-1-c1;
                        f2 = width-1-f1 ; e2 = height-1-e1;
                        h2 = width-1-h1 ; g2 = height-1-g1;
                        j2 = width-1-j1 ; i2 = height-1-i1;
                        l2 = width-1-l1 ; k2 = height-1-k1;
                        n2 = width-1-n1 ; m2 = height-1-m1; break;    
                    }     
                case 3:
                    if (mx){
                        x2 = y1; y2 = x1; 
                        b2 = a1; a2 = b1;
                        d2 = c1; c2 = d1;
                        f2 = e1; e2 = f1;
                        h2 = g1; g2 = h1;
                        j2 = i1; i2 = j1;
                        l2 = k1; k2 = l1;
                        n2 = m1; m2 = n1; break;

                    }
                    else if (my){
                        x2 = width-1-y1; y2 = height-1-x1;
                        b2 = width-1-a1; a2 = height-1-b1;
                        d2 = width-1-c1; c2 = height-1-d1;
                        f2 = width-1-e1; e2 = height-1-f1;
                        h2 = width-1-g1; g2 = height-1-h1;
                        j2 = width-1-i1; i2 = height-1-j1;
                        l2 = width-1-k1; k2 = height-1-l1;
                        n2 = width-1-m1; m2 = height-1-n1; break;
                    }
                    else{
                        x2 = y1; y2 = height-1-x1; 
                        b2 = a1; a2 = height-1-b1;
                        d2 = c1; c2 = height-1-d1;
                        f2 = e1; e2 = height-1-f1;
                        h2 = g1; g2 = height-1-h1;
                        j2 = i1; i2 = height-1-j1;
                        l2 = k1; k2 = height-1-l1;
                        n2 = m1; m2 = height-1-n1; break;
                    }
            }
        }
        else if (mx){
            y2 = height-1-y1;   a2 = height-1-a1;   c2 = height-1-c1; e2 = height-1-e1;
            g2 = height-1-g1;   i2 = height-1-i1;   k2 = height-1-k1; m2 = height-1-m1; 
        }
        else if (my){
            x2 = width-1-x1;    b2 = width-1-b1;    d2 = width-1-d1;    f2 = width-1-f1;
            h2 = width-1-h1;    j2 = width-1-j1;    l2 = width-1-l1;    n2 = width-1-n1;
        }
        data_array[i].row = y2;
        data_array[i].col = x2;
        data_array[i+1].row = a2;
        data_array[i+1].col = b2;
        data_array[i+2].row = c2;
        data_array[i+2].col = d2;
        data_array[i+3].row = e2;
        data_array[i+3].col = f2;
        data_array[i+4].row = g2;
        data_array[i+4].col = h2;
        data_array[i+5].row = i2;
        data_array[i+5].col = j2;
        data_array[i+6].row = k2;
        data_array[i+6].col = l2;
        data_array[i+7].row = m2;
        data_array[i+7].col = n2;
        r_frame[y2*width + x2] = data.c;
        r_frame[a2*width + b2] = data2.c;   
        r_frame[c2*width + d2] = data3.c;  
        r_frame[e2*width + f2] = data4.c;       
        r_frame[g2*width + h2] = data5.c;       
        r_frame[i2*width + j2] = data6.c;       
        r_frame[k2*width + l2] = data7.c;       
        r_frame[m2*width + n2] = data8.c;       

    }
    // printf("%d",i);
    for (; i< id; i++){
        struct non_white_data data = data_array[i];
        y1 = data.row - up;
        x1 = data.col + right;
        x2 = x1;
        y2 = y1;
        if (clockwise){
            switch(clockwise){
                case 1:
                    x2 = width-1-y1; y2 = x1; break;
                case 2:
                    x2 = width-1-x1 ; y2 = height-1-y1; break;
                case 3:
                    x2 = y1; y2 = height-1-x1; break;
            }
            x1 = x2;
            y1 = y2;
        }
        if (mx){
            y2 = height-1-y1;
            y1 = y2;
        }
        if (my){
            x2 = width-1-x1;
            x1 = x2;
        }
        data_array[i].row = y2;
        data_array[i].col = x2;
        r_frame[y2*width + x2] = data.c;
        
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


    int ratio = 10;
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
            memset(frame, white, times3(height*width));
            transform(frame_buffer, up, right, clockwise, mx, my, height, width, data, data_id);
	        verifyFrame(frame_buffer, width, height, grading_mode);
            up = 0;right=0;clockwise=0;mx=false;my=false;
        }
    }
    free(data);
    return;
}

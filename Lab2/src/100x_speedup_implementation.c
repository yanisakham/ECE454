#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"  // DO NOT REMOVE this line
#include "implementation_reference.h"   // DO NOT REMOVE this line

unsigned char *processMoveUp(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processMoveDown(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processMoveLeft(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processMoveRight(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processRotateCW(unsigned char *buffer_frame, unsigned width, unsigned height, int rotate_iteration);
unsigned char *processRotateCCW(unsigned char *buffer_frame, unsigned width, unsigned height, int rotate_iteration);
unsigned char *processMirrorX(unsigned char *buffer_frame, unsigned int width, unsigned int height, int _unused);
unsigned char *processMirrorY(unsigned char *buffer_frame, unsigned int width, unsigned int height, int _unused);

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image up
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveUp(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // printf("enter up \n");
    // handle negative offsets
    if (offset < 0){
        return processMoveDown(buffer_frame, width, height, offset * -1);
    }

    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);

    // store shifted pixels to temporary buffer
    int w3 = width*3;
    int rw=0;
    int c3;
    int row3;
    int o3 = offset*w3;
    int ho = height-offset;
    for (int row = 0; row < ho; row++) {
        row3 = rw + o3;
        c3 = 0;
        for (int column = 0; column < width; column++) {
            int position_rendered_frame = rw + c3;
            int position_buffer_frame = row3 + c3;
            buffer_frame[position_rendered_frame] = buffer_frame[position_buffer_frame];
            buffer_frame[position_rendered_frame + 1] = buffer_frame[position_buffer_frame + 1];
            buffer_frame[position_rendered_frame + 2] = buffer_frame[position_buffer_frame + 2];
            c3 += 3;
        }
        rw += w3;
    }
///
    // fill left over pixels with white pixels
    for (int row = ho; row < height; row++) {
        rw=row*w3;
        c3 = 0;
        for (int column = 0; column < width; column++) {
            int position_rendered_frame = rw + c3;
            buffer_frame[position_rendered_frame] = 255;
            buffer_frame[position_rendered_frame + 1] = 255;
            buffer_frame[position_rendered_frame + 2] = 255;
            c3 += 3;
        }
    }

    // copy the temporary buffer back to original frame buffer
    // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image left
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveRight(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // printf("enter Right func \n");

   // handle negative offsets
    if (offset < 0){
        return processMoveLeft(buffer_frame, width, height, offset * -1);
    }

    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);
    int w3 = width*3;
    int rw=0;
    int o3 = offset*3;
    int c3;
    // store shifted pixels to temporary buffer
    for (int row = 0; row < height; row++) {
        c3 = w3-3;
        for (int column = width-1; column >= offset; column--) {
            int position_rendered_frame = rw + c3;
            int position_buffer_frame = rw + c3 - o3;
            buffer_frame[position_rendered_frame] = buffer_frame[position_buffer_frame];
            buffer_frame[position_rendered_frame + 1] = buffer_frame[position_buffer_frame + 1];
            buffer_frame[position_rendered_frame + 2] = buffer_frame[position_buffer_frame + 2];
            c3 -= 3;
        }
        rw += w3;
    }

    // fill left over pixels with white pixels
    rw = 0;
    for (int row = 0; row < height; row++) {
        c3 = 0;
        for (int column = 0; column < offset; column++) {
            int position_rendered_frame = rw + c3;
            buffer_frame[position_rendered_frame] = 255;
            buffer_frame[position_rendered_frame + 1] = 255;
            buffer_frame[position_rendered_frame + 2] = 255;
            c3 += 3;
        }
        rw += w3;
    }

    // copy the temporary buffer back to original frame buffer
    // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;

}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image up
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveDown(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // printf("enter down \n");
    // handle negative offsets
    if (offset < 0){
        return processMoveUp(buffer_frame, width, height, offset * -1);
    }

    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);
    int w3= width*3;
    int row3;
    int rw = (height-1)*w3;
    int c3;
    // store shifted pixels to temporary buffer
    for (int row = height-1; row >= offset; row--) {
        row3 = (row-offset)*w3;
        c3 = 0;
        for (int column = 0; column < width; column++) {
            int position_rendered_frame = rw + c3;
            int position_buffer_frame = row3 + c3;
            buffer_frame[position_rendered_frame] = buffer_frame[position_buffer_frame];
            buffer_frame[position_rendered_frame + 1] = buffer_frame[position_buffer_frame + 1];
            buffer_frame[position_rendered_frame + 2] = buffer_frame[position_buffer_frame + 2];
            c3 += 3;
        }
        rw-= w3;
    }

    // fill left over pixels with white pixels
    rw = 0;
    for (int row = 0; row < offset; row++) {
        c3 = 0;
        for (int column = 0; column < width; column++) {
            int position_rendered_frame = rw + c3;
            c3 += 3;
            buffer_frame[position_rendered_frame] = 255;
            buffer_frame[position_rendered_frame + 1] = 255;
            buffer_frame[position_rendered_frame + 2] = 255;
        }
        rw += w3;
    }

    // copy the temporary buffer back to original frame buffer
    // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;    
    
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image right
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveLeft(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // handle negative offsets
    // printf("enter Left func \n");

    if (offset < 0){
        return processMoveRight(buffer_frame, width, height, offset * -1);
    }

    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);
    int w3= width*3;
    int rw=0;
    int c3;
    int o3=offset*3;
    int wo=(width - offset);

    // store shifted pixels to temporary buffer
    for (int row = 0; row < height; row++) {
        c3 = 0;
        for (int column = 0; column < wo; column++) {
            int position_rendered_frame = row*width*3 + c3;
            int position_buffer_frame = row*width*3 + c3 + o3;
            buffer_frame[position_rendered_frame] = buffer_frame[position_buffer_frame];
            buffer_frame[position_rendered_frame + 1] = buffer_frame[position_buffer_frame + 1];
            buffer_frame[position_rendered_frame + 2] = buffer_frame[position_buffer_frame + 2];
            c3 += 3;
        }
        rw += w3;
    }

    // fill left over pixels with white pixels
    rw = 0;
    for (int row = 0; row < height; row++) {
        c3 = wo*3;
        for (int column = wo; column < width; column++) {
            int position_rendered_frame = rw + c3;
            buffer_frame[position_rendered_frame] = 255;
            buffer_frame[position_rendered_frame + 1] = 255;
            buffer_frame[position_rendered_frame + 2] = 255;
            c3 += 3;
        }
        rw += w3;
    }

    // copy the temporary buffer back to original frame buffer
    // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;

}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param rotate_iteration - rotate object inside frame buffer clockwise by 90 degrees, <iteration> times
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note: You can assume the frame will always be square and you will be rotating the entire image
 **********************************************************************************************************************/
unsigned char *processRotateCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                               int rotate_iteration) {
    // printf("enter CW \n");
    // handle negative offsets
    if (rotate_iteration < 0){
        return processRotateCCW(buffer_frame, width, height, rotate_iteration * -1);
    }

    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);
    int temp1, temp2, temp3, rw3, c3,rr3,rc3;
    int r = (width + 1)/2;
    int c = (height + 1)/2;
    int w3 = width*3;
    int hw3 = (height-1)*w3;
    int w13 = w3-3;
    // store shifted pixels to temporary buffer
    for (int iteration = 0; iteration < rotate_iteration; iteration++) {
        int render_column = width - 1;
        int render_row = 0;
        rw3 = 0;
        rc3 = w13;
        for (int row = 0; row < r; row++) {
            c3 = 0;
            rr3 = 0;
            for (int column = 0; column < c; column++) {
                int Q4 = rw3 + c3;
                int Q1 = rr3 + rc3;
                int Q2 = hw3 -rw3+ w13-c3;
                int Q3 = hw3 -rr3+ w13-rc3;
                temp1 = buffer_frame[Q2];
                temp2 = buffer_frame[Q2 + 1];
                temp3 = buffer_frame[Q2 + 2];
                buffer_frame[Q2] = buffer_frame[Q1];
                buffer_frame[Q2 + 1] = buffer_frame[Q1 + 1];
                buffer_frame[Q2 + 2] = buffer_frame[Q1 + 2];
                buffer_frame[Q1] = buffer_frame[Q4];
                buffer_frame[Q1 + 1] = buffer_frame[Q4 + 1];
                buffer_frame[Q1 + 2] = buffer_frame[Q4 + 2];
                buffer_frame[Q4] = buffer_frame[Q3];
                buffer_frame[Q4 + 1] = buffer_frame[Q3 + 1];
                buffer_frame[Q4 + 2] = buffer_frame[Q3 + 2];
                buffer_frame[Q3] = temp1;
                buffer_frame[Q3 + 1] = temp2;
                buffer_frame[Q3 + 2] = temp3;
                render_row += 1;
                rr3 += w3;
                c3 += 3;
            }
            render_row = 0;
            render_column -= 1;
            rc3 -= 3;
            rw3 += w3;
        }

        // copy the temporary buffer back to original frame buffer
        // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);
    }

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;

}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param rotate_iteration - rotate object inside frame buffer counter clockwise by 90 degrees, <iteration> times
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note: You can assume the frame will always be square and you will be rotating the entire image
 **********************************************************************************************************************/
unsigned char *processRotateCCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                                int rotate_iteration) {
    // printf("enter CCW \n");
   if (rotate_iteration < 0){
        // handle negative offsets
        // rotating 90 degrees counter clockwise in opposite direction is equal to 90 degrees in cw direction
        for (int iteration = 0; iteration > rotate_iteration; iteration--) {
            buffer_frame = processRotateCW(buffer_frame, width, height, 1);
        }
    } else {
        // rotating 90 degrees counter clockwise is equivalent of rotating 270 degrees clockwise
        for (int iteration = 0; iteration < rotate_iteration; iteration++) {
            buffer_frame = processRotateCW(buffer_frame, width, height, 3);
        }
    }

    // return a pointer to the updated image buffer
    return buffer_frame;

}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorX(unsigned char *buffer_frame, unsigned int width, unsigned int height, int _unused) {
    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);
    // printf("enter MX \n");
    int temp1, temp2, temp3;
    int h = (height-1)/2;
    // store shifted pixels to temporary buffer
    for (int row = 0; row <= h; row++) {
        for (int column = 0; column < width; column++) {
            int position_rendered_frame = row * height * 3 + column * 3;
            int position_buffer_frame = (height - row - 1) * height * 3 + column * 3;
            temp1 = buffer_frame[position_rendered_frame];
            temp2 = buffer_frame[position_rendered_frame+1];
            temp3 = buffer_frame[position_rendered_frame+2];
            buffer_frame[position_rendered_frame] = buffer_frame[position_buffer_frame];
            buffer_frame[position_rendered_frame + 1] = buffer_frame[position_buffer_frame + 1];
            buffer_frame[position_rendered_frame + 2] = buffer_frame[position_buffer_frame + 2];
            buffer_frame[position_buffer_frame] = temp1;
            buffer_frame[position_buffer_frame+1] = temp2;
            buffer_frame[position_buffer_frame+2] = temp3;
        }
    }

    // copy the temporary buffer back to original frame buffer
    // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;

}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorY(unsigned char *buffer_frame, unsigned width, unsigned height, int _unused) {
    // printf("enter MY \n");
    // allocate memory for temporary image buffer
    // unsigned char *rendered_frame = allocateFrame(width, height);

    // store shifted pixels to temporary buffer
    int temp1;
    int temp2;
    int temp3;
    int w2 = (width-1)/2;
    int h3 = height*3; 
    int rh;
    int w3= (width-1)*3;
    int c3;

    for (int row = 0; row < height; row++) {
        rh = row * h3;
        for (int column = 0; column <= w2; column++) {
            c3 = column * 3;
            int position_rendered_frame = rh + c3;
            int position_buffer_frame = rh + w3-c3;
            temp1 =buffer_frame[position_rendered_frame];
            temp2 = buffer_frame[position_rendered_frame+1];
            temp3 = buffer_frame[position_rendered_frame+2];
            buffer_frame[position_rendered_frame] = buffer_frame[position_buffer_frame];
            buffer_frame[position_rendered_frame + 1] = buffer_frame[position_buffer_frame + 1];
            buffer_frame[position_rendered_frame + 2] = buffer_frame[position_buffer_frame + 2];
            buffer_frame[position_buffer_frame] = temp1;
            buffer_frame[position_buffer_frame+1] = temp2;
            buffer_frame[position_buffer_frame+2] = temp3;
        }
    }

    // copy the temporary buffer back to original frame buffer
    // buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);

    // free temporary image buffer
    // deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;

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
 * @param sensor_values - structure stores parsed key value pairs of program instructions
 * @param sensor_values_count - number of valid sensor values parsed from sensor log file or commandline console
 * @param frame_buffer - pointer pointing to a buffer storing the imported  24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param grading_mode - turns off verification and turn on instrumentation
 ***********************************************************************************************************************
 *
 **********************************************************************************************************************/
void implementation_driver(struct kv *sensor_values, int sensor_values_count, unsigned char *frame_buffer,
                           unsigned int width, unsigned int height, bool grading_mode) {
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
                    // case 0: // no rotate
                    //     up += val; break;
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
                    // case 0: // no rotate
                    //     up += val; break;
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
                    // case 0: // no rotate
                    //     up -= val; break;
                    case 1: // 90 deg clockwise
                        right -= val; break;
                    case 2: // 180 deg
                        up -= val; break;
                    case 3: //270 deg clockwise
                        right += val; break;
                }
            }else if (clockwise){
                switch(clockwise){
                    // case 0: // no rotate
                    //     up -= val; break;
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
                    // case 0:
                    //     right -= val; break;
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
                    // case 0:
                    //     right -= val; break;
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
                    // case 0:
                    //     right += val; break;
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
                    // case 0:
                    //     right += val; break;
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
        // printf("\n");
        // printf(key);
        // printf(" up %d right %d mx my %d %d clock %d ", up, right, mx, my, clockwise);
        processed_frames +=1;
        if (processed_frames % 25 == 0) {
            if (up!=0){
                frame_buffer = processMoveUp(frame_buffer, width, height, up);
            }
            if (right!=0){
                frame_buffer = processMoveRight(frame_buffer, width, height, right);
            }
            if(clockwise){
                frame_buffer = processRotateCW(frame_buffer, width, height, clockwise);
            }
            if (mx){
                frame_buffer = processMirrorX(frame_buffer, width, height, 1);
            }
            if (my){
                frame_buffer = processMirrorY(frame_buffer, width, height, 1);
            }
            up = 0, right = 0, clockwise = 0, mx = false, my = false;
            
	    // printBMP(width, height, frame_buffer);
	    verifyFrame(frame_buffer, width, height, grading_mode);
	    // printBMP(width, height, frame_buffer);
	    }
    }
    return;
}

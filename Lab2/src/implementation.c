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
void transform(unsigned char*frame, int up, int right,int clockwise,bool mx,bool my, int height,int width,struct non_white_data* data_array,int id, int loop);

#define white 0xffffff
#define times3(x) ((x<<1)+x)

void transform(unsigned char*frame, int up, int right,int clockwise,bool mx,bool my, int height,int width, struct non_white_data* data_array, int id, int loop){
    struct color * r_frame = (struct color *) frame;
    // printf("up %d right %d clock %d mx %d my %d", up, right, clockwise, mx, my);
    int x2, y1, a1, b2, c1, d2, e1, f2, g1, h2, i1, j2, k1, l2, m1, n2;
    int w1 = width -1, hh = height-1;
    register struct non_white_data * temp = &data_array[0]; 
    struct non_white_data * data2;
    struct non_white_data * data3;
    struct non_white_data * data4;
    struct non_white_data * data5;
    struct non_white_data * data6;
    struct non_white_data * data7;
    struct non_white_data * data8;
    struct non_white_data * end = temp + id;
    register struct non_white_data * limit = end - 7;
    if (loop!=0){
        
        if (clockwise){
            switch (clockwise)
            {
            case 1:
                if (mx){
                  for (; temp < limit; temp +=8) {
                        data2 = temp+1;     
                        data3 = temp+2;      
                        data4 = temp+3;     
                        data5 = temp+4;  //  g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;  //  i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;  //  k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;  //  m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        x2 = w1-(temp)->row+up; y1 = hh-(temp)->col-right;
                        b2 = w1-data2->row+up; a1 = hh-data2->col-right;
                        d2 = w1-data3->row+up; c1 = hh-data3->col-right;
                        f2 = w1-data4->row+up; e1 = hh-data4->col-right; 
                        h2 = w1-data5->row+up; g1 = hh-data5->col-right;
                        j2 = w1-data6->row+up; i1 = hh-data6->col-right;
                        l2 = w1-data7->row+up; k1 = hh-data7->col-right;
                        n2 = w1-data8->row+up; m1 = hh-data8->col-right;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c;       
                    }   
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->row+up; y1 = hh-(temp)->col-right;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else if (my){
                    for (; temp < limit; temp +=8) {
    
                        x2 = (temp)->row - up;     y1 = (temp)->col + right;   //   x2 = x1;  
                        data2 = temp+1;    b2 = data2->row - up;    a1 = data2->col + right;    // b2 = b1; 
                        data3 = temp+2;    d2 = data3->row - up;    c1 = data3->col + right;    // d2 = d1;  
                        data4 = temp+3;    f2 = data4->row - up;    e1 = data4->col + right;    // f2 = f1; 
                        data5 = temp+4;    h2 = data5->row - up;    g1 = data5->col + right;    // h2 = h1;  
                        data6 = temp+5;    j2 = data6->row - up;    i1 = data6->col + right;    // j2 = j1; 
                        data7 = temp+6;    l2 = data7->row - up;    k1 = data7->col + right;    // l2 = l1; 
                        data8 = temp+7;    n2 = data8->row - up;    m1 = data8->col + right;    // n2 = n1;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = (temp)->row - up;     y1 = (temp)->col + right;   //   x2 = x1;  
                        (temp)->row = y1;
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else{
                    for (; temp < limit; temp +=8) {
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;

                        x2 = w1-(temp)->row+up; y1 = (temp)->col + right;
                        b2 = w1-data2->row+up; a1 = data2->col + right;
                        d2 = w1-data3->row+up; c1 = data3->col + right;
                        f2 = w1-data4->row+up; e1 = data4->col + right;
                        h2 = w1-data5->row+up; g1 = data5->col + right;
                        j2 = w1-data6->row+up; i1 = data6->col + right;
                        l2 = w1-data7->row+up; k1 = data7->col + right;
                        n2 = w1-data8->row+up; m1 = data8->col + right;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->row+up; y1 = (temp)->col + right;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
            case 2:
                if (mx){
                  for (; temp < limit; temp +=8) {
                               y1 = (temp)->row - up;   //  x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;    a1 = data2->row - up;  //  b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;    c1 = data3->row - up;  //  d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;    e1 = data4->row - up;  //  f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;    g1 = data5->row - up;  //  h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;    i1 = data6->row - up;  //  j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;    k1 = data7->row - up;  //  l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;    m1 = data8->row - up;  //  n1 = data8->col + right;     n2 = n1;
                        x2 = w1-(temp)->col - right ; 
                        b2 = w1-data2->col - right ; 
                        d2 = w1-data3->col - right ; 
                        f2 = w1-data4->col - right ;  
                        h2 = w1-data5->col - right ; 
                        j2 = w1-data6->col - right ; 
                        l2 = w1-data7->col - right ; 
                        n2 = w1-data8->col - right ;
                        
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c;       
                    }   
                    for (; temp < end; temp ++){
                         y1 = (temp)->row - up; x2 = w1-(temp)->col - right ; 
                        (temp)->row = y1;
                        (temp)->col = x2; 
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else if (my){
                    for (; temp < limit; temp +=8) {

                               //y1 = temp->row - up;     x2 = temp->col + right;   //   x2 = x1;  
                        data2 = temp+1;    //a1 = data2->row - up;    b2 = data2->col + right;   //  b2 = b1; 
                        data3 = temp+2;    //c1 = data3->row - up;    d2 = data3->col + right;   //  d2 = d1;  
                        data4 = temp+3;    //e1 = data4->row - up;    f2 = data4->col + right;   //  f2 = f1; 
                        data5 = temp+4;    //g1 = data5->row - up;    h2 = data5->col + right;    // h2 = h1;  
                        data6 = temp+5;    //i1 = data6->row - up;    j2 = data6->col + right;    // j2 = j1; 
                        data7 = temp+6;    //k1 = data7->row - up;    l2 = data7->col + right;    // l2 = l1; 
                        data8 = temp+7;    //m1 = data8->row - up;    n2 = data8->col + right;    // n2 = n1;
                        x2 = (temp)->col + right ; y1 = hh-(temp)->row + up;
                        b2 = data2->col + right ; a1 = hh-data2->row + up;
                        d2 = data3->col + right ; c1 = hh-data3->row + up;
                        f2 = data4->col + right ; e1 = hh-data4->row + up; 
                        h2 = data5->col + right ; g1 = hh-data5->row + up;
                        j2 = data6->col + right ; i1 = hh-data6->row + up;
                        l2 = data7->col + right ; k1 = hh-data7->row + up;
                        n2 = data8->col + right ; m1 = hh-data8->row + up; 

                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = (temp)->col + right ; y1 = hh-(temp)->row + up;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else{
                    for (; temp < limit; temp +=8) {
                              // y1 = temp->row - up;     x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
            
                        x2 = w1-(temp)->col-right ; y1 = hh-(temp)->row + up;
                        b2 = w1-data2->col-right ; a1 = hh-data2->row + up;
                        d2 = w1-data3->col-right ; c1 = hh-data3->row + up;
                        f2 = w1-data4->col-right ; e1 = hh-data4->row + up; 
                        h2 = w1-data5->col-right ; g1 = hh-data5->row + up;
                        j2 = w1-data6->col-right ; i1 = hh-data6->row + up;
                        l2 = w1-data7->col-right ; k1 = hh-data7->row + up;
                        n2 = w1-data8->col-right ; m1 = hh-data8->row + up;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->col-right ; y1 = hh-(temp)->row + up;
                        (temp)->row = hh-(temp)->row + up;
                        (temp)->col = w1-(temp)->col-right;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
            case 3:
                if (mx){
                  for (; temp < limit; temp +=8) {
                               //y1 = temp->row - up;     x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;    //a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;    //c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;    //e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;    //g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;    //i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;    //k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;    //m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        x2 = (temp)->row - up; y1 = (temp)->col+right; 
                        b2 = data2->row - up; a1 = data2->col+right;
                        d2 = data3->row - up; c1 = data3->col+right;
                        f2 = data4->row - up; e1 = data4->col+right;
                        h2 = data5->row - up; g1 = data5->col+right;
                        j2 = data6->row - up; i1 = data6->col+right;
                        l2 = data7->row - up; k1 = data7->col+right;
                        n2 = data8->row - up; m1 = data8->col+right;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c;       
                    }   
                    for (; temp < end; temp ++){
                        x2 = (temp)->row - up; y1 = (temp)->col+right; 
                        (temp)->row = y1; 
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else if (my){
                    for (; temp < limit; temp +=8) {
                              // y1 = temp->row - up;     x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        
                        x2 = w1-(temp)->row + up; y1 = hh-(temp)->col -right;
                        b2 = w1-data2->row + up; a1 = hh-data2->col -right;
                        d2 = w1-data3->row + up; c1 = hh-data3->col -right;
                        f2 = w1-data4->row + up; e1 = hh-data4->col -right; 
                        h2 = w1-data5->row + up; g1 = hh-data5->col -right;
                        j2 = w1-data6->row + up; i1 = hh-data6->col -right;
                        l2 = w1-data7->row + up; k1 = hh-data7->col -right;
                        n2 = w1-data8->row + up; m1 = hh-data8->col -right; 
                        
                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->row + up; y1 = hh-(temp)->col -right;
                        (temp)->row = y1;
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else{
                    for (; temp < limit; temp +=8) {
                              // y1 = temp->row - up;     x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        
                        x2 = (temp)->row-up;  y1 = hh-(temp)->col - right; 
                        b2 = data2->row-up; a1 = hh-data2->col - right;
                        d2 = data3->row-up; c1 = hh-data3->col - right;
                        f2 = data4->row-up; e1 = hh-data4->col - right;
                        h2 = data5->row-up; g1 = hh-data5->col - right;
                        j2 = data6->row-up; i1 = hh-data6->col - right;
                        l2 = data7->row-up; k1 = hh-data7->col - right;
                        n2 = data8->row-up; m1 = hh-data8->col - right;

                        (temp)->row = y1;
                        (temp)->col = x2;
                        data2->row = a1;
                        data2->col = b2;
                        data3->row = c1;
                        data3->col = d2;
                        data4->row = e1;
                        data4->col = f2;
                        data5->row = g1;
                        data5->col = h2;
                        data6->row = i1;
                        data6->col = j2;
                        data7->row = k1;
                        data7->col = l2;
                        data8->row = m1;
                        data8->col = n2;
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = (temp)->row-up;  y1 = hh-(temp)->col - right; 
                        (temp)->row = y1;
                        (temp)->col = x2;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
            }
        }
        else if (mx){
            for (; temp < limit; temp +=8) {
                       y1 = hh- (temp)->row + up;     x2 = (temp)->col + right;      //x2 = x1;  
                data2 = temp+1;    a1 = hh- data2->row + up;    b2 = data2->col + right;     //b2 = b1; 
                data3 = temp+2;    c1 = hh- data3->row + up;    d2 = data3->col + right;     //d2 = d1;  
                data4 = temp+3;    e1 = hh- data4->row + up;    f2 = data4->col + right;     //f2 = f1; 
                data5 = temp+4;    g1 = hh- data5->row + up;    h2 = data5->col + right;     //h2 = h1;  
                data6 = temp+5;    i1 = hh- data6->row + up;    j2 = data6->col + right;     //j2 = j1; 
                data7 = temp+6;    k1 = hh- data7->row + up;    l2 = data7->col + right;     //l2 = l1; 
                data8 = temp+7;    m1 = hh- data8->row + up;    n2 = data8->col + right;     //n2 = n1;
        
                (temp)->row = y1;
                (temp)->col = x2;
                data2->row = a1;
                data2->col = b2;
                data3->row = c1;
                data3->col = d2;
                data4->row = e1;
                data4->col = f2;
                data5->row = g1;
                data5->col = h2;
                data6->row = i1;
                data6->col = j2;
                data7->row = k1;
                data7->col = l2;
                data8->row = m1;
                data8->col = n2;
                r_frame[y1*width + x2] = (temp)->c;
                r_frame[a1*width + b2] = data2->c;   
                r_frame[c1*width + d2] = data3->c;  
                r_frame[e1*width + f2] = data4->c;       
                r_frame[g1*width + h2] = data5->c;       
                r_frame[i1*width + j2] = data6->c;       
                r_frame[k1*width + l2] = data7->c;       
                r_frame[m1*width + n2] = data8->c;    
            }
            for (; temp < end; temp ++){
                y1 = hh- (temp)->row + up;     x2 = (temp)->col + right;      //x2 = x1;  
                (temp)->col = x2;
                (temp)->row = y1;
                r_frame[y1*width + x2] = (temp)->c;
            }

            return;
        }
        else if (my){
            for (; temp < limit; temp +=8) {
                y1 = (temp)->row - up;     x2 = w1-(temp)->col - right;    //  x2 = x1;  
                data2 = temp+1;    a1 = data2->row - up;    b2 = w1-data2->col - right;    //b2 = b1; 
                data3 = temp+2;    c1 = data3->row - up;    d2 = w1-data3->col - right;    // d2 = d1;  
                data4 = temp+3;    e1 = data4->row - up;    f2 = w1-data4->col - right;    // f2 = f1; 
                data5 = temp+4;    g1 = data5->row - up;    h2 = w1-data5->col - right;    // h2 = h1;  
                data6 = temp+5;    i1 = data6->row - up;    j2 = w1-data6->col - right;    // j2 = j1; 
                data7 = temp+6;    k1 = data7->row - up;    l2 = w1-data7->col - right;    // l2 = l1; 
                data8 = temp+7;    m1 = data8->row - up;    n2 = w1-data8->col - right;    // n2 = n1;
                (temp)->row = y1;
                (temp)->col = x2;
                data2->row = a1;
                data2->col = b2;
                data3->row = c1;
                data3->col = d2;
                data4->row = e1;
                data4->col = f2;
                data5->row = g1;
                data5->col = h2;
                data6->row = i1;
                data6->col = j2;
                data7->row = k1;
                data7->col = l2;
                data8->row = m1;
                data8->col = n2;
                r_frame[y1*width + x2] = (temp)->c;
                r_frame[a1*width + b2] = data2->c;   
                r_frame[c1*width + d2] = data3->c;  
                r_frame[e1*width + f2] = data4->c;       
                r_frame[g1*width + h2] = data5->c;       
                r_frame[i1*width + j2] = data6->c;       
                r_frame[k1*width + l2] = data7->c;       
                r_frame[m1*width + n2] = data8->c;    
            }
            for (; temp < end; temp ++){
                y1 = (temp)->row - up;     x2 = w1-(temp)->col - right;    //  x2 = x1;  
                (temp)->row =y1 ;
                (temp)->col = x2;
                r_frame[y1*width + x2] = temp->c;
            }
            return;
        }
        else{
            for (; temp < limit; temp +=8) {
                       y1 = temp->row - up;     x2 = temp->col + right;      //x2 = x1;  
                data2 = temp+1;    a1 = data2->row - up;    b2 = data2->col + right;     //b2 = b1; 
                data3 = temp+2;    c1 = data3->row - up;    d2 = data3->col + right;     //d2 = d1;  
                data4 = temp+3;    e1 = data4->row - up;    f2 = data4->col + right;     //f2 = f1; 
                data5 = temp+4;    g1 = data5->row - up;    h2 = data5->col + right;     //h2 = h1;  
                data6 = temp+5;    i1 = data6->row - up;    j2 = data6->col + right;     //j2 = j1; 
                data7 = temp+6;    k1 = data7->row - up;    l2 = data7->col + right;     //l2 = l1; 
                data8 = temp+7;    m1 = data8->row - up;    n2 = data8->col + right;     //n2 = n1;
                (temp)->row = y1;
                (temp)->col = x2;
                data2->row = a1;
                data2->col = b2;
                data3->row = c1;
                data3->col = d2;
                data4->row = e1;
                data4->col = f2;
                data5->row = g1;
                data5->col = h2;
                data6->row = i1;
                data6->col = j2;
                data7->row = k1;
                data7->col = l2;
                data8->row = m1;
                data8->col = n2;
                r_frame[y1*width + x2] = (temp)->c;
                r_frame[a1*width + b2] = data2->c;   
                r_frame[c1*width + d2] = data3->c;  
                r_frame[e1*width + f2] = data4->c;       
                r_frame[g1*width + h2] = data5->c;       
                r_frame[i1*width + j2] = data6->c;       
                r_frame[k1*width + l2] = data7->c;       
                r_frame[m1*width + n2] = data8->c;    
            }
            for (; temp < end; temp ++){
                y1 = (temp)->row - up;     x2 = (temp)->col + right;      //x2 = x1;  
                (temp)->row = y1;
                (temp)->col = x2;
                r_frame[y1*width + x2] = (temp)->c;
            }
            return;

        }
    }
    else{
        
        if (clockwise){
            switch (clockwise)
            {
            case 1:
                if (mx){
                  for (; temp < limit; temp +=8) {
                                
                        data2 = temp+1;     
                        data3 = temp+2;      
                        data4 = temp+3;     
                        data5 = temp+4;  //  g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;  //  i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;  //  k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;  //  m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        x2 = w1-(temp)->row+up; y1 = hh-(temp)->col-right;
                        b2 = w1-data2->row+up; a1 = hh-data2->col-right;
                        d2 = w1-data3->row+up; c1 = hh-data3->col-right;
                        f2 = w1-data4->row+up; e1 = hh-data4->col-right; 
                        h2 = w1-data5->row+up; g1 = hh-data5->col-right;
                        j2 = w1-data6->row+up; i1 = hh-data6->col-right;
                        l2 = w1-data7->row+up; k1 = hh-data7->col-right;
                        n2 = w1-data8->row+up; m1 = hh-data8->col-right;
                       
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c;       
                    }   
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->row+up; y1 = hh-(temp)->col-right;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else if (my){
                    for (; temp < limit; temp +=8) {
    
                               x2 = (temp)->row - up;     y1 = (temp)->col + right;   //   x2 = x1;  
                        data2 = temp+1;    b2 = data2->row - up;    a1 = data2->col + right;    // b2 = b1; 
                        data3 = temp+2;    d2 = data3->row - up;    c1 = data3->col + right;    // d2 = d1;  
                        data4 = temp+3;    f2 = data4->row - up;    e1 = data4->col + right;    // f2 = f1; 
                        data5 = temp+4;    h2 = data5->row - up;    g1 = data5->col + right;    // h2 = h1;  
                        data6 = temp+5;    j2 = data6->row - up;    i1 = data6->col + right;    // j2 = j1; 
                        data7 = temp+6;    l2 = data7->row - up;    k1 = data7->col + right;    // l2 = l1; 
                        data8 = temp+7;    n2 = data8->row - up;    m1 = data8->col + right;    // n2 = n1;           
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = (temp)->row - up;
                        y1 = (temp)->col + right;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else{
                    for (; temp < limit; temp +=8) {

                              // y1 = temp->row - up;     x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        x2 = w1-(temp)->row+up; y1 = (temp)->col + right;
                        b2 = w1-data2->row+up; a1 = data2->col + right;
                        d2 = w1-data3->row+up; c1 = data3->col + right;
                        f2 = w1-data4->row+up; e1 = data4->col + right;
                        h2 = w1-data5->row+up; g1 = data5->col + right;
                        j2 = w1-data6->row+up; i1 = data6->col + right;
                        l2 = w1-data7->row+up; k1 = data7->col + right;
                        n2 = w1-data8->row+up; m1 = data8->col + right;
                        
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->row+up; y1 = (temp)->col + right;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
            case 2:
                if (mx){
                  for (; temp < limit; temp +=8) {
                               y1 = (temp)->row - up;   //  x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;    a1 = data2->row - up;  //  b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;    c1 = data3->row - up;  //  d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;    e1 = data4->row - up;  //  f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;    g1 = data5->row - up;  //  h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;    i1 = data6->row - up;  //  j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;    k1 = data7->row - up;  //  l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;    m1 = data8->row - up;  //  n1 = data8->col + right;     n2 = n1;
                        x2 = w1-(temp)->col - right ; 
                        b2 = w1-data2->col - right ; 
                        d2 = w1-data3->col - right ; 
                        f2 = w1-data4->col - right ;  
                        h2 = w1-data5->col - right ; 
                        j2 = w1-data6->col - right ; 
                        l2 = w1-data7->col - right ; 
                        n2 = w1-data8->col - right ;
                        
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c;       
                    }   
                    for (; temp < end; temp ++){
                        y1 = (temp)->row - up;
                        x2 = w1-(temp)->col - right ; 
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else if (my){
                    for (; temp < limit; temp +=8) {

                               //y1 = temp->row - up;     x2 = temp->col + right;   //   x2 = x1;  
                        data2 = temp+1;    //a1 = data2->row - up;    b2 = data2->col + right;   //  b2 = b1; 
                        data3 = temp+2;    //c1 = data3->row - up;    d2 = data3->col + right;   //  d2 = d1;  
                        data4 = temp+3;    //e1 = data4->row - up;    f2 = data4->col + right;   //  f2 = f1; 
                        data5 = temp+4;    //g1 = data5->row - up;    h2 = data5->col + right;    // h2 = h1;  
                        data6 = temp+5;    //i1 = data6->row - up;    j2 = data6->col + right;    // j2 = j1; 
                        data7 = temp+6;    //k1 = data7->row - up;    l2 = data7->col + right;    // l2 = l1; 
                        data8 = temp+7;    //m1 = data8->row - up;    n2 = data8->col + right;    // n2 = n1;
                        x2 = (temp)->col + right ; y1 = hh-(temp)->row + up;
                        b2 = data2->col + right ; a1 = hh-data2->row + up;
                        d2 = data3->col + right ; c1 = hh-data3->row + up;
                        f2 = data4->col + right ; e1 = hh-data4->row + up; 
                        h2 = data5->col + right ; g1 = hh-data5->row + up;
                        j2 = data6->col + right ; i1 = hh-data6->row + up;
                        l2 = data7->col + right ; k1 = hh-data7->row + up;
                        n2 = data8->col + right ; m1 = hh-data8->row + up; 

                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = (temp)->col + right ; y1 = hh-(temp)->row + up;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else{
                    for (; temp < limit; temp +=8) {
                              // y1 = temp->row - up;     x1 = temp->col + right;      x2 = x1;  
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
            
                        x2 = w1-(temp)->col-right ; y1 = hh-(temp)->row + up;
                        b2 = w1-data2->col-right ; a1 = hh-data2->row + up;
                        d2 = w1-data3->col-right ; c1 = hh-data3->row + up;
                        f2 = w1-data4->col-right ; e1 = hh-data4->row + up; 
                        h2 = w1-data5->col-right ; g1 = hh-data5->row + up;
                        j2 = w1-data6->col-right ; i1 = hh-data6->row + up;
                        l2 = w1-data7->col-right ; k1 = hh-data7->row + up;
                        n2 = w1-data8->col-right ; m1 = hh-data8->row + up;

                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->col-right ; y1 = hh-(temp)->row + up;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
            case 3:
                if (mx){
                  for (; temp < limit; temp +=8) {
                        data2 = temp+1;    //a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;    //c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;    //e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;    //g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;    //i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;    //k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;    //m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        x2 = (temp)->row - up; y1 = (temp)->col+right; 
                        b2 = data2->row - up; a1 = data2->col+right;
                        d2 = data3->row - up; c1 = data3->col+right;
                        f2 = data4->row - up; e1 = data4->col+right;
                        h2 = data5->row - up; g1 = data5->col+right;
                        j2 = data6->row - up; i1 = data6->col+right;
                        l2 = data7->row - up; k1 = data7->col+right;
                        n2 = data8->row - up; m1 = data8->col+right;
                        
                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c;       
                    }   
                    for (; temp < end; temp ++){
                        x2 = (temp)->row - up; y1 = (temp)->col+right; 
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else if (my){
                    for (; temp < limit; temp +=8) {
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        
                        x2 = w1-(temp)->row + up; y1 = hh-(temp)->col -right;
                        b2 = w1-data2->row + up; a1 = hh-data2->col -right;
                        d2 = w1-data3->row + up; c1 = hh-data3->col -right;
                        f2 = w1-data4->row + up; e1 = hh-data4->col -right; 
                        h2 = w1-data5->row + up; g1 = hh-data5->col -right;
                        j2 = w1-data6->row + up; i1 = hh-data6->col -right;
                        l2 = w1-data7->row + up; k1 = hh-data7->col -right;
                        n2 = w1-data8->row + up; m1 = hh-data8->col -right; 

                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = w1-(temp)->row + up; y1 = hh-(temp)->col -right;
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
                else{
                    for (; temp < limit; temp +=8) {
                        data2 = temp+1;   // a1 = data2->row - up;    b1 = data2->col + right;     b2 = b1; 
                        data3 = temp+2;   // c1 = data3->row - up;    d1 = data3->col + right;     d2 = d1;  
                        data4 = temp+3;   // e1 = data4->row - up;    f1 = data4->col + right;     f2 = f1; 
                        data5 = temp+4;   // g1 = data5->row - up;    h1 = data5->col + right;     h2 = h1;  
                        data6 = temp+5;   // i1 = data6->row - up;    j1 = data6->col + right;     j2 = j1; 
                        data7 = temp+6;   // k1 = data7->row - up;    l1 = data7->col + right;     l2 = l1; 
                        data8 = temp+7;   // m1 = data8->row - up;    n1 = data8->col + right;     n2 = n1;
                        
                        x2 = (temp)->row-up;  y1 = hh-(temp)->col - right; 
                        b2 = data2->row-up; a1 = hh-data2->col - right;
                        d2 = data3->row-up; c1 = hh-data3->col - right;
                        f2 = data4->row-up; e1 = hh-data4->col - right;
                        h2 = data5->row-up; g1 = hh-data5->col - right;
                        j2 = data6->row-up; i1 = hh-data6->col - right;
                        l2 = data7->row-up; k1 = hh-data7->col - right;
                        n2 = data8->row-up; m1 = hh-data8->col - right;

                        r_frame[y1*width + x2] = (temp)->c;
                        r_frame[a1*width + b2] = data2->c;   
                        r_frame[c1*width + d2] = data3->c;  
                        r_frame[e1*width + f2] = data4->c;       
                        r_frame[g1*width + h2] = data5->c;       
                        r_frame[i1*width + j2] = data6->c;       
                        r_frame[k1*width + l2] = data7->c;       
                        r_frame[m1*width + n2] = data8->c; 
                    }
                    for (; temp < end; temp ++){
                        x2 = (temp)->row-up; y1 = hh-(temp)->col - right; 
                        r_frame[y1*width + x2] = (temp)->c;
                    }
                    return;
                }
            }
        }
        else if (mx){
            for (; temp < limit; temp +=8) {
                       y1 = hh- (temp)->row + up;     x2 = (temp)->col + right;      //x2 = x1;  
                data2 = temp+1;    a1 = hh- data2->row + up;    b2 = data2->col + right;     //b2 = b1; 
                data3 = temp+2;    c1 = hh- data3->row + up;    d2 = data3->col + right;     //d2 = d1;  
                data4 = temp+3;    e1 = hh- data4->row + up;    f2 = data4->col + right;     //f2 = f1; 
                data5 = temp+4;    g1 = hh- data5->row + up;    h2 = data5->col + right;     //h2 = h1;  
                data6 = temp+5;    i1 = hh- data6->row + up;    j2 = data6->col + right;     //j2 = j1; 
                data7 = temp+6;    k1 = hh- data7->row + up;    l2 = data7->col + right;     //l2 = l1; 
                data8 = temp+7;    m1 = hh- data8->row + up;    n2 = data8->col + right;     //n2 = n1;
            
                r_frame[y1*width + x2] = (temp)->c;
                r_frame[a1*width + b2] = data2->c;   
                r_frame[c1*width + d2] = data3->c;  
                r_frame[e1*width + f2] = data4->c;       
                r_frame[g1*width + h2] = data5->c;       
                r_frame[i1*width + j2] = data6->c;       
                r_frame[k1*width + l2] = data7->c;       
                r_frame[m1*width + n2] = data8->c;    
            }
            for (; temp < end; temp ++){
                y1 = hh- (temp)->row + up;     x2 = (temp)->col + right;            
                r_frame[y1*width + x2] = (temp)->c;
            }

            return;
        }
        else if (my){
            for (; temp < limit; temp +=8) {
                       y1 = (temp)->row - up;     x2 = w1-(temp)->col - right;    //  x2 = x1;  
                data2 = temp+1;    a1 = data2->row - up;    b2 = w1-data2->col - right;    //b2 = b1; 
                data3 = temp+2;    c1 = data3->row - up;    d2 = w1-data3->col - right;    // d2 = d1;  
                data4 = temp+3;    e1 = data4->row - up;    f2 = w1-data4->col - right;    // f2 = f1; 
                data5 = temp+4;    g1 = data5->row - up;    h2 = w1-data5->col - right;    // h2 = h1;  
                data6 = temp+5;    i1 = data6->row - up;    j2 = w1-data6->col - right;    // j2 = j1; 
                data7 = temp+6;    k1 = data7->row - up;    l2 = w1-data7->col - right;    // l2 = l1; 
                data8 = temp+7;    m1 = data8->row - up;    n2 = w1-data8->col - right;    // n2 = n1;
                r_frame[y1*width + x2] = (temp)->c;
                r_frame[a1*width + b2] = data2->c;   
                r_frame[c1*width + d2] = data3->c;  
                r_frame[e1*width + f2] = data4->c;       
                r_frame[g1*width + h2] = data5->c;       
                r_frame[i1*width + j2] = data6->c;       
                r_frame[k1*width + l2] = data7->c;       
                r_frame[m1*width + n2] = data8->c;    
            }
            for (; temp < end; temp ++){
                y1 = (temp)->row - up;     x2 = w1-(temp)->col - right;
                r_frame[y1*width + x2] = (temp)->c;
            }
            return;
        }
        else{
            for (; temp < limit; temp +=8) {
                y1 = (temp)->row - up;     x2 = (temp)->col + right;      //x2 = x1;  
                data2 = temp+1;    a1 = data2->row - up;    b2 = data2->col + right;     //b2 = b1; 
                data3 = temp+2;    c1 = data3->row - up;    d2 = data3->col + right;     //d2 = d1;  
                data4 = temp+3;    e1 = data4->row - up;    f2 = data4->col + right;     //f2 = f1; 
                data5 = temp+4;    g1 = data5->row - up;    h2 = data5->col + right;     //h2 = h1;  
                data6 = temp+5;    i1 = data6->row - up;    j2 = data6->col + right;     //j2 = j1; 
                data7 = temp+6;    k1 = data7->row - up;    l2 = data7->col + right;     //l2 = l1; 
                data8 = temp+7;    m1 = data8->row - up;    n2 = data8->col + right;     //n2 = n1;

                r_frame[y1*width + x2] = (temp)->c;
                r_frame[a1*width + b2] = data2->c;   
                r_frame[c1*width + d2] = data3->c;  
                r_frame[e1*width + f2] = data4->c;       
                r_frame[g1*width + h2] = data5->c;       
                r_frame[i1*width + j2] = data6->c;       
                r_frame[k1*width + l2] = data7->c;       
                r_frame[m1*width + n2] = data8->c;    
            }
            for (; temp < end; temp ++){
                y1 = (temp)->row - up;
                x2 = (temp)->col + right;
                r_frame[y1*width + x2] = (temp)->c;
            }
            return;

        }
    }
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
    int processed_frames = 0;
    register int rw = 0, data_id =0;
    int row_width = times3(width);
    struct color pixel;
    struct color white_pixel = {0xff,0xff,0xff};
    char * white_row = (char*) malloc(row_width);
    memset(white_row, white, row_width);
    int loop = sensor_values_count/25;
    int ratio = 10;
    int smallrow = width/ratio;
    int offsetrow = width%ratio;
    int offsetrow3 = times3(offsetrow);
    int smallrow3 = times3(smallrow);
    int i;
    int col;
    int border = height*0.15*row_width;
    char * whiteborder = (char*) malloc(border);
    memset(whiteborder, white, border);
    int row = (memcmp(&frame[rw], whiteborder, border))? height*0.15 : 0;
    int end = height*0.85*width;
    int bot_height = (memcmp(&frame[end], whiteborder, border))? end: height;
    for (; row < bot_height; row ++){
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
    register int up = 0, right = 0, clockwise = 0;
    register bool mx = false, my = false;
    int val;
    char * key; 
    sensor_values_count= sensor_values_count - sensor_values_count%25;
    for (int sensorValueIdx = 0; sensorValueIdx < sensor_values_count; sensorValueIdx++) {
        val = sensor_values[sensorValueIdx].value;
        key = sensor_values[sensorValueIdx].key;

        if (!strcmp(key, "W")) {
            if (clockwise){
                val = mx ? 0-val :val;
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
                val = mx ? 0-val :val;
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
                val = my ? 0-val :val;
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
                val = my ? 0-val :val;
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
            loop = loop - 1;
            struct color * r_frame = (struct color *) frame_buffer;
            for (int i = 0; i < data_id; i ++){
                r_frame[data[i].row*width+data[i].col] = white_pixel;
            }
            // memset(frame, white, times3(height*width));
            transform(frame_buffer, up, right, clockwise, mx, my, height, width, data, data_id,loop);
	        verifyFrame(frame_buffer, width, height, grading_mode);
            up = 0;right=0;clockwise=0;mx=false;my=false;
        }
    }
    // free(data);
    return;
}

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int bytes_per_pixel; /* 3:RGB, 4:RGBA */
    unsigned char*    pixel_data;
}PICT_STRUCT;

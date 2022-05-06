# Stegano-BMP
**Stegano-BMP** is a C program to hide BMP files into other BMP files using Least Significant Bit (LSB)

# Definitions of functions
`int hide_bmp_into_bmp(FILE** from, FILE** to, FILE** output)`
| argument | description |
|---|---|
| FILE** from | handle to base BMP file (rb) |
| FILE** to | handle to BMP file to write inside base (rb) |
| FILE** output | handle to output file (w+b) |

`int restore_bmp_from_bmp(FILE** bmp, FILE** output)`
| argument | description |
|---|---|
| FILE** bmp | handle to stegano BMP file (rb) |
| FILE** to | handle to file where to save extracted BMP file (w+b) |
# Usage
An example of usage is included in the **main.c** file

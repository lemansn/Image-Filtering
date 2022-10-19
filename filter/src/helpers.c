#include "helpers.h"
#include <stdio.h>
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    int avarage;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {


            avarage = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen +image[i][j].rgbtRed)/3);

            image[i][j].rgbtGreen = avarage;
            image[i][j].rgbtBlue = avarage;
            image[i][j].rgbtRed = avarage;

        }
    }

}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp;

    for (int j = 0; j < width / 2; j++)
    {
        for (int i = 0; i < height; i++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;


        }
    }


    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            int x[] = {i-1,i,i+1};
            int y[] = {j-1,j,j+1};

            float sumRed,sumBlue,sumGreen,count;

            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 3; ++l) {

                    if (x[k] >=0 && x[k] <height && y[l] >=0 && y[l] <width ){


                        sumBlue += temp[x[k]][y[l]].rgbtBlue;
                        sumGreen += temp[x[k]][y[l]].rgbtGreen;
                        sumRed += temp[x[k]][y[l]].rgbtRed;
                        count++;

                    }
                }
            }

            temp[i][j].rgbtRed =round(sumRed/count);
            temp[i][j].rgbtGreen =round(sumGreen/count);
            temp[i][j].rgbtBlue =round(sumBlue/count);


        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;

        }
    }

}
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int GR[3][3];
    int GG[3][3];
    int GB[3][3];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float red, green, blue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
           temp[h][w] = image[h][w];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int countx = 0;

            for (int x = i - 1; x < i + 2; x++)
            {
                int county = 0;
                for (int y = j - 1; y < j + 2; y++)
                {
                    if ((x < 0 || y < 0) || (x >= height || y >= width))
                    {
                        GR[countx][county] = 0;
                        GG[countx][county] = 0;
                        GB[countx][county] = 0;
                    }
                    else
                    {
                        GR[countx][county] = temp[x][y].rgbtRed;
                        GG[countx][county] = temp[x][y].rgbtGreen;
                        GB[countx][county] = temp[x][y].rgbtBlue;
                    }

                    county++;

                }
                countx++;
            }

            float sumxR = 0, sumyR = 0, sumxG = 0, sumyG = 0, sumxB = 0, sumyB = 0;
            for (int ix = 0; ix <= 2; ix++)
            {
                for (int iy = 0; iy <= 2; iy++)
                {
                    sumxR += (GR[ix][iy] * Gx[ix][iy]);
                    sumxG += (GG[ix][iy] * Gx[ix][iy]);
                    sumxB += (GB[ix][iy] * Gx[ix][iy]);

                    sumyR += (GR[ix][iy] * Gy[ix][iy]);
                    sumyG += (GG[ix][iy] * Gy[ix][iy]);
                    sumyB += (GB[ix][iy] * Gy[ix][iy]);
                }
            }


            red = round(sqrt((sumxR * sumxR) +(sumyR * sumyR)));
            green = round( sqrt((sumxG * sumxG) + (sumyG * sumyG)));
            blue = round(sqrt((sumxB * sumxB) + (sumyB * sumyB)));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}








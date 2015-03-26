#include <QCoreApplication>
#include <iostream>
#include <sstream>
#include <string>
#include <QtGui/QImage>
#include <cmath>

QImage image(640,480, QImage::Format_RGB32);

float bLeft(float x1, float x2, float x3)
{
    if (x1 <= x2 && x1 <= x3)
    {
        return x1;
    }
    else if (x2 <= x1 && x2 <= x3)
    {
        return x2;
    }
    else
        return x3;
}

float bRight(float x1, float x2, float x3)
{
    if (x1 >= x2 && x1 >= x3)
    {
        return x1;
    }
    else if (x2 >= x1 && x2 >= x3)
    {
        return x2;
    }
    else
        return x3;
}

float bUp(float y1, float y2, float y3)
{
    if (y1 <= y2 && y1 <= y3)
    {
        return y1;
    }
    else if (y2 <= y1 && y2 <= y3)
    {
        return y2;
    }
    else
        return y3;
}

float bBottom(float y1, float y2, float y3)
{
    if (y1 >= y2 && y1 >= y3)
    {
        return y1;
    }
    else if (y2 >= y1 && y2 >= y3)
    {
        return y2;
    }
    else
        return y3;
}

int main(int argc, char *argv[])
{
    using namespace std;
    string delim1 = ",";
    string delim2 = ":";
    string input;
    int x1, x2, x3, y1, y2, y3;
    float r1, r2, r3, g1, g2, g3, b1, b2, b3;
    float boundLeft, boundRight, boundTop, boundBottom;
    size_t pos = 0;
    QRgb value = qRgb(255,255,255);

    cout << "Please Enter 3 Points\n";
    cout << "All Points must be in the format x,y:r,g,b\n";
    cout << "r,g,b values should all be between 0-1\n";

    // input for the first point
    cout << "Point 1: \n";
    cin >> input;
    pos = input.find(delim1);
    x1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim2);
    y1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    r1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    g1 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    b1 = atoi(input.c_str());

    // input for the second point
    cout << "Point 2: \n";
    cin >> input;
    pos = input.find(delim1);
    x2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim2);
    y2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    r2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    g2 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    b2 = atoi(input.c_str());

    // input for the third point
    cout << "Point 3: \n";
    cin >> input;
    pos = input.find(delim1);
    x3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim2);
    y3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    r3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    pos = input.find(delim1);
    g3 = atoi(input.substr(0, pos).c_str());
    input.erase(0, pos + delim1.length());
    b3 = atoi(input.c_str());

    // sets initial triangle points
    value = qRgb((r1*255),(g1*255),(b1*255));
    image.setPixel(x1,y1,value);
    value = qRgb((r2*255),(g2*255),(b2*255));
    image.setPixel(x2,y2,value);
    value = qRgb((r3*255),(g3*255),(b3*255));
    image.setPixel(x3,y3,value);

    // sets the bounding box quardinates
    boundLeft = bLeft(x1, x2, x3);
    boundRight = bRight(x1, x2, x3);
    boundTop = bUp(y1, y2, y3);
    boundBottom = bBottom(y1, y2, y3);

    // fill pixels inside triangle
    float det = ((y2-y3)*(x1-x3))+((x3-x2)*(y1-y3));
    for(int i = boundLeft; i < boundRight; i++)
    {
        for(int j = boundTop; j < boundBottom; j++)
        {
            float l1 = ((y2-y3)*(i-x3))+((x3-x2)*(j-y3));
            l1 = l1 / det;
            if(l1 > 0 && l1 < 1)
            {
                float l2 = ((y3-y1)*(i-x3))+((x1-x3)*(j-y3));
                l2 = l2 / det;
                if(l2 > 0 && l2 < 1 && (l1 + l2) < 1 && (l1 + l2) > 0)
                {
                    float l3 = 1 - l1 - l2;
                    float r = (l1*r1) + (l2*r2) + (l3*r3);
                    float g = (l1*g1) + (l2*g2) + (l3*g3);
                    float b = (l1*b1) + (l2*b2) + (l3*b3);
                    value = qRgb((r*255),(g*255),(b*255));
                    image.setPixel(i,j,value);
                }
            }
        }
    }

    // Displays the info obtained
    cout << "You Entered in format x,y:r,g,b\n";
    cout << "Point 1: " << x1 << "," << y1 << ":" << r1 << "," << g1 << "," << b1 << "\n";
    cout << "Point 2: " << x2 << "," << y2 << ":" << r2 << "," << g2 << "," << b2 << "\n";
    cout << "Point 3: " << x3 << "," << y3 << ":" << r3 << "," << g3 << "," << b3 << "\n";

    // Output
    if(image.save("triangle.jpg",0,100)) {
        cout << "Output triangle.jpg" << endl;
    } else {
        cout << "Unable to save triangle.jpg" << endl;
    }

    QCoreApplication a(argc, argv);
    return a.exec();
}

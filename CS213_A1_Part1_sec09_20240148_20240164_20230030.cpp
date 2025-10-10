// mini_photoshop project a1 for cs
// name :John Samy Gadelkareem  s:s23           Id:20240148 Filters : 2,5,8,11 + bonus tv & purple
// name :Ahmed Khattab          didn't register Id:20230030 Filters : 1,4,7,10
// name : Hassan Mohammed       s:s9            Id:20240164 Filters : 3,6,9,12
// github repo: https://github.com/JO-291/mini_photoshop
// drive :     https://drive.google.com/drive/folders/1MF-7ubACQxSf8J2ZoOHFS-64Bhg3LIil?usp=sharing

#include<iostream>
#include<cmath>
#include <vector>
#include<stack>
#include "Image_Class.h"
using namespace std;

void save_image(Image image,string photo){
    string filename;
    cout<<"To Save As(y) or Save(s)??\n(y/s) choose:\n";
    char h;cin>>h;h = tolower(h);
    while (h != 'y' && h != 's') {
        cout << "Invalid input! Try again (y/s): ";
        cin >> h;
        h = tolower(h);
    }
    if(h=='y') {
        cout << "\nPls enter image name to store new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
        cin >> filename;
        image.saveImage(filename);
    }
    else image.saveImage(photo);
}

void printmssg() {
    cout<<"\n->Choose which filter u like to use or \n(0) to undo \n (-1)-to end program\n(20)-to edit on new image\n";
    cout<<"->  1 - Grayscale\n";
    cout<<"->  2 - Black and White\n";
    cout<<"->  3 - Invert Image\n";
    cout<<"->  4 - Merge Images\n";
    cout<<"->  5 - Flip Image\n";
    cout<<"->  6 - Rotate Image\n";
    cout<<"->  7 - Darken and Lighten Image\n";
    cout<<"->  8 - Crop Images\n";
    cout<<"->  9 - Adding a Frame to the Picture\n";
    cout<<"->  10- Detect Image Edges\n";
    cout<<"->  11- Resizing Images\n";
    cout<<"->  12- Blur Images\n";
    cout<<"->  13- TV filter\n";
    cout<<"->  14- Purple filter\n->";
}
//1-Grayscle
Image grayscale(Image& image){
    for(int i = 0;i<image.width;i++){
        for(int j = 0;j<image.height;j++){
            unsigned int avg = 0;
            for(int k=0; k<3; k++) avg += image(i,j,k);
            avg = avg/3;
            for(int k = 0; k<3; k++) image(i,j,k)=avg;
        }
    }
    return image;
    }

// 2- Black and white
Image black_white(Image& image) {
    for (int i=0;i<image.width;i++) {
        for (int j=0;j<image.height;j++) {
            unsigned int avg=0;
            for (int k=0;k<3;k++) avg += image(i,j,k);
            avg/=3;
            if (avg>90) {
                for (int k=0;k<3;k++) image(i,j,k) = 255;
            }
            else {
                for (int k=0;k<3;k++) image(i,j,k) =0;
            }
        }
    }
    cout<<"Done  ;)\n";
    return image;
}

// 3- Invert Filter
Image invert(Image& img ) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) {
                unsigned char val = img.getPixel(x, y, c);
                img.setPixel(x, y, c, 255 - val);
            }
        }
    }
    return img;
}
//  4-  merge
Image merge(Image& image1,Image& image2){
    Image newimage1;
    Image newimage2;
    if(image1.width!=image2.width||image1.height!=image2.height) {
        cout << "chose an option:" << endl;
        cout << "1-resize both to the greatest height and width" << endl;
        cout << "2-merge the common area of smaller height and width" << endl;
        int a, x, y;
        cin >> a;
        while (a != 1 && a != 2) {
            cout << "Invalid input! Try again (1/2): ";
            cin >> x;
        }
        if (a == 1) {
            if (image1.width > image2.width) {
                x = image1.width;
            } else {
                x = image2.width;
            }
            if (image1.height > image2.height) {
                y = image1.height;
            } else {
                y = image2.height;
            }
            double new1w = (double) image1.width/x;
            double new1h = (double) image1.height/y;
            double new2w = (double) image2.width/x;
            double new2h = (double) image2.height/y;
            newimage2 = Image(x,y);
            newimage1 = Image(x,y);
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    for (int k = 0; k < 3 ; ++k) {
                        newimage1(i,j,k) = image1(min((int)round(new1w*i),image1.width-1), min((int)round(new1h*j),image1.height-1),k);
                        newimage2(i,j,k) = image2(min((int)round(new2w*i),image2.width-1), min((int)round(new2h*j),image2.height-1),k);
                    }
                }

            }
            image1 = newimage1;
            image2 = newimage2;
        }
        if(a==2){
            if (image1.width < image2.width) {
                x = image1.width;
            } else {
                x = image2.width;
            }
            if (image1.height < image2.height) {
                y = image1.height;
            } else {
                y = image2.height;
            }
            double new1w = (double) image1.width/x;
            double new1h = (double) image1.height/y;
            double new2w = (double) image2.width/x;
            double new2h = (double) image2.height/y;
            newimage2 = Image(x,y);
            newimage1 = Image(x,y);
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    for (int k = 0; k < 3 ; ++k) {
                        newimage1(i,j,k) = image1(min((int)round(new1w*i),image1.width-1), min((int)round(new1h*j),image1.height-1),k);
                        newimage2(i,j,k) = image2(min((int)round(new2w*i),image2.width-1), min((int)round(new2h*j),image2.height-1),k);
                    }
                }
            }
            image1 = newimage1;
            image2 = newimage2;
        }
    }

Image merged(image1.width,image1.height);
    for (int i = 0; i < image1.width; ++i) {
        for (int j = 0; j < image1.height; ++j) {
            for (int k = 0; k < 3; ++k) merged(i,j,k) = (image1(i,j,k)+image2(i,j,k))/2;
        }
    }
    return merged;
}


//  5-  horizontal & Vertical
Image horizontal_Vertical(Image& image){
    Image image2(image.width,image.height);
    cout<<"Enter h for horizontal Flip or v for vertical Flip:\n";
    char h;cin>>h;
    while (h != 'h' && h != 'v') {
        cout << "Invalid input! Try again (h/v): ";
        cin >> h;
        h = tolower(h);
    }
    for(int i=0;i<image.width;i++) {
        for(int j=0;j<image.height;j++){
            for(int m=0;m<3;m++) {
                if (h=='h') image2(image.width-i-1  ,j,m)=image(i,j,m);
                else image2(i,image.height-j-1,m)=image(i,j,m);
            }
        }
    }
    cout<<"Done  ;)\n";
    return image2;
}

// 6- Rotate Filter
void Rotate(Image& img){
    int angle;
    cout << "Enter rotation angle (90 / 180 / 270): ";
    cin >> angle;
    while (angle != 90 && angle != 180 && angle != 270) {
        cout << "Invalid input! Try again (90 / 180 / 270): ";
        cin >> angle;
    }
    int newWidth = (angle == 180) ? img.width : img.height;
    int newHeight = (angle == 180) ? img.height : img.width;

    unsigned char* rotatedData = new unsigned char[newWidth * newHeight * img.channels];

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < img.channels; c++) {
                unsigned char value = img.getPixel(x, y, c);

                int newX, newY;
                if (angle == 270) {
                    newX = y;
                    newY = img.width - 1 - x;
                } else if (angle == 180) {
                    newX = img.width - 1 - x;
                    newY = img.height - 1 - y;
                } else if (angle == 90) {
                    newX = img.height - 1 - y;
                    newY = x;
                } else {
                    cout << "Unsupported angle!\n";
                    exit(0);
                }

                rotatedData[(newY * newWidth + newX) * img.channels + c] = value;
            }
        }
    }
    stbi_image_free(img.imageData);

    img.imageData = rotatedData;
    img.width = newWidth;
    img.height = newHeight;
}

//7- Darken and lighten
Image Darkenandlighten(Image& image){
    cout<<"what do you want to do:"<<endl;
    cout<<"enter 1 to darken"<<endl;
    cout<<"enter 2 to lighten"<<endl;
    int x;
    cin>>x;
    while (x != 1 && x != 2) {
        cout << "Invalid input! Try again (1/2): ";
        cin >> x;
    }
    if(x == 1){
        for(int i = 0;i<image.width;++i){
            for(int j = 0;j<image.height;++j){
                for(int k = 0;k<3;++k){
                    float pix = static_cast<float>(image(i, j, k));
                    pix *= 0.5f;
                    pix = max(0.0f, pix);
                    image(i, j, k) = static_cast<unsigned char>(pix);
                }
            }
        }
    }
    else if(x == 2){
        for(int i = 0;i<image.width;++i){
            for(int j = 0;j<image.height;++j){
                for(int k = 0;k<3;++k){
                    float pix = static_cast<float>(image(i, j, k));
                    pix *= 1.5f;
                    pix = min(255.0f, pix);
                    image(i, j, k) = static_cast<unsigned char>(pix);
                }
            }
        }
    }
    return image;
}


// 8- crop
Image crop(Image& image) {
    cout<<"Enter where to cut row*col:\n";
    int rownod,colnod;
    cin>>rownod>>colnod;
    cout<<"Enter cropped Image Dimensions row*col:\n-> ";
    int row,col;
    cin>>row>>col;
    while (image.width < rownod + row || image.height < colnod + col) {
    cout << "Invalid input! Try again with valid inputs \n -> ";
    cin >> row >> col;
}
    cout<<"test\n";
    Image image2(row,col);

    for(int i=rownod;i<rownod+row;i++) {
        for(int j=colnod;j<colnod+col;j++) {
            for(int k=0;k<3;k++) image2(i-rownod,j-colnod,k)=image(i,j,k);
        }
    }
    cout<<"Done  ;)\n";
    return image2;
}


// 9- Frame filter
Image frame(Image& img){
    int thickness;
    int choice;
    cout << "Enter frame thickness: ";
    cin >> thickness;

    cout << "Choose frame type (0 = Simple, 1 = Decorated): ";
    cin >> choice;
    while (choice != 0 && choice != 1) {
        cout << "Invalid input! Try again (0/1): ";
        cin >> choice;
    }
    int newW = img.width + 2 * thickness;
    int newH = img.height + 2 * thickness;

    Image framed(newW, newH);

    for (int y = 0; y < newH; y++) {
        for (int x = 0; x < newW; x++) {
            for (int c = 0; c < img.channels; c++) {
                unsigned char val;
                if (x >= thickness && x < thickness + img.width &&
                    y >= thickness && y < thickness + img.height) {
                    val = img.getPixel(x - thickness, y - thickness, c);
                }
                else {
                    if (choice == 0) val = 255;
                    else {
                        if (((x / 10) + (y / 10)) % 2 == 0) val = (c == 0 ? 255 : 0);
                        else val = 0;
                    }
                }
                framed.setPixel(x, y, c, val);
            }
        }
    }
    return framed;
}


//10 - detect edge
Image edgeDetection(Image& image){
    image = grayscale(image);
    int diffright,diffdown;
    for (int i = 0; i < image.width-1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {
            diffright = abs(image(i, j, 0) - image(i + 1, j, 0));
            diffdown = abs(image(i, j, 0) - image(i, j + 1, 0));

            for (int k = 0; k < 3; ++k) {

                if (diffright > 30 || diffdown > 30) {
                    image(i, j, k) = 0;
                }
                else{
                    image(i,j,k) = 255;
                }
            }
        }
    }
    return image;
}


// 11 - resize
Image resize(Image& image) {
    cout<<"enter Row*column spaced :\n";
    int row,col;
    cin>>row>>col;
    Image image2(row,col);
    double Rr=(double)image.width/row;
    double Rc=(double)image.height/col;
    cout<<Rr<<" "<<Rc<<'\n';
    for (int i=0;i<image2.width;i++) {
        for (int j=0;j<image2.height;j++) {
            int r= round(Rr*i);
            int c= round(Rc*j);
            if (r>=image.width) r=image.width-1;
            if (c>=image.height) c =image.height-1  ;
            for (int k=0;k<3;k++) image2(i,j,k)=image(r,c,k);
        }
    }
    cout<<"Done  ;)\n";
    return image2;
}


// 12- Blur Filter
Image blur(Image& img){
    for (int y = 5; y < img.height -5 ; y++) {
        for (int x = 5; x < img.width-5 ; x++) {
            for (int c = 0; c < img.channels; c++) {
                int sum = 0;
                for (int dy = -5; dy <= 5; dy++) {
                    for (int dx = -5; dx <= 5; dx++) sum += img.getPixel(x + dx, y + dy, c);
                }
                img.setPixel(x, y, c, sum / 121);
            }
        }
    }
    return img;
}

// TV filter 13
Image TV_filter(Image& image) {
    for (int i=0;i<image.width;i++) {
        for (int j=0;j<image.height;j++) {
            if (j%4==0) {
                for (int k=0;k<3;k++) image(i,j,k)=0;
            }
        }
    }
    return image;
}

Image purple(Image& image) {;
    for (int i=0;i<image.width;i++) {
        for (int j=0;j<image.height;j++) {
            for (int k=0;k<3;k++) {
                if (k==0||k==2)image(i,j,k) = 2.4f*(int)image(i,j,k) ;
            }
        }
    }
    return image;
}


int main(){
    stack<Image> history;
    stack<string> filenames;
    string photo,filename;
    cout<<"Please enter The Image Name->  ";
    cin>>photo;
    filenames.push(photo);
    Image image(photo);
    if(image.loadNewImage(photo)) {
        history.push(image);
        cout<<"Image Loaded Successfully!"<<endl;
    }
    else cout<<"Image Not Loaded!\n";
    while (true){
    Image framed;
    printmssg();
    int filter;cin>>filter;cout<<'\n';

    switch (filter) {
        case -1:
            cout<<"save?? (1)-to save\n(0)-to not save \n ";
        int k;
        cin>>k;
        while (k != 1 && k != 0) {
            cout << "Invalid input! Try again (1 or 0): ";
            cin >> k;
        }
        if (k)save_image(image,photo);
        return 0;
        break;

        case 0:
            if (history.size() > 1) {
                history.pop();
                filenames.pop();
                image=history.top();
                photo=filenames.top();
                image.saveImage(photo);
                cout<<"Undo done.\n";
            }
            else cout<<"There isn't a previous version!\n";
        break;

        case 1:
            cout<<"You picked option 1  \n";
            image = grayscale(image);
            history.push(image);
            filenames.push(photo);

            save_image(image,photo);
            break;

        case 2:
            cout<<"You picked option 2 \n";
            image=black_white(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 3:
            cout<<"You picked option 3 \n";
            image=invert(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 4: {
            cout << "You picked option 4 \n";
            cout << "Enter the second image name:\n";
            string photo2;
            cin>>photo2;
            Image image2(photo2);
            image = merge(image, image2);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;
        }
        case 5:{
            cout<<"You picked option 5 \n";
            image=horizontal_Vertical(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;
        }

        case 6:
            cout<<"You picked option 6 \n";
            Rotate(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 7:
            cout<<"You picked option 7 \n";
            image = Darkenandlighten(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 8:
            cout<<"You picked option 8 \n";
            image=crop(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 9:
            cout<<"You picked option 9 \n";
            framed= frame(image);
            history.push(framed);
            filenames.push(photo);
            save_image(framed,photo);
            break;

        case 10:
            cout<<"You picked option 10 \n";
            image=edgeDetection(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 11:
            cout<<"You picked option 11\n";
            image=resize(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 12:
            cout<<"You picked option 12\n";
            image=blur(image);
            history.push(image);
            filenames.push(photo);
            save_image(image,photo);
            break;

        case 13:
            cout<<"You picked option 13\n";
            image=TV_filter(image);
            history.push(image);
            save_image(image,photo);
            filenames.push(photo);
            break;

        case 14:
             cout<<"You picked option 14\n";
             image=purple(image);
             history.push(image);
             image.saveImage(photo);
            filenames.push(photo);
             break;
        case 20: {
            string newfile;
            cout<<"enter the name of the new image:\n";
            cin>>newfile;
            Image image3(newfile);
            image=image3;
            photo=newfile;
            while (!history.empty()) history.pop();
            while (!filenames.empty()) filenames.pop();
            history.push(image);
            filenames.push(photo);
            break;
        }
        default:
            cout<<"Invalid choice!\n";
    }
    }
}

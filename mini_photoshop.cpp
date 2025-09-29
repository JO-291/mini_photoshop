#include<iostream>
#include<cmath>
#include "Image_Class.h"
using namespace std;
string jpg=".jpg";
void printmssg() {
  cout<<"->Choose which filter u like to use or 15 to End program\n";
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
  cout<<"->  14- Purple filter\n";;
//15- Gaussian filter
}

// 2- Black and white
Image black_white(Image image) {
  for (int i=0;i<image.width;i++) {
     for (int j=0;j<image.height;j++) {
       int avg=0;
       for (int k=0;k<3;k++) {
         avg += image(i,j,k);
       }
       avg/=3;
       if (avg>90) {
         for (int k=0;k<3;k++) {
           image(i,j,k) = 255;
         }
       }
       else {
         for (int k=0;k<3;k++) {
           image(i,j,k) =0;
         }
       }
     }
   }
   cout<<"Done  ;)\n";
  return image;
}

//  5-  horizontal & Vertical
Image horizontal_Vertical(Image image){
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
  return image;
}


// 8- crop
Image crop(Image image) {
  cout<<"Enter cropped Image Dimensions:\n";
  int row,col;
  cin>>row>>col;
  Image image2(row,col);
  cout<<"Enter where to cut:\n";
  int rownod,colnod;
  cin>>rownod>>colnod;
  for(int i=rownod;i<rownod+row;i++) {
    for(int j=colnod;j<colnod+col;j++) {
      for(int k=0;k<3;k++) image2(i-rownod,j-colnod,k)=image(i,j,k);

    }
  }
  cout<<"Done  ;)\n";
  return image;
}

// 11 - resize
Image resize(Image image) {
  cout<<"enter Row*column spaced :\n";
  int row,col;
  cin>>row>>col;
  Image image2(row,col);
  double Rr=(double)image.width/row;
  double Rc=(double)image.height/col;
  cout<<Rr<<" "<<Rc<<'\n';
  for (int i=0;i<image2.width;i++) {
    for (int j=0;j<image2.height;j++) {
      int r=round(Rr*i);
      int c=round(Rc*j);
      if (r>=image.width) r=image.width-1;
      if (c>=image.height) c =image.height-1  ;
      for (int k=0;k<3;k++) image2(i,j,k)=image(r,c,k);
    }
  }
  cout<<"Done  ;)\n";
  return image;
}
// TV filter 13
Image TV_filter(Image image) {
  for (int i=0;i<image.width;i++) {
    for (int j=0;j<image.height;j++) {
      if (j%4==0) {
        for (int k=0;k<3;k++) {
          image(i,j,k)=0;
        }
      }
    }
  }
  return image;
}

Image purple(Image image) {;
  for (int i=0;i<image.width;i++) {
    for (int j=0;j<image.height;j++) {
      for (int k=0;k<3;k++) {
        image(i,j,k) += (k==0||k==1)?50:0;
      }
    }
  }
  return image;
}

int main(){
  //while (true){
    string photo;
    cout<<"Please enter The Image Name->  ";
    cin>>photo;
    cout<<photo<<'\n';
    Image image(photo);
    if( image.loadNewImage(photo)) cout<<"Image Loaded Successfully!"<<endl;
    else {cout<<"Image Not Loaded!\n";
    //  break;
    }
    printmssg();
    int filter;cin>>filter;cout<<'\n';
  switch (filter) {
    case 1:
      cout<<"You picked option 1  \n";
    break;

    case 2:
      cout<<"You picked option 2 \n";
      image=black_white(image);
      image.saveImage(photo+jpg);
      break;

    case 3:
      cout<<"You picked option 3 \n";
      break;

    case 4:
      cout<<"You picked option 4 \n";
      break;

    case 5:
      cout<<"You picked option 5 \n";
      image=horizontal_Vertical(image);
      image.saveImage(photo+jpg);
      break;

    case 6:
      cout<<"You picked option 6 \n";
      break;

    case 7:
      cout<<"You picked option 7 \n";
      break;

    case 8:
      cout<<"You picked option 8 \n";
      image=crop(image);
      image.saveImage(photo+jpg);
      break;

    case 9:
      cout<<"You picked option 9 \n";
      break;

    case 10:
      cout<<"You picked option 10\n";
      break;

    case 11:
      cout<<"You picked option 11\n";
      resize(image);
      break;

    case 12:
      cout<<"You picked option 12\n";
      break;

    case 13:
      cout<<"You picked option 13\n";
      image=TV_filter(image);
      image.saveImage(photo+jpg);
      break;

    case 14:
      cout<<"You picked option 13\n";
      image=purple(image);
      image.saveImage(photo+jpg);
      break;

    default:
          cout<<"Invalid choice!\n";
    }

    //}
}
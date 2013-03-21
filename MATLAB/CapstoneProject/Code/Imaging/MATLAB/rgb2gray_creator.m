I = imread('1.jpg');
Y = uint8(I);
J=im2uint8(Y);
I = mat2gray(J);
I = rgb2gray(I);
imshow(I);
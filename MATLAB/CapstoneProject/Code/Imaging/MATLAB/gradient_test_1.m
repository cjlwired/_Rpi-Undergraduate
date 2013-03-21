ima = imread('a1.jpg');
k=3;
[mu,mask]=kmeans(ima,k);
mask1= mask(:,:,1);
imagesc(mask1);colormap(gray);

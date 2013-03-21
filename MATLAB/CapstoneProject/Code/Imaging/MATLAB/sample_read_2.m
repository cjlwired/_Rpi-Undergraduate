clear all;
close all;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Img = imread('a1.jpg');  % sample grayscale image

%Image passed through segmentation
%ima = imread('a1.jpg');
%k=3;
%[mu,mask]=kmeans(ima,k);
%mask1= mask(:,:,1);
%Img= stretch(mask1,0,3);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Img=double(Img(:,:,1));
sigma=1.5;    % scale parameter in Gaussian kernel for smoothing.
G=fspecial('gaussian',15,sigma);
Img_smooth=conv2(Img,G,'same');  % smooth image by Gaussiin convolution
[Ix,Iy]=gradient(Img_smooth);
f=Ix.^2+Iy.^2;
g=1./(1+f);  % edge indicator function.

epsilon=1.5; % the papramater in the definition of smoothed Dirac function

timestep=5;  % time step
mu=0.2/timestep;  % coefficient of the internal (penalizing) energy term P(\phi)
          % Note: the product timestep*mu must be less than 0.25 for stability!

lambda=5; % coefficient of the weighted length term Lg(\phi)
alf=3;   % coefficient of the weighted area term Ag(\phi);
         % Note: Choose a positive(negative) alf if the initial contour is outside(inside) the object.

[nrow, ncol]=size(Img);
figure;imagesc(Img, [0, 255]);colormap(gray);hold on;
text(6,6,'Left click to get points, right click to get end point','FontSize',[12],'Color', 'r');

% mouse click to specify initial contour/region
BW = roipoly;   % get a region R inside a polygon, BW is a binary image with 1 and 0 inside or outside the polygon;
c0=4; % the constant value used to define binary level set function;
initialLSF= c0*2*(0.5-BW); % initial level set function: -c0 inside R, c0 outside R;

% initialLSF = binaryInitial(con, nrow, ncol);

u=initialLSF;

[c,h] = contour(u,[0 0],'r');
u=initialLSF;
figure;imagesc(Img, [0, 255]);colormap(gray);hold on;
[c,h] = contour(u,[0 0],'r');                          
title('Initial contour');

% start level set evolution
for n=1:600
    u=EVOLUTION(u, g ,lambda, mu, alf, epsilon, timestep, 1);    
    if mod(n,20)==0
        pause(0.001);
        imagesc(Img, [0, 255]);colormap(gray);hold on;
        [c,h] = contour(u,[0 0],'r'); 
        iterNum=[num2str(n), ' iterations'];        
        title(iterNum);
        hold off;
    end
end
imagesc(Img, [0, 255]);colormap(gray);hold on;
[c,h] = contour(u,[0 0],'r'); 
totalIterNum=[num2str(n), ' iterations'];  
title(totalIterNum);

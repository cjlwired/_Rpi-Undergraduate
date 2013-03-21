clear all;
close all;
Img = imread('Test_img4.jpg');  % synthetic noisy image

%ima = imread('Test_img4.jpg');
%k=3;
%[mu,mask]=kmeans(ima,k);
%mask1= mask(:,:,1);
%Img= stretch(mask1,0,3);

Img=double(Img(:,:,1));
sigma=1.5;    % scale parameter in Gaussian kernel for smoothing
G=fspecial('gaussian',15,sigma);
Img_smooth=conv2(Img,G,'same');  % smooth image by Gaussian convolution
[Ix,Iy]=gradient(Img_smooth);
f=Ix.^2+Iy.^2;
g=1./(1+f);  % edge indicator function.

epsilon=1.5; % the paramater in the definition of smoothed Dirac function

timestep=5;  % time step
mu=0.2/timestep;  % coefficient of the internal (penalizing) energy term P(\phi)
          % Note: the product timestep*mu must be less than 0.25 for stability!

lambda=5; % coefficient of the weighted length term Lg(\phi)
alf=2;   % coefficient of the weighted area term Ag(\phi);
         % Note: Choose a positive(negative) alf if the initial contour is outside(inside) the object.

% define initial level set function (LSF) as -c0, 0, c0 at points outside, on
% the boundary, and inside of a region R, respectively.
[nrow, ncol]=size(Img);  
c0=1.07;
initialLSF=c0*ones(nrow,ncol);
w=0;
initialLSF(w+1:end-w, w+1:end-w)=1;  % zero level set is on the boundary of R. 
                                     % Note: this can be commented out. The intial LSF does NOT necessarily need a zero level set.
                                     
initialLSF(w+2:end-w, w+2: end-w)=-c0; % negative constant -c0 inside of R, postive constant c0 outside of R.
u=initialLSF;
figure;imagesc(Img, [0, 255]);colormap(gray);hold on;
[c,h] = contour(u,[0 0],'r');                          
title('Initial contour');


% start level set evolution
for n=1:20
    u=EVOLUTION(u, g ,lambda, mu, alf, epsilon, timestep, 1);      
    if mod(n,1)==0
        pause(0.001);
        imagesc(Img, [0, 255]);colormap(gray);hold on;
        [c,h] = contour(u,[0 0],'r'); 
        iterNum=[num2str(n), ' iterations'];        
        title(iterNum);
        hold off;
    end
end
imagesc(Img, [0, 255]);colormap(gray);hold on;
imwrite(Img, 'img1_contour.jpg');
[c,h] = contour(u,[0 0],'r'); 
totalIterNum=[num2str(n), ' iterations'];  
title(['Final contour, ', totalIterNum]);


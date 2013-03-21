% Shahin Namazi
% Contrast Sketching

function Z = stretch(A,T_1,T_2)

X = double(A);
T_1 = double(T_1);
T_2 = double(T_2);

for i=1:size(X,1)
    for j=1:size(X,2)
        if X(i,j) <= T_1
            Y(i,j) = 0;
        elseif X(i,j) >= T_2
            Y(i,j) = 255;
        else
            Y(i,j) = -255*((X(i,j)-T_1)/(T_1-T_2));
            %Y(i,j) = 100;
        end
    end
end

Z = uint8(floor(Y));
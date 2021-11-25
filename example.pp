int n1 = 1;
int n2 = 1;
canvas cv = {30,10};
int i = 0;

cv char {10,3, 'x'};
cv char {20,3, 'x'};
while (i < 30){
    cv hor {0,30,i};    
    cv vert {0,18,i};
    i = i +3;
};

plot cv;
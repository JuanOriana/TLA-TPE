canvas arg = {27, 9};
canvas suiza = {31, 10};
canvas usa = {31,10};
canvas greece = {31, 10};
int i = 0;
main:
write("\nArgentina\n");
while (i < 3){
    arg hor {0,26,i};
    i = i +1;
}
arg fill {11,4,15,4,'*'};
arg fill {13,3,13,5,'*'};
i = 0;
while (i < 3){
    arg hor {0,26,8-i};
    i = i +1;
}
arg color {4};
plot (arg);

write ("\nSuiza\n");
suiza fill {0,0,30,9,'#'};
suiza fill {13,2,17,7,' '};
suiza fill {10,4,20,5,' '};
suiza color {1};
plot (suiza);

write ("\nUnited States of America\n");
usa fill {0,0,30,9,'='};
usa fill {0,0,10,4,'*'};
usa vert {0,4,10};
plot (usa);

write ("\nGrecia\n");
greece fill {0,0,30,9,'='};
greece fill {3,1,5,3,' '};
greece fill {1,2,7,2,' '};
plot (greece);
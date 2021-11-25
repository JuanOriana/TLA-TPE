int start = 0;
int max;
int impossible = 0;
int done = 0;
canvas cv = {26,11};
write "Escribe hasta que primo quieres probar: ";
read max;
write "\n";

# Y labels
cv char {3,0,'0'};
cv char {5,0,'1'};
cv char {7,0,'2'};
cv char {9,0,'3'};
cv char {11,0,'4'};
cv char {13,0,'5'};
cv char {15,0,'6'};
cv char {17,0,'7'};
cv char {19,0,'8'};
cv char {21,0,'9'};

# X labels
cv char {0,1,'0'};
cv char {0,2,'1'};
cv char {0,3,'2'};
cv char {0,4,'3'};
cv char {0,5,'4'};
cv char {0,6,'5'};
cv char {0,7,'6'};
cv char {0,8,'7'};
cv char {0,9,'8'};
cv char {0,10,'9'};


while(start <= max){
    impossible = 0;
    done = 0;
    write start;
    write " ";
    if (start == 2 || start == 3){
        done = 1;
    };

    if (done == 0){
        if (!(start <= 1 || start % 2 == 0 || start % 3 == 0)){
            int j  = 5;
            while (j*j < start){
                if (start % j ==0 || start % (j+2) == 0){
                    impossible = 1;
                };
                j = j+6;
            };
        }else{
            impossible = 1;
        };
    };

    if (impossible == 1){
        write "no ";
    }
    else
    {
        cv dot {start%10*2+3,start/10+1};
    };
    write "es primo\n";

    start = start + 1;
};

write "\n\n Primos del 0 al 99: \n";

plot cv;

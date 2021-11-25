int start = 1;
int max;
int impossible = 0;
int done = 0;
write "Escribe hasta que primo quieres probar: ";
read max;
write "\n";

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

    if (done == 1 || impossible == 1){
        write "no ";
    };
    write "es primo\n";

    start = start + 1;
};

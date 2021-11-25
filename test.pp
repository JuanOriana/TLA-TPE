string hola = "DONE!";
double n = 3;
main:
while (n < 30){
    write n;
    n = n + 0.5;
    if (n%4 ==0){
        return 0;
    }
}

write hola;
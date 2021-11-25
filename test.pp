int i = 10;
string hola = "DONE!";
main:

while (i < 30){
    write i+1;
    i = i+3;
    if (i%2 ==0){
        return 0;
    }
}

write hola;
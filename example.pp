int n1 = 1;
int n2 = 1;
string xd = "fiumba\n";
int n3 = 0;
int test;
write n1;
write n2;

while (n3 < 120){
    write "Adivina el proximo valor de n: ";
    read test;
    n3 = xd;
    if (test == n3){
        write "Le pegaste!!\n";
    }
    else{
        write "No le pegaste!!\n";
        write n3;
    };
    n1 = n2;
    n2 = n3;
};
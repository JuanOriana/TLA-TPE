double n1 = f0.9;
int n2 = 3;

main:
write ("Bienvenido al evaluador matematico!\n\n");
write ("Se trabaja con el double n1 = ");
write (n1);
write ("\nY con el int n2 = ");
write (n2);

write ("\n\nn1 + n2: ");
write (n1+n2);
write ("\nn1 - n2: ");
write (n1-n2);
write ("\nn1 * n2: ");
write (n1*n2);
write ("\nn1 / n2: ");
write (n1/n2);
write ("\nn2 % 3: ");
write (n2%3);
write ("\nn1 && n2: ");
write (n1&&n2);
write ("\n((n1+n2)/n2*n1)*n1: ");
write (((n1+n2)/n2*n1)*n1);

int n = -1;

write ("\n\nAhora comienza el test de precision. Ingresa un numero del 1 al 100. Se dividira 1 en N partes iguales y \
las sumaremos de a una a una variable double. Finalmente se compara con el valor \
integral para ver la precision.\n\n");

write ("Ingresa tu numero: ");
read (n);
if (n <= 0 || n > 100){
    write ("El numero tiene que ir del 1 al 100!\n");
    return -1;    
}
    

double fract = f1.0 / n;
double sum = 0;
write ("Se usara una fraccion de: ");
write (fract);

while (n){
    sum = sum + fract;
    n = n-1;
}
write ("\n\nEl valor resultante de la suma es:");
write (sum);
write ("\nEl resultado de hacer la suma == 1 es: ");
if (sum == 1){
    write ("VERADERO\n\n");
}
else{
    write ("FALSO\n\n");
}
# Trabajo Práctico Especial - TLA
En este trabajo se presenta el diseño de la grámatica y compilador del lenguaje **Canvalize**. Para mas detalles sobre su proposito y diseño ver el informe en
directorio *./docs/informe.pdf*

## Construcción y ejecucción
Para construir el proyecto, es tan facil como hacer un make en el directorio principal
```console
foo@bar:~/TLA_TPE/$ make
```
Luego encontraremos el ejecutable del compilador **gcav** en el directorio principal. Los codigos fuente de los programas de ejemplo se encuentran en el 
directorio *examples* mientras que los codigos fuente para los programas de ejemplo de error estan en *./examples/error_cases*. El compilador lleva como argumento
no obligatorio el archivo fuente (si no se le pasa ningun archivo se leera de STDIN) y como opcion **-o** el output del ejecutable. Aqui un ejemplo de compilacion: 
```console
foo@bar:~/TLA_TPE/$ ./gcav -o program ./examples/prime.can
```

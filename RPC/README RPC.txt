Para compilar los archivos en RPC ejecutar lo siguiente:

rpcgen -C diccionario.x

Nota: Los archivos generados los tengo subidos desde el inicio

Para compilar el cliente y servidor ejecutar:

g++ -o client diccionario_xdr.c diccionario_clnt.c client.cpp
g++ -o server diccionario_xdr.c diccionario_svc.c server.cpp

Finalmente, para ejecutar el cliente y el servidor ejecutar:

sudo ./server
sudo ./client locahost

Nota2: Los diccionarios precargados tienen el prefijo Dict_X (donde X es un numero)

Nota3: El cliente al conectarse le dice al servidor que cargue los diccionarios que tiene en su carpeta

Nota4: Las palabras se guardan en un multimap en el servidor 

El programa permite las siguientes opciones:

1.- Verificar palabra: revisa si la palabra esta en el diccionario (se le entrega la ID del diccionario)
2.- Agregar palabra: se le pasa la palabra y el diccionario al cual se quiere agregar
3.- Sugerir palabra: se le da una palabra y revisa en todos los diccionarios, si esta sugiere la misma palabra, si no esta se le manda a una sugerencia

Nota5: Sugerencia para el programa son palabras que parten con la misma letra

4.- Agregar palabras por archivo: Se le pasa el path de un archivo, el cual se lee y se manda al servidor, lo cual entrega una estadística de palabras encontradas, agregadas al diccionario y que ya estaban

5.- Mostrar todas las palabras de un diccionario en particular

6.- Salir: sale xD

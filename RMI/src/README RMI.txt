Para compilar el RMI debe hacer lo siguiente:

Compilar cada uno de las clases que hay, con los comandos

javac Servidor.java
javac Cliente.java
javac ClienteP2P.java
javac InterfazRemotaServidor.java
javac InterfazRemotoCliente.java 
javac ObjetoRemotoCliente.java
javac ObjetoRemotoServidor.java

PD: De todos modos subí cada clase compilada

Luego en un terminal ejecutar:
rmiregistry 1989

Nota: El puerto que elegi es 1989 para que todos los clientes se conecten (y asi esta configurado mi programa)

Después, para iniciar el servidor, colocar:
java -Djava.security.policy=java.policy Servidor

Y para iniciar cada cliente colocar
java Cliente

Nota: El servidor SOLO se utiliza para ver todos los usuarios en red. Sin embargo, si uno conoce el nombre de usuario del otro cliente, se pueden conectar entre sí usando la opción de conexión manual

Nota2: El mensaje se envía a todos los usuarios conectados a la red

Nota3: Los seguidores reciben siempre notificaciones del que siguen, estando o no en la misma red

Nota4: Al iniciar el Cliente, este pide un nombre de usuario para conectarse

Nota5: El timeline simplemente muestra el usuario y el mensaje que envió al cliente

El programa permite las siguientes opciones:

1.- Unirse a una red: Muestra todos los usuarios que se han logueado en el programa, para luego colocar el nombre de uno, y se establece una conexión con él. (para esto se requiere del servidor)

2.- Buscar usuarios en la red: Se hace un broadcast a todos los clientes conectados, y se obtiene una lista de todos los usuarios conectados a esta red (no se usa el Servidor)

3.- COnectarse manualmente a otro usuario: Permite conectarse a un usuario directamente si se conoce su nombre de usuario

4.- Volverse seguidor: Muestra una lista de usuarios, del cual uno puede elegir ser seguidor de alguno (se requere del servidor para esto, aunque se podria modificar pidiendo solo el mnombre si se conoce) (Claro que una vez establecida la conexión no se usa el servidor

5.- Mandar mensaje: Se envia un mensaje tanto a los seguidores como a los que se encuentran en la red (este mensaje se guarda en el timeline)

6.- Mostrar timeline: Permite mostrar los mensajes que el cliente recibe (junto con el nombre del que lo envia)

7.- Ver a los que sigo: Muestra una lista de usuarios qeu el cliente actual sigue

8.- Salir: Sale xD

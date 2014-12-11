import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.EventObject;
import java.util.Map;
import java.util.Scanner;


public class ClienteP2P{
	
	public InterfazRemotaServidor objetoRemotoServer;
	public InterfazRemotaCliente objetoRemotoCliente;
    private String myname;
    private int id;
    
    public void initialize(String name) throws RemoteException, MalformedURLException{
    	objetoRemotoCliente = (InterfazRemotaCliente) new ObjetoRemotoCliente(name);
        Naming.rebind("//localhost:1989/"+name, objetoRemotoCliente);
        id = objetoRemotoServer.conectar(name);
    }
    
    public void console() throws RemoteException, Exception{
    		Scanner s =  new Scanner(System.in);
        	System.out.print("Bienvenido al twitter RMI de Marco Arias\nPor favor ingrese su nombre\n");
        	myname = s.nextLine();
            initialize(myname);
            boolean b =true;
        while(b){    
            System.out.println("Ingrese una opción\n\n1.- Unirse a una red\n2.- Buscar usuarios de la red\n3.- Conectarse manualmente a otro usuario\n4.- Volverse seguidor\n5.- Mandar mensaje\n6.- Mostrar timeline\n7- Ver a los que sigo\n8.- Salir");
            int op = Integer.parseInt(s.nextLine());
            if(op==1){
            	Map m = objetoRemotoServer.getClients();
            	System.out.println("Usuarios en línea");
            	for(int i =0;i<m.size();i++){
            		System.out.println("N "+i+" "+m.get(i));
            	}
            	System.out.println("Ingrese el nombre del cliente que quiera seguir");
            	String name = s.nextLine();
            	if(name.equals(myname)){
            		System.out.println("No se puede conectar a sí mismo");
            	}
            	else{
            		objetoRemotoCliente.setClienteRed(name);
            	}
            }
            else if(op==2){
            	objetoRemotoCliente.buscarConectados();
            }
            else if(op==3){
            	System.out.println("Ingrese el nombre del cliente con el que desee conectarse");
            	String cln = s.nextLine();
            	objetoRemotoCliente.setClienteRed(cln);
            }
            else if(op==4){
            	Map m = objetoRemotoServer.getClients();
            	conectarCliente(m,s);
            }
            else if(op==5){
            	System.out.println("Ingrese el mensaje a enviar\n");
            	String msn = s.nextLine();
            	enviarMensaje(msn);
            }
            else if(op==6){
            	mostrarMensajes();
            }
            else if(op==7){
            	verUsuariosQueSigo();
            }
            else if(op==8){
            	b = false;
            	System.out.println("Se va a salir del programa");
            	System.out.println("Adios =)");
            }
            else{
            	System.out.println("Ingrese una opción válida");
            }
    	}
    }
    
    public void conectarCliente(Map m, Scanner s) throws RemoteException, NotBoundException{
    	System.out.println("Usuarios en línea");
    	for(int i =0;i<m.size();i++){
    		System.out.println("N "+i+" "+m.get(i));
    	}
    	System.out.println("Ingrese el nombre de cliente que quiera seguir");
    	String name = s.nextLine();
    	if(name.equals(myname)){
    		System.out.println("No se peude conectar a sí mismo");
    	}
    	else{
        	objetoRemotoCliente.setAlQueSigo(name);
    	}
    	
    }
    
	public String getName() {
		return myname;
	}
	
	public void enviarMensaje(String msn) throws RemoteException, NotBoundException{
		objetoRemotoCliente.save(myname, msn);
		objetoRemotoCliente.sendSeguidores(myname,msn);
		objetoRemotoCliente.send(myname, msn);
		System.out.println("Mensajes enviados");
	}
	
	public void verUsuariosQueSigo() throws RemoteException{
		objetoRemotoCliente.observarSeguidos(myname);
	}
	
	public void mostrarMensajes() throws RemoteException{
		objetoRemotoCliente.verMensajes();
	}

}

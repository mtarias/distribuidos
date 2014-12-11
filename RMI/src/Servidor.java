import java.rmi.*;
import java.rmi.server.*;
import java.util.Map;
public class Servidor { 
	
	public static void main (String args[]){
	System.setSecurityManager(new RMISecurityManager());
        try{
            System.setProperty ("java.rmi.server.codebase", "file:/user/mtarias/tarea1/rmi");
            ObjetoRemotoServidor objetoRemoto = new ObjetoRemotoServidor();
            Naming.rebind("//localhost:1989/ObjetoRemoto", objetoRemoto);
        }
        catch(Exception e){
            System.out.println("Error:"+e.toString());
        }
    }
    

}

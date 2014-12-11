import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.util.EventObject;
import java.util.Scanner;
import java.util.Map;

import javax.xml.bind.Marshaller.Listener;

public class Cliente{


	public static void main(String args[]){
        try{
            ClienteP2P cliente = new ClienteP2P();
        	Registry registry = LocateRegistry.getRegistry(1989);
            cliente.objetoRemotoServer = (InterfazRemotaServidor) registry.lookup("ObjetoRemoto");
            cliente.console();
        }
        catch(Exception e){
            System.out.print("Error: "+e.toString());
        }
        
    }

}

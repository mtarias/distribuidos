import java.io.Serializable;
import java.rmi.*;
import java.rmi.server.*;
import java.util.HashMap;
import java.util.Map;

public class ObjetoRemotoServidor extends UnicastRemoteObject implements InterfazRemotaServidor{
	
	private HashMap<Integer,String> clientes;
    private int n;
	
	protected ObjetoRemotoServidor() throws RemoteException {
		super();
		clientes = new HashMap<Integer, String>();
		n = 0;
	}
	
	public static void main(String args[]){ 
    	
    }
    
    public int conectar(String client) throws RemoteException{
    	
    	try{
    		clientes.put(n, client);
    		System.out.println("Cliente agregado a servidor");
    		n++;
    		return n-1;
    	}
    	catch (Exception e){
    		System.out.println(e.getMessage());
    	}
    	return n;
    }
    
    public Map getClients(){
    	return clientes;
    }

}
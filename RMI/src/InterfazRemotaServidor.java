import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Map;


public interface InterfazRemotaServidor extends Remote{
	public Map getClients()throws RemoteException;

	public int conectar(String name) throws RemoteException;
	
}

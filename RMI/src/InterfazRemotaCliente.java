import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;

public interface InterfazRemotaCliente extends Remote{
	
	public void setSeguidor(String name) throws RemoteException, NotBoundException;

	public void setAlQueSigo(String name) throws RemoteException, NotBoundException;

	public void save(String myname, String msn)throws RemoteException;

	public void sendSeguidores(String name,String msn) throws RemoteException;
	
	public void observarSeguidos(String myname)throws RemoteException;
	
	public String getName() throws RemoteException;
	
	public void verMensajes() throws RemoteException;

	public void recibirSolicitud(String name)throws RemoteException;
	
	public void setClienteRed(String name)throws RemoteException, NotBoundException;

	public void receive(ArrayList<String> mensajeros,String mensajero,
			String msn) throws RemoteException;

	public void send(String myname,String msn) throws RemoteException, NotBoundException;

	public ArrayList<InterfazRemotaCliente> buscar(
			ArrayList<InterfazRemotaCliente> cn)throws RemoteException;

	public void buscarConectados()throws RemoteException;


}

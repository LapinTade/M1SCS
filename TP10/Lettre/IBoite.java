package Lettre;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IBoite extends Remote {
	Message releverMessage() throws RemoteException;
	void deposerMessage(Message msg) throws RemoteException;
}

package Lettre;

import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class Server extends UnicastRemoteObject implements IBoite {
	Message msg;
	public Server() throws RemoteException {
		super();
		msg = new Message();
	}
	
	public Message releverMessage() throws RemoteException {
		return msg;
	}
	
	public void deposerMessage(Message msg) throws RemoteException{
		this.msg = msg;
	}
	
	public static void main(String[] args) throws Exception {
		Server srv = new Server();
		Naming.bind("localhost", srv);
	}
}

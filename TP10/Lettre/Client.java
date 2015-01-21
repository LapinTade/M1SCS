package Lettre;
import java.net.MalformedURLException;
import java.rmi.*;

public class Client {
	public static void main(String[] args) throws Exception {
		IBoite ib = (IBoite) Naming.lookup("localhost");
		
		Message msg = new Message();
		msg.nom = "LAPIN";
		msg.mess = "I <3 CARROTS";
		
		ib.deposerMessage(msg);
	}
}

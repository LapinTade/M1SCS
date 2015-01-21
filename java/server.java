import java.net.Socket;
import java.net.ServerSocket;
import java.io.InputStream;	
import java.io.IOException;

public class server {
  public static void main(String [] args) {
    ServerSocket srv ;
    byte[] tabloServ = new byte[4];
    try {
      srv = new ServerSocket(5555) ;
      Socket sockComm = srv.accept() ;
      InputStream is = sockComm.getInputStream();
      
      int recu = is.read(tabloServ);
      // afficher tabloServ 
      is.close(); // ferme le flux
      sockComm.close() ;  srv.close(); // ferme la socket de comm et de connex
    } catch(IOException e) {System.out.println("ERROR");}
    System.out.println(tabloServ[0]);
    System.out.println(tabloServ[1]);
    System.out.println(tabloServ[2]);
  } // main
  
} // class


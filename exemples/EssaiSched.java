class EssaiThread extends Thread {

    // lorsque l'on met static, c'est la meme variable 
    // qui est definie dans chaque thread.
    // private static long vart;

    // lorsque l'on ne met pas static, on a une variable par thread
    private String message;

    /** constructeur permettant de nommer le processus */
    public EssaiThread(String message) {
        this.message = message;
    }

    /** affiche son nom puis passe le controle au suivant */
    public void run(){

	
	while(true){
            System.out.print(message);	
	    yield();
	}
        
    }
    
}

public class EssaiSched {
    
    public static void main(String args[]) {
    
	new EssaiThread("Foo").start();
	new EssaiThread("Bar").start();
        /*Thread bar = new EssaiThread("Bar");
        bar.setPriority(Thread.NORM_PRIORITY+3);
	bar.start();*/
    }

}

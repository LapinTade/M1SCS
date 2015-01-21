/*
 LecteurRedacteur
  - threads lecture/écriture partageant un texte commun
  - priorité "égale"
 */

class Texte {
    private int nbLecteurs = 0;
    private boolean lecture = false;
    private boolean redaction = false;
    
    public synchronized void debutLecture(){
	System.out.println(Thread.currentThread().getName() + " j'ai demande lire");
	while (redaction) 
	    try{
		wait();
	    }catch(InterruptedException e){}
	System.out.println(Thread.currentThread().getName() + " je lis ");
//			   "nbLect = " + nbLecteurs + "red " + redaction);
	nbLecteurs++;
	if (nbLecteurs==1) lecture = true;
    }
    
    public synchronized void finLecture() {
	nbLecteurs--;
	System.out.println(Thread.currentThread().getName() + " j'ai fini lire ");
	if(nbLecteurs==0) {
		lecture = false;
		notifyAll();
	}
   }
    
    public synchronized void debutEcriture() {
    System.out.println(Thread.currentThread().getName() + " j'ai demande ecrire ");
	while (lecture || redaction) 
	    try{
		wait();
	    }catch(InterruptedException e){}
	System.out.println(Thread.currentThread().getName() + " j'ecris ");
//                           "nbLect = " + nbLecteurs+"red " + redaction);
	redaction = true;	
    }
    
    public synchronized void finEcriture() {
	redaction = false;
	// il faut reveiller tout le monde car
	// plusieurs lecteurs sont peut-etre bloques
		System.out.println(Thread.currentThread().getName() + " j'ai fini ecrire ");
	notifyAll();

    }
}

class Lecteur extends Thread {
    private int id;
    private Texte texte;
    
    public Lecteur(int id, Texte texte) {
	this.id = id;
	this.texte = texte;
    }
    
    public void run() {
	while(true) {
	    try {
		
		sleep((int)(Math.random()*1000));
		//System.out.println("Le lecteur "+id+"name"+ getName()+" demande a lire");
		texte.debutLecture();
		//System.out.println("Le lecteur "+id+"name"+ getName()+" commence la lecture");
		sleep((int)(Math.random()*1000));
		texte.finLecture();
		//System.out.println("Le lecteur "+id+"name"+ getName()+" a fini sa lecture");
	    } catch (InterruptedException e) {
		
	    }
	}
    }
}

class Redacteur extends Thread {
    private int id;
    private Texte texte;
    
    public Redacteur(int id, Texte texte) {
	this.id = id;
	this.texte = texte;
    }
    
    public void run() {
	while(true) {
	    try {
		
		sleep((int)(Math.random()*1000));
		//System.out.println("Le redacteur "+id+"name"+ getName()+" demande a ecrire");
		texte.debutEcriture();
		//System.out.println("Le redacteur "+id+"name"+ getName()+" commence sa redaction");
		sleep((int)(Math.random()*1000));
		texte.finEcriture();
		//System.out.println("Le redacteur "+id+"name"+ getName()+" a fini sa redaction");
	    } catch (InterruptedException e) {
		
	    }
	}
    }
}

public class LecteurRedacteurMain {
    
    public static void main(String[] args) {
	Texte texte = new Texte();
	
	for(int i = 0; i<5; i++) {
	    Lecteur l = new Lecteur(i, texte);
	    l.start();
	}
	for(int i = 0; i<5; i++) {
	    Redacteur r = new Redacteur(i, texte);
	    r.start();
	}
	
    }
    
}

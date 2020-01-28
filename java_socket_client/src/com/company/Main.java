package com.company;

import java.io.*;
import java.net.*;

public class Main {

    private static int port;

    public static void main(String[] args) throws IOException {
        String adresse, line;
        Reader readSoc;
        PrintStream sortie = null;
        boolean fin = false;

        if (args.length != 2) {
            System.out.println("usage : java client nom_serveur port");
            System.exit(0);
        }
        adresse = args[0];
        port = new Integer(args[1]).intValue();
        Socket socket = new Socket(adresse, port);
        Reader reader = new InputStreamReader(System.in);
        BufferedReader keyboard = new BufferedReader(reader);
        sortie = new PrintStream(socket.getOutputStream());
        readSoc = new InputStreamReader(socket.getInputStream());
        BufferedReader keyboardSoc = new BufferedReader(readSoc);
        while (true) {
            System.out.flush();
            System.out.println("-------------------------------------------------");
            System.out.println("*                   Menu                        *");
            System.out.println("-------------------------------------------------");
            System.out.println("*        1.Compter nombre de voyelle            *");
            System.out.println("*        2.Compter nombre de mots               *");
            System.out.println("*        3.Quitter                              *");
            System.out.println("-------------------------------------------------");
            System.out.println("Enter un nombre:  ");
            line = keyboard.readLine();
            switch(line.charAt(0))
            {
                case '1':
                    System.out.println("-------------------------------------------------");
                    System.out.println("*          Compter nombre de Voyelle            *");
                    System.out.println("-------------------------------------------------");
                    System.out.println("Entrer une phrase : ");
                    sortie.println("1");
                    keyboardSoc.readLine();
                    sortie.println(keyboard.readLine());
                    System.out.println("\nReponse :");
                    System.out.println(keyboardSoc.readLine());
                    System.out.println("Cliquer sur entrer pour retourner au menu...");
                    keyboard.readLine();
                    break;
                case '2':
                    System.out.println("-------------------------------------------------");
                    System.out.println("*          Compter nombre de mots               *");
                    System.out.println("-------------------------------------------------");
                    System.out.println("Entrer une phrase : ");
                    sortie.println("2");
                    keyboardSoc.readLine();
                    sortie.println(keyboard.readLine());
                    System.out.println("\nReponse :");
                    System.out.println(keyboardSoc.readLine());
                    System.out.println("Cliquer sur entrer pour retourner au menu...");
                    keyboard.readLine();
                    break;
                case '3':
                    sortie.println("3");
                    fin = true;
                    break;
                default:
                    System.out.println("Erreur => Entrer un nombre entre 1 et 3");
                    System.out.println("Cliquer sur entrer pour retourner au menu...");
                    keyboard.readLine();
            }

            if (fin)
                break;
        }
        // fermeture de la socket
        socket.close();
        System.out.println("Deconnection -> Fin de programme");
    }
}
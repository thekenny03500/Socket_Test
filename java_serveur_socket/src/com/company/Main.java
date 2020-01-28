package com.company;

import java.io.*; import java.net.*;

public class Main {
    private static int port;

    public static void main(String[] args) throws IOException {
        boolean boucle = true, fin = false;
        Reader reader;
        PrintStream sortie=null;
        Socket soc;
        String line;
        String result = "";
        if(args.length != 1)
        {
            System.out.println("usage : java serveur port");
            System.exit(0);
        }

        port = new Integer(args[0]).intValue();
        ServerSocket s = new ServerSocket (port);
        System.out.println("La socket serveur est cree");
        while (true)
        {
            boucle = true;
            System.out.println("en attente de connexion");
            soc = s.accept();
            System.out.println("Connexion realise a " + soc.toString());
            reader = new InputStreamReader(soc.getInputStream());
            sortie = new PrintStream(soc.getOutputStream());
            BufferedReader keyboard = new BufferedReader (reader);
            while (boucle)
            {
                line = keyboard.readLine();
                if(line == null)
                {
                    line ="3";
                    System.out.println("Perte de connexion\n");
                }
                System.out.println("buf "+line.charAt(0));
                switch(line.charAt(0))
                {
                    case '1':
                        System.out.println("Function 1 => OK");
                        sortie.println("ARK");
                        line = keyboard.readLine();
                        System.out.println("Function 1 => buf result "+line);
                        result = Integer.toString(countVoyelle(line));
                        break;
                    case '2':
                        System.out.println("Function 2 => OK");
                        sortie.println("ARK");
                        line = keyboard.readLine();
                        System.out.println("Function 2 => buf result "+line);
                        result = Integer.toString(countWord(line));
                        break;
                    case '3':
                        fin = true;
                        break;
                    default:
                        System.out.println("Erreur => Entrer un nombre entre 1 et 3");
                }

                if(fin)
                {
                    boucle = false;
                    line = null;
                    soc.close();
                }
                else
                {
                    sortie.println(result);
                    result = null;
                }
            }
        }
    }

    public static int countVoyelle(String pharse)
    {
        int toSender = 0, nbchar = pharse.length();

        String voyelles = "aeiouyAEIOUY";

        for(int i = 0; i < nbchar; i++)
        {
            if(voyelles.indexOf(pharse.charAt(i))>=0)
            {
                toSender++;
            }
        }

        return toSender;
    }

    public static int countWord(String phrase)
    {
        int toSender = 0, nbchar = phrase.length();
        boolean inWord = false;

        for (int i = 0; i < nbchar; ++i)
        {
            switch(phrase.charAt(i))
            {
                case '\0':
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    if (inWord)
                    {
                        inWord = false;
                        toSender++;
                    }
                    break;
                default: inWord = true;
            }
        }
        if (inWord)
        {
            toSender++;
        }

        return toSender;
    }
}

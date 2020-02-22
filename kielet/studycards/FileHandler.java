import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;


class FileHandler {

    public void readFile(final File f, final WordPairList list) {
        String line = null;
        BufferedReader reader = null;
        int tabLoc;
        int spcLoc;
        String word1;
        String word2;

        try {

            reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream(f), "UTF-8"));
            // Windows, Venäjä/Russian, Unicode text files
            /*reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream(f), "UTF-16"));*/

            // Windows, Saksa/German, normal text files
            /*  reader = new BufferedReader(new InputStreamReader(
                    new FileInputStream(f)));*/
            
            line = reader.readLine();

            while (line != null) {
                line = line.trim();
                if (line.length() > 0) {
                    tabLoc = line.indexOf("\t");

                    if (tabLoc == -1) {
                        spcLoc = line.indexOf(" ");

                        word1 = line.substring(0, spcLoc);
                        word2 = line.substring(spcLoc + 1, line.length());

                    }
                    else {
                        word1 = line.substring(0, tabLoc);
                        word2 = line.substring(tabLoc + 1, line.length());
                    }
                    word1 = word1.trim();
                    word2 = word2.trim();
                    list.add(new WordPair(word1, word2));
                }
                line = reader.readLine();
            }

        }
        catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        catch (IOException e) {
            /* Karkea käsittely */
            e.printStackTrace();
            return;
        }
        finally { /* Suoritetaan aina */
            /* Siivousyritelmä */
            if (reader != null) {
                try {
                    reader.close();
                }
                catch (IOException e) {
                    /* Karkea käsittely II */
                    e.printStackTrace();
                    return;
                }
            }
        }

    }

}

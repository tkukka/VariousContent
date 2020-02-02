import java.io.BufferedReader;
import java.io.Console;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

/**
 *  Open JDK 11.0
 *
 * http://zetcode.com/java/readtext/
 *
 */
public class JavaFileRead {
    public static final String FILENAME = "./eng-uk_web_2002_1M-words.txt";

    /**
     *
     * @param filename
     * @return
     */
    public static int read_file(final String filename) {
        int i = 0;
        try (final BufferedReader infile = new BufferedReader(new FileReader(filename, StandardCharsets.UTF_8))) {
            String line = null;

            while ((line = infile.readLine()) != null) {
                ++i;
            }

        } catch (final FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (final IOException e) {
            e.printStackTrace();
        }
        return i;
    }

    /**
     *
     * @param filename
     * @return
     */
    public static int read_file2(String filename) {
        try {
            final List<String> lines = Files.readAllLines​(Path.of(filename), StandardCharsets.UTF_8);
            return lines.size();
        } catch (final IOException e) {
            e.printStackTrace();
        }
        return 0;
    }

    public static void main(final String[] args) {
        final Console con = System.console();
        if (con != null) {
            con.writer().println("Java reading file: " + JavaFileRead.FILENAME );
            final int nlines = JavaFileRead.read_file(FILENAME);
            //final int nlines = JavaFileRead.read_file2(FILENAME);
            con.writer().println("Lines: " + nlines);
            con.writer().println("Java exit");
        }
    }
}

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;


class StudyCardsController  implements  ActionListener,  ItemListener {
    public static final String cmdReadFile = "ReadFile";
    public static final String cmdNext = "next";
    public static final String cmdRemove = "remove";
    
    private final StudyCards view;
    private final JFileChooser file_choose;
    private final FileHandler fh = new FileHandler();
    private final WordPairList pairs = new WordPairList();
    private WordPair current_pair = null;
    private boolean show_both = false;
    private boolean reverse = false;
    
    /**
     * 
     * @param v
     */
    public StudyCardsController(StudyCards v) {
        view = v;
        
        String dir = System.getProperty("user.dir");
        file_choose = new JFileChooser(new File(dir));
        file_choose.setFileSelectionMode(JFileChooser.FILES_ONLY);
        file_choose.setMultiSelectionEnabled(false);
    }
    
    
    
    
    
    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub

    }

    public void actionPerformed(ActionEvent e) {
        String cmd = e.getActionCommand();
        WordPair wp = null;

        if (cmd.equals(cmdReadFile)) {
            loadFile();
            show_both = false;
            wp = pairs.get();
            current_pair = wp;

            view.setBtn1Text("Näytä vastaus");
            if (wp != null) {
                if (reverse) {
                    view.setLblText(wp.getWord2());
                }
                else {
                    view.setLblText(wp.getWord1());
                }
            }
            else {
                view.setLblText("(Tyhjä)");
            }
        }
        else if (cmd.equals(cmdNext)) {

            if (show_both == false) {

                if (current_pair != null) {

                    if (reverse) {

                        view.setLblText(current_pair.getWord2() + "  =  "
                                + current_pair.getWord1());

                    }
                    else {
                        view.setLblText(current_pair.getWord1() + "  =  "
                                + current_pair.getWord2());

                    }
                    
                    show_both = true;
                    view.setBtn1Text("Seuraava");

                }
                
            }
            else {

                wp = pairs.get();
                current_pair = wp;
                show_both = false;
                view.setBtn1Text("Näytä vastaus");
                if (wp != null) {

                    if (reverse) {
                        view.setLblText(wp.getWord2());
                    }
                    else {
                        view.setLblText(wp.getWord1());
                    }

                }

            }

        }
        else if (cmd.equals(cmdRemove)) {

            pairs.remove(current_pair);
            show_both = false;
            wp = pairs.get();
            current_pair = wp;
            view.setBtn1Text("Näytä vastaus");
            if (wp != null) {
                if (reverse) {
                    view.setLblText(wp.getWord2());
                }
                else {
                    view.setLblText(wp.getWord1());
                }

            }
            else {
                view.setLblText("(Loppu)");
            }
        }

    }
    
    /**
     * 
     */
    private void loadFile() {
        int response = file_choose.showOpenDialog(view);
        
        
        if (response == JFileChooser.APPROVE_OPTION) {
            File listFile = file_choose.getSelectedFile();

            if (listFile.isFile() == false) {
                JOptionPane.showMessageDialog(view, "Tiedostoa "
                        + listFile.getName() + " ei löydy.", "Virhe",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
            else if (listFile.canRead() == false) {
                JOptionPane.showMessageDialog(view, "Tiedostoa "
                        + listFile.getName() + " ei voi lukea.", "Virhe",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            pairs.clear();
            fh.readFile(listFile, pairs);
            pairs.randomize();
            
        }
        
        
    }





    public void itemStateChanged(ItemEvent arg0) {
        reverse = !reverse;
        
    }
    
    
    
    
}

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;

class StudyCards extends JFrame implements Runnable {
    private static final long serialVersionUID = 2946043831177946957L;
    private final StudyCardsController ctrl;
    private JLabel laabel;
    private JButton nextBtn;
    private JButton removeBtn;
    
    public StudyCards() {
        super("Sanasto");
        ctrl = new StudyCardsController(this);

    }
    
    
    /**
     * 
     */
    private void createUI() {
        JFrame.setDefaultLookAndFeelDecorated(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        
        JPanel lowPanel2  = new JPanel();
        lowPanel2.setLayout(new BoxLayout(lowPanel2,BoxLayout.LINE_AXIS));
        
        nextBtn = new JButton("Näytä vastaus");
        nextBtn.addActionListener(ctrl);
        nextBtn.setActionCommand(StudyCardsController.cmdNext);
        
        lowPanel2.add(nextBtn);
        lowPanel2.add(Box.createRigidArea(new Dimension(15,0)));
        removeBtn = new JButton("Poista");
        removeBtn.addActionListener(ctrl);
        removeBtn.setActionCommand(StudyCardsController.cmdRemove);
        lowPanel2.add(removeBtn);

       

        
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel,BoxLayout.PAGE_AXIS));
        
        
        laabel = new JLabel("(Tyhjä)", SwingConstants.CENTER );
        laabel.setFont(new Font("Arial", Font.PLAIN, 18));
        laabel.setPreferredSize(new Dimension(500,100));
        laabel.setBorder(BorderFactory.createLineBorder(Color.black));
        
        
        JPanel centPanel = new JPanel(new BorderLayout());
        centPanel.add(laabel, BorderLayout.CENTER);
        mainPanel.add(centPanel);
        mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
        mainPanel.add(lowPanel2);
        mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
        //mainPanel.add(midPanel, BorderLayout.CENTER);
        getContentPane().setLayout(new BorderLayout());
        getContentPane().add(mainPanel, BorderLayout.CENTER);
        
        
        JMenuBar menuBar = new JMenuBar();
        JMenu menu1 = new JMenu("Tiedosto");
        JMenuItem menuitem11 = new JMenuItem("Lue sanalista...");
        menuitem11.addActionListener(ctrl);
        menuitem11.setActionCommand(StudyCardsController.cmdReadFile);
        
        JMenu menu2 = new JMenu("Asetukset");
        JCheckBoxMenuItem menuitem21 = new JCheckBoxMenuItem("Käänteinen suunta");
        menuitem21.setSelected(false);
        menuitem21.addItemListener(ctrl);
         
        
        menuBar.add(menu1);
        menuBar.add(menu2);
        menu1.add(menuitem11);
        menu2.add(menuitem21);
        setJMenuBar(menuBar);
        
        
        
        
        setResizable(true);
        pack();
        setLocationRelativeTo(null); 
        setVisible(true);
    }
    
    public void setLblText(String s) {
        laabel.setText(s);
    }
    
    public void setBtn1Text(String s) {
        nextBtn.setText(s);
    }
    
    /**
     * @param args
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new StudyCards());

    }

    public void run() {
        createUI();
        
    }

}

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;


public class NumberView extends JFrame implements Runnable, ActionListener {

    /**
     * 
     */
    private static final long serialVersionUID = -8705213482291766648L;
    private static final String cmdNew = "new";
    private static final Random rnd = new Random();
     
    
    private JLabel laabel;
    private JLabel laabel1;

    public NumberView(String string) {
       super(string);
    } 
   
   
    private void createUI() {
        JFrame.setDefaultLookAndFeelDecorated(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel lowPanel2  = new JPanel();
        lowPanel2.setLayout(new BoxLayout(lowPanel2,BoxLayout.LINE_AXIS));
        
        
        
        laabel = new JLabel(" ", SwingConstants.CENTER );
        laabel.setFont(new Font("Arial", Font.PLAIN, 18));
        //laabel.setPreferredSize(new Dimension(50,20));
        laabel.setBorder(BorderFactory.createLineBorder(Color.blue));
                        
        lowPanel2.add(laabel);
        lowPanel2.add(Box.createRigidArea(new Dimension(15,0)));
        
        JButton nextBtn = new JButton("Uusi");
        //nextBtn.setPreferredSize(new Dimension(120,25));
        nextBtn.addActionListener(this);
        nextBtn.setActionCommand(cmdNew);
        
        lowPanel2.add(nextBtn);
        
        
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel,BoxLayout.PAGE_AXIS));
        
        
        laabel1 = new JLabel("(Ans)", SwingConstants.CENTER );
        laabel1.setFont(new Font("Arial", Font.PLAIN, 18));
        laabel1.setPreferredSize(new Dimension(500,100));
        laabel1.setBorder(BorderFactory.createLineBorder(Color.black));
        
        JPanel centPanel = new JPanel(new BorderLayout());
        mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
        mainPanel.add(lowPanel2);
        mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
        centPanel.add(laabel1, BorderLayout.CENTER);
        mainPanel.add(centPanel);
        mainPanel.add(Box.createRigidArea(new Dimension(0,10)));
        
        getContentPane().setLayout(new BorderLayout());
        getContentPane().add(mainPanel, BorderLayout.CENTER);
        
        
        
        setResizable(true);
        pack();
        setLocationRelativeTo(null); 
        setVisible(true);
    }
    
    
    
    /**
     * @param args
     */
    public static void main(String[] args) {
       SwingUtilities.invokeLater(new NumberView("Numerot"));

    }

    
    @Override
    public void run() {
        createUI();
        
    }


    @Override
    public void actionPerformed(ActionEvent e) {
      
        int i = rnd.nextInt(999999999);
        
        while(i < 0)
        {
            i = rnd.nextInt();
        }
        
        laabel.setText(Integer.toString(i));
        
        laabel1.setText(Number.Display(i));
        
        
    }

}

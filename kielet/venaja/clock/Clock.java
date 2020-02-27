import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;

/**
 * 
 */
class Clock extends JFrame implements Runnable, ActionListener, MouseListener,
        MouseWheelListener {

    private JLabel laabel;
    private JButton nextButton;
    private JButton showButton;
    private JTextArea txtField;
    private static final Random rndmSource = new Random();
    private int hour = 12;
    private int minute = 0;
    private boolean modify_hours = true;

    private static final String[] CARDINALS_M = { "ноль", "оди́н", "два",
            "три", "четы́ре", "пять", "шесть", "семь", "во́семь", "де́вять",
            "де́сять", "оди́ннадцать", "двена́дцать" };

    private static final String[] CARDINALS_F = { "ноль", "одна́", "две",
            "три", "четы́ре", "пять", "шесть", "семь", "во́семь", "де́вять",
            "де́сять", "оди́ннадцать", "две́надцать", "трина́дцать",
            "четы́рнадцать", "пятна́дцать", "шестна́дцать", "семна́дцать",
            "восемна́дцать", "девятна́дцать", "два́дцать", "два́дцать одна́",
            "два́дцать две", "два́дцать три", "два́дцать четы́ре",
            "два́дцать пять", "два́дцать шесть", "два́дцать семь",
            "два́дцать во́семь", "двадцать де́вять" };

    private static final String[] MINUTES = { "мину́та", "мину́ты", "мину́т" };

    private static final String[] ORDINALS_GEN = { "нолевого", "второ́го",
            "тре́тьего", "четвёртого", "пя́того", "шесто́го", "седьмо́го",
            "восьмо́го", "девя́того", "деся́того", "оди́ннадцатого",
            "двена́дцатого", "пе́рвого" };

    private static final String[] HOURS = { "час", "часа́", "часо́в" };

    private static final String[] CARDINALS_GEN_F = { "ноли", "одно́й", "двух",
            "трёх", "четырёх", "пяти́", "шести́", "семи́", "восьми́",
            "девяти́", "десяти́", "оди́ннадцати", "двена́дцати", "трина́дцати",
            "четы́рнадцати", "пятна́дцати", "шестна́дцати", "семна́дцати",
            "восемна́дцати", "девятна́дцати", "двадцати́", "двадцати́ одно́й",
            "двадцати́ двух", "двадцати́ трёх", "двадцати́ четырёх",
            "двадцати́ пяти́", "двадцати́ шести́", "двадцати́ семи́",
            "двадцати́ восьми", "двадцати́ девяти́"

    };

    /**
     * 
     */
    private static final long serialVersionUID = 5916917978491262550L;

    /**
     * 
     */
    public Clock() {
        super("Paljonko kello on?  Кото́рый час?");

    }

    /**
     * 
     */
    private void createUI() {
        JFrame.setDefaultLookAndFeelDecorated(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        txtField = new JTextArea();
        txtField.setRows(2);
        txtField.setFont(new Font("Arial", Font.PLAIN, 18));
        txtField.setEditable(false);
        txtField.setMargin(new java.awt.Insets(2, 2, 2, 0));
        //txtField.setColumns(30);
        txtField.setAlignmentY(Component.LEFT_ALIGNMENT);
        txtField.setBorder(BorderFactory.createTitledBorder(BorderFactory
                .createLineBorder(Color.black), "Vastaus:"));

        showButton = new JButton("Näytä vastaus");
        showButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        showButton.addActionListener(this);
        showButton.setActionCommand("show");

        nextButton = new JButton("Seuraava aika");
        nextButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        nextButton.addActionListener(this);
        nextButton.setActionCommand("next");

        JPanel btnPanel = new JPanel();
        btnPanel.add(showButton);
        btnPanel.add(nextButton);

        JPanel lowPanel = new JPanel();
        lowPanel.setLayout(new BoxLayout(lowPanel, BoxLayout.PAGE_AXIS));
        lowPanel.add(txtField);
        lowPanel.add(Box.createRigidArea(new Dimension(0, 5)));
        lowPanel.add(btnPanel);

        lowPanel.add(Box.createRigidArea(new Dimension(0, 5)));

        laabel = new JLabel("12.00", SwingConstants.CENTER);
        laabel.setFont(new Font("Arial", Font.PLAIN, 18));
        laabel.setPreferredSize(new Dimension(400, 40));
        laabel.setBorder(BorderFactory.createLineBorder(Color.black));
        laabel.addMouseListener(this);
        laabel.addMouseWheelListener(this);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.PAGE_AXIS));

        JPanel centPanel = new JPanel(new BorderLayout());
        centPanel.add(laabel, BorderLayout.CENTER);
        mainPanel.add(centPanel);
        mainPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        mainPanel.add(lowPanel);

        getContentPane().setLayout(new BorderLayout());
        getContentPane().add(mainPanel, BorderLayout.CENTER);

        setResizable(true);
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
    }

    /* (non-Javadoc)
     * @see java.lang.Runnable#run()
     */
    public void run() {
        createUI();

    }

    /**
     * 
     * @return
     */
    private String getTime() {
        int min;
        int count = 0;

        hour = rndmSource.nextInt(12) + 1;
        String t1 = "";
        if (hour < 10) {
            t1 = "0";
        }
        t1 += Integer.toString(hour);

        do {
            min = rndmSource.nextInt(60);
            count++;
        } while (min % 5 != 0 && count < 3);

        minute = min;
        String t2 = "";
        if (min < 10) {
            t2 = "0";
        }
        t2 += Integer.toString(min);
        return t1 + "." + t2;
    }

    /**
     * 
     */
    private void buildAnswer(StringBuilder a1, StringBuilder a2) {
        String answer1 = new String();
        String answer2 = new String();

        if (minute == 0) {
            // sharp hour
            if (hour == 1) {
                answer1 = HOURS[0];
            }
            else {
                answer1 = CARDINALS_M[hour];
                if (hour >= 2 && hour <= 4) {
                    answer1 += (" " + HOURS[1]);
                }
                else {
                    answer1 += (" " + HOURS[2]);
                }
            }
        }
        else if (minute < 30) {

            answer1 = CARDINALS_F[minute];
            if (minute == 1 || minute == 21) {
                answer1 += (" " + MINUTES[0]);
            }
            else if ((minute >= 2 && minute <= 4) || (minute >= 22 && minute <= 24)) {
                answer1 += (" " + MINUTES[1]);
            }
            else {
                answer1 += (" " + MINUTES[2]);
            }

            answer1 += (" " + ORDINALS_GEN[hour]);

            if (minute == 15) {
                answer2 = "че́тверть " + ORDINALS_GEN[hour];
            }

        }
        else if (minute > 30) {
            int missing = 60 - minute;

            if (missing == 1 || missing == 21) {
                answer1 = "без " + CARDINALS_GEN_F[missing] + " (" + MINUTES[1]
                        + ")";
            }
            else {
                answer1 = "без " + CARDINALS_GEN_F[missing] + " (" + MINUTES[2]
                        + ")";
            }

            if (hour == 12) {
                answer1 += " час";
            }
            else {
                answer1 += (" " + CARDINALS_M[hour + 1]);
            }

            if (minute == 45) {
                answer2 = "без че́тверти";

                if (hour == 12) {
                    answer2 += " час";
                }
                else {
                    answer2 += (" " + CARDINALS_M[hour + 1]);
                }

            }

        }
        else {
            answer1 = "полови́на" + " " + ORDINALS_GEN[hour];
            answer2 = "пол" + ORDINALS_GEN[hour];

        }

        a1.append(answer1);
        a2.append(answer2);

    }

    /**
     * 
     */
    public void actionPerformed(ActionEvent arg0) {
        String cmd = arg0.getActionCommand();

        if (cmd.equals("next")) {
            laabel.setText(getTime());
            txtField.setText(" ");
        }
        else if (cmd.equals("show"))

        {
            showAnswer();
        }

    }

    private void showAnswer() {
        StringBuilder answer1 = new StringBuilder();
        StringBuilder answer2 = new StringBuilder();
        buildAnswer(answer1, answer2);
        if (answer2.length() == 0) {
            txtField.setText(answer1.toString());
        }
        else {
            txtField.setText("1. " + answer1 + "\n2. " + answer2);
        }
    }

    private void formTime() {
        String t1 = "";
        if (hour < 10) {
            t1 = "0";
        }
        t1 += Integer.toString(hour);

        String t2 = "";
        if (minute < 10) {
            t2 = "0";
        }
        t2 += Integer.toString(minute);
        laabel.setText(t1 + "." + t2);
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Clock());

    }

    private void inc_hour() {
        if (hour == 12) {
            hour = 1;
        }
        else {
            hour++;
        }

    }

    private void dec_hour() {
        if (hour == 1) {
            hour = 12;
        }
        else {
            hour--;
        }
    }

    private void inc_minute() {
        if (minute == 59) {
            minute = 0;
        }
        else {
            minute++;
        }

    }

    private void dec_minute() {
        if (minute == 0) {
            minute = 59;
        }
        else {
            minute--;
        }
    }

    public void mouseClicked(MouseEvent arg0) {

        switch (arg0.getButton()) {
        case MouseEvent.BUTTON1:
            modify_hours = true;
            inc_hour();
            break;

        case MouseEvent.BUTTON2:
            /*showAnswer();
            break;*/
            return;

        case MouseEvent.BUTTON3:
            modify_hours = false;
            inc_minute();
            break;

        default:
            break;
        }

        formTime();
        showAnswer();

    }

    public void mouseEntered(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    public void mouseExited(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    public void mousePressed(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    public void mouseReleased(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    public void mouseWheelMoved(MouseWheelEvent arg0) {
        int notches = arg0.getWheelRotation();

        if (notches < 0) {

            if (modify_hours) {
                inc_hour();
            }
            else {
                inc_minute();
            }

        }
        else {
            if (modify_hours) {
                dec_hour();
            }
            else {
                dec_minute();
            }

        }

        formTime();
        showAnswer();

    }

}


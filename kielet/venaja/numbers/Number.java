
import java.util.Stack;


public final class Number {
    private static final String[] CARDINAL0_19 = { "ноль", "один", "два",
            "три", "четыре", "пять", "шесть", "семь", "восемь", "девять",
            "десять", "одиннадцать", "двенадцать", "тринадцать",
            "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать",
            "восемнадцать", "девятнадцать" };

    private static final String[] CARDINAL20_90 = { "--", "**", "двадцать",
            "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят",
            "восемьдесят", "девяносто" };

    private static final String[] CARDINAL100_900 = { "++", "сто", "двести",
            "триста", "четыреста", "пятьсот", "шестьсот", "семьсот",
            "восемьсот", "девятьсот" };

/*
    private static final String[] FORMS_THOUSAND = { "тысяча", "тысячи", "тысяч"};
    private static final String[] FORMS_MILLION = { "миллион", "миллиона", "миллионов"};
    */
    private static final String[][] FORMS = { null, { "тысяча", "тысячи", "тысяч"}, { "миллион", "миллиона", "миллионов"} };
    
    private static final boolean[]  MASC_FORM = { true, false, true};
    
    private static final String F_ONE = "одна";
    private static final String F_TWO = "две";
    private static final String ERROR = "(error)";

    
    private static final Stack<String> stringStack = new Stack<String>();

    private static final void Digit3(int value, boolean IsMasculine,
            final String[] forms)
    {
        int units = value % 10;
        int tens = (value/10) % 10;
        int hundreds = (value/100) % 10;
        
        /*if (forms == null)
        {
            
            System.out.print(2);
        }*/
        
        /*if(value == 0)
        {
            stringStack.push(CARDINAL0_19[0]);
        }
        else*/
        if (tens <= 1) // X00...X19
        {
            if (forms == null) {

                if ((tens != 0) || (units != 0)) // Prevent X00 becoming zero.
                {
                    stringStack.push(CARDINAL0_19[tens * 10 + units]);
                }
            }
            else
            {
                
                if (units == 1) {
                    stringStack.push(forms[0]);
                    if (IsMasculine == true) {
                        stringStack.push(CARDINAL0_19[units]);
                    }
                    else {
                        stringStack.push(F_ONE);
                    }
                }
                else if (units == 2) {
                    stringStack.push(forms[1]);

                    if (IsMasculine == true) {
                        stringStack.push(CARDINAL0_19[units]);
                    }
                    else {
                        stringStack.push(F_TWO);
                    }

                }
                else if ((units == 3) || (units == 4)) {
                    stringStack.push(forms[1]);
                    stringStack.push(CARDINAL0_19[units]);
                }
                else {
                    stringStack.push(forms[2]);
                    if ((tens != 0) || (units != 0)) // Prevent X00 becoming zero.
                    {
                        stringStack.push(CARDINAL0_19[10*tens+units]);  //!!  
                    }
                }
                
                
            }
            
            
        }
        else { // X20...X99

            if (forms == null) {
                if (units >= 1) {
                    stringStack.push(CARDINAL0_19[units]);
                }
            }
            else {
                if (units == 1) {
                    stringStack.push(forms[0]);
                    if (IsMasculine == true) {
                        stringStack.push(CARDINAL0_19[units]);
                    }
                    else {
                        stringStack.push(F_ONE);
                    }
                }
                else if (units == 2) {
                    stringStack.push(forms[1]);

                    if (IsMasculine == true) {
                        stringStack.push(CARDINAL0_19[units]);
                    }
                    else {
                        stringStack.push(F_TWO);
                    }

                }
                else if ((units == 3) || (units == 4)) {
                    stringStack.push(forms[1]);
                    stringStack.push(CARDINAL0_19[units]);
                }
                else {
                    stringStack.push(forms[2]);
                    if (units > 0) { //!!
                        stringStack.push(CARDINAL0_19[units]);
                    }
                }

            }

            // Tens
            stringStack.push(CARDINAL20_90[tens]);
        }

        if((hundreds >= 1) && (hundreds <= 9))
        {
            stringStack.push(CARDINAL100_900[hundreds]);
        }
       
        
    }
    
    /**
     * 
     * @param value
     * @return
     */
    public static final String Display(int value) {
        StringBuilder s = new StringBuilder("");
        String out = null;
        int th_count = 0;
        int group = 0;

        if (value == 0) {
            return CARDINAL0_19[0];
        }
        else if (value < 0) {
            return ERROR;
        }

        stringStack.clear();
        
        while (value > 0) {
            group = value % 1000;
            if (group > 0) {
                Digit3(group, MASC_FORM[th_count], FORMS[th_count]);
            }
            value /= 1000;
            th_count++;
        }

        while (stringStack.isEmpty() == false)
        {
            s.append(stringStack.pop());
            s.append(" ");
        }

       out = s.toString().trim();
        
        return out;
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
       
        Display(1000);

    }

}

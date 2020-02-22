import java.util.Random;
import java.util.Vector;


class WordPairList {
    
    private Vector<WordPair> list = new Vector<WordPair>(150);
    private int next = 0;
    private static Random rndSource = new Random();
    
    public WordPairList() {
        
    }

    
    public void add(final WordPair wp) {
        
        wp.setPosition(list.size());
        list.add(wp);
        
    }
    
    
    public WordPair get() {
        WordPair wp = null;
        
        if (list.isEmpty() == true) {
            return null;
        }
        /*System.out.println("Get 1");
        System.out.flush();*/
        wp = list.get(next);
        //wp = list.get(rndSource.nextInt(list.size()));
        
        next = (next + 1) % list.size(); 
        return wp;
    }
    
    public void clear() {
        list.clear();
        next = 0;
    }
    
    public void randomize() {
        int e = list.size();
        int s = e;
        int j;
        int b;
        e--;
        for(int i = 0; i < e; i++) {
            j = rndSource.nextInt(s);
            b = i+j;
            
            WordPair tmp = list.elementAt(i);
            WordPair tmp2 = list.elementAt(b);
            list.setElementAt(tmp2, i);
            list.setElementAt(tmp, b);
            s--;
            
        }
        
        
    }
    
    public void remove(final WordPair wp) {
        
        if (wp == null) {
            return;
        }
        
        int ind = wp.getPosition();
        
        int e = list.size();
        
        for(int i = 0; i < e; i++) {
            /*System.out.println("Get 2, " + (list.size()-1));
            System.out.flush();*/
            WordPair tmp = list.get(i);
            if(tmp.getPosition() == ind) {
                
                list.remove(i);
                if(i < next) {
                    next--;/*
                    System.out.println(next + ", " + (list.size()-1));
                    System.out.flush();
                    */
                }
                break;
            }
        }
        
        
    }
    
    
}

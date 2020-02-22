
class WordPair {

    private String word1;
    private String word2;
    private int list_position = -1;
    
    
    public WordPair() {
        word1 = "";
        word2 = "";
        list_position = -1;
    }
    
    public WordPair(final String w1, final String w2) { 
        setWords(w1, w2);
        list_position = -1;
    }
        
    public void setPosition(int pos) {
        list_position = pos;
    }
    public int getPosition() {
        return list_position;
    }
    
    public void setWords(final String w1, final String w2) {
        word1 = w1;
        word2 = w2;
    }
    
    public String getWord1() {
        return word1;
    }
    
    public String getWord2() {
        return word2;
    }

    
    /**
     * 
     */
    public String toString() {
       
        return word1 + ":" + word2;
    }
}

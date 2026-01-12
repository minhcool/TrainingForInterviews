class Solution {
public:
/*
store an iterator that represents the first position that we need to process during a line
- greedily add the words in
- calculate the number of total spaces -> we need at least one space between words
- create the final string
- note: in case of one word, pad the spaces to the right of the word
*/
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int itr1 = 0;
        vector<string> answer;
        while(itr1 < words.size()){
            int itr2 = itr1;
            int totalChars = words[itr1].length();
            while(itr2 < words.size()){
                itr2++;
                if(itr2 == words.size()){
                    itr2--;
                    break;
                }
                totalChars += words[itr2].length() + 1;
                if(totalChars > maxWidth){
                    totalChars -= words[itr2].length() + 1;
                    itr2--;
                    break;
                }
            }
            
            string curLine;
            int remChars = maxWidth - totalChars, numWords = (itr2 - itr1 + 1);
            remChars += (numWords - 1);
            if(numWords == 1){
                curLine += words[itr1];
                while(curLine.length() < maxWidth) curLine.push_back(' ');
            }
            else{
                // baseSpace: every separations has at least baseSpace chars, (additionalSpace) first separations will have an extra space
                int baseSpace = remChars / (numWords - 1), additionalSpace = remChars % (numWords - 1);
                if(itr2 == (words.size() - 1)){// last line
                    baseSpace = 1;
                    additionalSpace = 0;
                }
                curLine += words[itr1];
                for(int i = itr1 + 1; i <= itr2; i++){
                    for(int j = 0; j < baseSpace; j++) curLine += ' ';
                    if(additionalSpace > 0){
                        curLine += ' ';
                        additionalSpace--;
                    }
                    curLine += words[i];
                }
                while(curLine.length() < maxWidth) curLine.push_back(' ');
            }
            answer.push_back(curLine);
            itr1 = itr2 + 1;
        }
        return answer;
    }
};
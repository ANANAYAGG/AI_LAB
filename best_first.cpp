#include <bits/stdc++.h>
using namespace std;

class Graph 
{
    int n;
public:
    vector<vector<int>> matrix;    
    Graph() 
    {
        n = 28; // 26 letters + '.' + ' '
        matrix.resize(n, vector<int>(n, 0));
    }
    
    int getIndex(char ch) { // character to index
        if (ch == '.')
            return 26;
        else if (ch == ' ')
            return 27;
        else
            return ch - 'a';
    }
    
    char getChar(int i) {  // index to character
        if (0 <= i && i <= 25)
            return 'a' + i;
        else if (i == 26)
            return '.';
        else
            return ' ';
    }
    
    void buildGraph(string s) {
        int prev_idx = -1;
        for (char ch : s) {
            // Convert to lowercase if uppercase
            if ('A' <= ch && ch <= 'Z') 
            {
                ch = tolower(ch);
            }

            // Only process valid characters
            if (ch == '.' || ch == ' ' || ('a' <= ch && ch <= 'z')) 
            {
                int curr_idx = getIndex(ch);

                if (prev_idx != -1) 
                {
                    matrix[prev_idx][curr_idx]++;
                }

                prev_idx = curr_idx;
            }
        }
    }
    
    void showMatrix() 
    {
        float width = 3.7;  // Adjust width to better fit the matrix size
        cout << "Adjacency Matrix:\n";

        // Print column headers
        cout << "   ";  // Initial space for the row header
        for (int i = 0; i < n; i++) {
            cout << setw(width) << getChar(i);
        }
        cout << endl; // Move to the next line

        // Print each row of the matrix with the corresponding row header
        for (int i = 0; i < n; i++) {
            cout << getChar(i) << " "; // Print the row header
            for (int j = 0; j < n; j++) {
                cout << setw(width) << matrix[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
};

string bestFirstSearch(Graph &g, char startChar = 'e') 
{
    int n = g.matrix.size();
    priority_queue<pair<int, int>> pq;  
    vector<int> visited(n, 0);
    string output = "";
    
    if ('A' <= startChar && startChar <= 'Z') 
    {
        startChar = tolower(startChar);
    }
    
    if (!(startChar == ' ' || startChar == '.' || ('a' <= startChar && startChar <= 'z'))) 
    {
        cout << "INVALID STARTING CHARACTER.\n";
        return output;
    }
    
    int startIndex = g.getIndex(startChar);
    pq.push({0, startIndex}); 
    
    while (!pq.empty()) 
    {
        int vertex = pq.top().second;
        pq.pop();

        if (visited[vertex]) continue;

        visited[vertex] = 1;
        output += g.getChar(vertex);
        
        for (int i = 0; i < n; i++) 
        {
            if (!visited[i] && g.matrix[vertex][i] > 0) 
            {
                pq.push({g.matrix[vertex][i], i});
            }
        }
    }
    
    return output;
}

int main() 
{
    string text = "Everything was in confusion in the Oblonskys house.\n"
                  "The wife had discovered that the husband was carrying on an intrigue with a French\n"
                  "girl, who had been a governess in their family, and she had announced to\n"
                  "her husband that she could not go on living in the same house with him.\n"
                  "This position of affairs had now lasted three days, and not only the\n"
                  "husband and wife themselves, but all the members of their family and\n"
                  "household, were painfully conscious of it. Every person in the house\n"
                  "felt that there was no sense in their living together, and that the\n"
                  "stray people brought together by chance in any inn had more in common\n"
                  "with one another than they, the members of the family and household of\n"
                  "the Oblonskys. The wife did not leave her own room, the husband had not\n"
                  "been at home for three days. The children ran wild all over the house\n"
                  "the English governess quarreled with the housekeeper, and wrote to a\n"
                  "friend asking her to look out for a new situation for her the man-cook\n"
                  "had walked off the day before just at dinner time the kitchen-maid, and\n"
                  "the coachman had given warning.\n"
                  "Three days after the quarrel, Prince Stepan Arkadyevitch\n"
                  "Oblonsky--Stiva, as he was called in the fashionable world--woke up at\n"
                  "his usual hour, that is, at eight oclock in the morning, not in his\n"
                  "wife bedroom, but on the leather-covered sofa in his study. He turned\n"
                  "over his stout, well-cared-for person on the springy sofa, as though he\n"
                  "would sink into a long sleep again he vigorously embraced the pillow on\n"
                  "the other side and buried his face in it but all at once he jumped up,\n"
                  "sat up on the sofa, and opened his eyes.\n"
                  "Stepan Arkadyevitch eyes twinkled gaily, and he pondered with a smile.\n"
                  "There was a great deal more that was\n"
                  "delightful, only there no putting it into words, or even expressing it\n"
                  "in one thoughts awake. And noticing a gleam of light peeping in\n"
                  "beside one of the serge curtains, he cheerfully dropped his feet over\n"
                  "the edge of the sofa, and felt about with them for his slippers, a\n"
                  "present on his last birthday, worked for him by his wife on gold-colored\n"
                  "morocco. And, as he had done every day for the last nine years, he\n"
                  "stretched out his hand, without getting up, towards the place where his\n"
                  "dressing-gown always hung in his bedroom. And thereupon he suddenly\n"
                  "remembered that he was not sleeping in his wife room, but in his\n"
                  "study, and why: the smile vanished from his face, he knitted his brows.\n\n"
                  "Most unpleasant of all was the first minute when, on coming, happy and\n"
                  "good-humored, from the theater, with a huge pear in his hand for his\n"
                  "wife, he had not found his wife in the drawing-room, to his surprise had\n"
                  "not found her in the study either, and saw her at last in her bedroom\n"
                  "with the unlucky letter that revealed everything in her hand.\n\n"
                  "She, his Dolly, forever fussing and worrying over household details, and\n"
                  "limited in her ideas, as he considered, was sitting perfectly still with\n"
                  "the letter in her hand, looking at him with an expression of horror,\n"
                  "despair, and indignation.\n\n"
                  "And at this recollection, Stepan Arkadyevitch, as is so often the case,\n"
                  "was not so much annoyed at the fact itself as at the way in which he had\n"
                  "met his wife words.\n\n"
                  "There happened to him at that instant what does happen to people when\n"
                  "they are unexpectedly caught in something very disgraceful. He did not\n"
                  "succeed in adapting his face to the position in which he was placed\n"
                  "towards his wife by the discovery of his fault. Instead of being hurt,\n"
                  "denying, defending himself, begging forgiveness, instead of remaining\n"
                  "indifferent even--anything would have been better than what he did\n"
                  "do--his face utterly involuntarily (reflex spinal action, reflected\n"
                  "Stepan Arkadyevitch, who was fond of physiology)--utterly involuntarily\n"
                  "assumed its habitual, good-humored, and therefore idiotic smile.\n\n"
                  "This idiotic smile he could not forgive himself. Catching sight of that\n"
                  "smile, Dolly shuddered as though at physical pain, broke out with her\n"
                  "characteristic heat into a flood of cruel words, and rushed out of the\n"
                  "room. Since then she had refused to see her husband.";   

    Graph g;
    g.buildGraph(text);
    g.showMatrix();
    
    string result = bestFirstSearch(g); 
    cout << "\nResulting path:\n" << result << "\n";
    
    return 0;
}

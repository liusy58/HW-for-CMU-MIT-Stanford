#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

using std::cout;    using std::cin;
using std::endl;    using std::string;
using std::vector;  using std::ifstream;

// function prototypes
template <typename T>
void printVector(const vector<T>& v);

string fileToString(ifstream& inp);
double mag(const vector<int>& v);
int dotProduct(const vector<int>& v1, const vector<int>& v2);
int count_occurences(const string& text, const string& inpFeature);
double getSimilarity(const string& text1, const string& text2, const vector<string>& featureVec);
vector<string> createFeatureVec();
vector<int> createDocVec(const string& text, const vector<string>& featureVec);

int main() {
    // create vector of function words
    vector<string> featureVec = createFeatureVec();

    // get text of the files and store in strings,
    ifstream file1("madison.txt");
    ifstream file2("jj.txt");
    ifstream file3("hamilton.txt");
    ifstream file4("unknown.txt");

    string f_mad = fileToString(file1);
    string f_jj = fileToString(file2);
    string f_ham = fileToString(file3);
    string f_unk = fileToString(file4);

    // computeSimilarity
    cout << "Similarity - madison <-> unknown:    "  << getSimilarity(f_mad, f_unk, featureVec) << endl;
    cout << "Similarity - jj <-> unknown:         "  << getSimilarity(f_jj, f_unk, featureVec)  << endl;
    cout << "Similarity - hamilton <-> unknown:   "  << getSimilarity(f_ham, f_unk, featureVec) << endl;

    return 0;
}


vector<string> createFeatureVec() {
    return {"a", "about", "above", "after", "again", "against", "all",
            "am", "an", "and", "any", "are", "aren't", "as", "at", "be",
            "because", "been", "before", "being", "below", "between", "both",
            "but", "by", "can't", "cannot", "could", "couldn't", "did", "didn't",
            "do", "does", "doesn't", "doing", "don't", "down", "during", "each",
            "few", "for", "from", "further", "had", "hadn't", "has", "hasn't",
            "have", "haven't", "having", "he", "he'd", "he'll", "he's", "her",
            "here", "here's", "hers", "herself", "him", "himself", "his", "how",
            "how's", "i", "i'd", "i'll", "i'm", "i've", "if", "in", "into", "is",
            "isn't", "it", "it's", "its", "itself", "let's", "me", "more", "most",
            "mustn't", "my", "myself", "no", "nor", "not", "of", "off", "on", "once",
            "only", "or", "other", "ought", "our", "ours", "ourselves", "out", "over",
            "own", "same", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't",
            "so", "some", "such", "than", "that", "that's", "the", "their", "theirs", "them",
            "themselves", "then", "there", "there's", "these", "they", "they'd", "they'll", "they're",
            "they've", "this", "those", "through", "to", "too", "under", "until", "up", "very", "was",
            "wasn't", "we", "we'd", "we'll", "we're", "we've", "were", "weren't", "what", "what's", "when",
            "when's", "where", "where's", "which", "while", "who", "who's", "whom", "why", "why's", "with",
            "won't", "would", "wouldn't", "you", "you'd", "you'll", "you're", "you've", "your", "yours",
            "yourself", "yourselves", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".",
            "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_", "`", "{", "|", "}", "~"};
}


template <typename T>
void printVector(const vector<T>& v) {
    cout << "{";
    if(!v.empty()) {
        for(size_t i = 0; i < v.size()-1; ++i) {
            cout << v[i] << ", ";

        }
        cout << v[v.size()-1];
    }
    cout << "}" <<endl;
}


string fileToString(ifstream& inp) {
    string ret;
    string line;
    while(std::getline(inp, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        ret += line + " ";
    }
    return ret;
}


double getSimilarity(const string& text1, const string& text2,
                     const vector<string>& featureVec) {
    /* create doc vector for text 1 */
    vector<int> docVec1 = createDocVec(text1, featureVec);

    /* create doc vector for text 2 */
    vector<int> docVec2 = createDocVec(text2, featureVec);

    /* calculate dot product */
    int dot_prod = dotProduct(docVec1, docVec2);

    /*
     * Return similarity.
     *
     * One caveat; if one of the vectors in the zero vector,
     * we will end up dividing by 0. To avoid this we explicitly
     * check for this and if dot_prod == 0, we return 0. Otherwise
     * we return the normal answer.
     */
    return (dot_prod == 0) ?  0 : dot_prod/(mag(docVec1)*mag(docVec2));
}


double mag(const vector<int>& v) {
    return std::sqrt(dotProduct(v, v));
}


int dotProduct(const vector<int>& v1, const vector<int>& v2) {
    if(v1.size() != v2.size()) {
        cout << "Size mismatch" << endl;
        return -1;
    }
    /*
     * The inner_product algorithm calculates exactly what
     * we need; the dot product!
     */
    return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
}


vector<int> createDocVec(const string& text,
                         const vector<string>& featureVec) {
    /*
     * For each feature in the featureVec, we get
     * the number of times it occurs in text and append
     * that to our return vector.
     *
     * Note: This is not the most efficient way to do
     * this but this approach will be more helpful for
     * assignment 2.It is also not egregiously slower and
     * will run almost instantly for most texts.
     */
    vector<int> result;
    for(const auto& feature : featureVec) {
        result.push_back(count_occurences(text, feature));
    }
    return result;
}


int count_occurences(const string& text, const string& inpFeature) {
    /*
     * We pad each feature with spaces on either side
     * so it doesn't count an occurenct of, say, "as"
     * in the word "master".
     *
     * This does disregard a few tokens e.g. those ending
     * with punctuation etc. The best way to refine this would
     * be to look at the <regex> library!
     */
    string feature = " " + inpFeature + " ";
    /*
     * Here, start and end denote the ranges of the text input that we
     * should search for the feature within.
     */
    auto start = text.begin();
    auto end = text.end();

    int counter = 0;
    while(start != end) {
        /* Find occurence of feature in the range [start, end).
         *
         * The std::search algorithm looks for the sequence denoted
         * by [feature.begin(), feature.end()) and returns an
         * iterator to the position where the sequence was found in the
         * text from [start, end).
         *
         * If the sequence isn't found, the algorithm returns the end iterator.
         *
         */
        auto curr = std::search(start, end, feature.begin(), feature.end());

        /* If no sequence of feature found in the search range,
         * there is nothing left to do.
         */
        if(curr == end) break;

        /*
         * Else increment count and set start to one past the position where
         * the feature subsequence was found. This is so that in the next time in the loop,
         * the algorithm will looks for a different instance of the feature sequence.
         */
        ++counter;
        start = curr + 1;
        // else increment count
    }

    return counter;
}

#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include "csvstream.hpp"
#include <cmath>
using namespace std;


class Classifier {
private:
    int total;
    int vocab;
    set<string> words;
    set<string> labels;
    map<string, int> wordNum;
    map<string, int> labelNum;
    map<pair<string, string>, int> lw;
    csvstream csvin;
    set<string> current;
    bool d;

    void unique_words(const string &str) {
        istringstream source(str);
        currentword(str);
        for (auto& a:current) {
            if (words.find(a) == words.end()) {
                words.insert(a);
            }
            wordNum[a];
            ++wordNum[a];
        }
    }

    void words_label (string l, const string &str) {
        istringstream source(str);
        string word;
        set<string> a;
        while (source >> word) {
            if (a.find(word) == a.end()) {
                a.insert(word);
            }
        }
        for (auto& s: a) {
            pair<string, string> current (l, s);
            lw[current];
            ++lw[current];
        }
    }

public:

    Classifier (string filename, bool de): csvin(filename, ',', true), d(de){};
    
    void train() {
        map<string, string> row;
        csvin >> row;
        total = 1;
        labels.insert(row["tag"]);
        labelNum[row["tag"]];
        ++labelNum[row["tag"]];
        unique_words(row["content"]);
        words_label(row["tag"], row["content"]);
        if (d) {
            cout << "training data:"<<endl;
            cout << "  label = " << row["tag"] 
            << ", content = " << row["content"] << endl;
        }
        while (csvin >> row) {
            if (d) {
            cout << "  label = " << row["tag"] 
            << ", content = " << row["content"] << endl;
            }
            if (labels.find(row["tag"]) == labels.end()) {
                labels.insert(row["tag"]);
                labelNum[row["tag"]];
                ++labelNum[row["tag"]];
            } else {
                ++labelNum[row["tag"]];
            }
            unique_words(row["content"]);
            words_label(row["tag"], row["content"]);
            total++;
        }
        vocab = words.size();
        cout << "trained on " << int(total) << " examples" << endl;

        if (d) {
            cout << "vocabulary size = " << vocab << endl;
        }
        cout << "" << endl;
        if (d) {
            cout << "classes:" << endl;
            for (auto& str: labels) {
                cout<<"  "<<str<<", "<<labelNum[str]<< " examples, log-prior = "
                <<log(labelNum[str]/static_cast<double>(total))<<endl;
            }
            cout<<"classifier parameters:"<<endl;
            for (auto& str: labels) {
                for (auto& w:words) {
                    pair<string, string> p(str,w);
                    if (lw.find(p) != lw.end()) {
                        cout << "  "<<str<<":"<<w<<", count = "<<lw[p]
                        <<", log-likelihood = "<<log_likelihood(p)<<endl;
                    }
                }
            }
            cout<<""<<endl;
        }
        int sum = 0;
        int sum2 = 0;
        for (auto& a : labels) {
            sum = sum + labelNum[a];
        }
        for (auto& a : words) {
            sum2 = sum2 + wordNum[a];
        }
    }

    string predict(const string &str) {
        currentword(str);
        string result = *labels.begin();
        double score = 0;
        double highest = get_score(*labels.begin());
        for (auto& str: labels) {
            score = get_score(str);
            if (score > highest || (score == highest && str < result)) {
                highest = score;
                result = str;
            }
        }
        cout<<", predicted = "<<result<<", log-probability score = "<< highest<<endl;
        cout<<"  content = "<<str<<endl;
        cout<<""<<endl;

        return result;
    }

    void currentword(const string &str) {
        istringstream source(str);
        string word;
        current.clear();
        while (source >> word) {
            if (current.find(word) == current.end()) {
                current.insert(word);
            }
        }
    }

    double get_score(string n) {
        double s = log(labelNum[n]/1.0/total);
        for (const auto&str: current) {
            pair<string, string> c(n, str);
            s = s + log_likelihood(c);
        }
        return s;
    }

    double log_likelihood(pair<string, string> p) {
            if (words.find(p.second) == words.end()) {
                return log(1.0/(total));
            } else if (lw.find(p) == lw.end()){
                return log(wordNum[p.second]/1.0/total);
            } else {
                return log(lw[p]/1.0/labelNum[p.first]);
            }
    }


    


};


int main(int argc, char*argv[]) {
    cout.precision(3);
    if (argc == 3 || (argc == 4 && string(argv[3]) == "--debug")) {
        
    } else {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    ifstream file;
    file.open(argv[1]);
    if(!file.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return 2;    
    }

    ifstream test;
    test.open(argv[2]);
    if(!test.is_open()) {
        cout << "Error opening file: " << argv[2] << endl;
        return 2;    
    }
    bool debug = (argc == 4 && string(argv[3]) == "--debug");
    Classifier classifier(argv[1], debug);  
    classifier.train();
    csvstream testin(argv[2]);
    map<string, string> row;
    int predict = 0;
    int total = 0;
    cout<< "test data:"<<endl;
    while (testin >> row) {
        total++;
        string tlabel = row["tag"];
        cout << "  correct = "<< tlabel;
        string label = classifier.predict(row["content"]);
        if (tlabel == label){
            predict++;
        }
    }
    cout << "performance: " << predict << " / " 
    << total << " posts predicted correctly"<<endl;
    return 0;
}

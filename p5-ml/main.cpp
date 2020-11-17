#include "Map.h"
#include "csvstream.h"
#include <map>
#include <set>
using namespace std;

set<string> unique_words(const string &str){
    istringstream source(str);
    set<string> words;
    string word;
    while(source>>word){
        words.insert(word);
    }
    return words;
}

set<string> unique_words_v2(const string &str){
    istringstream source{str};
    return {istream_iterator<string>{source},istream_iterator<string>{}};
}
int main(int argc,char *argv[] ){

    if (!((argc==3) |(argc==4))){
        cout<<" Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<<endl;
        return 1;
    }

    if (argc==4){
        if (strcmp(argv[3],"--debug")!=0){
        cout<<" Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"<<endl;
            return 1;
        }
    }

    string train_csv = argv[1];
    string test_csv  = argv[2];

    csvstream csvin(train_csv);
    csvstream testcsvin(test_csv);

    if (!csvin){
        cout<<"Error opening file: "<<train_csv<<endl;
    }

    if (!testcsvin){
        cout<<"Error opening file: "<<test_csv<<endl;
    }
    cout.precision(3);

//vector<pair<string, string>> row;
    
    map<string,string> row;
    set<string> BagOfWords,uni_BOW;
    set<string> Tag,uni_Tag;
    int num_post = 0;
    map<string,int>  w_num_post;
    map<string,int>  c_num_post;
    map<pair<string,string>,int> cw_num_post;
    if (argc>=4){
        cout<<"training data:"<<endl;
    }
    while(csvin >>row){
        if (argc>=4){
            cout<<"  "<<"label = "<<row["tag"]<<", content = "<<row["content"]<<endl;
        }
        uni_Tag = unique_words(row["tag"]);
        c_num_post[row["tag"]]++;
        Tag.insert( uni_Tag.begin(), uni_Tag.end());
        uni_BOW = unique_words(row["content"]);
        for (auto &word:uni_BOW){
            w_num_post[word]++;
            cw_num_post[make_pair(row["tag"],word)]++;
        }
        BagOfWords.insert( uni_BOW.begin(),uni_BOW.end());
        num_post+=1;
    }
    int unique_vocab = BagOfWords.size();
    cout<<"trained on "<<num_post<<" examples"<<endl;
    if (argc>=4){
        cout<<"vocabulary size = "<<unique_vocab<<endl;
    }
    cout<<endl;
    if (argc>=4){
        cout<<"classes:"<<endl;
        for (auto & label:Tag){
            cout<<"  "<<label<<", "<<c_num_post[label]<<" examples, log-prior = "<< log((float) c_num_post[label]/num_post)<<endl;
        }
    }

    if (argc>=4){
        cout<<"classifier parameters:"<<endl;
        for (auto & pair: cw_num_post){
            cout<<"  "<<pair.first.first<<":"<<pair.first.second<<", count = "<<pair.second<<", log-likelihood = "<<log( (float) pair.second/c_num_post[pair.first.first]) <<endl;
        }
        cout<<endl;
    }

    vector<string> true_tag,pred_tag;
    vector<float> mle;
    float tmp = 0;
    string uni_pred_tag ;
    int correct_num = 0;
    cout<<"test data:"<<endl;

    while(testcsvin>>row){
        mle.clear();
        true_tag.push_back(row["tag"]);
        uni_BOW = unique_words(row["content"]);
        for (auto &label: Tag){
            tmp= log((float) c_num_post[label]/num_post);
            for (auto & word:uni_BOW){
                if (BagOfWords.find(word)==BagOfWords.end()){
                    tmp+=log((float) 1/num_post);
                }
                else if (cw_num_post[make_pair(label,word)]>0){
                    tmp+=log( (float) cw_num_post[make_pair(label,word)]/c_num_post[label]);
                }
                else{
                    tmp+=log((float) w_num_post[word]/num_post);
                }
            }
            if (mle.size()==0){
                uni_pred_tag = label;
            }
            else if (tmp>*max_element(mle.begin(),mle.end())){
                uni_pred_tag = label;
            }
            mle.push_back(tmp);
        }
        pred_tag.push_back(uni_pred_tag);
        cout<<"  correct = "<<row["tag"]<<", predicted = "<<uni_pred_tag<<", log-probability score = "<<*max_element(mle.begin(),mle.end())<<endl;
//        for (auto &iter : mle){
//            cout<<iter<<endl;
//        }
        cout<<"  content = "<<row["content"]<<endl<<endl;
        if (row["tag"].compare(uni_pred_tag)==0) {
            correct_num++;
        }
    }
    cout<<"performance: "<<correct_num<<" / "<<true_tag.size()<<" posts predicted correctly"<<"\n";
    
}

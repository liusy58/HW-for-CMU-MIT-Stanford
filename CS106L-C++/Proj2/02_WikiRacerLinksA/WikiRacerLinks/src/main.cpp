#include <iostream>
#include <fstream>
#include <unordered_set>
#include<vector>
#include<sstream>
using std::cout;            using std::endl;
using std::string;          using std::unordered_set;


string prefixx="/Users/liusiyu/Downloads/winter/HW-for-CMU-MIT-Stanford/CS106L-C++/Proj2/02_WikiRacerLinksA/WikiRacerLinks/res/";

string READFILE(string filename)
{
    string FILE=prefixx+filename;
    std::ifstream outfile;
    std::ostringstream buffer;
    outfile.open(FILE);
    char word;
    while(outfile.get(word))
    {
        buffer.put(word);
    }
    return buffer.str();
}

void findWikiLinks(const string& page_html,string filename)
{
    string FILE=prefixx+"out_"+filename;
    unordered_set<string>res;
    std::ofstream outfile(FILE);
    string target = "href=";
    auto iterator=std::search(page_html.begin(),page_html.end(),target.begin(),target.end());
    while(iterator!=page_html.end())
    {
        iterator+=6;
        string templink="";
        while(*iterator!='"')
            templink+=*iterator++;
        cout<<templink<<endl;
        if(templink.substr(0,6)=="/wiki/"&&std::all_of(templink.begin(),templink.end(),[](char ch){ return ch!='#'&& ch!=':'&&ch!='.';}))
        {
            cout<<templink<<endl;
            res.insert(templink.substr(6));
        }

        iterator = std::search(iterator,page_html.end(),target.begin(),target.end());
    }

     for(auto str:res)
         outfile<<str<<endl;
     outfile.close();
}

int main() {
	
    /* TODO: Write code here! */

    /* Note if your file reading isn't working, please follow the
     * steps posted on the front page of the CS106L website. Essentially
     * go to the projects tab on the panel on the left, and in the run
     * section, uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */
    std::vector<std::string>filenames={"simple.txt","quokka.txt","sking.txt"};

    for(auto filename:filenames)
    {
        cout<<filename<<endl;
        string page_html=READFILE(filename);
        findWikiLinks(page_html,filename);

    }


}

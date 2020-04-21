
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>
#include "wikiscraper.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;




/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */



vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: Fill in the findWikiLinks method in wikiscraper.cpp,
    //       then write this  function as per the handout.
    //
    //                Best of luck!

    WikiScraper scraper;
    vector<string> res;
    std::set<string> visited;
    auto target_set=scraper.getLinkSet(end_page);
    auto cmpFn = [&](const vector<string>&ladder1,const vector<string>&ladder2){
           string page1=ladder1.back();
           string page2=ladder2.back();

           auto link1=scraper.getLinkSet(page1);
           auto link2=scraper.getLinkSet(page2);
           vector<string>v_inter1,v_inter2;
           std::set_intersection(link1.begin(),link1.end(),target_set.begin(),
                                             target_set.end(),std::back_inserter(v_inter1));
           std::set_intersection(link2.begin(),link2.end(),target_set.begin(),
                                             target_set.end(),std::back_inserter(v_inter2));

           return v_inter1.size()<v_inter2.size();

    };
    std::priority_queue<vector<string>, vector<vector<string>>, decltype(cmpFn)> ladderQueue(cmpFn);
    ladderQueue.push({start_page});

    while(!ladderQueue.empty())
    {
        auto now=ladderQueue.top();
        ladderQueue.pop();

        auto now_page_set=scraper.getLinkSet(now.back());
        if(now_page_set.count(end_page))
        {
                now.push_back(end_page);
                return now;
        }
        for(auto neighbor:now_page_set){
         if(visited.count(neighbor))
             continue;
         visited.insert(neighbor);
         now.push_back(neighbor);
         ladderQueue.push(now);
         now.pop_back();
    }
    }
    return res;
}



int main() {
    auto ladder = findWikiLadder("Fruit", "Strawberry");
    cout << endl;

    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;
        cout << "\t";

        // Print the ladder here!
    }

    return 0;
}





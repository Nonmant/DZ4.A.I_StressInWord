//https://contest.yandex.ru/contest/27665/problems/I/

#include "funcs.h"
#include <bits/stdc++.h>

std::set<unsigned int> extractStresses(std::string & word){
    std::set<unsigned int> stresses;
    for(int j = 0; j < word.size(); ++j){
        if(isupper(word[j])){
            stresses.insert(j);
            word[j] = tolower(word[j]);
        }
    }
    return stresses;
}

void parseFile(std::istream & input, std::ostream & output){

    //! @brief word - stress letters indexes
    std::map<std::string, std::set<unsigned int>> dict;

    unsigned int N;
    input >> N;
    std::string word;
    for(int i = 0; i < N; ++i){
        input >> word;
        auto stresses = extractStresses(word);
        dict[word].insert(stresses.begin(), stresses.end());
    }

    std::list<std::string> sequence;
    std::copy(std::istream_iterator<std::string>(input),
              std::istream_iterator<std::string>(),
              std::back_inserter(sequence));

    unsigned int errors = 0;
    for(auto & w : sequence){
        auto stresses = extractStresses(w);
        if(stresses.empty()){++errors; continue;}
        if(dict.count(w)){
            std::vector<int> intersection;
            std::set_intersection(dict[w].begin(), dict[w].end(),
                                  stresses.begin(), stresses.end(),
                                  std::back_inserter(intersection));
            if(intersection.size() != stresses.size())
                ++errors;
        } else {
            if(stresses.size() != 1)
                ++errors;
        }
    }

    output << errors;
}

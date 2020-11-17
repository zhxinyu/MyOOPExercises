//
//  stats.cpp
//  p1-stats
//
//  Created by Xinyu Zhang on 6/29/19.
//  Copyright © 2019 Xinyu Zhang. All rights reserved.
//

#include <stdio.h>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<double> > summarize(vector<double> v){
    assert(v.size()>=1);
    sort(v.begin(),v.end());
    vector<double> data;
    vector<vector<double>> output;
    int count = 1;
    for (auto i =v.cbegin();i!=v.cend();i++){
        //if ( (i==v.cbegin()) | (*(i-1)!= *(i)) ){
        data.push_back(*i);
        while((i+1!=v.cend())&(*(i+1)==*(i)) ){
            count++;
            i++;
        }
        data.push_back(count);
        output.push_back(data);
        data.clear();
        count = 1;
        //}
    }
    return output;
    //assert(false);
}

int count(vector<double> v){
    assert(v.size()>=1);
    return static_cast<int>(v.size());
//assert(false);
}

double sum(vector<double> v){
    assert(v.size()>=1);
    double output = 0;
    for(auto i=v.cbegin(); i!=v.cend(); ++i){
        output+=*i;}
    return output;
//assert(false);
}

double mean(vector<double> v ){
    assert(v.size()>=1);
    return sum(v)/v.size();
//assert(false);
}

double median(vector<double> v){
    assert(v.size()>=1);
    sort(v.begin(),v.end());
    if (v.size() % 2==0)
        return *(v.begin()+v.size()/2-1)/2+*(v.begin()+v.size()/2)/2;
    else
        return *(v.begin()+(v.size()-1)/2);
    //assert(false);
}

double mode(vector<double> v){
    assert(v.size()>=1);
    int frequency = 0;
    double output;
    vector<vector<double>> data = summarize(v);
    for (auto i : data){
        if (frequency<*(i.end()-1)){
            output = *(i.begin());
            frequency =*(i.end()-1);
        }
    }
    return output;
}

double min(vector<double> v){
    assert(v.size()>=1);
    sort(v.begin(),v.end());
    return *v.cbegin();
    //assert(false);
}

double max(vector<double> v){
    assert(v.size()>=1);
    sort(v.begin(),v.end());
    return *(v.begin()+v.size()-1);
    //assert(false);
}

double stdev(vector<double> v){
    assert(v.size()>=1);
    if (v.size()==1) return 0;
    double avg_v = mean(v);
    double output = 0;
    for (auto i=v.cbegin();i!=v.cend();i++){
        output+=pow(*i-avg_v,2);
    }
    return sqrt(output/(v.size()-1));
    //assert(false);
}

double percentile(vector<double> v,double p ){
    assert((v.size()>=1)& (p>=0) & (p<=1));
    sort(v.begin(),v.end());
    double n  = p*(v.size()-1)+1;
    double fractpart = 0;
    double intpart = 0;
    fractpart = modf(n,&intpart);
    return *(v.begin()+intpart-1)+fractpart*(*(v.begin()+intpart)-*(v.begin()+intpart-1));
    //    assert(false);
}


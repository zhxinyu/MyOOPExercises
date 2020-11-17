//
//  main.cpp
//  p1-stats
//
//  Created by Xinyu Zhang on 6/29/19.
//  Copyright © 2019 Xinyu Zhang. All rights reserved.
//

#include <stdio.h>
#include "p1_library.h"
#include <iostream>
#include "stats.h"
using namespace std;

int main() {
    cout << "hello from main!\n";
    string filename,column_name;
    cout << "enter a filename"<<endl;
    cin >>filename;
    cout <<"enter a column name"<<endl;
    cin >> column_name;
    cout<< "reading column "<<column_name<<" from "<<filename<<endl;
    vector<double> raw_data =  extract_column( filename, column_name);
    vector<vector<double>> summarize_data = summarize(raw_data);
    cout<<"Summary (values: frequency)"<<endl;
    for (auto i : summarize_data){
        cout<<*(i.cbegin())<<": "<<*(i.begin()+1)<<endl;
    }
    cout<<"count = "<<count(raw_data)<<endl;
    cout<<"sum = "<<sum(raw_data)<<endl;
    cout<<"mean = "<<mean(raw_data)<<endl;
    cout<<"stdev = "<<stdev(raw_data)<<endl;
    cout<<"median = "<<median(raw_data)<<endl;
    cout<<"mode = "<<mode(raw_data)<<endl;
    cout<<"min = "<<min(raw_data)<<endl;
    cout<<"max = "<<max(raw_data)<<endl;
    cout<<" 0th percentile = "<<percentile(raw_data, 0)<<endl;
    cout<<" 25th percentile = "<<percentile(raw_data, 0.25)<<endl;
    cout<<" 50h percentile = "<<percentile(raw_data, 0.5)<<endl;
    cout<<" 75th percentile = "<<percentile(raw_data, 0.75)<<endl;
    cout<<" 100th percentile = "<<percentile(raw_data, 1)<<endl;
}

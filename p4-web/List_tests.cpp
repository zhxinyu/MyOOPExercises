// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
    List<int> my_list;
    
    
    assert(my_list.empty());
    my_list.push_front(1);
    my_list.push_front(2);
    my_list.push_front(3);
    my_list.push_front(3);
    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(3);

    assert(my_list.size()==8);
    assert(my_list.front()==3);
    my_list.front()=4;
    assert(my_list.front()==4);
    assert(my_list.back()==3);
    my_list.back()=4;
    assert(my_list.front()==4);
    my_list.pop_front();
    my_list.pop_back();
    assert(my_list.size()==6);
    my_list.push_front(4);
    my_list.push_back(4);
    List<int> my_list2(my_list);
    my_list.front()=5;

    std::cout<<"Here!"<<std::endl;
    List<int> my_list3 = my_list2;
    assert(my_list3.front()==4);
    List<int> my_list4;
    my_list4=my_list2;
    
    my_list.pop_front();
    my_list.push_front(4);
    List<int>::Iterator iter = my_list.begin();
    List<int>::Iterator iter2(++my_list.begin());
    List<int>::Iterator iter3(my_list.end());
    
    assert(iter!=iter2);
    assert(--iter2==iter);
    for (List<int>::Iterator iter4=iter;iter4!=iter3;++iter4){
        std::cout<<*(iter4)<<std::endl;
    }
    for (List<int>::Iterator iter4=my_list.begin();iter4!=my_list.end();++iter4){
        std::cout<<*(iter4)<<std::endl;
    }
    my_list.erase(my_list.begin());
    my_list.insert(my_list.begin(),4);
    
    while(!my_list.empty()){
        my_list.pop_front();

    }
    assert(my_list.size()==0);
//    assert(false);

}

TEST_MAIN()

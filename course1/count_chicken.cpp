//count_chicken.cpp
#include <iostream>
using namespace std;
int main(void)
{
    int chicken,hen,cock;
    cout<<"chicken hen cock"<<endl;
    for(chicken=0; chicken<100; chicken+=3)
        for(hen=0; hen<=33; hen++)
            if((cock=100-chicken-hen)> -1)
                if(chicken/3+hen* 3+cock* 5==100)
                    cout<<" "<<chicken<<" "<<hen<<" "<<cock<<endl;
    return 0;
}


#include <iostream>

using namespace std;

#define P1_Vertices 100
#define P2_Vertices 100
#define P1_edges 7

void problem1()
{
    cout << P1_Vertices << ' ' << (P1_Vertices * (P1_Vertices - 1))/2 << endl;
    for (int i = 1; i <= P2_Vertices; i++)
    {
        for (int j = i + 1; j <= P2_Vertices; j++)
        {
            if (i != j)
            {   
                cout << i << ' '  << j  << ' ';
                if (j%10 == 0)
                {
                    cout << 15 << ' '<< 10 << endl;
                }else{
                    cout << 10*(j%10) << ' ' <<  (((2*j)%15) + 5) << endl;
                }
            }
        }
    }
    cout << endl; 
    int request_id{1};
    int source{1};
    for (int i = 10; i < 95000; i++)
    {
        cout << "insert" << ' ' << request_id++ << ' ';
        if (i%100 != 0)
        {
            source = i%100;
        }
        else{
            source = 100;
        }
        cout << source <<  ' ' << "{ ";
        for (int j = 1; j <= P1_Vertices; j++)
        {

            cout <<  j << ' ';
            
        }
        cout << "} " << "10" << endl; 
        if (i % 1000 == 0)
        {
            cout << "rearrange" << endl;
        }
    }



    return;

}


void problem2()
{
    cout << P2_Vertices << ' ' << (P2_Vertices * (P2_Vertices - 1))/2 << endl;
    for (int i = 10; i <= P2_Vertices; i++)
    {
        for (int j = i + 1; j <= P2_Vertices; j++)
        {
            if (i != j)
            {   
                cout << i << ' '  << j  << ' ';
                if (j%10 == 0)
                {
                    cout << 15 << ' '<< 10 << endl;
                }else{
                    cout << 10*(j%10) << ' ' <<  (((2*j)%15) + 5) << endl;
                }
            }
        }
    }

    cout << endl; 
    int request_id{1};
    int source{1};
    for (int i = 10; i < 95000; i++)
    {
        cout << "insert" << ' ' << request_id++ << ' ';
        if (P2_Vertices%i != 0)
        {
            source = P2_Vertices%i;
        }
        else{
            source = P2_Vertices/2;
        }
        cout << source <<  ' ' << "{ " << source << ' ';
        for (int j = 1; j <= j%P2_Vertices; j++)
        {
            if((source + j) % (P2_Vertices + 1) > 0)
            {
            cout << (source + j) % (P2_Vertices + 1) << ' ';
            }
        }
        cout << "} " << "10" << endl; 
        if (i % 1000 == 0)
        {
            cout << "rearrange" << endl;
        }
    }

}

int main()
{
    problem1();
    //problem2();
    return 0;
}
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int Test, cakes, children, k, S, E;

    scanf("%d",&Test);

    while(Test--)
    {
        scanf("%d %d %d",&cakes,&children,&k);

        vector<pair<int,int>> vectorPair;

        for(int i = 0; i < children; i++)
        {
            scanf("%d %d",&S,&E);
            vectorPair.push_back({S,E});
        }

        vectorPair.push_back({0,0});
        vectorPair.push_back({cakes+1,cakes+1});

        sort(vectorPair.begin(),vectorPair.end());

        if(k == 0)
        {
            int cnt=0;
            for(int i = 0; i < vectorPair.size()-1; i++)
            {
                for(int j = i+1; j < vectorPair.size(); i++)
                {
                    if(vectorPair[i].second < vectorPair[j].first)
                        break;
                    else
                        cnt++;
                }
            }

            if(cnt)
                printf("Bad\n");
            else
                printf("Good\n");
        }
        
        else
        {
            int check = 0;

            for(int i=0; i+1 < vectorPair.size(); i++)
            {
                if(vectorPair[i].second >= vectorPair[i+1].first)
                {
                    check = 1;

                    bool condition = false;

                    pair<int,int> p = {vectorPair[i].first, vectorPair[i].second};

                    int length = vectorPair[i].second-vectorPair[i].first;

                    vectorPair.erase(vectorPair.begin()+i);

                    for(int j = 0; j+1 < vectorPair.size(); j++)
                    {
                        if(vectorPair[j+1].first - vectorPair[j].second - 2 >= length)
                            condition=true;
                        else if(vectorPair[j+1].first <= vectorPair[j].second)
                        {
                            condition = false;
                            break;
                        }
                    }

                    if(condition)
                        printf("Good\n");
                    else
                        printf("Bad\n");

                    break;
                }
            }
            if(check == 0)
                printf("Good\n");
        }
    }
    return 0;
}
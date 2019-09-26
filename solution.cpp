/* Code by
               __            __                       __         
              /\ \__        /\ \                     /\ \        
   __     _ __\ \ ,_\       \ \ \___      __      ___\ \ \/'\    
 /'__`\  /\`'__\ \ \/        \ \  _ `\  /'__`\   /'___\ \ , <    
/\ \L\.\_\ \ \/ \ \ \_        \ \ \ \ \/\ \L\.\_/\ \__/\ \ \`\  
\ \__/.\_\ \_\  \ \__\        \ \_\ \_\ \__/.\_\ \____\ \_\ \_\
 \/__/\/_/ \/_/   \/__/  _______\/_/\/_/\/__/\/_/\/____/ \/_/\/_/
                        /\______\                                
                        \/______/                                
*/

#include "bits/stdc++.h"
using namespace std;
#define max(a, b) (a < b? b : a)
#define min(a, b) ((a>b)?b:a)
#define mod 1e9+7
#define FOR(a,c)   for ( int (a)=0; (a)<(c); (a)++)
#define FORL(a,b,c)  for ( int (a)=(b); (a)<=(c); (a)++)
#define FORR(a,b,c)  for (  int (a)=(b); (a)>=(c); (a)--)
#define INF 1000000000000000003
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
#define F first
#define S second
#define PB push_back
#define POB pop_back
#define MP make_pair

int N;

// Fitness Checking by checking number of conflicts
long long int fitness_value(vector<int> v){
    map <int,int> diag1,diag2;
    map <int,int>::iterator it;
    FORL(i,1,v.size()){
        // cout<<"Diag1 "<<i<<" "<<v[i-1]<<" "<<i-v[i-1]<<endl;
        diag1[i-v[i-1]]++;
        // cout<<"Diag2 "<<i<<" "<<v[i-1]<<" "<<i+v[i-1]<<endl;
        diag2[i+v[i-1]]++;
    }

    ll conflicts = 0;

    for(it=diag1.begin();it!=diag1.end();it++){
        if(it->second>1){
            conflicts+=((it->second*(it->second-1))/2);
        }
    }
    for(it=diag2.begin();it!=diag2.end();it++){
        if(it->second>1){
            conflicts+=((it->second*(it->second-1))/2);
        }
    }

    return conflicts;

}

// Crossover using Single Point Crossover
pair<vector<int>,vector<int>> crossover(vector<int> a, vector<int> b){
    // FOR(j,N)
    //     cout<<a[j]<<" ";
    // cout<<endl;
    // FOR(j,N)
    //     cout<<b[j]<<" ";
    // cout<<endl;

    ll pointt = rand()%(a.size());
    // cout<<"Point: "<<pointt<<endl;
    ll point = pointt;
    vector<int> p;
    FOR(i,point)
        p.PB(a[i]);
    while(p.size()!=a.size()){

        ll val = b[point],boola=1;

        FOR(i,p.size()){
            if(p[i]==val){
                boola =0;
                break;
            }
        }
        if(boola)
            p.PB(val);
        point = (point+1)%(a.size());
    }
    point=pointt;

    vector<int> q;
    FOR(i,point)
        q.PB(b[i]);
    while(q.size()!=b.size()){

        ll val = a[point],boola=1;

        FOR(i,q.size()){
            if(q[i]==val){
                boola =0;
                break;
            }
        }
        if(boola)
            q.PB(val);
        point = (point+1)%(a.size());
    }

    // cout<<"After Crossing"<<endl;
    // FOR(j,p.size())
    //     cout<<p[j]<<" ";
    // cout<<endl;
    // FOR(j,q.size())
    //     cout<<q[j]<<" ";
    // cout<<endl;

    return MP(p,q);
}


bool fitness_compare(vector<int> a, vector<int> b){
    return fitness_value(a)<fitness_value(b);
}


int main() {

cout<<"Enter Number of Queens: ";
cin>>N;

vector<vector<int>> v;
srand(time(0));

// vector<int> test{4,2,5,2,6,3};
// cout<<fitness_value(test)<<endl;

FOR(i,2*N){
    vector<int> p;
    FORL(j,1,N)
        p.PB(j);
    random_shuffle(p.begin(),p.end());
    v.PB(p);

    // FOR(j,N)
    //     cout<<p[j]<<" ";
    // cout<<endl;
    // cout<<"Fitness Value: "<<fitness_value(p)<<endl;
}


sort(v.begin(),v.end(),fitness_compare);
ll generation = 1;
while(fitness_value(v[0])>0){

    cout<<"Generation Number: "<<generation++<<" with fitness Value of "<<fitness_value(v[0])<<endl;

    FOR(i,N){
        // Crossover
        ll firstt = rand()%(2*N),secondd=rand()%(2*N);
        pair<vector<int>,vector<int>> crossed = crossover(v[firstt],v[secondd]);

        //Mutate the Crossed over Chromosomes using 2 swap Mutation
        if((rand()%100) <50){
            firstt = rand()%(N);
            secondd=rand()%(N);
            swap(crossed.F[firstt],crossed.F[secondd]);
            firstt = rand()%(N);
            secondd=rand()%(N);
            swap(crossed.F[firstt],crossed.F[secondd]);
        }

        if((rand()%100) <50){
            firstt = rand()%(N);
            secondd=rand()%(N);
            swap(crossed.S[firstt],crossed.S[secondd]);
            firstt = rand()%(N);
            secondd=rand()%(N);
            swap(crossed.S[firstt],crossed.S[secondd]);
        }
        v.PB(crossed.F);
        v.PB(crossed.S);
    }
    sort(v.begin(),v.end(),fitness_compare);

    // Making Population Back to 2*N
    while(v.size()>(2*N))
        v.POB();
}


// FOR(i,N){
//     cout<<v[0][i]<<" ";
// }
// cout<<endl;

cout<<"Found Solution in Generation "<<generation<<endl;
FOR(i,N)
  cout<<v[i]<<endl;
cout<<endl;
FOR(i,N){
    FOR(j,N){
        if(v[0][i]==(j+1))
            cout<<"#";
        else
            cout<<"_";
    }
    cout<<endl;
}

return 0;
}

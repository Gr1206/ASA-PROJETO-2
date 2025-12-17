#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;


bool hasDL(const vector<unordered_set<int>> &mapa, int j, int a){
    return mapa[j].find(a) != mapa[j].end();
}
int calcCusto(int M, int paths){
    return 1+paths%M;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
     
    int N;
    int M;
    int m1, m2; 
    int K;
    cin >> N; 
    cin >> M; 
    cin >> m1 >> m2; 
    cin >> K; 
    

    vector<vector<pair<int, int>>> camioes(M+1);

    vector<vector<int>> mapa(N+1); 
    vector<unordered_set<int>> mapings(N+1);

    vector<int> inDeg(N+1, 0); //in degree de todos os nós 
    vector<int> outDeg(N+1, 0);
    queue<int> queue;
    vector<int> ordemTopologica(N+1);
        

    int v1, v2;
    for(int i = 0; i < K; i++){
        cin >> v1 >> v2; 
        mapa[v1].push_back(v2);
        mapings[v1].insert(v2);
        inDeg[v2]++;
        outDeg[v1]++;

    }
    /*
    for(int i = 1; i <= N ;i++){
        for(auto &adj : mapa[i]){
            cout << adj << ' ';
        }
        cout << endl;
    }
    for(int i = 1; i<=N; i++){
        cout << inDeg[i] << ' ';
    }
    cout << endl;
    for(int j = 1; j<=N; j++){
        cout << outDeg[j] << ' ';
    }
    cout << endl;
    */
    vector<int> inDegCopy = inDeg;

    //kahn's
    for(int i = 1; i <= N; i++){
        if(inDegCopy[i] == 0){ 
            queue.push(i); //colocar elemento concreto na queue
        }
    }
    int j = 1;
    while(!queue.empty()){
        int elem = queue.front();
        ordemTopologica[j] = elem;
        queue.pop();
        for(int vertice : mapa[elem]){
            //decrementar nos que aponta que tinha zero de in degree
            inDegCopy[vertice]--;
            if(inDegCopy[vertice] == 0){ //verificação se algum dos vértices ficou com in 0
                queue.push(vertice);
            }
        }
        j++;
    }
    vector<vector<unsigned>> dp(N+1, vector<unsigned>(N+1, 0));


    //fim kahn's
    
    /*for(int i = 1; i <= N; i++){
        cout << ordemTopologica[i] << ' ';

    }
    cout<<endl
    */
   

    bool dl1;
    bool dl2;
    int b = 0;
    int c = 0;
    int ver1 = 0;
    int ver2 = 0;
    int ver3 = 0;
    int custo = 0;
    for(int h = N-1;h>0;h--){
        if(inDeg[ordemTopologica[h]] == 0 && outDeg[ordemTopologica[h]] == 0){continue;}
        for(int i =h+1, a = h; i<=N;i++, a++){

            ver1 = ordemTopologica[h];
            ver2 = ordemTopologica[i];
            if (hasDL(mapings, ver1, ver2)){
                dp[h][i]++;
            }
            for (int j = a; j>h; j--){
                b = dp[j][i];
                if (b==0){
                    continue;
                }
                ver3 = ordemTopologica[j];
                dl1 = hasDL(mapings, ver3, ver2);
                dl2 = hasDL(mapings, ver1, ver3);
                if ((dl1 && dl2) || (!dl1 && dl2)){
                    dp[h][i]+=b%M;
                }
            }
            c = dp[h][i];
            if(c != 0){
                custo  = calcCusto(M, c);
                camioes[custo].push_back(make_pair(ver1, ver2));
            }

        }
    }
    /*
    for (int i = 1; i<=N;i++){
        for (int h = 1; h<=N; h++){
            cout << dp[i][h] <<' ';
        }
        cout<<'\n';
    }
    */
    
    for(auto &camiao : camioes){
        sort(camiao.begin(), camiao.end());
    }

    for(int i = m1; i <= m2; i++){
        cout << 'C'<<i;
        for(auto &j : camioes[i]) {
            cout << ' ' <<  j.first <<',' << j.second;
        }

        cout << endl;
    }



    return 0;
}
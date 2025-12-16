#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

//compile : g++ -std=c++11 -O3 -Wall main.cpp -lm

//tabela de DP

//implementação de grafos

//ordenação topológica
bool hasDL(const vector<unordered_set<int>> &mapa, int j, int a){
    return mapa[j].find(a) != mapa[j].end();
}
int calcCusto(int M, int paths){
    return 1+paths%M;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    //handle input 
    int N;
    int M;
    int m1, m2; 
    int K;
    cin >> N; //Ler N
    cin >> M; //Ler M
    cin >> m1 >> m2; //ler m1 e m2
    cin >> K; //Ler K
    

    vector<vector<pair<int, int>>> camioes(M+1);

    vector<vector<int>> mapa(N+1); //temos de ter cuidado o primeiro vai ser 0
    vector<unordered_set<int>> mapings(N+1);

    vector<int> inDeg(N+1, 0); //in degree de todos os nós 
    queue<int> queue;
    vector<int> ordemTopologica(N+1);
    //vector<vector<int>> dp(N+2, 0);
    vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
        
    //vector<vector<celula>> cache(N + 2, vector<celula>(N + 2)); //tabela de DP inicializar
    int v1, v2;
    for(int i = 0; i < K; i++){
        cin >> v1 >> v2; //ligação vinda do input
        mapa[v1].push_back(v2);
        mapings[v1].insert(v2);
        inDeg[v2]++;

    }
    
    
    //kahn's
    for(int i = 1; i <= N; i++){
        if(inDeg[i] == 0){ 
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
            inDeg[vertice]--;
            if(inDeg[vertice] == 0){ //verificação se algum dos vértices ficou com in 0
                queue.push(vertice);
            }
        }
        j++;
    }

    //fim kahn's
    
    for(int i = 1; i <= N; i++){
        cout << ordemTopologica[i] << ' ';

    }
    cout << endl;
    bool bomba;
    bool clat;
    int b = 0;
    int ver1 = 0;
    int ver2 = 0;
    int ver3 = 0;
    int custo = 0;
    int sigma = 0;
    for(int h = N-1;h>0;h--){
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
                bomba = hasDL(mapings, ver3, ver2);
                clat = hasDL(mapings, ver1, ver3);
                if ((bomba && clat) || (!bomba && clat)){
                    dp[h][i]+=b;
                }
            }
            custo = calcCusto(M,sigma);
            if (custo != 0){
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
    
    
    for(int i = m1; i <= m2; i++){
        cout << 'C'<<i<<' ';
        for(auto &j : camioes[i]) {
            cout <<  j.first <<',' << j.second << ' ';
        }
        cout << endl;
    }

    //NumeroCamiaoParaCaminho(A,B) = 1+#caminhos(A,B)%M




    //handle output
    return 0;
}


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//compile : g++ -std=c++11 -O3 -Wall main.cpp -lm

//tabela de DP

//implementação de grafos

//ordenação topológica

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

    vector<vector<int>> mapa(N+1); //temos de ter cuidado o primeiro vai ser 0
    vector<int> inDeg(N+1, 0); //in degree de todos os nós 
    queue<int> queue;
    vector<int> ordemTopologica(N+1);
    int v1, v2;
    for(int i = 1; i < K; i++){
        cin >> v1 >> v2;
        mapa[v1].push_back(v2);
        inDeg[v2]++;

    }
    
    for(int i = 1; i <= N; i++){
        cout << i;
        for(int j : mapa[i]) {
            cout << ' ' << j;
        }
        cout << endl;
    }
    for(int i = 1; i <= N ;i++){
        cout << inDeg[i] << ' ';
    }
    cout << endl;

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

    //NumeroCamiaoParaCaminho(A,B) = 1+#caminhos(A,B)%M




    //handle output
    return 0;
}
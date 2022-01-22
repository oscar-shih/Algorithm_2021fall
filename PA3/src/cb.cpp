#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>
#include <algorithm>
#define NIL -1000
#define NOE -101
#define NOQ -102
using namespace std;

vector <tuple <int, int, int>> undirected_graph(int num_v, int num_e, vector<tuple<int, int, int>> &Graph){
    vector <tuple <int, int, int>> ans;
    vector <bool> connect;
    for (int i = 0; i < num_v; i++)
        connect.push_back(false);

    int **G = new int* [num_v];
    for (int i = 0; i < num_v; i++)
        G[i] = new int [num_v+2];
    for (int i = 0; i < num_v; i++){
        for (int j = 0; j < num_v; j++)
            G[i][j] = NOE; // no edge
    }
    for (int i = 0; i < num_v; i++){
        G[i][num_v+1] = NOE; // Key
        G[i][num_v] = NIL; // Predecessor
    }
    for (int i = 0; i < Graph.size(); i++){
        G[get<0>(Graph.at(i))][get<1>(Graph.at(i))] = get<2>(Graph.at(i));
    }
    int i = 0;
    while (i < num_v){
        int j= 1, k = 0;
        while (j < num_v){
            if (G[j][num_v+1] <= 100 && G[j][num_v+1] >= -100 && G[j][num_v+1] > G[k][num_v+1])
                k = j;
            j++;
        }
        G[k][num_v+1] = NOQ;
        if (k != 0){
            if (G[k][G[k][num_v]] > G[G[k][num_v]][k])
                G[k][G[k][num_v]] = NOE;
            else
                G[G[k][num_v]][k] = NOE;
        }
        for (int j = 0; j < num_v; j++){
            if (G[j][num_v+1] <= 100 && G[k][j] >= -100 && G[j][num_v+1] != NOQ && G[j][num_v+1] < G[k][j]){
                G[j][num_v] = k;
                G[j][num_v+1] = G[k][j];
            }
            else if (G[j][num_v+1] <= 100 && G[j][k] >= -100 && G[j][num_v+1] != NOQ && G[j][num_v+1] < G[j][k]){
                G[j][num_v] = k;
                G[j][num_v+1] = G[j][k];
            }
            else
                continue;
        }
        i++;
    }
    for (int i = 0; i < num_v; i++){
        for (int j = 0; j < num_v; j++){
            if (G[i][j] <= 100 && G[i][j] >= -100){ // range of weight
                tuple <int, int, int> temp = make_tuple(i, j, G[i][j]);
                ans.push_back(temp);
            }
            else
                continue;    
        }
    }
    return ans;
}

vector <tuple <int, int, int>> directed_graph(int num_v, int num_e, vector<tuple<int, int, int>> &Graph){
    vector <tuple <int, int, int>> ans;
    // TODO: Finish it with calculating cyclebreaking of weighted graph. NP-Hard.

    vector <int> Queue;
    int **G = new int* [num_v];
    for (int i = 0; i < num_v; i++)
        G[i] = new int [num_v+2];
    for (int i = 0; i < num_v; i++){
        for (int j = 0; j < num_v; j++)
            G[i][j] = NOE; // no edge
    }
    for (int i = 0; i < num_v; i++){
        G[i][num_v+1] = NOE; // Key
        G[i][num_v] = NIL; // Predecessor
    }
    for (int i = 0; i < Graph.size(); i++)
        G[get<0>(Graph.at(i))][get<1>(Graph.at(i))] = get<2>(Graph.at(i));

    while (true){
        int i = 0, ft = 0, bk = 0;
        while (i < num_v){
            for (int j = 0; j < num_v; j++){
                if (G[i][j] < 0 || G[i][j] <= G[ft][bk])
                    continue;
                else{
                    ft = i;
                    bk = j;
                }
            }
            i++;
        }
        if (ft == 0 and bk ==0)
            break;

        vector <bool> connect;
        for (int i = 0; i < num_v; i++)
            connect.push_back(false);
        connect.at(bk) = true;
        bool end = false;
        Queue.push_back(bk);
        while (!(Queue.empty() || end)){
            auto k = Queue.front();
            Queue.erase(Queue.begin());
            for (int i = 0; i < num_v; i++){
                if (G[k][i] == NOQ && i == ft){
                    end = true;
                    G[ft][bk] -= 300;
                    Queue.clear();
                    break;
                }
                else if (!(G[k][i] != NOQ || connect.at(i))){
                    connect.at(i) = true;
                    Queue.push_back(i);
                }
                else 
                    continue;
            }
        }
        if (!end)
            G[ft][bk] = NOQ;
    }
    for (int i = 0; i < num_v; i++){
        for (int j = 0; j < num_v; j++){
            if (G[i][j] <= 100 && G[i][j] >= -100){
                tuple <int, int, int> temp = make_tuple(i, j, G[i][j]);
                ans.push_back(temp);
            }
            if (G[i][j] <= -200){
                G[i][j] += 300;
                tuple <int, int, int> temp2 = make_tuple(i, j, G[i][j]);
                ans.push_back(temp2);
            }     
        }
    }
    return ans;
}

int main(int argc, char *argv[]){
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    string mode; // u or d.
    int num_v, num_e;
    fin >> mode >> num_v >> num_e;

    int u, v, w, end;
    vector <tuple <int, int, int>> Graph;
    for (int i = 0; i < num_e; i++){
        fin >> u >> v >> w;
        tuple <int, int, int> temp = make_tuple(u, v, w);
        Graph.push_back(temp);
    }
    fin >> end; // end = 0
    if (end != 0)
        return 0; //check if readfiles were correct.
        
    // Calculate for the answers and write them into output files.
    vector <tuple <int, int, int>> ans; // Record the removed edges.
    if (mode[0] == 'u')
        ans = undirected_graph(num_v, num_e, Graph);
    else if (mode[0] == 'd')
        ans = directed_graph(num_v, num_e, Graph);
    else{
        cout << "mode not found!" << endl;
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < ans.size(); i++)
        sum += get<2>(ans.at(i));
    fout << sum << endl;

    // Write removed Edges and their weights.
    for (int i = 0; i < ans.size(); i++)
        if (get<2>(ans.at(i)) >= -100)
            fout << get<0>(ans.at(i)) << " " << get<1>(ans.at(i)) << " " << get<2>(ans.at(i)) << endl;
    fout.close();
    fin.close();
    return 0;
}
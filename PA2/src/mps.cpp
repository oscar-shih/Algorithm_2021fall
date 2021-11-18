// Author: b08502141 NTUEE Shih, Min-Han for 2021fall Algorithm PA2
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void chord(int i, int j, int **connection, vector<int>& chords, vector< vector<int> >& ans){
    //Top-Down Method
    if (i == j) return;
    else{
        if (connection[i][j] == 4){
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            ans.push_back(temp);
            return;
        } else if (connection[i][j] == 3){
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            ans.push_back(temp);
            chord(i, chords[j]-1, connection, chords, ans);
            chord(chords[j]+1, j-1,connection, chords, ans);
        } else if (connection[i][j] == 2){
            vector<int> temp;
            temp.push_back(chords[j]);
            temp.push_back(j);
            ans.push_back(temp);
            chord(i+1, j-1, connection, chords, ans);
        } else if (connection[i][j] == 1)
            chord(i, j-1, connection, chords, ans);
        else return;
    }
}

int mps(int i, int j, int **m, bool **visit, int **connection, vector<int>& chords){
    if (visit[i][j] != 0) return m[i][j];
    else if (i == j){
        m[i][j] = 0;
        return 0;
    } else if (j - i == 1){
        if (chords[j] != i){
            visit[i][j] = true;
            m[i][j] = 0;
            return 0;
        } else{
            visit[i][j] = true;
            m[i][j] = 1;
            connection[i][j] = 4;
            return 1;
        }
    } else{
        int k = chords[j];
        if (k == i){
            if (visit[i][j] == false) 
                m[i][j] = mps(i+1, j-1, m, visit, connection, chords) + 1;
            connection[i][j] = 2;
            visit[i][j] = true;
        } else if (k > j || k < i){
            if (m[i][j] == 0)
                m[i][j] = mps(i, j-1, m, visit, connection, chords);
            connection[i][j] = 1;
            visit[i][j] = true;
        } else{
            if (visit[i][k-1] == false){
                m[i][k-1] = mps(i, k-1, m, visit, connection, chords);
                visit[i][k-1] = true;
            } 
            if (visit[i][j-1] == false){
                m[i][j-1] = mps(i, j-1, m, visit, connection, chords);
                visit[i][j-1] = true;
            } 
            if (visit[k+1][j-1] == false){
                m[k+1][j-1] = mps(k+1, j-1, m, visit, connection, chords);
                visit[k+1][j-1] = true;
            }
            if (m[i][j-1] > m[i][k-1] + 1 + m[k+1][j-1]){
                visit[i][j] = true;
                m[i][j] = m[i][j-1];
                connection[i][j] = 1;
            } else{
                visit[i][j] = true;
                m[i][j] = m[i][k-1] + 1 + m[k+1][j-1];
                connection[i][j] = 3;
            }
        }
    }
    return m[i][j];
}

int main(int argc, char *argv[]){
    vector< vector<int> > ans;
    fstream input(argv[1]);
    fstream output;
    output.open(argv[2], ios::out);

    vector<int> chords;
    int n = 0, index1 = 0, index2 = 0;
    input >> n;
    chords.reserve(n);

    while (input >> index1 >> index2){
        chords[index1] = index2;
        chords[index2] = index1;
    }

    int **m = new int *[n];
    int **connection = new int *[n];
    bool **visit = new bool *[n];
    for (int i = 0; i < n; i++){
        m[i] = new int [n];
        connection[i] = new int [n];
        visit[i] = new bool [n];
    }
    printf("%d\n", mps(0, n-1, m, visit, connection, chords));
    chord(0, n-1, connection, chords, ans);
    sort(ans.begin(), ans.end());

    output << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
        output << ans[i][0] << " " << ans[i][1] << "\n";
    input.close();
    return 0;
}
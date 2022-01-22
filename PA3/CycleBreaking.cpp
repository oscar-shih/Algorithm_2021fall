#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main (int argc, char *argv[]){

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    char mode;
    int num_ver , num_edg;
    int ** vertice;

    fin >> mode >> num_ver >> num_edg;
    vertice = new int* [ num_ver  ];
    for (int i = 0; i < num_ver; i++)
        vertice [ i ] =  new int [ num_ver +3 ];
    for (int i = 0; i < num_ver; i++)
        for (int j = 0; j < num_ver; j++)
            vertice [ i ] [ j ] = -101;           //< -100 mean no edge
     for (int i = 0; i < num_ver; i++){
        vertice [ i ] [ num_ver ] = -1;         //pi
        vertice [ i ] [ num_ver +1 ] = -101; //key

     }
    int v1, v2, w;

    for (int i = 0; i < num_edg; i++){
        fin >> v1 >> v2 >> w ;
        vertice [ v1 ] [ v2 ] = w ;
    }

    int zero;
    fin >>zero;


        for (int i = 0; i<num_ver; i++){
            int u = 0;
            for (int j = 1; j<num_ver; j++)
                if(vertice [ j ] [num_ver+1] >= -100 ){
                    if(vertice [ j ] [num_ver+1] > vertice [ u ] [num_ver+1])
                        u = j;
                }
            vertice [u] [num_ver +1] = -102;    //not in Q (the vertice is select)
            if (u != 0){
                vertice [u] [vertice[u][num_ver]] > vertice [vertice[u][num_ver]] [u] ? vertice [u] [vertice[u][num_ver]]= -105 : vertice [vertice[u][num_ver]] [u] = -105;        
            }


            for(int j = 0; j<num_ver; j++){
                if (vertice[ u ][ j ] >= -100){
                    if (vertice [ j ] [num_ver +1] != -102)
                        if(vertice[ u ][ j ] > vertice [ j ] [num_ver +1] ){
                            vertice[ j ][num_ver] = u;
                            vertice [ j ] [num_ver +1] = vertice[ u ][ j ] ;
                        }
                }

                if (vertice[ j ][ u ] >= -100){
                    if (vertice [ j ] [num_ver +1] != -102)
                        if(vertice[ j ][ u ] > vertice [ j ] [num_ver +1] ){
                            vertice[ j ][num_ver] = u;
                            vertice [ j ] [num_ver +1] = vertice[ j ][ u ] ;
                        }
                }
            }
        }
    if (mode == 'd' ){
            int sum2 = 0;
            vector <int> Q;
            while (true){

                int head = 0 ,tail = 0;
                for (int i = 0; i < num_ver; i++){
                    for (int j = 0; j < num_ver ; j++){
                        if (vertice[ i ][ j ] >= 0){                      //smaller than 0 must cut
                            if ( vertice [ i ] [ j ] > vertice [ head ][ tail ] ){
                                head = i;
                                tail = j;
                            }
                        }
                    }
                }

                if (head == 0 && tail == 0)
                    break;

                int v;
                bool end_ = false;
                Q.push_back( tail );

                bool* judge;
                    judge = new bool [num_ver];
                for (int i = 0; i<num_ver; i++)
                    judge [i] = false;
                judge [tail] = true;

                while (!Q.empty() && !end_){
                    v = Q.front();
                    Q.erase(Q.begin());
                    for (int i = 0; i < num_ver; i++){
                            if ( vertice [ v ] [ i ] == -105 ){
                                if (i == head){
                                    vertice [ head ] [ tail ] -= 1100;
                                    end_ = true;
                                    Q.clear();
                                    break;
                                }
                                if (judge[i] == false){
                                    Q.push_back( i );
                                    judge[i] = true;
                                }
                            }
                    }
                }

                if (end_ == false){
                    vertice [ head ] [ tail ] = -105;

                }
            }
    }

            int sum = 0;
            for (int i = 0; i < num_ver; i++)
                for (int j = 0; j < num_ver ; j++){
                    if (vertice[ i ][ j ] >= -100){
                        sum += vertice[ i ][ j ] ;
                    }
                    if (vertice[ i ][ j ] <= -1000){
                            vertice[ i ][ j ] +=  1100;
                            sum += vertice[ i ][ j ] ;
                    }
                }
            fout <<  sum <<endl;
            for (int i = 0; i < num_ver; i++)
                for (int j = 0; j < num_ver ; j++){
                    if (vertice[ i ][ j ] >= -100){
                        fout<< i <<" " << j <<" "<< vertice[ i ][ j ] <<endl;
                    }
                }
    fout.close();
    fin.close();

}


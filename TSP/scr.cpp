#include "head.h"

using namespace std;

double dist( pt a, pt b )
{
    return sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2 ) );
}

void show_mat(vector<vector<item>> &M)
{
    int N=M.size();
    int r, e;

    for (r=0; r<N; r++)
    {
        for (e=0; e<M[i].size(); e++)
        {
            cout<< M[r][e].id<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

vector<item>& knapsack (vector <vector<vector<item>>>& used, vector<item>& it, int K)
{
    int N=it.size();
    int p, q;
    vector<vector<int>> w(K+1, vector<int>(N+1));
    for (p=0; p<N; p++)
    {
        for (q=0; q<K; q++)
        {
            if (it[p].weight<=q+1)
            {
                if (w[q+1][p]>=w[q+1-it[p].weight][p]+it[p].value)
                {
                    w[q+1][p+1]=w[q+1][p];
                    used[q+1][p+1]=used[q+1][p];
                }
                else
                {
                    w[q+1][p+1]=w[q+1-it[p].weight][p]+it[p].value;
                    used[q+1][p+1]=used[q+1-it[p].weight][p];
                    used[q+1][p+1].push_back(it[p]);
                }
            }
            else
            {
                w[q+1][p+1]=w[q+1][p];
                used[q+1][p+1]=used[q+1][p];
            }
        }
    }
    return used[K][N];
}


void k_means(vector<vector<item>>& clusters, vector <item>& points, double mean)
{
    int N=points.size();
    int p;
 for (p=0; p<N; p++)
    {
        if (points[p].x>mean)
            clusters[0].push_back(points[p]);
        else
            clusters[1].push_back(points[p]);
    }
    clusters[0].push_back(points[0]);
    clusters[1].push_back(points[0]);
   
}

pair<double, int> cvrp(vector<item>& pnt, int V, int c)
{
    vector<vector<item>>usedused;
    vector<item>p=pnt;
    double ANS=0;
    int r,e,h;
    for (r=0; r<V;r++)
    {
            int N=p.size();
            int K=c;
            vector <vector<vector<item>>> used(K+1, vector<vector<item>>(N+1));
       
            usedused.push_back(knapsack(used, p, c));
            used.clear();
            for (e=0; e<usedused[i].size(); e++)
                {
                    for (h=0; h<p.size(); h++)
                    {
                        if (usedused[r][e].id==p[h].id)
                            p.erase(p.begin()+h);
                    }
                }
            if (p.size()==0)
                break;
    }
    V=V+2-usedused.size();
    double ans=0;

    for (r=0; r<usedused.size(); r++)
    {
        Path cur;
        for (e=0; e<usedused[i].size(); e++)
        {
             pt newone = {usedused[r][e].id, usedused[r][e].x, usedused[r][e].y};
   	         cur.add_node(newone);
        }
        cur.local_search_2();
        ans+=cur.length();
    }
    ANS += ans;
    return {ANS, V};
}
Path::Path(){
    num_of_nodes = 0;
    last_improvement_status = false;
}

void Path::add_node( pt &new_node )
{
    if( num_of_nodes > 1 )
    {
        path.push_back( path[0] );
        deque<pt>::iterator it = path.begin(),
                            here = it+1;
        double best_len = dist( *it, new_node ) + dist( new_node, *(it+1) );
        it++;

        for(int r=0; r<num_of_nodes-1; r++)
        {
            double tmp = dist( *it, new_node ) + dist( new_node, *(it+1) );
            if( tmp < best_len )
            {
                best_len = tmp;
                here = it+1;
            }
            it++;
        }

        path.emplace( here, new_node );
        path.pop_back();
    }
    else
        path.push_back( new_node );

    num_of_nodes++;
}

void Path::try_to_improve_2(int v1, int v2)
{

    if(v1>v2) swap(v1,v2);

    double init_dist =
          dist( path[v1], path[v1+1] )
        + dist( path[v2], path[v2+1] );
    double new_dist = dist( path[v1], path[v2] ) + dist( path[v1+1], path[v2+1] );
    if( init_dist > new_dist )
    {
        deque<pt>::iterator it1 = next( path.begin(), v1+1 );
        deque<pt>::iterator it2 = next( it1, v2-v1 );
        reverse( it1, it2 );
        last_improvement_status = true;
    }
}

double Path::length()
{
    double len = 0;
    for(int r=0; r<num_of_nodes; r++)
        len += dist( path[r], path[(r+1)%num_of_nodes] );

    return len;
}

void Path::local_search_2()
{
    path.push_back( path[0] );
    for(int r=0; r<num_of_nodes-2; r++)
        for(int e=r+2; e<num_of_nodes; e++)
        {

            try_to_improve_2(r,e);

            if(last_improvement_status)
            {
                last_improvement_status = false;
                e = e+2;
            }
        }
    path.pop_back();
}

void Path::show_a()
{
    for(auto p: path)
        cout<<p.id<<": ( "<<p.x<<", "<<p.y<<" )\n";
}

void Path::show()
{
    for(auto p: path)
        cout<<p.id<<" ";
}


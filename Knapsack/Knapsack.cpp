#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int solve(int k, vector<int> worht, vector<int> weights, int W) 
{
    vector<int> m_1(W + 1, 0);
    vector<int> m_2(W + 1, 0);
    int p, q;
    for (p = 1; p <= k; p++) 
    {
        vector<int> temp = m_1;
        m_1 = m_2;
        m_2 = temp;
        for (q = 0; q <= W; q++)
        {
            m_2[q] = m_1[q];
            if (q - weights[p - 1] >= 0) 
            {
                m_2[q] = max(m_2[q], m_1[q - weights[p - 1]] + worht[p - 1]);
            }
        }
    }
    int result = 0;
    for (p = W; p >= 0; p--) 
    {
        if (m_2[p] != 0) 
        {
            result = m_2[p];
            break;
        }
    }
    return result;
}

int main() 
{
    string path = "/Users/annalarina/knapsack";
    auto it = fs::directory_iterator(path);
    vector<fs::path> matrix_path;
    copy_if(fs::begin(it), fs::end(it), std::back_inserter(matrix_path),
        [](const auto& entry) 
        {
            return fs::is_regular_file(entry);
        });
    for (auto& p : matrix_path)
    {
        ifstream f;
        f.open(p.string());
        cout << p.string() << endl;
        int k, W;
        f >> k >> W;
        vector<int> worht;
        vector<int> weights;
        int p;
        for (p = 0; p < k; p++) 
        {
            int worht, weight;
            f >> worht >> weight;
            worht.push_back(worht);
            weights.push_back(weight);
        }
        int max_value = solve(k, worht, weights, W);
        cout << max_value << endl;
    }
    return 0;
}

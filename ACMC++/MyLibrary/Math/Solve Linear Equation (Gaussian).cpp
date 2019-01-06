#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;

enum SOL {
    NOSOL, UNIQUE, INFINIT
};

bool zeros(vector<double> &row) {
    for (auto elm : row)
        if (fabs(elm - 0.0) > EPS)
            return false;
    return true;
}

bool swapRow(int i, vector<vector<double> > &mat) {
    for (int j = i + 1; j < int(mat.size()); ++j) {
        if (fabs(mat[j][i] - 0.0) > EPS) {
            swap(mat[i], mat[j]);
            return true;
        }
    }
    return false;
}

void devideRow(int i, double x, vector<vector<double> > &mat) {
    for (int j = 0; j < int(mat[i].size()); ++j)
        mat[i][j] /= x;
}

void makeZero(int i, int j, vector<vector<double> > &mat) {
    double d = -mat[j][i];
    for (int k = 0; k < int(mat[i].size()); ++k)
        mat[j][k] += d * mat[i][k];
}

SOL solveLinearEquation(vector<vector<double> > &mat) {
    for (int i = 0; i < int(mat.size()); ++i) {
        if (zeros(mat[i])) {
            mat.erase(mat.begin() + i), i--;
            continue;
        }
        if (i == int(mat[i].size()))
            break;
        if (fabs(mat[i][i] - 0.0) < EPS)
            if (!swapRow(i, mat))
                return NOSOL;
        devideRow(i, mat[i][i], mat);
        for (int j = 0; j < int(mat.size()); ++j)
            if (i != j)
                makeZero(i, j, mat);
    }
    if (mat.size() + 1 == mat[0].size())
        return UNIQUE;
    if (mat.size() + 1 < mat[0].size())
        return INFINIT;
    return NOSOL;
}

vector<double> gaussian(vector<vector<double> > mat) {
    int state = solveLinearEquation(mat);
    if (state != 1)
        return vector<double>();
    vector<double> ret(mat[0].size() - 1);
    for (int i = 0; i < int(mat.size()); ++i)
        ret[i] = mat[i][int(mat[i].size()) - 1];
    return ret;
}

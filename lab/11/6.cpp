#include <bits/stdc++.h>
using namespace std;
template <unsigned M, unsigned N, unsigned K = 0>
struct PermutationHelper
{
    static const unsigned long long VALUE = (N - K) * PermutationHelper<M, N, K + 1>::VALUE;
};
template <unsigned M, unsigned N>
struct PermutationHelper<M, N, M>
{
    static const unsigned long long VALUE = 1;
};
template <unsigned M, unsigned N>
struct Permutation
{
    static const unsigned long long VALUE = PermutationHelper<M, N, 0>::VALUE;
};

int main()
{
    cout << Permutation<3, 25>::VALUE << endl;
}
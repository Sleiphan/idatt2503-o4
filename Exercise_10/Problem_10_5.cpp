#include <cmath>
#include <iostream>
#include <unordered_map>

using namespace std;

long long mod_exp(long long base, long long exp, long long mod)
{
  long long result = 1;
  base = base % mod;
  while (exp > 0)
  {
    if (exp % 2 == 1)
    {
      result = (result * base) % mod;
    }
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return result;
}

tuple<long long, long long, long long> shanks_algorithm(long long p, long long alpha, long long beta)
{
  long long m = static_cast<long long>(sqrt(p)) + 1;
  unordered_map<long long, long long> dictionary;

  cout << "Starting first loop..." << endl;
  for (long long j = 0; j < m; ++j)
  {
    if (j % (m / 10) == 0)
    {
      cout << "First loop progress: " << static_cast<double>(j) / m * 100.0 << "%" << endl;
    }
    long long value = mod_exp(alpha, m * j, p);
    dictionary[value] = j;
  }

  cout << "Starting second loop..." << endl;
  long long alpha_inv = mod_exp(alpha, p - 2, p);
  for (long long i = 0; i < m; ++i)
  {
    if (i % (m / 10) == 0)
    {
      cout << "Second loop progress: " << static_cast<double>(i) / m * 100.0 << "%" << endl;
    }
    long long val = (beta * mod_exp(alpha_inv, i, p)) % p;
    if (dictionary.find(val) != dictionary.end())
    {
      return make_tuple(m, i, dictionary[val]);
    }
  }

  return make_tuple(-1, -1, -1);
}

int main()
{
  long long m_ans, i_ans, j_ans;
  tie(m_ans, i_ans, j_ans) = shanks_algorithm(1000000007, 5, 144363234);

  if (m_ans != -1)
  {
    cout << "Shanks algorithm:" << endl;
    cout << "a is m*j+i = " << m_ans << "*" << j_ans << "+" << i_ans << " = " << m_ans * j_ans + i_ans << endl;
  }
  else
  {
    cout << "No solution found." << endl;
  }

  return 0;
}
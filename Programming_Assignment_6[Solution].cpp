//Checking part :
bool check(int mid) {
    int cnt = 1, temp = 0; // cnt indicate no. of student use in the allocation for some mid as upper_bound on no. of books per studnet
    for(int i = 0; i < n; ++i) {
        if(temp + a[i] > mid) {  // If adding a[i] increase the mid then we will start allocating next student.
            cnt++; // Thus we increase no. of student use.
            if(cnt > k) // If this exceed k (max student we have) return 0 immediately.
                return 0;
            temp = a[i];
        }
        else 
            temp += a[i];
    }
    return 1; // If every thing above passes good then return 1.

//Binary Search part: 
 int l = mn, r = mx;
    // mn is minimum of all, mx is the sum of all books in all cartons. 
    int ans = r;
    while(l <= r) {
        int mid = (l + r) / 2; // Careful this may lead to overflown so better to use l + (r - l) / 2, or use long long int (C++)
        if(check(mid)) { // Check for mid, if it is possible then try to minimize this upper_bound on no. of books each student. 
            ans = mid; // mark this as the answer till now, since it is passing checking.
            r = mid - 1;  // reduce range to lower the upper_bound on no. of books . So in order to reduce maximum books to single
        }
        else { // else if it is not possible, mean the mid require more than k student then increase the upper bound and thus l = mid + 1
            l = mid + 1;
        }
    }

//Code
#include <bits/stdc++.h>
using namespace std;

#define hey(x) cerr << #x << " is " << x << "\n";
#define int long long int
#define ll long long
#define vi vector<int>
#define vvi vector<vector<int> >
#define vpi vector<pair<int, int> >
#define vvpi vector<vector<pair<int, int> > >
#define all(v) (v).begin(), (v).end()   
#define rall(v) (v).rbegin(), (v).rend()
#define pii pair<int, int>
#define pb push_back
#define SZ(x) (int)(x).size()
#define F first
#define S second
#define PI 3.1415926535897932384626
#define out cout << fixed << setprecision(12)
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define inf 1e12

const int N = 1e6 + 10;
const int mod = 1e9 + 7;
const double pi = acos(-1);

vi a;
int n, k;

bool check(int mid) {
    int cnt = 1, temp = 0;
    for(int i = 0; i < n; ++i) {
        if(temp + a[i] > mid) {
            cnt++;
            if(cnt > k) 
                return 0;
            temp = a[i];
        }
        else
            temp += a[i];
    }
    return 1;
}

void go() {
    cin >> n >> k;
    a = vi(n);
    int mn = inf, mx = 0;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
        mn = min(mn, a[i]);
        mx += a[i];
    }
    int l = mn, r = mx;
    int ans = r;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    vi store;
    int temp = 0;
    int cnt = 0;
    for(int i = n - 1; i >= 0; --i) {
        if(temp + a[i] > ans) {
            store.pb(-1); // -1 used to know the pos of '/' in solution
            cnt++;
            temp = a[i];
            store.pb(a[i]);
        }
        else {
            store.pb(a[i]);
            temp += a[i];
        }
    }
    reverse(all(store));
    if(cnt > k - 1) {
        for(int i = SZ(store) - 1; i >= 0; --i) {
            if(store[i] == -1) {
                store[i] = 0;
                cnt--;
                if(cnt == k - 1)
                    break;
            }
        }
    }
    for(int i = 0; i < SZ(store); ++i) {
        if(store[i]){
            if(store[i] != -1 && cnt < k - 1) {
                if(i + 1 < SZ(store) && store[i + 1] != -1) {
                    cout << store[i] << " / ";
                    cnt++;
                }
                else {
                    cout << store[i] << ' ';
                }
            }
            else if(store[i] != -1) {
                cout << store[i] << " ";
            }
            else if(i + 1 != SZ(store)) {
                cout << "/ ";
            }
        }
    }
    cout << '\n';
}
    
int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    go();
    return 0;
}

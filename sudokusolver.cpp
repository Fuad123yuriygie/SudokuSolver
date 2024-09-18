#include <bits/stdc++.h>
int comparetor(int a[81], int pos, int permission[81]);
int identifier(int a[81], int pos);
int getValue(int a[81], int pos, int permission[81]);
int incrementer(int a[81], int pos);
int maxStack = 0;

using namespace std;
int main() {
    int inp[81], temp, flag[81];
    for (int i = 0; i < 81; i++) {
        cin >> inp[i];
        if (inp[i] == 0) flag[i] = 1;
        else flag[i] = 0;
    }
    // Primary setting up values for each entry
    for (int i = 0; i < 81; i++) {
        getValue(inp, i, flag);

    }

    // Refine each entry until no error detected (might run on an infinite loop)
    int prb = 0;
    for (int i = 0; i < 81; i++) {
        if (comparetor(inp, i, flag)) {

            getValue(inp, i, flag);
            prb = 1;
        }
        if (i == 80 && prb == 1) {
            i = 0;
            prb = 0;
        }
    }

    for (int k = 1, lol = 0; k <= 9; k++) {
        for (int j = 1; j <= 9; j++) {
            cout << setw(2) << inp[lol] << " ";
            lol++;
            if (j % 3 == 0) cout << " ";
        }
        if (k % 3 == 0) cout << endl;
        cout << endl;
    }

    cout << "Main complete" << endl;
    return 0;
}
// Identifie collusion exsistance
int comparetor(int a[81], int pos, int permission[81]) {
    int x, y, z, con = 0;
    x = pos % 9;
    y = pos - x;
    z = (pos / 27) * 3 + x / 3;
    for (int i = x; i < 81; i += 9) {
        if (i == pos) continue;
        else if (a[i] == a[pos]) {
            if (!permission[i]) return 10;
            con++;
        }
    }
    for (int i = y; i < y + 9; i++) {
        if (i == pos) continue;
        else if (a[i] == a[pos]) {
            if (!permission[i]) return 10;
            con++;
        }
    }
    int grp = (z * 3) + (z / 3) * 18;
    for (int i = grp; i <= grp + 20; i = (i + 1) + 6 * !((i + 1) % 3)) {
        if (i == pos) continue;
        else if (a[i] == a[pos]) {
            if (!permission[i]) return 10;
            con++;
        }
    }
    return con;

}
// Identifie collusion position
int identifier(int a[81], int pos) {
    int x, y, z;
    x = pos % 9;
    y = pos - x;
    z = (pos / 27) * 3 + x / 3;
    for (int i = x; i < 81; i += 9) {
        if (i == pos) continue;
        else if (a[i] == a[pos]) return i;
    }
    for (int i = y; i < y + 9; i++) {
        if (i == pos) continue;
        else if (a[i] == a[pos]) return i;
    }
    int grp = (z * 3) + (z / 3) * 18;
    for (int i = grp; i <= grp + 20; i = (i + 1) + 6 * !((i + 1) % 3)) {
        if (i == pos) continue;
        else if (a[i] == a[pos]) return i;
    }
    return 0;
}

int getValue(int a[81], int pos, int permission[81]) {
    if (!permission[pos]) return 0;
    maxStack++;
    if (maxStack == 1000) {
        maxStack = 0;
        return 0;
    }
    int col;
    incrementer(a, pos);
    cout << pos << " " << a[pos] << endl;
    for (int i = 0; i < 9 && comparetor(a, pos, permission) > 1; i++) {
        incrementer(a, pos);
        if (i == 7) {
            a[pos] = (int)pow(rand(), 2) % 10;
            if (a[pos] == 0) a[pos] = 7;
        }
    }
    if (comparetor(a, pos, permission) >= 1) {
        col = identifier(a, pos);
        getValue(a, col, permission);
    }
    return 0;
}
int incrementer(int a[81], int pos) {
    a[pos]++;
    if (a[pos] == 10) a[pos] = 1;
    return 0;
}

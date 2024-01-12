#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

int step[100005][3], cur, ao[10][10], a[10][10], l[10][10], c[10][10], s[4][4][10], op, x, y, z, solved, temp, failini;

string inp;

int num(int i, int j) {
    int cnt = 0;
    for (int k = 1; k <= 9; k++) if (l[i][k] == 0 && c[j][k] == 0 && s[(i - 1) / 3 + 1][(j - 1) / 3 + 1][k] == 0) cnt++;
    return cnt;
}

int get() {
    int cnt = 10;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (a[i][j] == 0) cnt = min(cnt, num(i, j));
        }
    }
    return cnt;
}

void hint(int i, int j) {
    int te;
    int cnt = num(i, j);
    if (cnt == 1) {
        for (int k = 1; k <= 9; k++) if (l[i][k] == 0 && c[j][k] == 0 && s[(i - 1) / 3 + 1][(j - 1) / 3 + 1][k] == 0) te = k;
        printf("You can now insert %d into(%d, %d).\n", te, i, j);
    }
    else {
        te = 0;
        printf("Candidates for(%d, %d): ", i, j);
        for (int k = 1; k <= 9; k++) {
            if (l[i][k] == 0 && c[j][k] == 0 && s[(i - 1) / 3 + 1][(j - 1) / 3 + 1][k] == 0) {
                cout << k;
                te++;
                if (te == cnt) cout << ".";
                else cout << ", ";
            }
        }
        printf("\n");
    }
    return;
}

void print() {
    cout << "Current Sudoku:\n";
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << a[i][j] << "\n"[j != 9];
        }
    }
    return;
}

void ini() {
    cur = 0;
    solved = 0;
    memset(l, 0, sizeof(l));
    memset(c, 0, sizeof(c));
    memset(s, 0, sizeof(s));
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            a[i][j] = ao[i][j];
            if (ao[i][j] < 0 || ao[i][j] > 9) {
                failini = 1;
                return;
            }
            if (a[i][j] != 0) {
                if (l[i][a[i][j]] || c[j][a[i][j]] || s[(i - 1) / 3 + 1][(j - 1) / 3 + 1][a[i][j]]) {
                    failini = 1;
                    return;
                }
                l[i][a[i][j]]++;
                c[j][a[i][j]]++;
                s[(i - 1) / 3 + 1][(j - 1) / 3 + 1][a[i][j]]++;
            }
        }
    }
    cout << "Initialization completed.\n";
    return;
}

void insert(int i, int j, int k, int m) {
    l[i][k] += m;
    c[j][k] += m;
    s[(i - 1) / 3 + 1][(j - 1) / 3 + 1][k] += m;
    a[i][j] = k + ((m - 1) / 2) * k;
    step[cur][0] = i;
    step[cur][1] = j;
    step[cur][2] = k;
    cur += m;
    return;
}

int main() {
    for (int i = 1; i <= 9; i++) {
        cin >> inp;
        for (int j = 1; j <= 9; j++) {
            ao[i][j] = inp[j - 1] - '0';
        }
    }
    failini = 0;
    ini();
    if (failini) {
        printf("Invalid Sudoku.\n");
        return 0;
    }
    while (1) {
        printf("operations:1.input the coordinate you are going to input and the number.\n");
        printf("           2.retreat.\n");
        printf("           3.hint.\n");
        printf("           9.end\n");
        temp = get();
        if (temp == 10) {
            printf("You have successfully solved this Sudoku.\n");
            return 0;
        }
        else if (temp == 0) {
            printf("You have failed.\nUndo or restart?\n");
        }
        cin >> op;
        if (op == 0) {
            ini();
        }
        else if (op == 1) {
            cin >> x >> y >> z;
            if (solved != -1) {
                if (1 <= x && x <= 9 && 1 <= y && y <= 9 && 1 <= z && z <= 9) {
                    if (a[x][y]) cout << "This cell is occupied.\n";
                    else if (l[x][z] == 0 && c[y][z] == 0 && s[(x - 1) / 3 + 1][(y - 1) / 3 + 1][z] == 0) insert(x, y, z, 1);
                    else cout << "This operation is invalid.\n";
                }
                else cout << "Invalid input.\n";
            }
        }
        else if (op == 2) {
            if (cur == 0) cout << "You can't undo.\n";
            else {
                insert(step[cur - 1][0], step[cur - 1][1], step[cur - 1][2], -1);
            }
        }
        else if (op == 3) {
            if (solved == -1) printf("You have failed.\nUndo or restart?\n");
            else if (temp == 1) {
                for (int i = 0; i < 81; i++) {
                    if (num((i / 9) + 1, (i % 9) + 1) == 1 && a[(i / 9) + 1][(i % 9) + 1] == 0) {
                        hint((i / 9) + 1, (i % 9) + 1);
                        break;
                    }
                }
            }
            else {
                for (int i = 1; i <= 9; i++) {
                    for (int j = 1; j <= 9; j++) {
                        if (num(i, j) == temp && a[i][j] == 0) hint(i, j);
                    }
                }
            }
        }
        else if (op == 9) {
            return 0;
        }
        else cout << "Invalid input.\n";
        print();
    }
}

/*
ÑùÀý£º
1.
030007004
602041000
050030967
040003006
087000350
900700020
718020040
000160809
400500030
´ð°¸£º
839657214
672941583
154832967
541283796
287496351
963715428
718329645
325164879
496578132
2.
800000000
003600000
070090200
050007000
000045700
000100030
001000068
008500010
090000400
´ð°¸£º
812753649
943682175
675491283
154237896
369845721
287169534
521974368
438526917
796318452
*/
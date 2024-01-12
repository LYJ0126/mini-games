//改进版：每次优先选择可枚举数目最少的位置，实现剪枝
//此程序的递归主体Search()函数由李亦非完成，其余部分及注释由罗远兢完成。
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

int cell[9][9], candidate[9][9][10], cell_remain[9][9], total_remain[10];
/*
cell:用来 记录当前数独局面，元素值为0表示位置为空。
candidate: candidate[i][j][k]的值表示cell[i][j]为零时将k填入此处是否会产生冲突，
    其中值为0表示不会（说明没有一个数=k与之冲突），值为i(i≠0)表明会，且产生冲突的因素（有值为k的数在同行/列/九宫格）个数为i。
    这样规定是为了方便在递归中回溯。
cell_remain:cell_remain[i][j]的值代表cell[i][j]可选元素的个数，
    即cell[i][j]==0时，candidate[i][j][k]中零元素的个数。
total_remain : 对m∈N，m∈[1,9],当前数独中有 total_remain[m] 个位置，其可选元素数⽬为m。其中，已
    填数字位置的可选元素数⽬为0。这样，我们就可以总是保证从可选元素最小的位置开始进行填数
solved : 值为1表明数独已解决，值为0表明数独未解决。
*/

//判断是否完成
bool solved;
//输⼊数独，预处理 candidate 数组
void Input() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> cell[i][j];
            if (cell[i][j] != 0) {
                //对cell[i][j]所在的行的其他元素的candidate进行预处理
                //即[i][k]处元素的candidate中，cell[i][j]这个候选元素变成‘1’（不可选）
                for (int k = 0; k < 9; k++) {
                    if (k == j) continue;
                    candidate[i][k][cell[i][j]]++;
                }
                //对cell[i][j]所在的列的其他元素的candidate进行预处理
                //即[k][j]处元素的candidate中，cell[i][j]这个候选元素变成‘1’（不可选）
                for (int k = 0; k < 9; k++) {
                    if (k == i) continue;
                    candidate[k][j][cell[i][j]]++;
                }
                //对cell[i][j]所在的九宫格的其他元素的candidate进行预处理
                //即[k][l]处((k,l)≠(i,j))元素的candidate中，cell[i][j]这个候选元素变成‘1’（不可选）
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if ((i / 3) * 3 + k == i || (j / 3) * 3 + l == j) continue;
                        candidate[(i / 3) * 3 + k][(j / 3) * 3 + l][cell[i][j]]++;
                    }
                }
            }
        }
    }
    return;
}

//预处理 cell_remain 和 total_remain 数组。
//cnt: 记录 cell[i][j] 可选元素的个数。
void InitiateRemain() {
    int cnt;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cnt = 0;
            if (cell[i][j] == 0) {
                //当cell[i][j]==0，即此处可以填数字时，遍历其候选数组candidate[i][j][k]，统计可选数字个数
                for (int k = 1; k <= 9; k++) {
                    if (candidate[i][j][k] == 0) cnt++;
                }
            }
            cell_remain[i][j] = cnt;
            total_remain[cnt]++;
        }
    }
    return;
}

/*Search  此处由李亦非同学完成
递归主体。当 solved为1时返回，当数独内所有位置的可选元素数⽬都为零时判断数独是否已被填好，其余情况
按可选元素数⽬最少的位置枚举。
minimum : 记录遍历 total_remain 后得到的可选元素个数的⾮零最⼩值（一定要非零！）。当该值不存在时 minimum 为零。
flag : ⽤来标记是否退出循环的变量。
current : 记录当前枚举位置的坐标
*/
void Search() {
    int minimum = 0;
    //从候选数个数为1开始寻找所有候选数还剩i个的位置的个数，若其≠0，说明i即可选元素个数的非0最小值
    for (int i = 1; i <= 9; i++) {
        if (total_remain[i] != 0) {
            minimum = i;
            break;
        }
    }
    //已经没有任何候选元素时，判断结果：若存在未填的数，说明未解决（无解），否则标记为已解决
    if (minimum == 0) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (cell[i][j] == 0) return;
            }
        }
        solved = 1;
        return;
    }
    else {
        int flag = 0;
        int current[2];
        //寻找所剩可选元素最少的位置并用current记录下其坐标
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (cell_remain[i][j] == minimum) {
                    current[0] = i;
                    current[1] = j;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) break;
        }
        //递归求解
        for (int d = 1; d <= 9; d++) {
            if (candidate[current[0]][current[1]][d] != 0) continue;//若d不可选，跳过
            cell_remain[current[0]][current[1]] = 0;//这个点剩余可选的数归为0
            total_remain[minimum]--;//候选数个数为minimum(即候选数最少)的位置个数减少一个
            total_remain[0]++;//候选数个数为0的位置个数加一，即减少一个需要填的空位
            cell[current[0]][current[1]] = d;//将d填入这个空位
            //判断列
            for (int j = 0; j < 9; j++) {
                if (j == current[1] || cell[current[0]][j] != 0) continue;
                //跳过已经有数的位置以及(current[0],current[1])这个位置
                //如果cell[current[0]][j]原本可以填入d，即candidate[current[0]][j][d] == 0，由于 cell[current[0]][current[1]] = d且与之同列,那么这个点要除去d这个候选数
                if (candidate[current[0]][j][d] == 0) {
                    total_remain[cell_remain[current[0]][j]]--;//所有可选元素个数与cell[current[0]][j]可选元素个数相同的位置数减少一个
                    cell_remain[current[0]][j]--;//位置（current[0],j）的候选数个数减一
                    total_remain[cell_remain[current[0]][j]]++;//和点（current[0],j）候选数相同的点（位置）的个数减一
                }
                candidate[current[0]][j][d]++;//点（current[0],j）原来的候选数d做上标记，表示d不再是其候选数
            }
            //后面的判断类似，我就不一步一步地细说了
            //判断行
            for (int i = 0; i < 9; i++) {
                if (i == current[0] || cell[i][current[1]] != 0) continue;
                //跳过已经有数的位置以及(current[0],current[1])这个位置
                //如果cell[i][current[1]]原本可以填入d，即candidate[i][current[1]][d] == 0，由于 cell[current[0]][current[1]] = d且与之同列,那么这个点要除去d这个候选数
                if (candidate[i][current[1]][d] == 0) {
                    total_remain[cell_remain[i][current[1]]]--;
                    cell_remain[i][current[1]]--;
                    total_remain[cell_remain[i][current[1]]]++;
                }
                candidate[i][current[1]][d]++;
            }
            //判断九宫格
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if ((current[0] / 3 * 3 + i == current[0] && current[1] / 3 * 3 + j == current[1]) || cell[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j] != 0) continue;
                    //在点（current[0],current[1]）所在的九宫格内，跳过已经有数的位置以及（current[0],current[1]）这个位置
                    //如果该点处原本可以填入d,即candidate[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j][d] == 0，由于cell[current[0]][current[1]] = d且与之同九宫格，那么该点处要除去d这个候选数
                    if (candidate[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j][d] == 0) {
                        total_remain[cell_remain[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j]]--;
                        cell_remain[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j]--;
                        total_remain[cell_remain[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j]]++;
                    }
                    candidate[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j][d]++;
                }
            }
            Search();
            if (solved == 1) return;
            //回溯
            cell_remain[current[0]][current[1]] = minimum;
            total_remain[minimum]++;
            total_remain[0]--;
            cell[current[0]][current[1]] = 0;
            for (int i = 0; i < 9; i++) {
                if (i == current[1] || cell[current[0]][i] != 0) continue;
                if (candidate[current[0]][i][d] == 1) {
                    total_remain[cell_remain[current[0]][i]]--;
                    cell_remain[current[0]][i]++;
                    total_remain[cell_remain[current[0]][i]]++;
                }
                candidate[current[0]][i][d]--;
            }
            for (int i = 0; i < 9; i++) {
                if (i == current[0] || cell[i][current[1]] != 0) continue;
                if (candidate[i][current[1]][d] == 1) {
                    total_remain[cell_remain[i][current[1]]]--;
                    cell_remain[i][current[1]]++;
                    total_remain[cell_remain[i][current[1]]]++;
                }
                candidate[i][current[1]][d]--;
            }
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if ((current[0] / 3 * 3 + i == current[0] && current[1] / 3 * 3 + j == current[1]) || cell[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j] != 0) continue;
                    if (candidate[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j][d] == 1) {
                        total_remain[cell_remain[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j]]--;
                        cell_remain[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j]++;
                        total_remain[cell_remain[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j]]++;
                    }
                    candidate[current[0] / 3 * 3 + i][current[1] / 3 * 3 + j][d]--;
                }
            }
        }
    }
}

//输出
void Output() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << cell[i][j] << " \n"[j == 8];
        }
    }
    return;
}

void Solve() {
    Input();
    InitiateRemain();
    solved = 0;
    Search();
    Output();
    return;
}

int main() {
    Solve();
    return 0;
}

/*
测试样例：
1.
 8 0 0 0 0 0 0 0 0
 0 0 3 6 0 0 0 0 0
 0 7 0 0 9 0 2 0 0
 0 5 0 0 0 7 0 0 0
 0 0 0 0 4 5 7 0 0
 0 0 0 1 0 0 0 3 0
 0 0 1 0 0 0 0 6 8
 0 0 8 5 0 0 0 1 0
 0 9 0 0 0 0 4 0 0
答案：
 8 1 2 7 5 3 6 4 9
 9 4 3 6 8 2 1 7 5
 6 7 5 4 9 1 2 8 3
 1 5 4 2 3 7 8 9 6
 3 6 9 8 4 5 7 2 1
 2 8 7 1 6 9 5 3 4
 5 2 1 9 7 4 3 6 8
 4 3 8 5 2 6 9 1 7
 7 9 6 3 1 8 4 5 2
2. 我们会发现法一要很长时间解决的问题，法二可以在1秒内解决
 9 0 0 8 0 0 0 0 0 
 0 0 0 0 0 0 5 0 0
 0 0 0 0 0 0 0 0 0
 0 2 0 0 1 0 0 0 3
 0 1 0 0 0 0 0 6 0
 0 0 0 4 0 0 0 7 0
 7 0 8 6 0 0 0 0 0
 0 0 0 0 3 0 1 0 0
 4 0 0 0 0 0 2 0 0
答案：
 9 7 2 8 5 3 6 1 4
 1 4 6 2 7 9 5 3 8
 5 8 3 1 4 6 7 2 9
 6 2 4 7 1 8 9 5 3
 8 1 7 3 9 5 4 6 2
 3 5 9 4 6 2 8 7 1
 7 9 8 6 2 1 3 4 5
 2 6 5 9 3 4 1 8 7
 4 3 1 5 8 7 2 9 6
*/
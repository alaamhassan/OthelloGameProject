void update_array(int arr[8][8], char i_org, char j_org, char player) {
    char i = i_org;
    char j = j_org;
    bool flag = 0;

    //updating rows above
    while (i != 0 && (arr[i - 1][j] != 0)) {
        i--;

        if (arr[i][j] == player) {
            i++;
            while (i != i_org) {
                arr[i][j] = player;
                i++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating rows below
     i = i_org;     j = j_org;     flag = 0;
    while (i != 8 && (arr[i + 1][j] != 0)) {
        i++;

        if (arr[i][j] == player) {
            i--;
            while (i != i_org) {
                arr[i][j] = player;
                i--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating coloums to the left
    i = i_org;     j = j_org;     flag = 0;
    while (j != 0 && (arr[i][j-1] != 0)) {
        j--;

        if (arr[i][j] == player) {
            j++;
            while (j != j_org) {
                arr[i][j] = player;
                j++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }


    //updating coloums to the right
    i = i_org;     j = j_org;     flag = 0;
    while (j != 8 && (arr[i][j+1] != 0)) {
        j++;

        if (arr[i][j] == player) {
            j--;
            while (j != j_org) {
                arr[i][j] = player;
                j--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }


    //updating up_left diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 0 && j!= 0 && (arr[i-1][j-1] != 0)) {
        i--; j--;

        if (arr[i][j] == player) {
            i++; j++;
            while (i != i_org) {
                arr[i][j] = player;
                i++; j++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating down-right diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i!= 8 && j != 8 && (arr[i+1][j + 1] != 0)) {
        i++;  j++;

        if (arr[i][j] == player) {
            i--;  j--;
            while (j != j_org) {
                arr[i][j] = player;
                i--;  j--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating up-right diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 0 && j != 8 && (arr[i - 1][j + 1] != 0)) {
        i--;  j++;

        if (arr[i][j] == player) {
            i++;  j--;
            while (j != j_org) {
                arr[i][j] = player;
                i++;  j--;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

    //updating down-left diagonal
    i = i_org;     j = j_org;     flag = 0;
    while (i != 8 && j != 0 && (arr[i + 1][j - 1] != 0)) {
        i++;  j--;

        if (arr[i][j] == player) {
            i--;  j++;
            while (j != j_org) {
                arr[i][j] = player;
                i--;  j++;
            }
            flag = 1;
        }
        if (flag == 1) break;
    }

}
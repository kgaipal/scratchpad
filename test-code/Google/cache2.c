int main() {

    static int x[5000][5000];

    for (int i = 0; i < 5000; i++) {

        for (int j = 0; j < 5000; j++) {

            x[j][i]++;

        }

    }

    return 0;

}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// Membuat bentukan untuk negara
struct Country {
    char name[24];
    int tier;
    int win;
};

// Membuat bentukan untuk grup
// Grup berisi array 4 negara
struct Group {
    char name;
    struct Country countries[4];
};

// Membuat bentukan untuk node tim
struct Team {
    char name[24];
    int tier;
    struct Team* next;
};

// Fungsi untuk menambahkan negara dari array ke grup
void addCountries(struct Group* group, struct Country countries[]) {
    for (int i = 0; i < 4; i++) {
        group->countries[i] = countries[i];
    }
}

// Fungsi untuk menjalankan pertandingan
void match(struct Country* country1, struct Country* country2) {
    int prob1 = 5 - country1->tier;
    int prob2 = 5 - country2->tier;
    int S = prob1 + prob2;
    int res = rand() % S;
    printf("%s vs %s\n", country1->name, country2->name);
    if (res < prob1) {
        printf("%s WINS\n", country1->name);
        country1->win++;
    }
    else {
        printf("%s WINS\n", country2->name);
        country2->win++;
    }
    printf("\n");
}

// Menjalankan pertandingan di fase grup dengan memanggil
// fungsi match
void group_stage(struct Group* group) {
    printf("Group %c \n\n", group->name);
    match(&(group->countries[0]), &(group->countries[1]));
    match(&(group->countries[2]), &(group->countries[3]));
    match(&(group->countries[0]), &(group->countries[2]));
    match(&(group->countries[1]), &(group->countries[3]));
    match(&(group->countries[0]), &(group->countries[3]));
    match(&(group->countries[1]), &(group->countries[2]));
}

// Fungsi untuk mengurutkan klasemen berdasarkan kemenangan
// menggunakan metode bubble sort
// dan mencetak klasemen grup
void group_stage_result(struct Group* group) {
    int switched = 1;
    struct Country hold;
    int i = 0;
    int j = 0;
    int size = 4;
    size -= 1;
    for (i = 0; i < size && switched; i++) {
        switched = 0;
        for (j = 0; j < size - i; j++) {
            if (group->countries[j].win < group->countries[j + 1].win) {
                switched = 1;
                hold = group->countries[j];
                group->countries[j] = group->countries[j + 1];
                group->countries[j + 1] = hold;
            }
        }
    }
    printf("Klasemen grup %c \n", group->name);
    for (int i = 0; i < 4; i++) {
        printf("%d. %s \n", i+1, group->countries[i].name);
    }
    printf("\n\n");
}

// Fungsi untuk membuat node tim
struct Team* new(struct Country country) {
    struct Team* team = (struct Team*)malloc(sizeof(struct Team));
    strcpy(team->name, country.name);
    team->tier = country.tier;
    team->next = NULL;
    return team;
}

// Fungsi untuk menambahkan node tim ke linked list tim
void addTeam(struct Team** head, struct Team* team) {
    if (*head == NULL){
        *head = team;
    } else {
        team->next = *head;
        *head = team;
    }
}

// Fungsi untuk menghapus node tim dari linked list tim
void removeTeam(struct Team** head, char name[]) {
    struct Team* team = *head;
    if (strcmp(team->name, name) == 0) {
        *head = team->next;
        free(team);
    }
    else {
        while (strcmp(team->next->name, name) != 0) {
            team = team->next;
        }
        struct Team* team2 = team->next;
        team->next = team2->next;
        free(team2);
    }
}

// Fungsi untuk menjalankan pertandingan di fase knockout
void knockOut(struct Team** head, struct Team* team1, struct Team* team2) {
    int prob1 = 5 - team1->tier;
    int prob2 = 5 - team2->tier;
    int S = prob1 + prob2;
    int res = rand() % S;
    printf("%s vs %s\n", team1->name, team2->name);
    if (res < prob1) {
        printf("%s WINS\n", team1->name);
        removeTeam(head, team2->name);
    }
    else {
        printf("%s WINS\n", team2->name);
        removeTeam(head, team1->name);
    }
    printf("\n");
}

// Fungsi untuk mencetak tim yang masih bertahan
void print(struct Team* head) {
    while(head!=NULL) {
        printf("%s\n", head->name);
        head = head->next;
    }
}

int main() {
    // Mengatur random seed dari waktu saat ini
    srand(time(0));
    // Membuat variabel negara-negara dan memasukkan datanya
    struct Country ITA = {"Italy", 1, 0},
        SWI = {"Switzerland", 2, 0},
        WAL = {"Wales", 3, 0},
        TUR = {"Turkey", 4, 0},
        BEL = {"Belgium", 1, 0},
        DEN = {"Denmark", 2, 0},
        RUS = {"Russia", 3, 0},
        FIN = {"Finland", 4, 0},
        NET = {"Netherlands", 1, 0},
        AUT = {"Austria", 2, 0},
        UKR = {"Ukraine", 3, 0},
        MKD = {"North Macedonia", 4, 0},
        ENG = {"England", 1, 0},
        CRO = {"Croatia", 2, 0},
        CZE = {"Czech", 3, 0},
        SCT = {"Scotland", 4, 0},
        SPA = {"Spain", 1, 0},
        SWE = {"Sweden", 2, 0},
        POL = {"Poland", 3, 0},
        SVK = {"Slovakia", 4, 0},
        FRA = {"France", 1, 0},
        POR = {"Portugal", 2, 0},
        GER = {"Germany", 3, 0},
        HUN = {"Hungary", 4, 0};

    // Mengelompokkan negara ke dalam array sesuai grup
    struct Country ACountries[] = {ITA, SWI, WAL, TUR};
    struct Country BCountries[] = {BEL, DEN, RUS, FIN};
    struct Country CCountries[] = {NET, AUT, UKR, MKD};
    struct Country DCountries[] = {ENG, CRO, CZE, SCT};
    struct Country ECountries[] = {SPA, SWE, POL, SVK};
    struct Country FCountries[] = {FRA, POR, GER, HUN};

    // Membuat grup-grup
    struct Group A = {'A'},
        B = {'B'},
        C = {'C'},
        D = {'D'},
        E = {'E'},
        F = {'F'};

    // Memasukkan negara-negara dari array ke dalam grup
    addCountries(&A, ACountries);
    addCountries(&B, BCountries);
    addCountries(&C, CCountries);
    addCountries(&D, DCountries);
    addCountries(&E, ECountries);
    addCountries(&F, FCountries);

    // Menjalankan fase grup
    group_stage(&A);
    group_stage_result(&A);
    group_stage(&B);
    group_stage_result(&B);
    group_stage(&C);
    group_stage_result(&C);
    group_stage(&D);
    group_stage_result(&D);
    group_stage(&E);
    group_stage_result(&E);
    group_stage(&F);
    group_stage_result(&F);

    // Membuat linked list dari node tim
    struct Team* teams = (struct Team*)malloc(sizeof(struct Team)); // tim yang bertahan
    // Membuat array untuk menyimpan node tim
    // Array dibuat agar bisa mengakses node berdasarkan index
    struct Team* teams_array[16];

    int j = 0;
    // Membuat node-node tim yang lolos dan memasukkannya ke dalam array
    for (int i = 0; i < 2; i++) {
        *(teams_array + j++) = new(A.countries[i]);
        *(teams_array + j++) = new(B.countries[i]);
        *(teams_array + j++) = new(C.countries[i]);
        *(teams_array + j++) = new(D.countries[i]);
        *(teams_array + j++) = new(E.countries[i]);
        *(teams_array + j++) = new(F.countries[i]);
    }
    *(teams_array + j++)  = new(A.countries[2]);
    *(teams_array + j++)  = new(B.countries[2]);
    *(teams_array + j++)  = new(E.countries[2]);
    *(teams_array + j++)  = new(F.countries[2]);

    // Menambahkan tim dari array node ke linked list
    for (int i = 0; i < j; i++) {
        addTeam(&teams, *(teams_array + i));
    }

    printf("Tim yang lolos fase grup\n");
    printf("------------------------\n");
    print(teams);

    printf("------- Round of 16 -------\n");
    knockOut(&teams, *(teams_array + 8), *(teams_array + 9));
    knockOut(&teams, *(teams_array + 7), *(teams_array + 15));
    knockOut(&teams, *(teams_array + 0), *(teams_array + 13));
    knockOut(&teams, *(teams_array + 1), *(teams_array + 14));
    knockOut(&teams, *(teams_array + 6), *(teams_array + 5));
    knockOut(&teams, *(teams_array + 10), *(teams_array + 3));
    knockOut(&teams, *(teams_array + 12), *(teams_array + 4));
    knockOut(&teams, *(teams_array + 11), *(teams_array + 2));

    // Mengurutkan kembali array berdasarkan tim yang lolos
    struct Team* team = teams;
    for (int i = 0; i < 8; i++) {
        *(teams_array + i) = team;
        team = team->next;
    }

    printf("------- Quarter final -------\n");
    knockOut(&teams, *(teams_array + 3), *(teams_array + 4));
    knockOut(&teams, *(teams_array + 2), *(teams_array + 5));
    knockOut(&teams, *(teams_array + 1), *(teams_array + 6));
    knockOut(&teams, *(teams_array + 0), *(teams_array + 7));

    // Mengurutkan kembali array berdasarkan tim yang lolos
    team = teams;
    for (int i = 0; i < 4; i++) {
        *(teams_array + i) = team;
        team = team->next;
    }

    printf("------- Semi final -------\n");
    knockOut(&teams, *(teams_array + 0), *(teams_array + 3));
    knockOut(&teams, *(teams_array + 1), *(teams_array + 2));

    // Mengurutkan kembali array berdasarkan tim yang lolos
    team = teams;
    for (int i = 0; i < 2; i++) {
        *(teams_array + i) = team;
        team = team->next;
    }

    printf("------- Final -------\n");
    knockOut(&teams, *(teams_array + 0), *(teams_array + 1));
    printf("Champion: ");
    print(teams);
}

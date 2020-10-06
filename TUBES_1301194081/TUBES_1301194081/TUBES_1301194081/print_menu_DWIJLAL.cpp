#include "header_DWIJLAL.h"

void cls() {
    system("cls");
}

void mainmenu (ListArticle &L, ListKeyword &Q) {
    int kode;
    do {
        cout << "================================================ \n";
        cout << "--------------Welcome to Our Program------------ \n";
        cout << "================================================ \n";
        cout << "1. Insert new Data Article \n";
        cout << "2. Insert new Keyword \n";
        cout << "3. Insert connection between article and keyword \n";
        cout << "4. Delete certain article \n";
        cout << "5. Delete article based on article's title \n";
        cout << "6. Delete keyword based on keyword's name \n";
        cout << "7. Print all articles and keywords \n";
        cout << "8. Print all keywords \n";
        cout << "9. Print all articles \n";
        cout << "10. Print Article based on many of study field \n";
        cout << "11. Print articles based on keyword \n";
        cout << "12. Print keywords based on article \n ";
        cout << "0. Quit \n";
        cout << "================================================ \n";
        cout << "----------------Data Article Program------------ \n";
        cout << "================================================ \n";
        cout << "enter code : ";
        cin >> kode;
        switch(kode) {
            case 0 : break;
            case 1 : menu_Insert_Article(L);
                     break;
            case 2 : menu_Insert_Keyword(Q);
                     break;
            case 3 : menu_Insert_connection(L,Q);
                     break;
            case 4 : menu_delete_certain_article(L);
                     break;
            case 5 : menu_delete_article(L);
                     break;
            case 6 : menu_delete_keyword(L,Q);
                     break;
            case 7 : system("cls");
                     printArticle_Keyword(L,Q);
                     break;
            case 8 : printKeyword(Q);
                     break;
            case 9 : printArticle(L);
                     break;
            case 10: printkajian_terbanyak_terdikit(L);
                     break;
            case 11: menu_print_article_baseonkeyword(L,Q);
                     break;
            case 12: menu_print_keyword_baseonarticle(L,Q);
                     break;
            default : cout << "Wrong Input Code ! \n";
                     break;
        }
        system("pause");
        system("CLS");
    } while ((kode != 0));
}

void menu_Insert_Article (ListArticle &L) {
    system("cls");
    string judul;
    string penulis;
    string publisher;
    string tahun;
    string abstrak;
    string again;
    do {
        do {
            //Get line untuk string yang bisa spasi
            cout << "type 'cancel' in all data article to cancel adding data article \n";
            cout << "Judul : ";
            getline(cin,judul);
            getline(cin,judul);
            cout << "\n";
            cout << "Penulis : ";
            getline(cin,penulis);
            cout << "\n";
            cout << "Publisher : ";
            getline(cin,publisher);
            cout << "\n";
            cout << "Abstrak : ";
            getline(cin,abstrak);
            cout << "\n";
            cout << "Tahun Posting : ";
            getline(cin,tahun);
            cout << "\n";
        } while (judul == "");
        if (judul != "cancel") {
            address_article P;
            createArticle(P,judul,penulis,publisher,tahun,abstrak);
            insertArticle(L,P);
            cout << "---Data Article has been add--- \n";
            system("pause");
            do {
                cout << "Insert new Data Article (yes/no) ? ";
                cin >> again;
            } while ((again != "yes") && (again != "no"));
        } else {
            cout << "Input has been cancel \n";
            again = "no";
        }
    } while (again != "no");
}

void menu_Insert_Keyword (ListKeyword &Q) {
    system("cls");
    string X;
    string again;
    do {
        do {
            cout << "type 'cancel' to cancel adding Keyword \n";
            cout << "Keyword : ";
            getline(cin,X);
            getline(cin,X);
        } while (X == "");
        if (X != "cancel") {
            address_keyword P;
            createKeyword(P,X);
            insertKeyword(Q,P);
            cout << "---Keyword has been add--- \n";
            system("pause");
            do {
                cout << "Insert new keyword (yes/no) ? ";
                cin >> again;
            } while ((again != "yes") && (again != "no"));
        } else {
            cout << "Input has been cancel \n";
            again = "no";
        }
    } while (again != "no");
}
void menu_Insert_connection (ListArticle &L, ListKeyword &Q) {
    string judul, keyword;
    address_article P;
    address_keyword R;
    bool error;
    string again;
    if ( (is_empty_keyword(Q)) || (is_empty_article(L)) ) {
        cout << "no data, please insert first in menu \n";
    } else {
         do {
            cls();
            error = false;
            printArticle_Keyword(L,Q);
            cout << "type 'cancel' to cancel adding connection \n";
            cout << "enter article's title : ";
            getline(cin,judul);
            getline(cin,judul);
            P = searchArticle(L,judul);
            if (P != nil) {
                cout << "available keyword name insert to " << judul << " : " <<endl;
                availablekeyword(P,Q);
                cout << "enter keyword : ";
                getline(cin,keyword);
            }
            R = seachKeyword_In_Listkeyword(Q,keyword);
            if ( (P == nil) || (R == nil)) {
                error = true;
                if (judul == "cancel") {
                    cout << "insert connection has been cancel \n";
                    again = "no";
                } else {
                    cout << "enter correct article's title or keyword \n";
                }
            } else {
                if (validation_double(P,R)) {
                    cout << "Article already have that keyword! \n";
                    error = true;
                } else {
                    connection(L,Q,judul,keyword);
                    cout << "connection is successful \n";
                }
            }
            if (!error) {
            do {
                cout << "Insert new connection (yes/no) ?";
                cin >> again;
                } while ((again != "yes") && (again != "no"));
            } else {
            if (judul != "cancel") system ("pause");
            }
            if (judul == "cancel") {
                error = false;
                again = "no";
            }
        } while ( (error) || (again == "yes"));
    }
}

void menu_delete_certain_article (ListArticle &L) {
    string judul;
    address_article P;
    bool error = false;
    if (!is_empty_article(L)) {
        do {
            error = false;
            cls();
            printArticle(L);
            P = searchArticle(L,judul);
            if (judul != "cancel") {
                if (P == nil) {
                    cout << "article's title not found \n";
                    error = true;
                } else {
                    deleteArticle(L,P,judul);
                    delete P;
                }
            }
            if (error){
                system("pause");
            }
        } while (error);
    } else {
        cls();
        cout << "empty article ! \n";
    }
}
void menu_delete_article (ListArticle &L) {
 string judul;
    address_article P;
    bool error = false;
    if (!is_empty_article(L)) {
        do {
            error = false;
            cls();
            printArticle(L);
            cout << "type 'cancel' to cancel delet tweet \n";
            cout << "enter article's title : ";
            getline(cin,judul);
            getline(cin,judul);
            P = searchArticle(L,judul);
            if (judul != "cancel") {
                if (P == nil) {
                    cout << "article's title not found \n";
                    error = true;
                } else {
                    deleteArticle(L,P,judul);
                    delete P;
                }
            }
            if (error){
                system("pause");
            }
        } while (error);
    } else {
        cls();
        cout << "empty article ! \n";
    }
}
void menu_delete_keyword (ListArticle &L, ListKeyword &Q) {
    string keyword;
    address_keyword P;
    bool error = false;
    if (!is_empty_keyword(Q)) {
        do {
            error = false;
            cls();
            printKeyword(Q);
            cout << "type 'cancel' to cancel delete keyword \n";
            cout << "enter keyword : ";
            getline(cin,keyword);
            getline(cin,keyword);
            P = seachKeyword_In_Listkeyword(Q,keyword);
            if (keyword != "cancel") {
                if (P == nil) {
                    cout << "keyword not found \n";
                    error = true;
                } else {
                    deleteKeyword(L,Q,P,keyword);
                    delete P;
                    cout << "keyword has been deleted \n";
                }
            }
            if (error == true) {
                system("pause");
            }
        } while (error);
    } else {
        cls();
        cout << "empty keyword ! \n";
    }
}
void menu_print_article_baseonkeyword (ListArticle L, ListKeyword Q) {
    bool error;
    string keyword;
    address_keyword P;
    do {
        error = false;
        cls();
        printKeyword(Q);
        cout << "type 'cancel' to cancel print Article \n";
        cout << "enter keyword name : ";
        getline(cin,keyword);
        getline(cin,keyword);
        if (keyword != "cancel") {
            P = seachKeyword_In_Listkeyword(Q,keyword);
            if (P == nil) {
                cout << "keyword not found! \n";
                error = true;
            } else {
                printArticle_base_on_keyword(L,Q,keyword);
            }
        } else {
            cout << "print has been cancel \n";
        }
        if (error == true) {
            system("pause");
        }
    } while (error);
}
void menu_print_keyword_baseonarticle (ListArticle L, ListKeyword Q) {
    bool error;
    string judul;
    address_article P;
    do {
        error = false;
        cls();
        printArticle(L);
        cout << "type 'cancel' to cancel print Keyword \n";
        cout << "enter article's name : ";
        getline(cin,judul);
        getline(cin,judul);
        if (judul != "cancel") {
            P = searchArticle(L,judul);
            if (P == nil) {
                cout << "article's title not found \n";
                error = true;
            } else {
                printKeyword_base_on_article(L,Q,judul);
            }
        } else {
            cout << "print has been cancel \n";
        }
        if (error == true) {
            system("pause");
        }
    } while (error);
}

#include "header_DWIJLAL.h"

void createList (ListArticle &L) {
    first(L) = nil;
    last(L) = nil;
}

void createListKeyword (ListKeyword &Q) {
    first(Q) = nil;
}


void createArticle (address_article &P, string judul, string penulis, string publisher, string tahun, string abstrak) { //alokasi
    P = new elmArticle;
    judul(P) = judul;
    penulis(P) = penulis;
    publisher(P) = publisher;
    tahun(P) = tahun;
    abstrak(P) = abstrak;
    relasi(P)= nil;
    next(P) = nil;
    linked(P) = 0;
}

void createKeyword (address_keyword &C,  string keyword) {
    C = new elmKeyword;
    keyword(C) = keyword;
    next(C) = nil;
    prev(C) = nil;
    relasi(C)= nil;
    linked(C) = 0;
}

void createRelasi (address_relasi &Q, address_keyword C){
    Q = new elmRelasi;
    to_keyword(Q) = C;
    next(Q) = nil;
    relasi(C)=Q;
}

bool is_empty_article (ListArticle L) {
    return ((first(L) == nil) && (last(L) == nil));
}

bool is_empty_keyword (ListKeyword Q) {
    return first(Q) == nil;
}

bool is_empty_relasi (address_article R) {
    return relasi(R) == nil;
}

void insertKeyword (ListKeyword &Q, address_keyword C) {
    if (is_empty_keyword(Q)) {
        first(Q) = C;
    } else {
        address_keyword R = first(Q);
        while (next(R) != nil) {
            R = next(R);
        }
        next(R) = C;
        prev(C) = R;
        next(C) = nil;
    }
}
void insertArticle (ListArticle &L, address_article P) {
    if (is_empty_article(L)) {
        first(L) = P;
        last(L) = P;
        next(P) = P;
    } else {
        address_article R = last(L);
        next(R) = P;
        next(P) = first(L);
        last(L) = P;
    }
}
void insertRelasi (address_article &R, address_relasi Q) {
    if (is_empty_relasi(R)) {
        relasi(R) = Q;
    } else {
        address_relasi P = relasi(R);
        while (next(P) != nil) {
            P = next(P);
        }
        next(P) = Q;
        next(Q) = nil;
    }
}
address_article searchArticle (ListArticle L , string judul) {
    address_article P = first(L);
    if (!is_empty_article(L)){
        do{
            P = next(P);
        }while ((P != first(L) ) && (judul(P) != judul));
    }
    return P;
}
address_keyword seachKeyword_In_Listkeyword (ListKeyword Q, string keyword) {
    address_keyword C = first(Q);
    while (((C) != nil) && (keyword(C) != keyword)) {
        C = next(C);
    }
    return C;
}

void connection (ListArticle &L, ListKeyword &L1,string judul, string keyword) {
    address_article P = searchArticle(L, judul);
    address_keyword Q = seachKeyword_In_Listkeyword(L1, keyword);
    address_relasi R;
    if ((P == nil) || (Q == nil)) {
        cout << "Article or Keyword is not in list \n";
    } else {
        createRelasi(R,Q);
        insertRelasi(P,R);
        linked(P)++;
        linked(Q)++;
    }
}

void printArticle (ListArticle L) {
    if (is_empty_article(L)) {
        cout << "Article is empty \n";
    } else {
        address_article P = first(L);
        cout << "Article : \n";
        cout << endl;
        do {
            cout << ". \t Judul : " << judul(P) << endl;
            cout << ". \t Penulis : " << penulis(P) << endl;
            cout << ". \t Publisher : " << publisher(P) << endl;
            cout << ". \t Tahun Posting : " << tahun(P) << endl;
            cout << ". \t Abstrak : " << abstrak(P) << endl;
            cout << endl;
            P = next(P);
        } while (P != first(L));
        cout << endl;
    }
}
void printKeyword (ListKeyword Q) {
    if (!is_empty_keyword(Q)) {
        address_keyword P = first(Q);
        cout << "Keyword : \n";
        int i = 1;
        while (P != nil) {
            cout << i << "." << keyword(P) << " ";
            P = next(P);
            i++;
        }
        cout << endl;
    } else {
        cout << "Keyword is empty\n";
    }
}
void printArticle_Keyword(ListArticle L, ListKeyword C) {
    if (!is_empty_article(L)) {
        address_article P = first(L);
        address_relasi R;
        int i = 1;
        cout << " Data Article : \n";
        do {
            cout << i << ". \t Judul : " << judul(P) << endl;
            cout << ". \t Penulis : " << penulis(P) << endl;
            cout << ". \t Publisher : " << publisher(P) << endl;
            cout << ". \t Tahun Posting : " << tahun(P) << endl;
            cout << ". \t Abstrak : " << abstrak(P) << endl;
            R = relasi(P);
            // Print semua keyword
            if (R != nil) {
                cout << "\t keyword : ";
                while (R != nil) {
                    cout << keyword(to_keyword(R)) << " ";
                    R = next(R);
                }
            } else {
                cout << ". \t doesn't connect with any keyword";
            }
            // end
            cout <<endl;
            i++;
            P = next(P);
        } while (P != first(L));
    } else {
        cout << "Data Article is empty \n";
    }
    if (!is_empty_keyword(C)) {
        address_keyword Q = first(C);
        cout << "Keyword : \n";
        int j = 1;
        while (Q != nil) {
            cout << j << "." << keyword(Q) << "\n";
            Q = next(Q);
            j++;
        }
        cout << endl;
    } else {
        cout << "Keyword is empty \n";
    }
}
void printkajian_terbanyak_terdikit(ListArticle L) {
    // mencetak article dengan bidang kajian terbanyak dan terdikit
    int maks = 0;
    int mini = 0;
    if (first(L) != nil) {
        address_article P = first(L);
        maks = linked(P);
        mini = linked(P);
        /** mencari maksimal dan minimum**/
        do {
            if (linked(P) >= maks) {
                maks = linked(P);
            }
            if (linked(P) < mini) {
                mini = linked(P);
            }
            P = next(P);
        } while (P != first(L));
        /**=================**/
        if ((maks == 0) && (mini == 0)) {
            cout << "Article is empty or no connection with keyword \n";
        } else {
            /** mencetak article yang linkednya berjumlah maksimal **/
            P = first(L);
            int i = 1;
            cout << "Article dengan bidang kajian terbanyak : \n";
            do {
                if (linked(P) == maks) {
                    cout << ". \t Judul : " << judul(P) << endl;
                    cout << ". \t Penulis : " << penulis(P) << endl;
                    cout << ". \t Publisher : " << publisher(P) << endl;
                    cout << ". \t Tahun Posting : " << tahun(P) << endl;
                    cout << ". \t Abstrak : " << abstrak(P) << endl;
                }
                P = next(P);
                i++;
            } while (P != first(L));
            cout << endl;
             /** mencetak article yang linkednya berjumlah minimal **/
            P = first(L);
            int j = 1;
            cout << "Article dengan bidang kajian terdikit : \n";
            do {
                if (linked(P) == mini) {
                    cout << ". \t Judul : " << judul(P) << endl;
                    cout << ". \t Penulis : " << penulis(P) << endl;
                    cout << ". \t Publisher : " << publisher(P) << endl;
                    cout << ". \t Tahun Posting : " << tahun(P) << endl;
                    cout << ". \t Abstrak : " << abstrak(P) << endl;
                }
                P = next(P);
                j++;
            } while (P != first(L));
            cout <<endl;
            /**=================**/
        }
    } else {
        cout << "Article is empty \n";
    }
}

void printArticle_base_on_keyword(ListArticle L, ListKeyword Q, string keyword) {
// mencetak article berdasarkan keyword tertentu
    if (is_empty_article(L) && is_empty_keyword(Q)) {
        cout << "Data is not available";
    } else if (is_empty_article(L)) {
        cout << "Article List didn't add yet \n";
    } else if (is_empty_keyword(Q)) {
        cout << "Keyword List didn't add yet \n";
    } else {
        address_article P = first(L);
        address_keyword R = seachKeyword_In_Listkeyword(Q,keyword);
        if (R != nil) {
            do {
                /**Mencari relasi yang terhubung dengan keyword yang telah didapatkan di R**/
                address_relasi A = relasi(P);
                while (A != nil) {
                    if (to_keyword(A) == R) {
                        cout << ". \t Judul : " << judul(P) << endl;
                        cout << ". \t Penulis : " << penulis(P) << endl;
                        cout << ". \t Publisher : " << publisher(P) << endl;
                        cout << ". \t Tahun Posting : " << tahun(P) << endl;
                        cout << ". \t Abstrak : " << abstrak(P) << endl;
                    }
                    A = next(A);
                }
                /**=================**/
                P = next(P);
            } while (P != first(L));
            cout << endl;
        } else {
            cout << "keyword not found \n";
        }
    }
}

void printKeyword_base_on_article(ListArticle L, ListKeyword Q, string judul) {
// mencetak keyword berdasarkan judul artikel tertentu
    if (is_empty_article(L) && is_empty_keyword(Q)) {
        cout << "Data is not available";
    } else if (is_empty_article(L)) {
        cout << "Article List didn't add yet \n";
    } else if (is_empty_keyword(Q)) {
        cout << "Keyword List didn't add yet \n";
    } else {
        address_article R = searchArticle(L,judul);
        if (R != nil) {
            address_relasi A = relasi(R);
            while (A != nil) {
                cout << keyword(to_keyword(A)) << " ";
                A = next(A);
            }
            /**=================**/
            cout << endl;
        } else {
            cout << "Article not found \n";
        }
    }
}


void deleteArticle (ListArticle &L, address_article P, string judul) {
    address_article R = first(L);
    if (first(L) != nil) {
        P = searchArticle(L,judul);
        if (P != nil) {
            address_relasi Q = relasi(P);
            while (Q != nil) {
                if (to_keyword(Q) != nil) {
                    linked(to_keyword(Q))--;
                    to_keyword(Q) = nil;
                }
                Q = next(Q);
            }
            if ((P == first(L)) && (P == last(L))) {
                next(P) = nil;
                createList(L);
            } else if (P == first(L)) {
                first(L) = next(P);
                next(last(L)) = first(L);
                next(P) = nil;
            } else {
                while (next(R) != P && R != nil) {
                    R = next(R);
                }
                if(R != nil ){
                    next(R) = next(P);
                    next(P) = nil;
                }
            }
            cout << "Article has been deleted \n";
        } else {
            cout << "Article not found \n";
        }
    } else {
        cout << "Empty Article \n";
    }
}
void deleteKeyword (ListArticle &L, ListKeyword &Q, address_keyword &P, string keyword) {
    address_keyword R = first(Q);
    if (R != nil) {
        P = seachKeyword_In_Listkeyword(Q,keyword);
        if (P != nil) {
            /**Delete child yang to_keywordnya keyword**/
            address_article S = first(L);
            address_relasi A;
            address_relasi B;
            address_relasi temp;
            while (S != nil) {
                A = relasi(S);
                while (A != nil) {
                    temp = next(A);
                    if (to_keyword(A) == P) {
                        /**delete relasi**/
                        if (A == relasi(S)) {
                            relasi(S) = next(A);
                            next(A) = nil;
                        } else {
                            B = relasi(S);
                            while (next(B) != A) {
                                B = next(B);
                            }
                            next(B) = next(A);
                            next(A) = nil;
                        }
                    }
                    A = temp;
                }
                S = next(S);
            }
            /**=================**/
            /** delete keyword **/
            if (P == first(Q)) {
                first(Q) = next(P);
                next(P) = nil;
            }else{
                while (next(R) != P) {
                    R = next(R);
                }
                next(R) = next(P);
                if(next(P)!=nil){
                    prev(next(P)) = R;
                }
                next(P) = nil;
                prev(P) = nil;
            }
            /**=================**/

        } else {
            cout << "Keyword not found \n";
        }
    }
}

bool validation_double (address_article P, address_keyword R) {
//mengvalidasi keyword yang terindikasi double dalam satu artcile
/** proses : mencari judul artikel dalam list article, mencari keyword dalam list keyword, lalu mengecek child dari
judul article tsb apakah ada yang terhubung dengan keyword, jika tidak maka kirimkan false, true jika sebaliknya **/
    address_relasi A = relasi(P);
    bool error = false;
    while ((A != nil) && (error != true)) {
        if (to_keyword(A) == R) {
            error = true;
        }
        A = next(A);
    }
    return error;
}
void availablekeyword (address_article P,ListKeyword Q) {
//mencetak keyword yang tersedia di konek
/** proses : mengecek satu persatu keyword, jika keyword tersebut ditunjuk oleh relasi P
maka tidak bisa dicetak, begitu sebaliknya **/
    address_keyword R = first(Q);
    int i = 1;
    while (R != nil) {
        if (!validation_double(P,R)) {
            cout << "\t" << i << ". " << keyword(R) << endl;
            i++;
        }
        R = next(R);
    }
}

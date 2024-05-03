/*
    ポインタについて
    制作　：てぐりむ
    制作日：2024/5/3

    譲渡禁止、このコメントを除く改変は自由です

    ソフ演II第4週までの内容です

    a -> b は aとbの値が等価であることを示しています

    コメントには主に下記の種類があります
    //           これは説明です
    //??         期待する動作をしていません
    // !!EROOR!! このコード又は関数はエラーになるので実行してはいけません

    フィードバックは必ずお願いします（ここが分かりやすいor分かりにくい、難しい、書かれてないけどここが分からない等々）
    怪しい箇所を見つけた場合、至急てぐりむ(@integlim)のDMまで
*/

#include <stdio.h>

#define N   5

// 宣言
void section1() {
    int x = 1; // xはint型
    int *p; // pはint型ポインタ
    p = &x; // &xはxのアドレス
    *p = 2;
    printf("x = %d\n", x);
    /*
        p  -> &x　：アドレス
        *p ->  x　：値
        こんな感じの対応
    */
}


// 初期化
void section2() {
    int n = 0;
    int *p = &n; // p -> &n です

    int a[N] = {0}; // ここで a は配列の先頭要素のアドレスを示すポインタ型定数
    int *ip = a; // ip -> a です
    ip[1] = 1;
    ip++;
    printf("*ip = ip[0] = %d\n", *ip);
}

// !!ERROR!! 領域の確保
// void bad_section2() {
//     int *p;
//     *p = 1; // 未定義動作、ポインタの指す領域は確保する必要があります
//      // ポインタの宣言のみではポインタの指す領域は確保されていないことに注意しましょう
// }


// 演算
void section3() {
    char a[] = "MASTER"; // a は配列の先頭要素のアドレスを示すポインタ型定数
    // !!ERROR!!    a++; // a は定数なので、変更できません
    a[2] = 'E';
    *(a+3) = 'A';
    4[a] = 'Z';
    char *p = a;
    p[5] = 'Y';
    p += 2; // p は変数なので、変更できます
    printf("p = %s\n", p); // *p は p の指す場所の値を取得するための演算であり、*p では文字列を指すポインタでないので渡せません
}

// !!ERROR!! 配列の演算
// void bad_section3() {
//     int a[N], b[N];
//     a = b; // 前述のように a は定数なので代入自体が不可です
// }


// 型の確認
void section4() {
    // 用意するポインタは示す変数の型に合うようにしましょう
    int a = 0;
    int *pa = &a;

    int b[N] = {0};
    int *pb = b;

    char c[N][N] = {0};
    char (*pc)[N] = c;
}


// section5で呼び出す関数
void mul_2(int *pa) {
    *pa *= 2;
}
void let_1(int *array_b) { // ここの引数は array_b[], array_b[N]などとしても同じです。
    array_b[0] = 1;
}

// 参照渡し
void section5() {
    int a = 3;
    mul_2(&a); // pa -> &a です。section2の初期化と一緒です
    printf("a = %d\n", a);

    int b[N] = {0};
    let_1(b); // array_b -> b です。これもsection2の初期化と一緒です
    printf("b[0] = %d\n", b[0]);
}


// section6で呼び出す変数と関数
int A_0[N][N] = {0};
int A_1[N][N] = {1};

void let_2(int (*a)[N]) { // a -> x です
    a = A_1; //?? a -> A_1 と上書きしています。これでは x に書き込みが出来ません
    a[0][0] = 2;
}
void let_3(int (**a)[N]) { // a -> &x です
    *a = A_1; // これなら x に書き込みが出来ますね
    /*
        a       *a      **a
    
        &x      x

                A_1

        イメージはこんな感じです。縦で等価なものを示しています
    */
    (*a)[0][0] = 3;
}

// 参照渡しの応用
void section6() {
    int (*x)[N]; // section4、型の確認と一緒です
    x = A_0;

    let_2(x); // a -> x です
    printf("  x[0][0] = %d\n",   x[0][0]); //?? let_2 を確認しましょう
    printf("A_1[0][0] = %d\n", A_1[0][0]);

    let_3(&x); // *a -> &x です
    printf("  x[0][0] = %d\n",   x[0][0]);
    printf("A_1[0][0] = %d\n", A_1[0][0]);
}


int main(void) {
    section1();
    section2();
    section3();
    section4();
    section5();
    section6();
    return 0;
}

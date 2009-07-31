#ifndef _CONFIG_H_
#define _CONFIG_H_

/* UTF8 入出力 */
#define UTF8_INPUT_ENABLE
#define UTF8_OUTPUT_ENABLE

/* Shift_JIS 範囲外の文字を、CP932 で同値な文字に読み換える */
#define SHIFTJIS_CP932

/* オプションで入力を指定した時に、文字コードを固定する */
#define INPUT_CODE_FIX

/* --overwrite オプション */
/* by Satoru Takabayashi <ccsatoru@vega.aichi-u.ac.jp> */
#define OVERWRITE

/* --cap-input, --url-input オプション */
#define INPUT_OPTION

/* --numchar-input オプション */
#define NUMCHAR_OPTION

/* --debug, --no-output オプション */
#define CHECK_OPTION

/* JIS X0212 */
#define X0212_ENABLE

/* --exec-in, --exec-out オプション
 * pipe, fork, execvp あたりが無いと動きません。
 * MS-DOS, MinGW などでは undef にしてください
 * child process 終了時の処理がいいかげんなので、
 * デフォルトで無効にしています。
 */
/* #define EXEC_IO */

/* SunOS の cc を使うときは undef にしてください */
#define ANSI_C_PROTOTYPE

/* int が 32bit 未満の環境で NUMCHAR_OPTION を使うには、
 * コメントを外してください。
 */
/* #define INT_IS_SHORT */


#if defined(INT_IS_SHORT)
typedef long nkf_char;
typedef unsigned char nkf_nfchar;
#else
typedef int nkf_char;
typedef int nkf_nfchar;
#endif

/* Unicode Normalization */
#define UNICODE_NORMALIZATION

#ifndef WIN32DLL
/******************************/
/* デフォルトの出力コード選択 */
/* Select DEFAULT_CODE */
#define DEFAULT_CODE_JIS
/* #define DEFAULT_CODE_SJIS */
/* #define DEFAULT_CODE_EUC */
/* #define DEFAULT_CODE_UTF8 */
/******************************/
#else
#define DEFAULT_CODE_SJIS
#endif

#if defined(NUMCHAR_OPTION) && !defined(UTF8_INPUT_ENABLE)
#define UTF8_INPUT_ENABLE
#endif

#ifdef UNICODE_NORMALIZATION
#ifndef UTF8_INPUT_ENABLE
#define UTF8_INPUT_ENABLE
#endif
#define NORMALIZATION_TABLE_LENGTH 942
#define NORMALIZATION_TABLE_NFC_LENGTH 3
#define NORMALIZATION_TABLE_NFD_LENGTH 9
struct normalization_pair{
    const nkf_nfchar nfc[NORMALIZATION_TABLE_NFC_LENGTH];
    const nkf_nfchar nfd[NORMALIZATION_TABLE_NFD_LENGTH];
};
#endif

#endif /* _CONFIG_H_ */

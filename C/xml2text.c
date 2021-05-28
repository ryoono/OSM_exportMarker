/*
* .osm.xmlより、信号機の緯度経度を.txtに書き出す
* http://d.hatena.ne.jp/l1o0/20110223/1298465520
* ↑めっちゃ参考にした(コピペ...)
*
* $ ./xml2text [読み込む.osm.xmlのURL] [書き出す.txtのURL]
*
* libxml2がインストールされていないとコンパイルエラーが発生します
*/

#include <stdio.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

int  processNode( xmlTextReaderPtr reader );
void export_text( xmlTextReaderPtr reader );

char *text_name;

int main( int argc, char **argv){

  //処理用および書き出し用
  //よくわからんけど xmlTextReaderPtrはポインタなのか上手に保存できないため
  //書き出し用に export_readerを使用する
  xmlTextReaderPtr reader;
  xmlTextReaderPtr export_reader;

  char *input_file;
  int   ret = 0;
  int   update_count = 0;

  FILE *fp;

  if (argc != 3) {
    printf("ζ*'ヮ')ζ <コマンドライン引数の数が違うかなーって\n");
    return 1;
  }

  input_file = argv[1];
  text_name  = argv[2];

  /*--=-=-*#*#@@ おまじない @@#*#*-=-=--*/
  LIBXML_TEST_VERSION;

  /* Read document */
  reader        = xmlReaderForFile(input_file, NULL, 0);
  export_reader = xmlReaderForFile(input_file, NULL, 0);

  if (NULL == reader) {
    fprintf(stderr, "Failed to parse %s\n", input_file);
    return 1;
  }

  //.txtファイルを初期化する
  fp = fopen( text_name, "w");
  fclose( fp );

  printf("( ´－｀) .｡oO（解析中...)\n");
  /* Parse XML */
  while( 1 == (ret = xmlTextReaderRead(reader)) ){

    int a = 0;
    a = processNode(reader);
    //タグが "node"だった場合
    if( a == 0 ){
      xmlTextReaderRead( export_reader );
      //溜まっていたアップデート
      if( update_count ){
        for( int i=0; i<update_count; i++ )xmlTextReaderRead( export_reader );
        update_count = 0;
      }
    }
    else{
      //nodeじゃない場合は export_readerを更新しないため、カウントしておく
      update_count++;
      if( a == 1 ){
        export_text( export_reader );
      }
    }
  }

  if (0 != ret) {
    fprintf(stderr, "%s : failed to parse\n", input_file);
  }

  printf("ｷﾀ━━━━━━━━━━━━━━━(ﾟ∀ﾟ)━━━━━━━━━━━━━━━!!");
  /* Free reader */
  xmlFreeTextReader(reader);
  xmlFreeTextReader(export_reader);

  xmlCleanupParser();

  return 0;
}


/*
* xmlを解析する
* 返り値
*   -1 ... タグ名が "node", "tag"以外の場合("tag"でかつ欲しい情報が無い場合を含む)
*    0 ... タグ名が "node"の場合
*    1 ... タグ名が "tab"で k="highway" v="traffic_signals"を含んでいる場合(信号機がある場合)
*/
int processNode( xmlTextReaderPtr reader ){

  const xmlChar *name;

  int   ret = 0;
  char  count = 0;

  FILE  *fp;

  /* Print node infos */
  name = xmlTextReaderConstName(reader);
  if( NULL == name ){
    name = BAD_CAST "--";
  }

  //タグが "node"の場合
  if( xmlStrEqual( xmlCharStrdup("node"), name) ){
    return 0;
  }
  //タグが "tag"の場合
  if( !xmlStrEqual( xmlCharStrdup("tag"), name) ){
    return -1;
  }

  //k="highway" v="traffic_signals"を探す
  if (1 == xmlTextReaderHasAttributes(reader)) {
    ret = xmlTextReaderMoveToFirstAttribute(reader);
    while( 1 == ret) {

      //k="highway"の検索
      if( xmlStrEqual( xmlCharStrdup("k"), xmlTextReaderConstName(reader))){
        if( xmlStrEqual( xmlCharStrdup("highway"), xmlTextReaderConstValue(reader))){
          count += 1;
        }
      }

      //v="traffic_signals"の検索
      if( xmlStrEqual( xmlCharStrdup("v"), xmlTextReaderConstName(reader))){
        if( xmlStrEqual( xmlCharStrdup("traffic_signals"), xmlTextReaderConstValue(reader))){
          count += 10;
        }
      }
      ret = xmlTextReaderMoveToNextAttribute(reader);
    }
  }

  //k="highway" v="traffic_signals"が存在した場合lat, lonを出力する
  if( count == 11 ){
    return 1;
  }
  return -1;
}

/*
* readerの緯度経度を.txtで書き出す
*/
void export_text( xmlTextReaderPtr reader ){

  FILE *fp;
  static const xmlChar *lat;
  static const xmlChar *lon;

  int ret = 0;

  if (1 == xmlTextReaderHasAttributes(reader)) {
    ret = xmlTextReaderMoveToFirstAttribute(reader);

    while(1 == ret) {

      //lat="???" lon="???"の検索
      if( xmlStrEqual( xmlCharStrdup("lat"), xmlTextReaderConstName(reader))){
        lat = xmlTextReaderConstValue(reader);
      }
      if( xmlStrEqual( xmlCharStrdup("lon"), xmlTextReaderConstName(reader))){
        lon = xmlTextReaderConstValue(reader);
      }
      ret = xmlTextReaderMoveToNextAttribute(reader);
    }
  }

  if( xmlStrlen(lat) > 0 && xmlStrlen(lon) > 0 ){

    fp = fopen( text_name, "a");
    fprintf( fp, "%s\n%s\n", lat, lon);
    fclose( fp );
    //printf("lat = %s, lon = %s\n", lat, lon);
  }

  return;
}

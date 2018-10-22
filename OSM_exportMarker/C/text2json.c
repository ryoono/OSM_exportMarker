/*
* xml2textで変換した.txtを.jsonに変換する
* https://www.ipentec.com/document/json-format
* ↑参考
*
* $ text2json [.txt]
*/

#include <stdio.h>

int main( int argc, char **argv){

  char *input_file;
  char *output_file;
  char s[256];
  char count = 0;
  char firstFlag = 1;
  FILE *input, *output;

  if( argc != 2 ){
    printf("コマンドライン引数に読み込むファイルを指定してください...(_ _)\n");
    return 1;
  }

  input_file  = argv[1];
  output_file = "../documents/data.json";

  //ファイルを開く
  if( NULL == (input = fopen( input_file, "r")) ){
    printf("ζ*'ヮ')ζ <指定されたファイルが存在しないかなーって\n");
    return -1;
  }
  output = fopen( output_file, "w");

  fprintf( output, "[\n");

  while (fgets(s, 256, input) != NULL) {

		if( s[0] != '\n' ){
      for( unsigned char i=0; i<128; i++ ){
        if( s[i] == '\n' ){
          s[i] = '\0';
          break;
        }
      }
      if( count == 0 ){
        if( firstFlag ){
          fprintf( output, "\t{\n");
          firstFlag = 0;
        }
        else{
          fprintf( output, "\t,\n\t{\n");
        }
        fprintf( output, "\t\"name\": \"\",\n");
        fprintf( output, "\t\"lat\": %s,\n", s);
        count++;
      }
      else{
        fprintf( output, "\t\"lng\": %s\n", s);
        fprintf( output, "\t}\n");
        count = 0;
      }
    }
	}

  fprintf( output, "]\n");

  fclose( input );
  fclose( output );

  printf("∞のワの <成功ですよ、成功！\n\n");

  return 0;
}

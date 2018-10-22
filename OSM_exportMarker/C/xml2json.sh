#!/bin/bash

#ちょっとめんどくさいけど
#[読み込む.osm.xmlファイル][書き出す.txt]
#結果は ../documents/data.json

if [ $# -eq 2 ]; then
  echo "xml2text..."
  ./xml2text $1 $2

  echo ""
  echo "text2json"
  ./text2json $2
else
  echo "Error..."
  echo "./xml2json.sh [読み込む.osm.xmlファイル] [書き出す.txt]"
  echo ""
  echo "Success :"
  echo "./xml2json.sh *.osm.xml *.txt"
  echo ""
fi

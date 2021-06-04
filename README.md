# OSM_exportMarker

Open Street Map(OSM)のexport機能で取得したxmlファイルから、信号機に関するデータのみを抜き出してjsonに書き出し  
また、信号機の位置をOSMにマーカーで表示する

## 使い方

1. オープンストリートマップから信号機を検索したい地域の *.osm.xml をダウンロードする  
2. ダウンロードした *.osm.xmlを documents直下に置く  
3. C/ に移動  
4. xml2json.shを実行する  
5. documents/*.jsonに緯度経度が書き出される  
6. html/marker.htmlで結果を出力できる  

## 使用ライブラリ

[libxml2](http://xmlsoft.org/index.html)

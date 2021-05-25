# OSM_exportMarker

Open Street Mapのexport機能で取得したxmlファイルから  
信号機に関するデータのみを抜き出してmapに表示する

## 解析

「C」参照

## 表示

「html」参照

## 使い方

オープンストリートマップから信号機を検索したい地域の *.osm.xml をダウンロードする  
documents/ に *.osm.xml を置く  
C/ に移動  
C/xml2json.sh を実行する  
documents/*.txt に緯度経度が書き出される  
★☆★☆完成★☆★☆  

コンパイルする場合はlibxml2をインストールしてください  
html/marker.html でデバッグできます(ローカルな場所にあると実行できない)